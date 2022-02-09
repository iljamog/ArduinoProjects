#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
ESP8266WiFiMulti WiFiMulti;

void setup() {
  
  Serial.begin(115200);
  pinMode( D1, INPUT);
  pinMode( D4, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  for (uint8_t t = 4; t > 0; t--) 
  {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }
  WiFi.begin("CGA2121_GNqnvHs", "Maryyyy777");
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Not connected");
  }
  Serial.println();
  Serial.println("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  
 String ip = WiFi.localIP().toString();
 byte button2State = digitalRead(D4);
 int val; 
 

 if (button2State == HIGH)
 {
  
   val = 2;
   Serial.println("2");
   digitalWrite(LED_BUILTIN, LOW);
   delay(200);
   
 } else {
  
    val = 0;
    digitalWrite(LED_BUILTIN, HIGH);
 }
 if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;
    HTTPClient http;
    
    if(val>0){
      Serial.print("[HTTP] begin...\n");
      String aadress="http://iljaasjadenett.000webhostapp.com/vastus.php?answer=";
      aadress+=ip;
      aadress+="Y";
      aadress+= val;
      aadress+="Y";
      Serial.println(aadress);
      
      if (http.begin(client, aadress)) {  // HTTP
        Serial.print("[HTTP] GET...\n");
        // start connection and send HTTP header
  
        
        int httpCode = http.GET();
  
        // httpCode will be negative on error
        if (httpCode > 0) {
          // HTTP header has been send and Server response header has been handled
          Serial.printf("[HTTP] GET... code: %d\n", httpCode);
  
          // file found at server
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String payload = http.getString();
            Serial.println(payload);
          }
        } else {
          Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
        
  
        http.end();
      } else {
        Serial.printf("[HTTP} Unable to connect\n");
      }
    } // if nupp lopp
  }
 delay(200);  
}
