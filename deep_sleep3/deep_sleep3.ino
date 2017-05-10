#include <ESP8266WiFi.h>
#include "DHT.h"


// Uncomment one of the lines below for whatever DHT sensor type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
// Replace with your network details
const char* ssid = "USERSPOTS5";
const char* password = "etkilab7766";


// ThingSpeak Settings
const int channelID = 268195;
String writeAPIKey = "B8CU10QEHPCWQIXC"; // write API key for your ThingSpeak Channel
const char* server = "api.thingspeak.com";
const int postingInterval = 2 * 1000; // post data every 20 seconds

// Web Server on port 80
 WiFiClient client ;

// DHT Sensor
const int DHTPin = 4;
const int DHTen = 12;
// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);

// Temporary variables
static char celsiusTemp[7];
static char humidityTemp[7];

// only runs once on boot
void setup() {
  // Initializing serial port for debugging purposes
  Serial.begin(115200);

  // Connecting to WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  pinMode(DHTen, OUTPUT);
 digitalWrite(DHTen, LOW);
  dht.begin();
//gpio.mode(DHTen,gpio.OUTPUT)
}

// runs over and over again
void loop() {
   Serial.println("gunaydin");
  // Listenning for new clients
  
   
      digitalWrite(DHTen,HIGH);
        delay(1000);
         Serial.println("Dht aktive");
     
     // gpio.write(DHTen,gpio.HIGH)
      for (int i=1; i <= 3; i++){
     Serial.println(i);
      delay(1000);
   } 
   


  
  if (client.connect(server, 80)) {
    Serial.println("New client");
    // bolean to locate when the http request ends

            //sensor readings
             float h = dht.readHumidity();
            // Read temperature as Celsius (the default)
            float t = dht.readTemperature();
             if (isnan(h) || isnan(t) ) {
              Serial.println("Failed to read from DHT sensor!");
              strcpy(celsiusTemp,"Failed");
              strcpy(humidityTemp, "Failed");         
            }else{
    String body1 = "field1=";
   // String body2 = "field2=";
    body1 += String(t);
   // body2 += String(h);
    
    Serial.print("sicaklik: ");
    Serial.println(t);
    Serial.print("nem: ");
    Serial.println(h);
    
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + writeAPIKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(body1.length());
    client.print("\n\n");
    client.print(body1);
    client.print("\n\n");
            }
        }
           // closing the client connection
    delay(1);
    //close
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("gec oldu");
    //system_deep_sleep(15*1000*1000);
    //System.sleep(SLEEP_MODE_DEEP, 1 * 60);
      digitalWrite(DHTen,LOW);
      Serial.println("Deactive");
      delay(10);
      ESP.deepSleep(30 * 1000000);
    }
        
