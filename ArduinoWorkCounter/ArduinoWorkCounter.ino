
int trig = 4; // NodeMCU Pin D1 > TRIGGER 
int echo = 5; // NodeMCU Pin D2 > ECHO

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "";
const char* password = "";
const char* nameOfHost = "workcounter-esp8266";

const char* host = "";
const int httpsPort = 443;

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char* fingerprint = "";

void setup()
{
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

void loop()
{
  //digitalWrite(vcc, HIGH);
  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echo, INPUT);
  duration = pulseIn(echo, HIGH);

  // convert the time into a distance
  //inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  //Serial.print(inches);
  //Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  // Send info to server
  sendToServer2(cm);

  delay(50);
}

//long microsecondsToInches(long microseconds)
//{
//// According to Parallax's datasheet for the PING))), there are
//// 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
//// second). This gives the distance travelled by the ping, outbound
//// and return, so we divide by 2 to get the distance of the obstacle.
//// See: http://www.parallax.com/dl/docs/prod/acc/28015-PI...
//return microseconds / 74 / 2;
//}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

void sendToServer(long cm) {
  HTTPClient http;

  //Serial.print("[HTTP] begin...\n");
  // configure traged server and url

  
  //String url = "/test.json";
  String url = "https://" + String(host) + "/pass/insertvalue.json?deviceid=1&distance=" + String(cm) + "&millis=" + String(millis());
  Serial.println(url);
  http.begin(url, fingerprint); //HTTPS
  
  //Serial.print("[HTTP] GET...\n");
  // start connection and send HTTP header
  int httpCode = http.GET();

  delay(1000);
  // httpCode will be negative on error
  if(httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
  
      // file found at server
      if(httpCode == HTTP_CODE_OK) {
          String payload = http.getString();
          Serial.println(payload);
      }
  } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  
  http.end();
}

void sendToServer2(long cm) {
  HTTPClient http;

  String url = "/pass/InsertSingleValue.json?deviceid=1&distance=" + String(cm) + "&millis=" + String(millis());
  Serial.println(url);
  //http.begin("192.168.1.172", 5006, url, fingerprint);
  http.begin(host, 80, url);
  http.GET();
   
}