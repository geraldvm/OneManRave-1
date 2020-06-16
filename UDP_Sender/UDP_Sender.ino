#include <SPI.h>        
#include <WiFi.h>
#include <WiFiUdp.h>
#include "secrets.h"

const char * udpAddress = "192,168,4,1";
const int udpPort = 34215;
const int LocaludpPort = 34214;


boolean connected = false;

WiFiUDP udp;

int i = 1;
int timeing = 0;
int lastTime = 0;
float aveTime = 0;

const char * networkName = "RaveOn";

void setup(){
  // Initilize hardware serial:
  Serial.begin(115200);
  
  //Connect to the WiFi network
  connectToWiFi(networkName, networkPswd);
  
}

void loop(){
  //only send data when connected
  if(connected){
    //Send a packet
    udp.beginPacket(udpAddress,udpPort);
    udp.printf("Seconds since boot: %lu", millis()/1000);
    Serial.println(udp.endPacket());
  }
  timeing += ( millis() - lastTime);  // keep adding up the time to average it 
  aveTime = (timeing / i);  // get the average
  
   if ( (i++ % 500) == 0 ) {     // don't print evertime so serial monitor doesn't bog us down
    
    Serial.println(aveTime);  
   }
   lastTime = millis();
   
}

void connectToWiFi(const char * ssid, const char * pwd){
  Serial.println("Connecting to WiFi network: " + String(ssid));

  // delete old config
  WiFi.disconnect(true);
  //register event handler
  WiFi.onEvent(WiFiEvent);
  
  //Initiate connection
  WiFi.begin(ssid, pwd);

  Serial.println("Waiting for WIFI connection...");
}

//wifi event handler
void WiFiEvent(WiFiEvent_t event){
    switch(event) {
      case SYSTEM_EVENT_STA_GOT_IP:
          //When connected set 
          Serial.print("WiFi connected! IP address: ");
          Serial.println(WiFi.localIP());  
          //initializes the UDP state
          //This initializes the transfer buffer
          udp.begin(WiFi.localIP(),LocaludpPort);
          
          connected = true;
          break;
      case SYSTEM_EVENT_STA_DISCONNECTED:
          Serial.println("WiFi lost connection");
          connected = false;
          break;
      default: break;
    }
}
