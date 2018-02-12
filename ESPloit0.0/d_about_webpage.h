static const char aboutPage[] PROGMEM = // #xxxxxxxx# are later to be changed in c function WebsiteContent()
  R"=====(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8" lang="en">
  <link rel="stylesheet" type="text/css" href="mystyle.css">
  <title>config MQTT</title>
</head>

<body>
  <div class="sidenav">
    <a href="/">Home</a>
    <a href="/wifi.html">WiFi</a>
    <a href="/mqtt.html">MQTT</a>
    <a href="/about.html">About</a>
  </div>
  <div class="main">
    <div>
      <div id = "aboutTitle" class = "subtitle">about</div>
    </div>
      <div class="descriptionBox">
        <div class="descriptionForm">my ip address</div>
          <span id="ip"></span>
        <div class="descriptionForm">mac address</div>
          <span id="mac"></span>
        <div class="descriptionForm">Device Name (AP name)</div>
          <span id="deviceName"></span>
        <div class="descriptionForm">MQTT Status</div>
          <span id="mqttStatus"></span>
        </div>
      </div>
  </div>
</body>
</html>

<SCRIPT> // here starts the Java script for AJAX method
    // pure HTML -> ajax with JASON parsing
    window.onload = function() {      
      var xhr_once = new XMLHttpRequest();
      xhr_once.open('GET', 'netParam.json', true);
      xhr_once.send(null);      
      xhr_once.onload = function(){ //when redy state changes
        if(xhr_once.status == 200){ //if server staus is ok
          responseObject = JSON.parse(xhr_once.responseText);
          document.getElementById('ip').innerHTML = responseObject.ip;
          document.getElementById('mac').innerHTML = responseObject.mac; 
          document.getElementById('deviceName').innerHTML = responseObject.deviceName;
          document.getElementById('mqttStatus').innerHTML = responseObject.mqttStatus;
        }
      }      
    }
  </SCRIPT>
)=====";


void handleAboutPage()
{
  server.send(200,"text/html", aboutPage);
}

const char JSON_netValues[] PROGMEM = // #xxxxxxxx# are later to be changed in c function XML_Content()
R"=====({
  "ip" : "#IP#",
  "mac" : "#MAC#",  
  "deviceName" : "#apNAME#",
  "mqttStatus": "#mqttStatus#"
}
)=====";

void netParamAjax() {  
   String jsonBuffer = String(JSON_netValues);
   jsonBuffer.replace("#IP#", myIP);
   jsonBuffer.replace("#MAC#", myMAC);
   jsonBuffer.replace("#apNAME#", deviceName);
   if (!mqttInit) jsonBuffer.replace("#mqttStatus#", "MQTT connection is DEACTIVATED");
   else{
        if (mqttConnectionStatus) jsonBuffer.replace("#mqttStatus#", "connected to broker: " + String(mqttValues[1]));
        else jsonBuffer.replace("#mqttStatus#", "not connected");
   }
   server.send(200, "text/html", jsonBuffer);
}
