/***********************************************/
/*                FILE SYSTEM                  */
/***********************************************/

void formatFS() {
  Serial.println("Formatting SPIFFS");
  SPIFFS.format();
  Serial.println("DONE, U're clean kiddo!");
}

void rebootESP() {
  Serial.println("reboot in 2 sec");
  delay(2000);
  ESP.reset();
  delay(2000);
}

/***********************************************/
/*                    WiFI                     */
/***********************************************/

bool APStart = false;
bool STAStart = false;

bool scanWiFi() {
  String findWiFi[30];              //set max WiFi scanned to 30
  bool networkScanResult = false;
  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup done");
  delay(500);
  Serial.println("scan start");
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
    Serial.println("no networks found. Start AP mode");
  }
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      findWiFi[i] = String( WiFi.SSID(i));
      Serial.print("SSID [");
      Serial.print(i + 1);
      Serial.print("]");
      Serial.println(findWiFi[i]);
      if (String(findWiFi[i]) == String (wifiValues[0])) {
        networkScanResult = Found_WiFi;
        Serial.println("FOUND WIFI!!!");
        break;
      }
    }
  }
  return networkScanResult;
}

void startAP() {
  Serial.println("Configuring access point...");
  WiFi.softAP(deviceName);
  IPAddress APIP = WiFi.softAPIP();
  myIP = String(APIP[0]) + String(".") + \
         String(APIP[1]) + String(".") + \
         String(APIP[2]) + String(".") + \
         String(APIP[3]);
  Serial.println(myIP);
  Serial.print("AP IP address: ");

  Serial.println(APIP);
  myIP = String(APIP);
  myMAC = WiFi.macAddress();
  APStart = true;
}


void setup_wifi(char ssid[], char pswd[]) {

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.hostname(deviceName);
  WiFi.begin(ssid, pswd);
  uint64_t millisAtConnection = millis();
  uint8_t wifiStatus = 0;

  while (wifiStatus != WL_CONNECTED ) {
    if (wifiStatus == 4) {
      Serial.printf("password is incorrect \nStart AP mode");
      startAP();
      break;
    }
    if ((unsigned long)(millis() - millisAtConnection) >= WiFiTimeoutInSeconds * 1000) {
      Serial.println();
      Serial.print("couldn't connect: ");
      switch (wifiStatus) {
        case 0: Serial.println("Wi-Fi is in process of changing between statuses");
          break;
        case 1: Serial.println("configured SSID cannot be reached");
          break;
        //case WL_CONNECTED: Serial.println("actually is't connected just after hitting timeout (this is happening once every 10^1000000 times...)");
        //   break;
        //case 4: Serial.println("password is incorrect");
        //  break;
        case 6: Serial.println("module is not configured in station mode (more likley too short timeout time)");
          break;
        default: Serial.println("REASON UNKNOWN");
          break;
      }
      Serial.println("hit time out... starting AP");
      startAP();
      break;
    }
    wifiStatus = WiFi.status();
    delay(500);
    Serial.print(".");
  }
  if (wifiStatus == WL_CONNECTED) {
    STAStart = true;
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    IPAddress ipAddress = WiFi.localIP();
    myIP = String(ipAddress[0]) + String(".") + \
           String(ipAddress[1]) + String(".") + \
           String(ipAddress[2]) + String(".") + \
           String(ipAddress[3])  ;
    Serial.println(myIP);
    myMAC = WiFi.macAddress();

  }
}

void StartWiFi() {
  if (scanWiFi()) {
    setup_wifi(wifiValues[0], wifiValues[1]);

  } else {
    Serial.println();
    startAP();
  }
}

/***********************************************/
/*                    MQTT                     */
/***********************************************/

boolean reconnect();
void callback(char* p_topic, byte* p_payload, unsigned int p_length);
uint64_t lastReconnectAttempt = 0;

void nonBlockingMQTTConnection() {
  randomSeed(micros());
  if (!client.connected()) {
    mqttConnectionStatus = false;
    unsigned long now = millis();
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      if (reconnect()) {
        lastReconnectAttempt = 0;
        mqttConnectionStatus = true;
      }
    }
  }
  else {
    client.loop();
  }
}

bool startMQTT() {
  if (String(mqttValues[0]) == "active") {
    client.setServer(mqttValues[1], atoi(mqttValues[2]));
    client.setCallback(callback);
    Serial.println("MQTT client is now ready for use");
    mqttInit = true;
  } else {
    Serial.print("MQTT is disabled");
    mqttInit = false;
  }
  return mqttInit;
}

bool saveConfig(char names[][NAME_BUFFER_SIZE], char values[][VALUE_BUFFER_SIZE], const char path[], uint8_t nrParameters) {
  Serial.println("saving config");
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  for (int i = 0; i < nrParameters; i++) json[names[i]] = values[i];
  File configFile = SPIFFS.open(path, "w");
  if (!configFile) {
    Serial.println("Failed to open config file for writing");
    return false;
  }
  json.printTo(Serial);
  Serial.println();
  json.printTo(configFile);
  return true;
}

bool loadConfig(char names[][NAME_BUFFER_SIZE], char values[][VALUE_BUFFER_SIZE], const char path[], uint8_t nrParameters) {
  Serial.printf("mounting %s\n", path);
  if (SPIFFS.exists(path)) {
    File configFile = SPIFFS.open(path, "r");
    if (!configFile) {
      Serial.println("Failed to open config file");
      return false;
    }
    size_t size = configFile.size();
    if (size > 1024) {
      Serial.println("Config file size is too large");
      return false;
    }
    std::unique_ptr<char[]> buf(new char[size]);
    configFile.readBytes(buf.get(), size);
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.parseObject(buf.get());
    json.printTo(Serial);
    Serial.println();
    if (!json.success()) {
      Serial.println("Failed to parse config file");
      return false;
    }
    for (int i = 0; i < nrParameters; i++)
      strcpy(values[i], json[names[i]]);
    return true;
  }
  else {
    Serial.printf("sorry, but the file %s does not exist..\n", path);
    return false;
  }
}

/***********************************************/
/*                  HANDLERS                   */
/***********************************************/

void handleWiFiArgs() {
  Serial.println("handling WiFi");
  server.send(200, "text/html", "saving parameter");
  for (int i = 0; i < server.args(); i++) {
    server.arg(i).toCharArray(wifiValues[i], VALUE_BUFFER_SIZE);              //load parameters in the array
  }
  saveConfig(wifiNames, wifiValues, wifi_path, NR_WIFI_PARAM);
  rebootESP();
}

void handleMqttArgs() {
  Serial.println("handling MQTT");
  server.send(200, "text/html", "saving parameter");
  if (server.args() == NR_MQTT_PARAM) { //MQTT enabled
    for (int i = 0; i < server.args(); i++) {
      server.arg(i).toCharArray(mqttValues[i], VALUE_BUFFER_SIZE);              //load parameters in the array
    }
  } else  memset(mqttValues[0], 0, VALUE_BUFFER_SIZE);

  saveConfig(mqttNames, mqttValues, mqtt_path, NR_MQTT_PARAM);
  rebootESP();
}

/***********************************************/
/*                  SERVER                     */
/***********************************************/

void startServer() {
  server.on("/", handleRootPage);
  server.on("/wifi.html", handleWiFiPage);
  server.on("/availWiFi", availWiFiContent);
  server.on("/mqtt.html", handleMqttPage);
  server.on("/about.html", handleAboutPage);
  server.on("/netParam.json", netParamAjax);
  server.on("/mystyle.css", handleStyles);
  server.on("/submitWiFi", handleWiFiArgs);
  server.on("/submitMqtt", handleMqttArgs);
  server.begin();
  Serial.println("Server Started");
}

