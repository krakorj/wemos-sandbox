/*
 * ESP8266 NodeMCU AJAX Demo
 * Updates and Gets data from webpage without page refresh
 * https://circuits4you.com
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "DHT.h"

#include "index.h" // Our HTML webpage contents with javascripts

// HW setup
#define LED LED_BUILTIN //On board LED
#define DHTPIN D4     // DTH pin
#define DHTTYPE DHT11   // DHT type

// DHT 
DHT dht(DHTPIN, DHTTYPE);

// Server setup
//SSID and Password of your WiFi router
const char* ssid = "RouterName";
const char* password = "Password";
ESP8266WebServer server(80); //Server on port 80

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 //Read HTML contents and send as web page
 server.send_P(200, "text/html", MAIN_page, sizeof(MAIN_page));
}

void handleADC() {
 int a = analogRead(A0);
 String adcValue = String(a);
 
 server.send(200, "text/plane", adcValue); //Send ADC value only to client ajax request
}

void handleDHT() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) 
  {
    Serial.println("Failed to read from DHT sensor!");
    server.send(422, "text/plane", "Failed to read from DHT sensor!");
  } 
 
  String json = "{\"temp\":\"" + String(t) + "\", \"hum\":\"" + String(h) + "\"}";
  Serial.println(json);
 
  server.send(200, "text/plane", json); //Send DTH value only to client ajax request
}

void handleLED() {
 String ledState = "OFF";
 String t_state = server.arg("LEDstate"); //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);
 Serial.println(t_state);
 if(t_state == "1")
 {
   digitalWrite(LED, LOW); //LED ON
   ledState = "ON"; //Feedback parameter
 }
 else
 {
   digitalWrite(LED, HIGH); //LED OFF
   ledState = "OFF"; //Feedback parameter  
 }
 
 server.send(200, "text/plane", ledState); //Send web page
}

//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  // Serial port
  Serial.begin(115200);
  
  // Wifi setup
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("Wifi setup");

  //Onboard LED port Direction output
  pinMode(LED, OUTPUT);
  Serial.println("LED setup");

  // DHT setup
  dht.begin();
  Serial.println("DHT setup");
  
  // Wifi go
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/setLED", handleLED);
  server.on("/readADC", handleADC);
  server.on("/readDHT", handleDHT);

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient();          //Handle client requests
}
 
