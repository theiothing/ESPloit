static const char cssStyling[] PROGMEM = // #xxxxxxxx# are later to be changed in c function WebsiteContent()
R"=====(
body{
  margin:0;
  padding:0;
  font-family: Nexa, sans-serif;
  text-align: center;
  background-color: #333;
  color:  #818181;
  letter-spacing: 2px;
}
.sidenav{
  height: 100%;
  width: 20%;
  max-width: 200px;
  font-size: 100%;
  font-size-adjust: auto;
  position: fixed;
  top: 0px;
  right: 0;
  background-color: #282a2d;
  overflow-x: hidden;
  padding-top: 20px;
}
.sidenav a {
  padding: 6px 8px 6px 16px;
  text-decoration: none;
  font-size: 20px;
  color: #818181;
  display: block;
}
.sidenav a:hover {
  background-color: #282a2d;
  color: #CCC;
  font-weight: bold;
  transition: 0.3s;
}
.main{
  position: absolute;
  left:0; right:20%;
  top:0; bottom:0;
  margin: auto;
}
.descriptionBox{
  border-radius: 5px;
  color: #333;
  background-color: #AAA;
  width: 70%;
  padding: 25px;
  margin: 0 auto;
}
.wifiTitle{
  margin : 20px;
}
.descriptionForm{
  color: #333;
  font-weight: bold;
}

input[type=text], input[type=password], select {
  width: 100%;
  padding: 12px 12px;
  margin: 5px 0px 20px 0px;
  display: inline-block;
  border: 1px solid #666;
  border-radius: 4px;
  box-sizing: border-box;
  font-family: Nexa, sans-serif;
  font-weight: bold;
  letter-spacing: 2px;

}
input[type=submit] {
  width: 100%;
  background-color: #223;
  color: #CCD;
  padding: 14px 20px;
  margin: 8px 0;
  border: none;
  border-radius: 4px;
  cursor: pointer;
  font-family:sans-serif;
  font-variant: small-caps;
  font-size:150%;

}
input[type=submit]:hover {
  background-color: #EAAF00;
  color: #00293C;
}
table {
  margin: 0 auto;
  padding: 20px;
}
.subtitle{
  font-size:150%;
  color: #AAA;
  padding: 20px;
  margin:0;
}
.ssid:hover{
  font-weight: bold;
  color: #EEE;
}
.formEnable{
  padding-bottom: 20px;
  font-weight: bold;
}

  
)=====";

void handleStyles()
{
  Serial.println("asking for styles");
  server.send(200,"text/css", cssStyling);
}

