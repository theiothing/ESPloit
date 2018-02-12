/*
 **********    ESPloit firmware 0.0 *************
 *   provides a webserver for wifi and mqtt broker configuration
 *   no subscription or publishing topics provided
 *   AP mode on IP: 192.168.4.1
 *   AP name: ESPLOIT AP as defined in "init.h"
 *      #define deviceName "ESPLOIT AP"
 *   in-line comments
 *   
 *   for more information reference:
 *   https://github.com/marcoprovolo/ESPloit
 */


#include <FS.h>                 //ESP8266 core
#include <ESP8266WiFi.h>        //ESP8266 core
#include <ESP8266WebServer.h>   //ESP8266 core
ESP8266WebServer server(80);    //ESP8266 core
#include <ArduinoJson.h>        //https://github.com/bblanchon/ArduinoJson
#include <PubSubClient.h>       //https://github.com/knolleary/pubsubclient
WiFiClient espClient;              //initialise a wifi client
PubSubClient client(espClient);    //creates a partially initialised client instance for MQTT

#include "init.h"
#include "a_root_webpage.h"
#include "b_wifi_webpage.h"
#include "c_mqtt_webpage.h"
#include "d_about_webpage.h"
#include "css.h"
#include "functions.h"

void setup(){
  Serial.begin(115200);
  Serial.println();
  // addyour setup configuration here
   
  SPIFFS.begin();
  // for debugging purposes
  //formatFS();

  //check a WiFi config file in the FS
  if (loadConfig(wifiNames, wifiValues, wifi_path, NR_WIFI_PARAM)) StartWiFi();
  else startAP();
  //check an MQTT config file in the FS
  if (STAStart && loadConfig(mqttNames, mqttValues, mqtt_path, NR_MQTT_PARAM)) startMQTT();
  else Serial.println("no MQTT config File or AP mode");
  
  startServer();  
}

void loop(){
  server.handleClient();
  if (mqttInit) nonBlockingMQTTConnection();
  /* your code here below*/

  
}

boolean reconnect() {
  Serial.println("Attempting MQTT connection...");
  String clientId = "ESP8266Client-";
  clientId += String(random(0xffff), HEX);
  // Attempt to connect
  if (client.connect(clientId.c_str(), mqttValues[3], mqttValues[4])) {
    Serial.printf("\nCONGRATS!!! U'r CONNECTED TO MQTT BROKER!\nstart making your things talk!!!");
    /*** subscribe here below ***/    
  }
  return client.connected();
}

void callback(char* p_topic, byte* p_payload, unsigned int p_length) {
  char msg_buff[100];
  for (int i = 0; i < p_length; i++) {
    msg_buff[i] = p_payload[i];
  }
  msg_buff[p_length] = '\0';
  /*** 
   *  here you recieve the payload on the topics you've been subscribed to.
   *  choose what to do here
   ***/
  
  
}
