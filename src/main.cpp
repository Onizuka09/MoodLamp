#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>

const char *ssid = "TOPNET_84D0";
const char *psswd = "emjsr5u0ui";
bool is_connected = false ;  

#define strip_Pin D3
#define Led_COUNT 60
#define hostname "esp_moodLamp"
#define relay_Pin D0
#define debug Serial
#define debug_led 2

ESP8266WebServer server(80);
StaticJsonDocument<200> jbuf;
Adafruit_NeoPixel strip(Led_COUNT, strip_Pin, NEO_GBR + NEO_KHZ800);


void handle_stripBrightness (){
  String data = server.arg("plain");
  DeserializationError error = deserializeJson(jbuf, data);

  // Test if parsing succeeds.
  if (error)
  {
    debug.print(F("deserializeJson() failed: "));
    debug.println(error.f_str());
    server.send(404, "text/plain", "Not a json string");
    return;
  }
  uint8_t brightness = jbuf["bright"];


  debug.println(brightness);
  strip.setBrightness(brightness);
  strip.show();
  server.send(200, "text/plain", "strip brightness set");
}

void set_stripColor(uint8_t red,uint8_t green,uint8_t blue  ){
  uint32_t color = strip.Color(blue, green, red);
  strip.fill(color, 0, Led_COUNT - 1);
  strip.show(); 
}

void handle_set_stripColor ()
{

  String data = server.arg("plain");
  DeserializationError error = deserializeJson(jbuf, data);

  // Test if parsing succeeds.
  if (error)
  {
    debug.print(F("deserializeJson() failed: "));
    debug.println(error.f_str());
    server.send(404,"text/plain","Not a json string");
    return;
  }
  uint8_t red = jbuf["r"];
  uint8_t green = jbuf["g"];
  uint8_t blue = jbuf["b"];

  debug.println(red);
  debug.println(green);
  debug.println(blue);
  set_stripColor(red, green, blue);
  server.send(200,"text/plain","strip color set");
}
void handle_ON (){
  if (is_connected){
  set_stripColor(127,127,127);
  server.send(200, "text/plain", "led turned ON");
  }
  else
  server.send(404, "text/plain", "you are not connected");
}
void handle_OFF()
{
  if (is_connected){
  set_stripColor(0,0,0);
  server.send(200, "text/plain", "led turned off");
  }
  else
  server.send(404, "text/plain", "you are not connected");
}
void Handle_connect()
{
  server.send(200, "text/plain", "connected to  esp8266");
  digitalWrite(relay_Pin, HIGH);
  is_connected = true;
}

void handle_disconnect()
{
  if (is_connected){
  is_connected = false ;
  digitalWrite(relay_Pin, LOW);
  server.send(200, "text/plain", "disconnected from  esp8266");
  }
  else {
  server.send(404, "text/plain", "you are not connected");
  }
}
void handle_NotFound()
{
  server.send(404, "text/plain", "ERROR: unknown path ");
} 
void setup()
{
  // put your setup code here, to run once:
  debug.begin(115200);
  pinMode(debug_led, OUTPUT);
  pinMode(relay_Pin, OUTPUT);
  digitalWrite(debug_led, 0); // HIGH

  WiFi.begin(ssid, psswd);
  while (WiFi.status() != WL_CONNECTED)
  {
  digitalWrite(debug_led, 0); // HIGH
  delay(250);
  digitalWrite(debug_led, 1); // HIGH
  delay(250);
  debug.print(".");
  }
  
  debug.println("");
  debug.print("connected to ");
  debug.println(ssid);
  debug.print("IP adress is ");
  debug.println(WiFi.localIP());

  if (MDNS.begin(hostname)){
    debug.println( "mDNS responder started !!");
    MDNS.addService("http", "tcp", 80);
    digitalWrite(debug_led, 0); // HIGH
  }
  else {
    debug.println("Error Setting up mDNS responder");
    digitalWrite(debug_led, 1); // LOW
    return ; 
  }
  server.on("/connect", Handle_connect);
  server.on("/on", handle_ON);
  server.on("/set_stripColor", handle_set_stripColor);

  server.on("/off", handle_OFF);
  server.on("/disconnect", handle_disconnect);
  server.on("/set_stripBrightness", handle_stripBrightness);

  server.onNotFound(handle_NotFound);

  // server.on("/off", []()
  //           {
  // debug.println("Off");
  // digitalWrite(2,1);
  // server.send(200); });

  server.begin();
  strip.begin();
  strip.setBrightness(50);
  strip.show();
  // digitalWrite(debug_led, 1); // low
  digitalWrite(relay_Pin, 0);
}

void loop()
{
    // digitalWrite(debug_led, 1); // low
  MDNS.update();

  // put your main code here, to run repeatedly:
  server.handleClient();
}