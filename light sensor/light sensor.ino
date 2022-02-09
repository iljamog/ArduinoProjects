/**
   BasicHTTPClient.ino

    Created on: 24.05.2015

*/

#include <Arduino.h>


#include <Time.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
//UUS
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"


// Insert Firebase project API Key
#define API_KEY "AIzaSyD0bUl5GZX1nOOW9QoA3tY3D1UaVqrOD7U"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://iljaiot-default-rtdb.europe-west1.firebasedatabase.app/" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

bool signupOK = false;
//UUS

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;
int analogPin = A0;
int val = 0;

void setup() {
  Serial.begin(115200);

  // Valgusfoor
   pinMode(16,HIGH);  // Blue led Pin Connected To D0 Pin   
   pinMode(5,HIGH);  // Green Led Pin Connected To D1 Pin   
   pinMode(4,HIGH);  // Red Led Connected To D2 Pin 
  //

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  //WiFi.mode(WIFI_STA);
  //WiFiMulti.addAP("b08918-2.4GHz", "287569606");
  
  WiFi.begin("AndroidAPA469", "aaaz3032");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Not connected");
  }
  Serial.println();

  Serial.println("Connected, IP address: ");
  Serial.println(WiFi.localIP());


  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("Signed into DB");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {

  //UUS

  if (Firebase.ready() && signupOK && digitalRead(2)==0){
    // Write an Int number on the database path test/int
    if (Firebase.RTDB.setInt(&fbdo, "nupp/int", 1)){
      Serial.println("PASSED");
      
            //VF
        // BLUE LED ON  
          digitalWrite(16,LOW);  
          digitalWrite(5,HIGH);  
          digitalWrite(4,HIGH);  
          delay(1000);  
          // GREEN LED ON  
          digitalWrite(16,HIGH);  
          digitalWrite(5,LOW);  
          digitalWrite(4,HIGH);  
          delay(1000);  
          // RED LED ON  
          digitalWrite(16,HIGH);  
          digitalWrite(5,HIGH);  
          digitalWrite(4,LOW);  
          delay(1000);  
        //VF
    }
    else {
      Firebase.RTDB.setInt(&fbdo, "nupp/int", 0);
    
      Serial.println("FAILED");
    }

  //UUS

  
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;

    val = analogRead(analogPin);  // read the input pin
    Serial.println(val);          // debug value

    Serial.print("[HTTP] begin...\n");
    String aadress="http://iljaasjadenett.000webhostapp.com/valgus.php?t=";
    aadress+=val;
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
  }

  delay(10000);
}
}
