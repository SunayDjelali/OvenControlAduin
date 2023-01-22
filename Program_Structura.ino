//Includes
#include <arduino.h>
#include <max6675.h>
#include <Countimer.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

//Define Display Seting
#define OLED_RESET -1 
#define SCREEN_ADDRESS 0x3C // OLED display Addres
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 32  // OLED display height, in pixels

//Set pin for relay in Array
int RelayPins[] = { 22, 23, 24, 25 };

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

//define Module Termocople connection pins (Digital Pins)
#define thermoSO  9 //Pin on the board SO
#define thermoCS  10 //Pin on the board CS
#define thermoSCK  11 //Pin on the board SCK
int currentTemperatureMAX6675;
//define Text Variables
String strTemperature = "Temperature:";
String strTime =        "Time       :";

//Create object MAX6675 chip, K-type Termocuple 
MAX6675 thermocouple(thermoSCK, thermoCS, thermoSO);

//Create object OLED display, SSD1306 chip
Adafruit_SSD1306 display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//choise what type of timer use from Countimer Class
Countimer tDown;

void setup() {
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
    // Termocuple set pins Mode INPUT
    pinMode(thermoSCK, INPUT);
    pinMode(thermoSO,INPUT);
    pinMode(thermoSCK,INPUT);
    //rottery encoder Timer set pins Mode INPUT
    pinMode(TimerCLK,INPUT);
    pinMode(TimerDT, INPUT);
    pinMode(TimerSW, INPUT);
    //Rottery Encoder Temperatura set pins Mode INPUT
    pinMode(TemperatureCLK,INPUT);
    pinMode(TemperatureDT, INPUT);
    pinMode(TemperatureSW, INPUT);

    //variable = value from pin
    previousTimerCLK = digitalRead(TimerCLK);
    previousTemperatureCLK = digitalRead(TemperatureCLK);

  delay(500);  // wait for MAX chip to stabilize  
}

void loop() {
  //here is main loping runining program go in everi functions one by one
    //funcTimer();
    //funcHeating();
    //func3();
  //Code for Temperature Read parameters from Roterey encoder Temperature
  if (digitalRead(TemperatureSW) == LOW) {
    CounterTemperature = 0;
    choisetTemperature = CounterTemperature;
    OLED_Dispaly();
    tone(Buzzer, 300);
    delay(200);
    noTone(Buzzer);
  }
  //variable = value from pin
  currentTemperatureCLK = digitalRead(TemperatureCLK);

  if (currentTemperatureCLK != previousTemperatureCLK) {
    if (digitalRead(TemperatureDT) != currentTemperatureCLK) {
      CounterTemperature = (CounterTemperature + step);
      choisetTemperature = CounterTemperature;
      tone(Buzzer, 600);
      delay(200);
      noTone(Buzzer);
    } else {
      if (CounterTemperature > 0) {
        CounterTemperature = (CounterTemperature - step);
        choisetTemperature = CounterTemperature;
        tone(Buzzer, 500);
        delay(200);
        noTone(Buzzer);
      } else {
        CounterTemperature = 0;
        tone(Buzzer, 1000);
        delay(1000);
        noTone(Buzzer);
      }
    }
    OLED_Dispaly();
  }

  previousTemperatureCLK = currentTemperatureCLK;

 //Code for Timer Read parameters from Roterey encoder Timer 

     if (digitalRead(TimerSW) == LOW) {
     CounterTimer = 0;
     choisetTemperature = CounterTimer;
     OLED_Dispaly();
     tone(Buzzer, 400);
     delay(300);
     noTone(Buzzer);
   }
   currentTimerCLK = digitalRead(TimerCLK);
   if (currentTimerCLK != previousTimerCLK) {
     if (digitalRead(TimerDT) != currentTimerCLK) {
       CounterTimer = (CounterTimer + step);
       ChoisetTime = CounterTimer;
       tone(Buzzer, 700);
       delay(300);
       noTone(Buzzer);
     } else {
       if (CounterTimer > 0) {
         CounterTimer = (CounterTimer - step);
         ChoisetTime = CounterTimer;
         tone(Buzzer, 600);
         delay(300);
         noTone(Buzzer);
       } else {
         CounterTimer = 0;
         tone(Buzzer, 900);
         delay(1000);
         noTone(Buzzer);
       }
     }
     OLED_Dispaly();
   }
   previousTimerCLK = currentTimerCLK;



}
//At this time i don'tknow work this?
void funcTimer() {
  //functione when pres furst buttone set time conter down
  tDown.setCounter(00, 10, 00, tDown.COUNT_DOWN , tDownComplete);
  //tDown.run();
  //tDown.start();
}
void OLED_Dispaly() {

  display.setTextColor(WHITE);
  display.clearDisplay();//Clearing Display
  display.setTextSize(1);//Font Size
  display.setCursor(0, 0);//Sting posiston cursor
  display.print(strTemperature); //showing Text
  display.print(CounterTemperature);// Showing Variable Value
  display.setCursor(0, 10); //Sting posiston cursor
  display.print("Variable   :"); //showing Text
  display.print(choisetTemperature); //Showing Variable Value
  display.setCursor(0, 20); //Sting posiston cursor
  display.print(strTime);
  display.print(ChoisetTime); //Showing Variable Value
  display.display();

}

void funcHeating() {
  //functione when press second buttone set off teperature
 //Create Variable for temperatore store
  currentTemperatureMAX6675 = (int)thermocouple.readCelsius();
//------------------------------------------------------------------
  //Degree Mark, length=1, position=3 (right)
  //display1.showString("\xB0", 1, 3);
  //display2.showString("\xB0", 1, 3);
  Serial.println(thermocouple.readCelsius());
  // if temprature goes above choiset C, turn the relay ON
    if (thermocouple.readCelsius() > choisetTemperature) {
      digitalWrite(RelayPins[0], HIGH);  // set pin 22 LOW
    } else {
      digitalWrite(RelayPins[0], LOW);  // set pin 22 HIGH
    }
  // For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
  delay(500);

}
//When time is end 00:00 turn off Oven
void tDownComplete()
{
	digitalWrite(RelayPins[0], HIGH);
}