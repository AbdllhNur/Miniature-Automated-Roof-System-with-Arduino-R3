#include <RTClib.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>

RTC_DS3231 rtc;
Adafruit_SSD1306 oled(128, 64, &Wire, 4);
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); 
Servo myservo;

char daysOfTheWeek[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
int Stemp = 50;

void setup() {
  Serial.begin(9600);
  rtc.begin();
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.clearDisplay();
  lcd.init();                      
  lcd.backlight();
  myservo.attach(9);
  pinMode (8 , INPUT);
  pinMode (7 , OUTPUT);
}

void loop() {
    DateTime now = rtc.now();
    oled.clearDisplay();
    oled.drawRect(1, 5, 126, 55, WHITE);
    oled.setTextSize(2);
    oled.setTextColor(WHITE);
    oled.setCursor(16, 20);
    oled.print(now.hour(), DEC);
    oled.print(':');
    oled.print(now.minute(), DEC);
    oled.print(':');
    oled.print(now.second(), DEC);
  
    oled.setTextSize(1);
    oled.setTextColor(WHITE);
    oled.setCursor(17, 40);
    oled.print(daysOfTheWeek[now.dayOfTheWeek()]);
  
    oled.setCursor(62, 40);
    oled.print(now.day(), DEC);
    oled.print('/');
    oled.print(now.month(), DEC);
    oled.print('/');
    oled.print(now.year(), DEC);
    oled.display();
    delay(100);

        
    int digital = digitalRead(8);
    Serial.print(digital);
    Serial.print(",");
    Serial.print(rtc.getTemperature());
    if(digital==0){
      digitalWrite(7, HIGH);
      if(Stemp!=100){
        for(int i = 50;i<=100;i++){
          myservo.write(i);
          delay(60);
        }
      }
      myservo.write(100);
      Stemp = myservo.read();
      digitalWrite(7, LOW);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print ("ATAP TERTUTUP");
      delay(500);
    }
    else{
      digitalWrite(7, LOW);
      if(Stemp!=50){
        for(int i = 100;i>=50;i--){
          myservo.write(i);
          delay(60);
        }
      }
      myservo.write(50);
      Stemp = myservo.read();
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print ("ATAP TERBUKA");
      delay(500);
    }
}
