static const char WiFiConfigPage[] PROGMEM = // #xxxxxxxx# are later to be changed in c function WebsiteContent()
  R"=====(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8" lang="en">
  <link rel="stylesheet" type="text/css" href="mystyle.css">
  <title>config wifi</title> 
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
      <div id = "wifiTitle" class = "subtitle">scanning WiFi..</div>
      <table id="wifiList"></table>
    </div>
    <div class="descriptionBox">
      <form action="/submitWiFi">
        <span class="descriptionForm"> WiFi Name </span><br/>
        <input type="text" name="SSID" id="ssidForm" placeholder="click the wifi name (SSID) if you want to connect from the scan result";><br/>
        <span class="descriptionForm"> WiFi Password </span><br/>
        <input type="password" name="PSWD"><br/>
        <input type="submit" value="! tell this to your micro !"><br/>
      </form>
    </div>
  </div>
</body>
</html>


  <SCRIPT> // here starts the Java script for AJAX method
    // pure HTML -> ajax
    window.onload = function() {      
      var xhr_once = new XMLHttpRequest();
      xhr_once.open('GET', 'availWiFi', true);
      xhr_once.send(null);      
      xhr_once.onload = function(){ //when redy state changes
        if(xhr_once.status == 200){ //if server staus is ok
          document.getElementById("wifiTitle").innerHTML = "Scan Result:";
          document.getElementById("wifiList").innerHTML = xhr_once.responseText;          
          var h = document.getElementsByClassName("ssid");          
          var prova = document.getElementById("wifiTitle");

          for (var i = 0; i < h.length; i++){
            h[i].onclick = function(event){
              autoCompileSsid(event);
            };
          }                  
          function autoCompileSsid(event){
            var SSIDName = event.target.textContent;
            document.getElementById("ssidForm").value = SSIDName;
          }
          
        }
      }      
    }
  </SCRIPT>
)=====";

void handleWiFiPage()
{
  server.send(200,"text/html", WiFiConfigPage);
}


void availWiFiContent() {
  Serial.println("scan start");
  String networks;
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) networks = "no networks found";
  else {
    networks = "<tr>"               
               "<th scope=\"col\">WiFi SSID</th>"
               "<th scope=\"col\">WiFi RSSI</th>"
               "</tr>";
    for (int i = 0; i < n; ++i) {
      networks += "<tr>"
                  "<td class=\"ssid\">" + String( WiFi.SSID(i)) + "</td>"
                  "<td class=\"rssi\">" + String( WiFi.RSSI(i));
      if (WiFi.encryptionType(i) == ENC_TYPE_NONE) networks += "</td>";
      else " *</tr>";
    }
  }
  server.send(200, "text/html", networks);
}
