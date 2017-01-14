#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "ESP8266WiFi.h"
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
const char *ssid = "anacronin badge";
const char *password = "pusipusi";

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", "<h1>senkin tuhma haxxor, tuo olutta hacklabin ständille </h1>");
}

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Set the LCD I2C address

void setup()
{
lcd.begin(16,2);
lcd.clear();

  lcd.setCursor(0,0); 
  lcd.print("Configuring AP");
  WiFi.softAP(ssid);
  IPAddress myIP = WiFi.softAPIP();
  lcd.setCursor(0,0);
  lcd.print("AP IP address: ");
  lcd.setCursor(0,1);
  lcd.println(myIP);
  server.on("/", handleRoot);
  server.begin();

lcd.clear();
lcd.setCursor(0,0); 
lcd.print("Hello Disobey!");
lcd.setCursor(0,1);
lcd.print("I'm anacron");
}

void loop()
{
  server.handleClient();
}
