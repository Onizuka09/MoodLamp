#include <lvgl.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include "time.h"
#include "RTClib.h"
#include "ui.h"
#include "images.h"
//----------------------------------------

// Defines the screen resolution.
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

// Defines the time interval for updating weather data.
#define INTERVAL_UPDATING_WEATHER_DATA 300 //--> 300 seconds (5 minutes). Weather data is updated every 5 minutes.

// LVGL draw into this buffer, 1/10 screen size usually works well. The size is in bytes.
#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint8_t *draw_buf;

// Used to track the tick timer.
uint32_t lastTick = 0;

//----------------------------------------SSID and PASSWORD of your WiFi network.
const char* ssid = "YOUR_WIFI_SSID";  //--> Your wifi name
const char* password = "YOUR_WIFI_PASSWORD"; //--> Your wifi password
//----------------------------------------

//----------------------------------------Your OpenWeatherMap API.
// Example:
// String openWeatherMapApiKey = "bd939aa3d23ff33d3c8f5dd1dd435";
String openWeatherMapApiKey = "REPLACE_WITH_YOUR_OPEN_WEATHER_MAP_API_KEY";

// Replace with your country code and city.
// Find city and country code here : https://openweathermap.org/
String city = "REPLACE_WITH_YOUR_CITY_NAME";
String countryCode = "REPLACE_WITH_YOUR_COUNTRY_ID_CODE";
//----------------------------------------

//----------------------------------------NTP Server and Time Settings.
// The DS3231 RTC module is not always accurate, so every time the ESP32 is turned on or rebooted,
// the time and date on the DS3231 RTC module will be set based on the time from the NTP Server.
// Please adjust the settings below to suit your area.

// Source : https://lastminuteengineers.com/esp32-ntp-server-date-time-tutorial/

const char* ntpServer = "pool.ntp.org";

// Example setting for "gmtOffset_sec".
// - For UTC -5.00 : -5 * 60 * 60 = -18000
// - For UTC +1.00 : 1 * 60 * 60 = 3600
// - For UTC +0.00 : 0 * 60 * 60 = 0
// Check the UTC list here: https://en.wikipedia.org/wiki/List_of_UTC_offsets
// Where I live uses UTC+07:00, so : 7 * 60 * 60 = 25200
// or 3600 * 7 = 25200
const long  gmtOffset_sec = 3600 * 7;

// Set it to 3600 if your country observes Daylight saving time. Otherwise, set it to 0.
// https://en.wikipedia.org/wiki/Daylight_saving_time
const int   daylightOffset_sec = 0;
//----------------------------------------

//----------------------------------------Variable for millis/timer.
unsigned long prevMill = 0;
const long intervalMill = 1000;
//----------------------------------------

char daysOfTheWeek[8][10] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Error"};
char namesOfMonths[13][6] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec", "Error"};
int d_year;
byte d_month, d_day, daysOfTheWeek_Val;
byte t_hour, t_minute, t_second;

int cnt = 0;

String str_Weather_Main, str_Weather_Icon, str_Weather_Description;
String str_Temperature, str_Feels_Like, str_Temp_Max, str_Temp_Min;
String str_Humidity, str_Wind_Speed, str_Pressure, str_Visibility;

char ca_Info_Status[50];

String jsonBuffer;

// Initialize RTC_DS3231 as "rtc".
RTC_DS3231 rtc;



//________________________________________________________________________________ log_print()
// If logging is enabled, it will inform the user about what is happening in the library.
void log_print(lv_log_level_t level, const char * buf) {
  LV_UNUSED(level);
  Serial.println(buf);
  Serial.flush();
}
//________________________________________________________________________________ 



//________________________________________________________________________________ set_initial_display_of_labels()
void set_initial_display_of_labels() {
  lv_label_set_text(objects.label_city, city.c_str());
  lv_label_set_text(objects.label_date, "--, ----");
  lv_label_set_text(objects.label_time, "--:--:--");
  lv_label_set_text(objects.label_weather_main, "--");
  lv_label_set_text(objects.label_weather_description, "--");
  lv_label_set_text(objects.label_temperature, "--.--°C");
  lv_label_set_text(objects.label_feels_like, "--.-- °C");
  lv_label_set_text(objects.label_temp_max, "--.-- °C");
  lv_label_set_text(objects.label_temp_min, "--.-- °C");
  lv_label_set_text(objects.label_humidity, "--%");
  lv_label_set_text(objects.label_wind, "-- km/h");
  lv_label_set_text(objects.label_pressure, "-- hPa");
  lv_label_set_text(objects.label_visibility, "-- km");
  lv_label_set_text(objects.label_info, "--");

  update_UI();
}
//________________________________________________________________________________ 



//________________________________________________________________________________ connecting_To_WiFi()
void connecting_To_WiFi() {
  lv_label_set_text(objects.label_info, "Connecting to WiFi...");
  update_UI();

  //----------------------------------------Set Wifi to STA mode.
  Serial.println();
  Serial.println("-------------WIFI mode");
  Serial.println("WIFI mode : STA");
  WiFi.mode(WIFI_STA);
  Serial.println("-------------");
  delay(1000);
  //---------------------------------------- 

  //----------------------------------------Connect to Wi-Fi (STA).
  Serial.println();
  Serial.println("-------------Connection");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  //:::::::::::::::::: The process of connecting ESP32 with WiFi Hotspot / WiFi Router.
  // The process timeout of connecting ESP32 with WiFi Hotspot / WiFi Router is 20 seconds.
  // If within 20 seconds the ESP32 has not been successfully connected to WiFi, the ESP32 will restart.
  // I made this condition because on my ESP32, there are times when it seems like it can't connect to WiFi, so it needs to be restarted to be able to connect to WiFi.
  
  int connecting_process_timed_out = 20; //--> 20 = 20 seconds.
  connecting_process_timed_out = connecting_process_timed_out * 2;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    if(connecting_process_timed_out > 0) connecting_process_timed_out--;
    if(connecting_process_timed_out == 0) {
      Serial.println();
      Serial.println("Failed to connect to WiFi. The ESP32 will be restarted.");
      Serial.println("-------------");
      
      lv_label_set_text(objects.label_info, "Failed to connect to WiFi.");
      update_UI();
      delay(2000);

      lv_label_set_text(objects.label_info, "The ESP32 will be restarted.");
      update_UI();
      delay(2000);
      
      ESP.restart();
    }
  }

  lv_label_set_text(objects.label_info, "Successfully connected to WiFi.");
  update_UI();
  
  Serial.println();
  Serial.println("WiFi connected.");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.println("-------------");
  //:::::::::::::::::: 
  delay(1000);

  lv_label_set_text(objects.label_info, "");
  update_UI();
  //---------------------------------------- 
}
//________________________________________________________________________________ 



//________________________________________________________________________________ get_TimeDate_from_NTP_server()
void get_TimeDate_from_NTP_server() {
  lv_label_set_text(objects.label_info, "Get Time and Date from NTP server...");
  update_UI();

  Serial.println();
  Serial.println("-------------");
  Serial.println("Get Time and Date from NTP server.");
  Serial.println("Please wait...");
  delay(500);

  if(WiFi.status()== WL_CONNECTED){
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  
    struct tm timeinfo;
  
    if (!getLocalTime(&timeinfo)) {
      lv_label_set_text(objects.label_info, "Failed to obtain time.");
      update_UI();
    
      Serial.println();
      Serial.println("Failed to obtain time.");
      Serial.println("-------------");
      delay(1500);
      return;
    }
  
    t_hour   = timeinfo.tm_hour;
    t_minute = timeinfo.tm_min;
    t_second = timeinfo.tm_sec;
  
    d_day   = timeinfo.tm_mday;
    d_month = timeinfo.tm_mon+1;
    d_year  = timeinfo.tm_year+1900;
  
    rtc.adjust(DateTime(d_year, d_month, d_day, t_hour, t_minute, t_second));
  
    char TimeDate[40];
    sprintf(TimeDate, "Date : %02d-%02d-%d | Time : %02d:%02d:%02d", d_day, d_month, d_year, t_hour, t_minute, t_second);

    lv_label_set_text(objects.label_info, "Successfully set time from NTP server.");
    update_UI();
  
    Serial.println();
    Serial.println("Successfully set time from NTP server.");
    Serial.println();
    Serial.println(TimeDate);
    Serial.println("-------------");
    delay(1000);

    lv_label_set_text(objects.label_info, "");
    update_UI();
  } else {
    lv_label_set_text(objects.label_info, "FAILED ! WiFi Disconnected.");
    update_UI();

    Serial.println();
    Serial.println("FAILED !");
    Serial.println("WiFi Disconnected");
    Serial.println("-------------");
    delay(1500);
  }
}
//________________________________________________________________________________ 



//________________________________________________________________________________ get_DateTime()
void get_DateTime() {
  DateTime now = rtc.now();

  d_year = now.year();
  d_month = now.month();
  if (d_month > 12 || d_month < 1) d_month = 13;
  d_day = now.day();
  daysOfTheWeek_Val = now.dayOfTheWeek();
  if (daysOfTheWeek_Val > 7 || daysOfTheWeek_Val < 0) daysOfTheWeek_Val = 7;
  t_hour = now.hour();
  t_minute = now.minute();
  t_second = now.second();

  //char full_DateTime[60];
  //sprintf(full_DateTime, "%s | %02d-%02d-%d | Time : %02d:%02d:%02d", daysOfTheWeek[daysOfTheWeek_Val], d_day, d_month, d_year, t_hour, t_minute, t_second);

  //Serial.print("Date : ");
  //Serial.println(full_DateTime);
}
//________________________________________________________________________________ 



//________________________________________________________________________________ update_DateTime()
void update_DateTime() {
  // Call the get_DateTime() subroutine.
  get_DateTime();

  char str_Date[23];
  lv_snprintf(str_Date, sizeof(str_Date), "%s, %02d-%s-%d", daysOfTheWeek[daysOfTheWeek_Val], d_day, namesOfMonths[d_month-1], d_year);
  lv_label_set_text(objects.label_date, str_Date);

  char str_Time[9];
  lv_snprintf(str_Time, sizeof(str_Time), "%02d:%02d:%02d", t_hour, t_minute, t_second);
  lv_label_set_text(objects.label_time, str_Time);
}
//________________________________________________________________________________ 



//________________________________________________________________________________ get_Data_from_OpenWeatherMap()
void get_Data_from_OpenWeatherMap() {
  lv_label_set_text(objects.label_info, "Update weather data...");
  update_UI();
  
  Serial.println();
  Serial.println("-------------");
  Serial.println("Update weather data (Getting Weather Data from OpenWeatherMap).");
  Serial.println("Please wait...");
  delay(500);
  
  // Check WiFi connection status.
  if(WiFi.status()== WL_CONNECTED){
    String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode + "&units=metric&APPID=" + openWeatherMapApiKey;
    
    jsonBuffer = httpGETRequest(serverPath.c_str());
    Serial.println();
    Serial.println("Weather Data in JSON form :");
    Serial.println(jsonBuffer);
    JSONVar myObject = JSON.parse(jsonBuffer);

    // JSON.typeof(jsonVar) can be used to get the type of the var.
    if (JSON.typeof(myObject) == "undefined") {
      strcpy(ca_Info_Status, "(Failed : Parsing input failed !)");
      
      Serial.println("Parsing input failed !");

      lv_label_set_text(objects.label_info, "");
      update_UI();
      return;
    }

    Serial.println();
    Serial.println("Weather Data taken");

    str_Weather_Main = JSON.stringify(myObject["weather"][0]["main"]);
    str_Weather_Main.replace("\"", ""); //--> Removes the Double quotes (") character in the string.
    str_Weather_Icon = JSON.stringify(myObject["weather"][0]["icon"]);
    str_Weather_Icon.replace("\"", "");
    str_Weather_Description = JSON.stringify(myObject["weather"][0]["description"]);
    str_Weather_Description.replace("\"", "");
    
    str_Temperature = JSON.stringify(myObject["main"]["temp"]);
    str_Feels_Like = JSON.stringify(myObject["main"]["feels_like"]);
    str_Temp_Max = JSON.stringify(myObject["main"]["temp_max"]);
    str_Temp_Min = JSON.stringify(myObject["main"]["temp_min"]);
    
    str_Humidity = JSON.stringify(myObject["main"]["humidity"]);
    str_Wind_Speed = JSON.stringify(myObject["wind"]["speed"]);
    str_Pressure = JSON.stringify(myObject["main"]["pressure"]);
    str_Visibility = JSON.stringify(myObject["visibility"]);

    Serial.println();
    Serial.print("Weather Main : ");Serial.println(str_Weather_Main);
    Serial.print("Weather Icon : ");Serial.println(str_Weather_Icon);
    Serial.print("Weather Description : ");Serial.println(str_Weather_Description);
    
    Serial.print("Temperature : ");Serial.print(str_Temperature);Serial.println(" °C");
    Serial.print("Feels Like : ");Serial.print(str_Feels_Like);Serial.println(" °C");
    Serial.print("Temp Max : ");Serial.print(str_Temp_Max);Serial.println(" °C");
    Serial.print("Temp Min : ");Serial.print(str_Temp_Min);Serial.println(" °C");
    
    Serial.print("Humidity : ");Serial.print(str_Humidity);Serial.println(" %");
    Serial.print("Wind Speed : ");Serial.print(str_Wind_Speed);Serial.println(" m/s");
    Serial.print("Pressure : ");Serial.print(str_Pressure);Serial.println(" hPa");
    Serial.print("Visibility : ");Serial.print(str_Visibility);Serial.println(" m");

    Serial.println("-------------");
    Serial.println();

    strcpy(ca_Info_Status, "(Succeed)");

    lv_label_set_text(objects.label_info, "");
    update_UI();
    delay(1000);
  }
  else {
    strcpy(ca_Info_Status, "(Failed : WiFi Disconnected !)");
    
    Serial.println("WiFi Disconnected");
    Serial.println("-------------");
    Serial.println();
  }
}
//________________________________________________________________________________



//________________________________________________________________________________ httpGETRequest()
String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path.
  http.begin(client, serverName);
  
  // Send HTTP POST request.
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  
  // Free resources.
  http.end();

  return payload;
}
//________________________________________________________________________________ 



//________________________________________________________________________________ update_Weather_Data()
void update_Weather_Data() {
  // Call the get_DateTime() subroutine.
  get_DateTime();

  char ca_Time[10];
  sprintf(ca_Time, "%02d:%02d:%02d", t_hour, t_minute, t_second);
  
  // Call the get_Data_from_OpenWeatherMap() subroutine.
  get_Data_from_OpenWeatherMap();

  // Displays weather conditions.
  lv_label_set_text(objects.label_weather_main, str_Weather_Main.c_str());

  //----------------------------------------Displays weather icon images.
  // For a list of icon variable names, see the "images.c" file.
  if (str_Weather_Icon == "01d") {
    lv_img_set_src(objects.image_icon_weather, &img_icon_01d_72p);
  } else if (str_Weather_Icon == "01n") {
    lv_img_set_src(objects.image_icon_weather, &img_icon_01n_72p);
  } else if (str_Weather_Icon == "02d") {
    lv_img_set_src(objects.image_icon_weather, &img_icon_02d_72p);
  } else if (str_Weather_Icon == "02n") {
    lv_img_set_src(objects.image_icon_weather, &img_icon_02n_72p);
  } else if (str_Weather_Icon == "03d" || str_Weather_Icon == "03n") {
    lv_img_set_src(objects.image_icon_weather, &img_icon_03d_03n_72p);
  } else if (str_Weather_Icon == "04d" || str_Weather_Icon == "04n") {
    lv_img_set_src(objects.image_icon_weather, &img_icon_04d_04n_72p);
  } else if (str_Weather_Icon == "09d" || str_Weather_Icon == "09n") {
    lv_img_set_src(objects.image_icon_weather, &img_icon_09d_09n_72p);
  } else if (str_Weather_Icon == "10d") {
    lv_img_set_src(objects.image_icon_weather, &img_icon_10d_72p);
  } else if (str_Weather_Icon == "10n") {
    lv_img_set_src(objects.image_icon_weather, &img_icon_10n_72p);
  } else if (str_Weather_Icon == "11d" || str_Weather_Icon == "11n") {
    lv_img_set_src(objects.image_icon_weather, &img_icon_11d_11n_72p);
  } else if (str_Weather_Icon == "13d" || str_Weather_Icon == "13n") {
    lv_img_set_src(objects.image_icon_weather, &img_icon_13d_13n_72p);
  } else if (str_Weather_Icon == "50d" || str_Weather_Icon == "50n") {
    lv_img_set_src(objects.image_icon_weather, &img_icon_50d_50n_72p);
  } 
  //----------------------------------------

  // Displays a description of weather conditions.
  lv_label_set_text(objects.label_weather_description, str_Weather_Description.c_str());

  //----------------------------------------Displays temperature values ​​and other temperature data.
  float f_Temp = str_Temperature.toFloat();
  char ca_Temp[10];
  lv_snprintf(ca_Temp, sizeof(ca_Temp), "%.1f°C", f_Temp);
  lv_label_set_text(objects.label_temperature, ca_Temp);

  float f_Feels_Like = str_Feels_Like.toFloat();
  char ca_Feels_Like[11];
  lv_snprintf(ca_Feels_Like, sizeof(ca_Feels_Like), "%.1f °C", f_Feels_Like);
  lv_label_set_text(objects.label_feels_like, ca_Feels_Like);

  float f_Temp_Max = str_Temp_Max.toFloat();
  char ca_Temp_Max[11];
  lv_snprintf(ca_Temp_Max, sizeof(ca_Temp_Max), "%.1f °C", f_Temp_Max);
  lv_label_set_text(objects.label_temp_max, ca_Temp_Max);

  float f_Temp_Min = str_Temp_Min.toFloat();
  char ca_Temp_Min[11];
  lv_snprintf(ca_Temp_Min, sizeof(ca_Temp_Min), "%.1f °C", f_Temp_Min);
  lv_label_set_text(objects.label_temp_min, ca_Temp_Min);
  //----------------------------------------

  // Displays humidity value.
  str_Humidity += " %";
  lv_label_set_text(objects.label_humidity, str_Humidity.c_str());

  // Displays wind speed values.
  // By default, wind speed values ​​from OpenWeatherMap are in meters per second (m/s).
  // "float f_Wind_Speed ​​= str_Wind_Speed.toFloat() * 3.6;" is to convert from m/s to km/h.
  float f_Wind_Speed = str_Wind_Speed.toFloat() * 3.6;
  char ca_Wind_Speed[12];
  lv_snprintf(ca_Wind_Speed, sizeof(ca_Wind_Speed), "%.1f km/h", f_Wind_Speed);
  lv_label_set_text(objects.label_wind, ca_Wind_Speed);

  // Displays pressure value (atmospheric pressure / air pressure).
  str_Pressure += " hPa";
  lv_label_set_text(objects.label_pressure, str_Pressure.c_str());

  // Displays visibility values.
  // By default, visibility values ​​from OpenWeatherMap are in meters.
  // "float f_Visibility = str_Visibility.toFloat() / 1000;" is to convert from meters to kilometers.
  float f_Visibility = str_Visibility.toFloat() / 1000;
  char ca_Visibility[9];
  lv_snprintf(ca_Visibility, sizeof(ca_Visibility), "%.1f km", f_Visibility);
  lv_label_set_text(objects.label_visibility, ca_Visibility);

  // Displays other information.
  char ca_Info[70];
  lv_snprintf(ca_Info, sizeof(ca_Info), "Last data update: %s %s", ca_Time, ca_Info_Status);
  lv_label_set_text(objects.label_info, ca_Info);
}
//________________________________________________________________________________ 



//________________________________________________________________________________ update_UI()
void update_UI() {
  lv_tick_inc(millis() - lastTick); //--> Update the tick timer. Tick is new for LVGL 9.
  lastTick = millis();
  lv_timer_handler(); //--> Update the UI.
}
//________________________________________________________________________________ 



//________________________________________________________________________________ VOID SETUP()
void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  Serial.println();
  delay(3000);

  //----------------------------------------Starting and setting up the DS3231 RTC module.
  Serial.println();
  Serial.println("------------");
  Serial.println("Starting the DS3231 RTC module.");
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  Serial.println("Successfully started the DS3231 RTC module.");
  Serial.println("------------");
  //----------------------------------------

  Serial.println();
  Serial.println("------------");
  Serial.println("ESP32 + TFT LCD Touchscreen ILI9341 + LVGL + EEZ Studio + OpenWeatherMap");
  Serial.println("Simple Weather Map");
  Serial.println("------------");
  delay(500);

  String LVGL_Arduino = String("LVGL Library Version: ") + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
  Serial.println();
  Serial.println("------------");
  Serial.println(LVGL_Arduino);
  Serial.println("------------");
  delay(500);

  //----------------------------------------LVGL setup.
  Serial.println();
  Serial.println("------------");
  Serial.println("Start LVGL Setup.");
  delay(500);

  // Start LVGL.
  lv_init();
  
  // Register print function for debugging.
  lv_log_register_print_cb(log_print);

  // Create a display object.
  lv_display_t * disp;
  
  // Initialize the TFT display using the TFT_eSPI library.
  draw_buf = new uint8_t[DRAW_BUF_SIZE];
  disp = lv_tft_espi_create(SCREEN_HEIGHT, SCREEN_WIDTH, draw_buf, DRAW_BUF_SIZE);
  // If the display on the TFT LCD has problems, try the line of code below:
  //disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, DRAW_BUF_SIZE);
  lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_90);

  Serial.println();
  Serial.println("LVGL Setup Completed.");
  Serial.println("------------");
  delay(500);
  //---------------------------------------- 

  // Integrate EEZ Studio GUI.
  ui_init();

  // Call the set_initial_display_of_labels() subroutine.
  set_initial_display_of_labels();
  delay(1000);

  // Call the connecting_To_WiFi() subroutine.
  connecting_To_WiFi();
  delay(1000);

  // Call the get_TimeDate_from_NTP_server() subroutine.
  get_TimeDate_from_NTP_server();
  delay(1000);

  // Call the update_Weather_Data() subroutine.
  update_Weather_Data();
  delay(1000);
}
//________________________________________________________________________________ 



//________________________________________________________________________________ VOID LOOP()
void loop() {
  // put your main code here, to run repeatedly:

  //----------------------------------------Timer/Millis to update time and date.
  // This Timer/Millis also functions to update weather data.
  unsigned long currentMill = millis();
  if (currentMill - prevMill >= intervalMill) {
    prevMill = currentMill;

    // Call the update_DateTime() subroutine.
    update_DateTime();

    cnt++;
    if (cnt > INTERVAL_UPDATING_WEATHER_DATA) {
      cnt = 0;
      
      // Call the update_Weather_Data() subroutine.
      update_Weather_Data();
    }
  }
  //---------------------------------------- 
  
  update_UI();

  delay(1);
}