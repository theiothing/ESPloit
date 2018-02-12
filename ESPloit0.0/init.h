//for FS and JSON

#define MAX_TOPIC_LENGTH 64
#define Found_WiFi true
#define No_Matching_WiFi false
#define WiFiTimeoutInSeconds 30
#define NAME_BUFFER_SIZE 10
#define VALUE_BUFFER_SIZE 36
#define MAX_TOPIC_LENGHT 128

#define deviceName "ESPLOIT AP"

/*********WiFi param*********/
#define NR_WIFI_PARAM 2
char wifiNames[][NAME_BUFFER_SIZE] =
{
  "ssid1",
  "psw1"
};
char wifiValues[NR_WIFI_PARAM][VALUE_BUFFER_SIZE];
const char* wifi_path = "/wificonf.json";

/*********MQTT param*********/
#define NR_MQTT_PARAM 6
char mqttNames[][NAME_BUFFER_SIZE] =
{
  "enable",
  "broker",
  "port",
  "user",
  "password",
  "t_header"
};
char mqttValues[NR_MQTT_PARAM][VALUE_BUFFER_SIZE];
const char* mqtt_path = "/mqttconf.json";

bool mqttInit;
bool mqttConnectionStatus;

String myIP;
String myMAC;



