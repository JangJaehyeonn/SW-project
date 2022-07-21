#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "DHT.h"
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int redPin = 9;
int greenPin = 10;
int bluePin = 11;
int reading;
int temp;
int AA= 2;
int AB= 3;

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(AA, OUTPUT);
  pinMode(AB, OUTPUT);
  dht.begin();
  lcd.init();
  lcd.clear();
  lcd.backlight();
}

void loop() {
  
  DHT11_code();
  Moi_code();
  CDS_code();
  delay(5000);
 }

void DHT11_code() {  //온습도 센서 코드
  int h = dht.readHumidity();  //습도
  int t = dht.readTemperature();  //온도
  lcd.setCursor(0, 0);
  lcd.print("H:");
  lcd.setCursor(3, 0);
  lcd.print(h);   //습도출력
  lcd.setCursor(5, 0);
  lcd.print("%");
  lcd.setCursor(8, 0);
  lcd.print("T:"); 
  lcd.setCursor(11, 0);
  lcd.print(t);   //온도출력
  lcd.setCursor(13, 0);
  lcd.print("'C");
}

int moi = 0;
void Moi_code() {   //수분센서 코드
  moi = analogRead(A0);
  lcd.setCursor(0, 1);
  lcd.print("M:");
  lcd.setCursor(3, 1);
  lcd.print(moi);
  if (moi < 200) {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(AA, HIGH);   //정방향으로 모터회전
    digitalWrite(AB, LOW);
    delay(5000);
  }
  else {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(AA, LOW);  //모터 정지
    digitalWrite(AB, LOW);  
    delay(5000);
 
  } 
}

int CDS = 0;
void CDS_code() { //CDS조도 센서 코드
  CDS = analogRead(A1);
  lcd.setCursor(8, 1);
  lcd.print("B:");
  lcd.setCursor(11, 1);
  lcd.print(CDS);
}
