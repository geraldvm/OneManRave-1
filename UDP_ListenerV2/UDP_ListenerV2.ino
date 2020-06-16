// starts this ESP as an access point
// also listens for UDP packets comming from the sender

#include <SPI.h>        
#include <WiFi.h>
#include <WiFiUdp.h>
#include <ESP32WebServer.h>
#include "secrets.h"

//Server at port 80
ESP32WebServer server(34215);

IPAddress local_ip(192,168,4,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

unsigned int localPort = 34215;      // local port to listen for UDP packets
byte packetBuffer[512]; //buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
WiFiUDP Udp;

void setup(){
  Serial.begin(115200);

  //Resets the wifi connection, solved a bug where no communication took place 
  WiFi.disconnect(true);
  delay(1000);  
  const char* ssid = "RaveOn";


  WiFi.softAP(ssid, pass);
  Serial.println(WiFi.softAPIP());
  server.begin();
  Serial.println("Server started");
  Udp.begin(localPort);
}

void loop(){
  delay(3000);
  int noBytes = Udp.parsePacket();
  String received_command = "";
   Serial.print(":Packet of ");
    Serial.print(noBytes);
    Serial.print(" received from ");
    Serial.print(Udp.remoteIP());
    Serial.print(":");
    Serial.println(Udp.remotePort());
    // We've received a packet, read the data from it
    Udp.read(packetBuffer,noBytes); // read the packet into the buffer

    // display the packet contents in HEX
    for (int i=1;i<=noBytes;i++)
    {
      Serial.print(packetBuffer[i-1],HEX);
      received_command = received_command + char(packetBuffer[i - 1]);
      if (i % 32 == 0)
      {
        Serial.println();
      }
      else Serial.print(' ');
    } // end for
    Serial.println();
}
