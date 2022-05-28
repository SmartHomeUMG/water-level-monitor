#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "SSID";
const char* password = "PASSWORD";

String serverName = "http://192.168.100.132:5108/HomeCondition/WaterLevel/Add?level=";

long last_read;
long last_send;
long read_interval = 2000;
long send_interval = 20000;

int sensor_value[10];
int nr_sample = 0;

void bubbleSort(){
  int temp, i, j;
  for(i = 0; i < 9; i++){
    for(j = 0; j < 10 - i - 1; j++){
      if(sensor_values[j] > sensor_values[j+1]){
        temp = sensor_values[j+1];
        sensor_values[j+1] = sensor_values[j];
        sensor_values[j] = temp;  
      } 
    }  
  }
}

void setup() {
  Serial.begin(115200); 

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
}

void loop() {
    //get value from sensor
  if ((millis() - last_read) > read_interval){
      sensor_value[nr_sample] = analogRead(A0);
      nr_sample++;
      last_read = millis();
  }
  
  // Send an HTTP GET request which contains samples' median
  if ((millis() - last_send) > send_interval) {
    bubbleSort();
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      String serverPath = serverName + sensor_value[4];
      
      http.begin(client, serverPath.c_str());
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    last_send = millis();
    nr_sample = 0;
  }
}