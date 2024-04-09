#include "ESP8266WiFi.h"
#include "WiFiClientSecure.h"
#include<SoftwareSerial.h> //Included SoftwareSerial Library


//user config:
const char* wifi_ssid = "Visokov Famely Network 2.4";             // replace MySSID with your WiFi network name
const char* wifi_password = "Dasha3Bu";         // replace MyPassword with your WiFi password
const char* apiKeyIn = "MGG2WBB7ZSW9WCPB";      // replace APIKEYIN with your channel write API Key
const unsigned int writeInterval = 25000; // write interval (in ms)

//thingspeak config.
const char* https_host = "api.thingspeak.com";         // thingspeak host name
const int https_port = 443;                        // https port
//create thingspeak client
WiFiClientSecure client;

SoftwareSerial s ( 5 , 4 );

byte tempByte[6];
float temp;


void getTem(){
  if (!client.connect(https_host, https_port)) {
    delay(200);
    return;
  }
  for (int i = 0; i < 6; i++){ 
      tempByte[i] = s.read();  
      Serial.print(tempByte[i]);
      Serial.print(" ");
  } 
  delay(1000); 
  if ( tempByte[0] == 1 && tempByte[5] == 1){ 
    for(int i = 1; i < 5; i++){ 
      ((byte*)&temp)[i] = tempByte[i]; 
    } 
  } else { 
    Serial.println("НЕ ВИЖУ ФЛАГОВ"); 
  }
    Serial.println("temp:" );
    Serial.println(temp);
    Serial.println((int)temp);

 //Create a URL for the request
 String url = "/update?api_key=";
 url += apiKeyIn;
 url += "&field1=";
 url += ((int)temp);
 
client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + https_host + "\r\n" +
               "Connection: close\r\n\r\n");

  client.connected();
}

void setup() {
  //Serial Begin at 9600 Baud 
  Serial.begin(9600);
  s.begin(9600);
  WiFi.begin(wifi_ssid, wifi_password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  }
  client.setInsecure();
 
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

}

void loop() {
   
   getTem();
   delay(7000);

}
