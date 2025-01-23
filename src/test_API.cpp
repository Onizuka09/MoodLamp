#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// WiFi credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// OpenWeatherMap API
const String apiKey = "YOUR_API_KEY";
const String city = "YOUR_CITY";
const String countryCode = "YOUR_COUNTRY_CODE";
const String units = "metric";  // Use "imperial" for Fahrenheit

String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode + "&units=" + units + "&appid=" + apiKey;

unsigned long lastTime = 0;
unsigned long timerDelay = 10000;  // Update every 10 seconds

void setup() {
  Serial.begin(115200);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    if(WiFi.status() == WL_CONNECTED){
      getWeatherData();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

void getWeatherData() {
  HTTPClient http;
  http.begin(serverPath.c_str());
  
  int httpResponseCode = http.GET();
  
  if (httpResponseCode == 200) {
    String payload = http.getString();
    
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);

    // Parse and print temperature and humidity
    float temp = doc["main"]["temp"];
    float humidity = doc["main"]["humidity"];

    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print("°C, Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}