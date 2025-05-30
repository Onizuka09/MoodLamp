#include <Arduino.h>
#include <HardwareSerial.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "ui/ui.h"
#include "RTC_module.h"

// Wi-Fi Credentials
#define ssid "TT_23C0"
#define password "i6q4k3b21r"

// Location Parameters
#define latitude String("13.41")
#define longitude String("52.52")
#define timezone String("auto")

// Weather Data Struct
struct WeatherData
{
  String last_update;
  String temperature;
  String humidity;
  int is_day;
  int weather_code;
  String weather_description;
};

WeatherData weather;

const char degree_symbol[] = "\u00B0C";
#define strip_Pin 26
#define Led_COUNT 60
#define debug Serial
// TFT DEfines

#define LVGL_TICK_PERIOD 20

// Set the screen resolution
static const uint16_t screenWidth = 480;
static const uint16_t screenHeight = 320;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 10];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight);

// RTC
RTC_Module RTC_mod;
#define UPDATE_INTERVAL 10800000 // 3 hours in milliseconds
// const long UPDATE_INTERVAL = 3 * 60 * 60; // 3 hours in seconds
unsigned long lastUpdateTime = 0;             // Store last update time

// Define the UART instance for HM-10
HardwareSerial HM10(2); // Use UART2 (GPIO16 & GPIO17)

// RGB LED strip instance
Adafruit_NeoPixel strip(Led_COUNT, strip_Pin, NEO_GBR + NEO_KHZ800);
// declaring days & Times
char daysOfTheWeek[8][10] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Error"};
char namesOfMonths[13][6] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec", "Error"};
void parseAndSetColor(const String &command);
void set_stripColor(uint8_t red, uint8_t green, uint8_t blue);
void updateWeatherData();
void fetchWeatherData();
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
void updateTime(lv_timer_t *timer);
void get_weather_description(int code);
void updateBrightness(uint8_t brightness);
void setup()
{
  // Start debug serial monitor
  debug.begin(115200);

  RTC_mod.RTC_Module_init();
  // Start HM-10 serial communication
  HM10.begin(9600, SERIAL_8N1, 16, 17); // HM-10: 9600 baud, RX, TX
  delay(1000);

  debug.println("BLE RGB LED Controller");
  debug.println("Waiting for commands in the format 'R : G : B'...");

  // Initialize the LED strip
  strip.begin();
  strip.setBrightness(50);
  strip.show();
  // tft begin
  lv_init();

  tft.begin();
  tft.setRotation(1);

  lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * 10);

  // Initialize the display.
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  ui_init();
  delay(1000);

  lv_timer_t *timer = lv_timer_create(updateTime, 1000, NULL); // Update sensor value after 2 second
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  char tmp[50];
  sprintf(tmp, "Conneting to WIFI SSID %s ...", ssid);
  lv_label_set_text(objects.label_info_val, tmp);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  // delay(100);
  // Serial.println("Connected!");
  char tmp2[50];

  sprintf(tmp2, "Conneted to WIFI SSID %s", ssid);
  lv_label_set_text(objects.label_info_val, tmp2);

  Serial.println("Setup done");
}
long lastT = 0;
void loop()
{
  lv_timer_handler();
  updateWeatherData();
  if (HM10.available())
  {
    String command = HM10.readStringUntil('\n');
    command.trim();
    parseAndSetColor(command);
  }
  delay(5);
}
void updateBrightness(uint8_t brightness)
{
  strip.setBrightness(brightness);
  strip.show();
}
void fetchWeatherData()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Not connected to Wi-Fi");
    return;
  }

  HTTPClient http;
  String url = "https://api.open-meteo.com/v1/forecast?latitude=36.82&longitude=10.12&current=temperature_2m,relative_humidity_2m&timezone=auto";
  http.begin(url);
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK)
  {
    StaticJsonDocument<512> doc;
    String payload = http.getString();
    DeserializationError error = deserializeJson(doc, payload);

    if (!error)
    {
      const char *datetime = doc["current"]["time"];
      weather.temperature = doc["current"]["temperature_2m"].as<String>();
      weather.humidity = doc["current"]["relative_humidity_2m"].as<String>();
      weather.is_day = 0;
      weather.weather_code = 0;
      get_weather_description(weather.weather_code);

      // Extract date and time
      String datetime_str = String(datetime);
      int splitIndex = datetime_str.indexOf('T');
      weather.last_update = datetime_str.substring(splitIndex + 1, splitIndex + 9);

      // Print Data
      Serial.println("Temperature: " + weather.temperature + degree_symbol);
      Serial.println("Humidity: " + weather.humidity + "%");
      Serial.println("Daytime: " + String(weather.is_day));
      Serial.println("Weather Code: " + String(weather.weather_code));
      Serial.println("Weather: " + weather.weather_description);
    }
    else
    {
      Serial.print("JSON parsing failed: ");
      Serial.println(error.c_str());
    }
  }
  else
  {
    Serial.printf("GET request failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}

void set_stripColor(uint8_t red, uint8_t green, uint8_t blue)
{
  uint32_t color = strip.Color(blue, green, red);
  strip.fill(color, 0, Led_COUNT - 1);
  strip.show();
}

void parseAndSetColor(const String &command)
{
  debug.println(command); // Print received command for debugging

  if (command.startsWith("RGB"))
  {
    int r = 0, g = 0, b = 0;
    
    // Corrected sscanf format with "RGB :" prefix
    if (sscanf(command.c_str(), "RGB :%d :%d :%d", &r, &g, &b) == 3)
    {
      if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255)
      {
        debug.print("Parsed RGB values: ");
        debug.print(r);
        debug.print(", ");
        debug.print(g);
        debug.print(", ");
        debug.println(b);

        set_stripColor(r, g, b);
        debug.println("LED color set successfully!");
      }
      else
      {
        debug.println("Error: RGB values out of range!");
      }
    }
    else
    {
      debug.println("Error: Failed to parse RGB command!");
    }
  }
  else if (command.startsWith("BRT"))
  {
    float bright = 0;
    
    // Corrected sscanf format with "BRT :" prefix
    if (sscanf(command.c_str(), "BRT :%f", &bright) == 1)
    {
      int bright_int = (int)bright; // Convert float to integer if needed
      
      if (bright_int >= 0 && bright_int <= 255)  // Adjust range as needed
      {
        debug.print("Parsed Brightness value: ");
        debug.println(bright_int);
        updateBrightness((uint8_t)bright_int);
      }
      else
      {
        debug.println("Error: Brightness value out of range!");
      }
    }
    else
    {
      debug.println("Error: Failed to parse Brightness command!");
    }
  }
  else
  {
    debug.println("Error: UNKNOWN command!");
  }
}

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)&color_p->full, w * h, true);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}

void updateTime(lv_timer_t *timer)
{
  RtcDateTime dt = RTC_mod.RTC_getDateTime();
  char Time[18];
  char days[30];

  // Format time as HH:MM:SS with leading zeros
  sprintf(Time, "%02d:%02d:%02d", dt.Hour(), dt.Minute(), dt.Second());

  // Format day as "Monday, January - 2024"
  sprintf(days, "%s, %s - %d", daysOfTheWeek[dt.DayOfWeek()], namesOfMonths[dt.Month() - 1], dt.Year());

  lv_label_set_text(objects.label_days_val, days);
  lv_label_set_text(objects.label_time_val, Time);
}

void get_weather_description(int code)
{
  if (code == 0)
  {
    weather.weather_description = (weather.is_day == 1) ? "SUNNY" : "SUNNY";
  }
  else if (code == 1 || code == 2)
  {
    weather.weather_description = "PARTLY CLOUDY";
  }
  else if (code == 3)
  {
    weather.weather_description = "OVERCAST";
  }
  else if (code == 45 || code == 48)
  {
    weather.weather_description = "FOG";
  }
  else if (code == 51 || code == 53 || code == 55)
  {
    weather.weather_description = "DRIZZLE";
  }
  else if (code == 56 || code == 57)
  {
    weather.weather_description = "FREEZING DRIZZLE";
  }
  else if (code == 61 || code == 63 || code == 65)
  {
    weather.weather_description = "RAIN";
  }
  else if (code == 66 || code == 67)
  {
    weather.weather_description = "FREEZING RAIN";
  }
  else if (code == 71 || code == 73 || code == 75)
  {
    weather.weather_description = "SNOW FALL";
  }
  else if (code == 77)
  {
    weather.weather_description = "SNOW GRAINS";
  }
  else if (code == 80 || code == 81 || code == 82)
  {
    weather.weather_description = "RAIN SHOWERS";
  }
  else if (code == 85 || code == 86)
  {
    weather.weather_description = "SNOW SHOWERS";
  }
  else if (code == 95)
  {
    weather.weather_description = "THUNDERSTORM";
  }
  else if (code == 96 || code == 99)
  {
    weather.weather_description = "THUNDERSTORM WITH HAIL";
  }
  else
  {
    weather.weather_description = "UNKNOWN WEATHER CODE";
  }

  Serial.println(weather.weather_description);
}

void updateWeatherData()
{
  // unsigned long currentTime =

  unsigned long currentTime = millis(); // Get current time

  if (currentTime - lastUpdateTime >= UPDATE_INTERVAL)
  {
    lastUpdateTime = currentTime; // Update the last update time

    fetchWeatherData();
    get_weather_description(weather.weather_code);

    lv_label_set_text(objects.label_temp_val, weather.temperature.c_str());
    lv_label_set_text(objects.label_hum_val, weather.humidity.c_str());
    lv_label_set_text(objects.label_weather_val, weather.weather_description.c_str());

    // debug.println("Weather data updated!");
  }
}