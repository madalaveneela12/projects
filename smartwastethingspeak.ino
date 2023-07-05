#include <ESP8266WiFi.h>
#include "ThingSpeak.h"
#include "secrets.h"


char ssid[] = "project";   // your network SSID (name)
char pass[] = "12345678";   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber =  2026860;
const char * myWriteAPIKey = "9QIQX37M4M3FSTUT" ;

String m1,m2,m3,m4,t;
String m,c,k,d,e,f;
int n;
void setup()
{
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);

  ThingSpeak.begin(client); // Initialize ThingSpeak
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }
}

void loop()
{

  if (Serial.available() > 0)
  {
    k = Serial.readString();
//    Serial.println(voltage);
    delay(1000);


if (k[0] == '@')
    {
      n = k.length();
      Serial.println(n);
      m = k.substring(1,n);
      Serial.print("distance:");
      Serial.println(m);
      ThingSpeak.writeField(myChannelNumber, 1, m, myWriteAPIKey); //Update in ThingSpeak
      delay(1000);
      Serial.println("Channel Updated field1");
    }
    if (k[0] == '#')
    {
      n = k.length();
      Serial.println(n);
      m1 = k.substring(1,n);
      Serial.print("ir:");
      Serial.println(m1);
      ThingSpeak.writeField(myChannelNumber, 2, m1, myWriteAPIKey); //Update in ThingSpeak
      delay(1000);
      Serial.println("Channel Updated field2");
    } 
    if (k[0] == '$')
    {
      n = k.length();
      Serial.println(n);
      m2 = k.substring(1,n);
      Serial.print("gas:");
      Serial.println(m2);
      ThingSpeak.writeField(myChannelNumber, 3, m2, myWriteAPIKey); //Update in ThingSpeak
      delay(1000);
      Serial.println("Channel Updated field3");
    }  
    if (k[0] == '%')
    {
      n = k.length();
      Serial.println(n);
      m3 = k.substring(1,n);
      Serial.print("humidity:");
      Serial.println(m2);
      ThingSpeak.writeField(myChannelNumber, 4, m3, myWriteAPIKey); //Update in ThingSpeak
      delay(1000);
      Serial.println("Channel Updated field4");
    }  
  }
}
