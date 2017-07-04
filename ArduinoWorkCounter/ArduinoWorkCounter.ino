//static const uint8_t D0   = 16;
//static const uint8_t D1   = 5;
//static const uint8_t D2   = 4;
//static const uint8_t D3   = 0;
//static const uint8_t D4   = 2;
//static const uint8_t D5   = 14;
//static const uint8_t D6   = 12;
//static const uint8_t D7   = 13;
//static const uint8_t D8   = 15;
//static const uint8_t D9   = 3;
//static const uint8_t D10  = 1;

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <NewPing.h>
#include "LedControl.h"

const char* ssid = "ssid";
const char* password = "pass";
const char* nameOfHost = "workcounter-esp8266";

const char* host = "";
const int httpsPort = 443;

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char* fingerprint = "";

NewPing sonar(D2, D1, 200);
LedControl lc=LedControl(D7, D5, D8, 1); //DataIn, CLK, LOAD

void setup()
{
  //The MAX72XX is in power-saving mode on startup, we have to do a wakeup call
  lc.shutdown(0,false);
  lc.shutdown(1,false);
  //Set the brightness to a medium values
  lc.setIntensity(0,8);
  lc.setIntensity(1,8);
  //and clear the display
  lc.clearDisplay(0);
  lc.clearDisplay(1);

  lc.setDigit(0, 0, 8, false);
  lc.setDigit(0, 1, 7, true);
  lc.setDigit(0, 2, 6, false);
  lc.setDigit(0, 3, 5, true);
  lc.setDigit(0, 4, 4, false);
  lc.setDigit(0, 5, 3, true);
  lc.setDigit(0, 6, 2, false);
  lc.setDigit(0, 7, 1, true);
  
  Serial.begin(9600);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  
  WiFi.hostname(nameOfHost);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  //long cm = sonar.ping_cm();
  long cm = sonar.convert_cm(sonar.ping_median(5));
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  lc.clearDisplay(0);
  setDisplayDistance(cm);

  // Send info to server
  if (cm < 160 && cm > 5) {
    sendToServer(cm);
  }
  delay(50);
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

void sendToServer(long cm) {
  HTTPClient http;

  String url = "/pass/InsertSingleValue.json?deviceid=1&distance=" + String(cm) + "&millis=" + String(millis());
  Serial.println(url);
  //http.begin("192.168.1.172", 5006, url, fingerprint);
  http.begin(host, 80, url);
  http.GET();
  http.end();
}

void setDisplayDistance(long cm) {
  byte c1 = ' ';
  char c2 = ' ';
  char c3 = ' ';
  char c4 = ' ';

  if (cm < 10) {
    c4 = (char)cm;
  }
  else if (cm < 100) {
    c4 = (char)cm%10;
    cm /= 10;
    c3 = (char)cm;
  }
  else if (cm < 1000) {
    c4 = (char)cm%10;
    cm /= 10;
    c3 = (char)cm%10;
    cm /= 10;
    c2 = (char)cm;
  }
  else {
    c4 = (char)cm%10;
    cm /= 10;
    c3 = (char)cm%10;
    cm /= 10;
    c2 = (char)cm%10;
    cm /= 10;
    c1 = (char)cm;
  }

  
  lc.setDigit(0, 0, c4, false);
  lc.setDigit(0, 1, c3, false);
  lc.setDigit(0, 2, c2, false);
  lc.setDigit(0, 3, c1, false);
}