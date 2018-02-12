/*
 * add ajax for placeholder parameters
 */

static const char MqttConfigPage[] PROGMEM = // #xxxxxxxx# are later to be changed in c function WebsiteContent()
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
      <div id = "wifiTitle" class = "subtitle">MQTT CONFIGURATION</div>
    </div>
    <div class="descriptionBox">
      <form action="/submitMqtt">
        <div class="formEnable">
        <input type="checkbox" name="mqttEnable" value="active" checked>Enable mqtt <br/>
        </div>
        <span class="descriptionForm"> Broker </span><br/>
        <input type="text" name="Broker"><br/>
        <span class="descriptionForm"> Port </span><br/>
        <input type="text" name="Port"><br/>
        <span class="descriptionForm"> Username </span><br/>
        <input type="text" name="user"><br/>
        <span class="descriptionForm"> Password </span><br/>
        <input type="password" name="PSWD"><br/>
        <span class="descriptionForm"> Topic Header </span><br/>
        <input type="text" name="topic" placeholder="{your/topic/header}/power"><br/>
        <input type="submit" value="! tell this to your micro !"><br/>
      </form>
    </div>
  </div>
</body>
</html>
)=====";


void handleMqttPage()
{
  server.send(200,"text/html", MqttConfigPage);
}
