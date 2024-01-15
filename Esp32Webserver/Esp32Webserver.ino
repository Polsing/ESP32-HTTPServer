#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include "DHT.h"

// Define DHT sensor pin and type
#define DHTPIN 2    
#define DHTTYPE DHT22

// Define WiFi credentials
#define WIFI_SSID "ps@2.4GHz"
#define WIFI_PASSWORD "apl-ps02"

// Define WiFi channel (optional)
#define WIFI_CHANNEL 6

// Create DHT sensor instance
DHT dht(DHTPIN, DHTTYPE);

// Create a WebServer instance on port 80
WebServer server(80);

// Variables to store sensor readings
float Humidity = 0;
float Temperature = 0;
float Fahrenheit = 0;

// Function to handle HTTP GET request for sensor values
void handleValueRequest() {
  // Set CORS header to allow access from any origin
  server.sendHeader("Access-Control-Allow-Origin", "*");

  // Set content type to JSON
  server.sendHeader("Content-Type", "application/json");

  // Create a JSON document to hold sensor data
  DynamicJsonDocument jsonDoc(200);
  jsonDoc["Humidity"] = Humidity;
  jsonDoc["Temperature"] = Temperature;
  jsonDoc["Fahrenheit"] = Fahrenheit;

  // Serialize JSON document to a string
  String jsonResponse;
  serializeJson(jsonDoc, jsonResponse);

  // Send HTTP response with JSON data
  server.send(200, "application/json", jsonResponse);
}

// Function to handle HTTP POST request for LED1 status
void getstatusLED1() {
  // Set CORS header to allow access from any origin
  server.sendHeader("Access-Control-Allow-Origin", "*");

  // Set content type to JSON
  server.sendHeader("Content-Type", "application/json");

  // Create a JSON document to hold response data
  DynamicJsonDocument jsonDoc(200);

  // Get the data parameter from the request
  String receivedData = server.arg("data");

  // Print received data to Serial for debugging
  Serial.print("LED1: ");
  Serial.println(receivedData);

  // Determine LED status based on received data
  if (receivedData == "true")
    jsonDoc["res"] = "on";
  else
    jsonDoc["res"] = "off";

  // Serialize JSON document to a string
  String jsonResponse;
  serializeJson(jsonDoc, jsonResponse);

  // Send HTTP response with JSON data
  server.send(200, "application/json", jsonResponse);
}

// Function to handle HTTP POST request for LED2 status
void getstatusLED2() {
  // Set CORS header to allow access from any origin
  server.sendHeader("Access-Control-Allow-Origin", "*");

  // Set content type to JSON
  server.sendHeader("Content-Type", "application/json");

  // Create a JSON document to hold response data
  DynamicJsonDocument jsonDoc(200);

  // Get the data parameter from the request
  String receivedData = server.arg("data");

  // Print received data to Serial for debugging
  Serial.print("LED2: ");
  Serial.println(receivedData);

  // Determine LED status based on received data
  if (receivedData == "true")
    jsonDoc["res"] = "on";
  else
    jsonDoc["res"] = "off";

  // Serialize JSON document to a string
  String jsonResponse;
  serializeJson(jsonDoc, jsonResponse);

  // Send HTTP response with JSON data
  server.send(200, "application/json", jsonResponse);
}

// Setup function, executed once at the beginning
void setup(void) {
  // Start Serial communication
  Serial.begin(115200);

  // Connect to WiFi using provided credentials
  Serial.print("Connecting to -> ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  // Wait for WiFi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Print WiFi connection details
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Define HTTP routes and associated handler functions
  server.on("/value", HTTP_GET, handleValueRequest);
  server.on("/led1", HTTP_POST, getstatusLED1);
  server.on("/led2", HTTP_POST, getstatusLED2);

  // Start the web server
  server.begin();

  // Initialize DHT sensor
  dht.begin();
}

// Loop function, executed repeatedly
void loop(void) {
  // Handle incoming client requests
  server.handleClient();

  // Read sensor values
  Humidity = dht.readHumidity();
  Temperature = dht.readTemperature();
  Fahrenheit = dht.readTemperature(true);

  // Delay to avoid rapid sensor readings
  delay(500);
}
