#include <Arduino.h>
#line 1 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino"
//Includes
#include <arduino.h>
#include <max6675.h>//forthermo cople
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

//Define SSD1309 ZJY_M242'OLED display connected using software SPI case
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

#define OLED_SDA 28
#define OLED_SCL 30
#define OLED_DC  24
#define OLED_CS  22
#define OLED_RES 26
//Create object OLED display, SSD1306 chip
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
 OLED_SDA, OLED_SCL, OLED_DC, OLED_RES, OLED_CS);

//define Module Termocople connection pins (Digital Pins)
int thermoSO = 9; //Pin on the board SO
int thermoCS = 10; //Pin on the board CS
int thermoSCK = 11; //Pin on the board SCK
int currentTemperatureMAX6675;

//Create object MAX6675 chip, K-type Termocuple 
MAX6675 thermocouple(thermoSCK, thermoCS, thermoSO);


//Set pin for relay in Array
int RelayPins[] = { 23, 25, 27, 29 };

//Set pin for button rottery encoder in Array (Digital Pins)
int InputPinsButton[] = { 4, 7};

//Define Rotteri encoder set hronometer (Digital Pins)
#define TimerCLK    2 //Pin on the boardclockwise detection
#define TimerDT     3 //Pin on the board counter clockwise detection
#define TimerSW     InputPinsButton[0] //Pin on the board Switch button
int CounterTimer = 0; //Variable countering Timer
int currentTimerCLK;  //Variable cureent countering  value Timer
int previousTimerCLK; //Variable for previous value
// ? Variable for choise timer ? what taype ? how many variables ? i don't know at this stage
int ChoisetTime;

//Define rottery encoder set temperature (Digital Pins)
#define TemperatureCLK    5 //Pin on the board clockwise detection
#define TemperatureDT     6 //Pin on the board counter clockwise detection
#define TemperatureSW     InputPinsButton[1] //Pin on the board Switch button
int CounterTemperature = 0; //Variable countering temperature
int currentTemperatureCLK;  //Variable cureent countering  value temperature
int previousTemperatureCLK; //Variable for previous value temperature
int choisetTemperature;    //Variable for Need temperature

//define Pin for the Piezo buzer  
#define Buzzer 8 // Pin on the board piezobuzer +
//Increase or decrease setting value ie. step 
#define step 10 


//define Text Variables
String strTemperature = "Temperature:";
String strTime =        "Time       :";

//choise what type of timer use from Countimer Class


#line 70 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino"
void setup();
#line 107 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino"
void loop();
#line 188 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino"
void OLED_Dispaly(void);
#line 212 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino"
void funcHeating(void);
#line 70 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino"
void setup() {
   Serial.begin(9600);
   // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
   if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
    //Setings Here pins mode OUTPUT, INPUTS

    //OUTPUT General ordinary
    for (int i = 0; i < 4; i++) {
      pinMode(RelayPins[i], OUTPUT);
      digitalWrite(RelayPins[i], HIGH);
    }
    //INPUT Generaly General ordinary
    for (int i = 0; i < 2; i++)
    {
      pinMode(InputPinsButton[i], INPUT);
    }

    //rottery encoder Timer set pins Mode INPUT
    pinMode(TimerCLK,INPUT);
    pinMode(TimerDT, INPUT);
    pinMode(TimerSW, INPUT);
    //Rottery Encoder Temperatura set pins Mode INPUT
    pinMode(TemperatureCLK, INPUT);
    pinMode(TemperatureDT, INPUT);
    pinMode(TemperatureSW, INPUT);

    display.clearDisplay();
    //variable = value from pin
    previousTimerCLK = digitalRead(TimerCLK);
    previousTemperatureCLK = digitalRead(TemperatureCLK);

  
}

void loop() {
  //here is main loping runining program go in everi functions one by one
    //funcTimer();
    funcHeating();
    //func3();
  //Code for Temperature Read parameters from Roterey encoder Temperature
  if (digitalRead(TemperatureSW) == LOW) {
    CounterTemperature = 0;
    choisetTemperature = CounterTemperature;
    OLED_Dispaly();
    tone(Buzzer, 300);
    delay(100);
    noTone(Buzzer);
  }
  //variable = value from pin
  currentTemperatureCLK = digitalRead(TemperatureCLK);

  if (currentTemperatureCLK != previousTemperatureCLK) {
    if (digitalRead(TemperatureDT) != currentTemperatureCLK) {
      CounterTemperature = (CounterTemperature + step);
      choisetTemperature = CounterTemperature;
      tone(Buzzer, 600);
      delay(100);
      noTone(Buzzer);
    } else {
      if (CounterTemperature > 0) {
        CounterTemperature = (CounterTemperature - step);
        choisetTemperature = CounterTemperature;
        tone(Buzzer, 500);
        delay(100);
        noTone(Buzzer);
      } else {
        CounterTemperature = 0;
        tone(Buzzer, 1000);
        delay(100);
        noTone(Buzzer);
      }
    }   
    OLED_Dispaly();
  }
  previousTemperatureCLK = currentTemperatureCLK;

 //Code for Timer Read parameters from Roterey encoder Timer 
     if (digitalRead(TimerSW) == LOW) {
     CounterTimer = 0;
     ChoisetTime = CounterTimer;
     OLED_Dispaly();
     tone(Buzzer, 400);
     delay(100);
     noTone(Buzzer);
   }
   currentTimerCLK = digitalRead(TimerCLK);
   if (currentTimerCLK != previousTimerCLK) {
     if (digitalRead(TimerDT) != currentTimerCLK) {
       CounterTimer = (CounterTimer + step);
       ChoisetTime = CounterTimer;
       tone(Buzzer, 700);
       delay(100);
       noTone(Buzzer);
     } else {
       if (CounterTimer > 0) {
         CounterTimer = (CounterTimer - step);
         ChoisetTime = CounterTimer;
         tone(Buzzer, 600);
         delay(100);
         noTone(Buzzer);
       } else {
         CounterTimer = 0;
         tone(Buzzer, 900);
         delay(100);
         noTone(Buzzer);
       }
     }
    
     OLED_Dispaly();
   }
   previousTimerCLK = currentTimerCLK;

}
//At this time i don'tknow work this?

void OLED_Dispaly(void) {
  display.clearDisplay();//Clearing Display
  display.setTextColor(WHITE);
  display.setTextSize(1);//Font Size
  display.setCursor(20, 0);//Sting posiston cursor
  display.print("S E T U P");
  display.setCursor(0, 10);
  display.print("---------------------");
  display.setCursor(0, 20);//Sting posiston cursor
  display.print(strTemperature); //showing Text
  display.print(CounterTemperature);// Showing Variable Value
  display.setCursor(0, 30); //Sting posiston cursor
  display.print("Variable   :"); //showing Text
  display.print(choisetTemperature); //Showing Variable Value
  display.setCursor(0, 40); //Sting posiston cursor
  display.print(strTime);
  display.print(ChoisetTime); //Showing Variable Value
  display.setCursor(0, 50); //Sting posiston cursor
  display.print(currentTemperatureMAX6675);
  display.print(F(" C"));
  display.display();
  delay(1000);
}

void funcHeating(void) {
 currentTemperatureMAX6675 = (int)thermocouple.readCelsius();
 //Serial.println(thermocouple.readCelsius());
 //Serial.println(currentTemperatureMAX6675);
  display.clearDisplay();
  display.setTextSize(1);               // Normal 1:1 pixel scale
  display.setTextColor(WHITE);  // Draw white text
  display.setCursor(0, 0);              // Start at top-left corner
  display.print(F("temperatura :"));
  display.print(currentTemperatureMAX6675);
  display.print(F(" C"));
  display.display();
  display.clearDisplay();
  delay(1000);
//OLED_Dispaly();
}
//When time is end 00:00 turn off Oven

