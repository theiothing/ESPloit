# ESPloit
\ɛks.plwa\ singular noun: A heroic or extraordinary deed.

## What is ESPloit?
A lightweight webserver for easily connect an ESP8266 board to WiFi and MQTT with a serverless control.

### The IDEA behind it
#### Super fast prototyping environment.
There are a lot of webservers framework out there. Most of them are developed starting from iTead Sonoff products based on ESP8266 chip. Even if they work great for Sonoff products, I've found that are not suitable for any IoT project, which is what I need. I also need portablity (configure different Networks and Brokers) and allow non-technical-users work confortably with "my things".
#### Serverless
Even if 90% of the WiFi IoT projects communicate with an MQTT broker, from time to time I need a single "thing" to be controlled locally and without any other infrastructure. That's why ESPloit can also control a device SERVERLESS. So if you want to build your own smart light you can always control it from the served webpage.
#### Standard Recipes
For the most common devices you can find ready-made recipes. You only need to configure "the thing" via web browser.

E.G. if you want to connect a relay, you need to connect it to your ESP, and then configure PIN and working logic (active-high or active-low) besides network credentials, from the web page just like you do when configuring a router. 

### Why should I USE it?
You can use MQTT communication, but you can also control one single device from its webpage - SERVERLESS

Web server is highly customizable since the HTML, CSS and SCRIPT files are accessible from a separate file page in the sketch.

setup() and loop() functions are as void as possible, the way you can focus on electronics and on the sketch of yours. ESPloit takes care of connection (WiFi) and communication (MQTT).

## How does it Work?
ESPloit is developed in Arduino IDE. It uses file system (SPIFFS) to store permanently data. It writes a JSON file to FS with the required fileds. For detailed description see documentation below.

This sketch is not a libray because I want everybody to customize it as they like.

## Getting Started

## How you should use it

## To Do (Next Step)
