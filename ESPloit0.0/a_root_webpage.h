

static const char rootWebPage[] PROGMEM = // #xxxxxxxx# are later to be changed in c function WebsiteContent()
  R"=====(
  <!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8" lang="en">
  <link rel="stylesheet" type="text/css" href="mystyle.css">
  <title>root</title>  
</head>

<body>

  <div class="sidenav">
    <a href="/">Home</a>
    <a href="/wifi.html">WiFi</a>
    <a href="/mqtt.html">MQTT</a>
    <a href="/about.html">About</a>
  </div>
  <div class="main">
    <h2 id="wifiTitle">..welcome buddy..</h2>
    <div class = "subtitle">void 0.0</div>
  </div>   
</body>
</html>
  
)=====";


void handleRootPage()
{
  server.send(200,"text/html", rootWebPage);
}


