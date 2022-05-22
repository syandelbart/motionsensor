
#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <gpio.h>;
#include <WiFiClient.h>
#include <ArduinoJson.h>

WiFiClient wifiClient;

#define PIR = 1;
int Status = 2;
int sensor = 13;

const char *ssid =  "SSID";  
const char *pass =  "WIFI_PASS";

const String ip = "HUE BRIDGE IP";
const String user = "HUE BRIDGE USER";

//Lights you want to switch with this motion sensor
int light_ids[] = {};
int light_amount = 0;

bool light_states[] = {false,false};

int light_on_times[] = {60,60}; //in seconds

int light_on_current[] = {0,0};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  delay(10);

  int numberOfNetworks = WiFi.scanNetworks();
 
  for (int i = 0; i < numberOfNetworks; i++) {
    String networkName = WiFi.SSID(i);
    int signalStrength = WiFi.RSSI(i);
 
    Serial.println(networkName + " (" + signalStrength + ")");
  }
            
  Serial.println("Connecting to ");
  Serial.println(ssid2); 
  WiFi.begin(ssid2,pass2); 
  while (WiFi.status() != WL_CONNECTED) 
     {
       delay(500);
       Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected"); 
  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());

  pinMode(sensor,INPUT);
  pinMode(Status,OUTPUT);

  //set initial times
  for(int i=0;i<light_amount;i++) {
    light_on_current[i] = light_on_times[i];
    
  }

  
  
}

void loop() {
  long state = digitalRead(sensor);
  if(state == HIGH) {
    digitalWrite(Status,LOW);
    for(int i=0;i<light_amount;i++) {
      if(!light_states[i]) {
        switchLight(light_ids[i],true);
        light_states[i] = true;
      }
      light_on_current[i] = light_on_times[i];
      
    }
    
  } else {
    digitalWrite(Status, HIGH);
    for(int i=0;i<light_amount;i++) {
      light_on_current[i] -= 1;
      if(light_on_current[i] == 0) {
        switchLight(light_ids[i],false);
        light_states[i] = false;
      }
    }
  }

  delay(1000);
}

bool getLightState(byte light_id) {
    HTTPClient http;
    String req = "http://" + ip + "/api/" + user + "/lights/" + light_id;
    http.begin(wifiClient,req);
    http.addHeader("Content-Type", "text/plain");
    int httpResponse = http.GET();
    if(httpResponse > 0) {
      String response = http.getString();
      Serial.println(httpResponse);
      Serial.println(response);
      
      return true;
    } else {
      Serial.print("Error sending change state: ");
      Serial.println(httpResponse);
      return true;
    }
  }

void switchLight(byte light_id,bool wanted_state) {
  HTTPClient http;
  String req = "http://" + ip + "/api/" + user + "/lights/" + light_id + "/state";
  Serial.println(req);
  http.begin(wifiClient,req);
  http.addHeader("Content-Type", "text/plain");

  String send = "{\"on\":";
  send += ((wanted_state) ? "true" : "false");
  send += "}";

  int httpResponse = http.PUT(send);

  if(httpResponse > 0) {
    String response = http.getString();
    Serial.println(httpResponse);
    Serial.println(response);
  } else {
    Serial.print("Error sending change state: ");
    Serial.println(httpResponse);
  }
  http.end();
}
