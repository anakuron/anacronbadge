#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include "./DNSServer.h"  
#include <ESP8266WebServer.h>

const byte        DNS_PORT = 53;  
IPAddress         apIP(192, 168, 4, 1);
DNSServer         dnsServer;
ESP8266WebServer server(80);

int piezoPin = 15;
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Set the LCD I2C address

String form =
  "<p>"
  "<center>"
  "<h1>anacronin badge</h1>"
  "<form action='msg'><p>Leave a msg <input type='text' name='msg' size=50 autofocus> <input type='submit' value='Submit'></form>"
  "</center>";

void handle_msg() 
{
server.send(200, "text/html", form);
String msg = server.arg("msg");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("nick: anacron");
  lcd.setCursor(0,1);
  lcd.print("msg: " + msg);
  Serial.println(msg);
  tone(piezoPin, 500, 500  );
  tone(piezoPin, 1000, 500);
}

void setup()
{

    Serial.begin(9600);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("anacronin badge");
  dnsServer.start(DNS_PORT, "*", apIP);
  
 server.onNotFound([]() {
    server.send(200, "text/html", form);
  });
 
  server.on("/", []()
  {
    server.send(200, "text/html", form);
  });
    server.on("/msg", handle_msg);     
  server.begin();

tone(piezoPin, 300, 500);
lcd.begin(16,2);
lcd.clear();
lcd.setCursor(0,0); 
lcd.print("Hello HSF!");
lcd.setCursor(0,1);
lcd.print("I'm anacron");
}

void loop()
{
  dnsServer.processNextRequest();
  server.handleClient();
}
