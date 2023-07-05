int  buttonState1;
int buttonState2;
#define trigPin 2
#define echoPin 3
long duration;
long distance = 0;
long distance1 = 0;
long distance2 = 0;
#define ir 4
#define gas 5
#define buz1 10
#define buz2 11
String msg;
String str, str1, str2, str3;
//int Temperature;
#define DHTPIN 7     // what pin we're connected to
#include "DHT.h"
#define DHTTYPE DHT11   // DHT 11 
// Initialize DHT sensor for normal Arduino
DHT dht(DHTPIN, DHTTYPE);
#include <SoftwareSerial.h>
SoftwareSerial ss(12, 13);

void setup()
{
  Serial.begin(9600);
  ss.begin(9600);
  dht.begin();
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(ir, INPUT);
  pinMode(gas, INPUT);
  pinMode(buz1, OUTPUT);
  pinMode(buz2, OUTPUT);
  digitalWrite(buz1, LOW);
  digitalWrite(buz2, LOW);
}
void loop()
{
  buttonState1 = digitalRead(ir);
  Serial.println("ir :");
  Serial.println(buttonState1);
  delay(1000);

  buttonState2 = digitalRead(gas);
  Serial.println("gas:");
  Serial.println(buttonState2);
  delay(1000);

  digitalWrite(trigPin, LOW);
  delay(1000);
  digitalWrite(trigPin, HIGH);
  delay(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);


  delay(2000);
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  int f = dht.readTemperature(true);
  // delay(2000);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %\t");
  Serial.print("Temperature: ");
  Serial.println(t);
  str = '%' + String(h);
  Serial.println(str);
  delay(1000);
  //  if (distance>21&&distance<25)
  //  {
  //    str = '@' + String("30");
  //    Serial.println(str);
  //    Serial.println("buz1 is high");
  //    delay(3000);
  //    digitalWrite(buz1, LOW);
  //    digitalWrite(buz1, HIGH);
  //    delay(3000);
  //    digitalWrite(buz1, LOW);
  //    delay(1000);
  //  }
  if (distance > 10 && distance < 20)
  {
    str = '@' + String("75");
    Serial.println(str);
    msg = "dustbin 75% filled near kinnera";
    SendMessage();
    delay(1000);
  }
  else if (buttonState1 == 0)   // ir
  {
    str = '#' + String(buttonState1);
    Serial.println(str);
    digitalWrite(buz1, HIGH);
    delay(3000);
    digitalWrite(buz1, LOW);
  }
  else
  {
    digitalWrite(buz1, LOW);
    digitalWrite(buz2, LOW);
  }
  if (distance > 0 && distance < 5)
  {
    digitalWrite(buz2, HIGH);
    delay(6000);
    digitalWrite(buz2, LOW);
    str = '@' + String("90");
    Serial.println(str);
    msg = "dustbin 90% filled near kinnera";
    SendMessage1();
  }
  else if (buttonState1 == 0)
  {
    str = '#' + String(buttonState1);
    Serial.println(str);
    digitalWrite(buz2, HIGH);
    delay(3000);
    digitalWrite(buz2, LOW);
    Serial.println("buz2 is high");
    //call();
  }
  else
  {
    digitalWrite(buz1, LOW);
    digitalWrite(buz2, LOW);
  }

  if (buttonState2 == 0)  // gas
  {
    str = '$' + String(buttonState2);
    Serial.println(str);
    msg = "toxic gases are detected";
    SendMessage();
    delay(5000);
    SendMessage1();
  }
  else if (t > 32)
  {
    str = '%' + String(h);
    Serial.println(str);
    msg = "Temperature increased";
    SendMessage();
    delay(5000);
    SendMessage1();
  }
  else
  {
    digitalWrite(buz1, LOW);
    digitalWrite(buz2, LOW);
  } 
}
void SendMessage()
{
  ss.println("Setting the GSM in text mode");
  ss.println("AT+CMGF=1\r");
  delay(2000);
  ss.println("Sending SMS to the desired phone number!");
  ss.println("AT+CMGS=\"+919390783825\"\r");
  // Replace x with mobile number
  delay(2000);

  ss.println(msg);
  delay(2000);
  ss.write(26);
  Serial.println("DONE..!!");
  delay(3000);
  delay(500);
}
void SendMessage1()
{
  ss.println("Setting the GSM in text mode");
  ss.println("AT+CMGF=1\r");
  delay(2000);
  ss.println("Sending SMS to the desired phone number!");
  ss.println("AT+CMGS=\"+918464927970\"\r");
  // Replace x with mobile number
  delay(2000);

  ss.println(msg);
  delay(2000);
  ss.write(26);
  Serial.println("DONE..!!");
  delay(3000);
  delay(500);
}
