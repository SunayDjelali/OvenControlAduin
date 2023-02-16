//Includes
#include <arduino.h>
#include <max6675.h>  //forthermo cople
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

//Define SSD1309 ZJY_M242'OLED display pixels
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

//Define SSD1309 ZJY_M242'OLED display connected Pins using software SPI case
#define OLED_SDA 28
#define OLED_SCL 30
#define OLED_DC 24
#define OLED_CS 22
#define OLED_RES 26

//define Module Termocople connection pins (Digital Pins)
#define thermoSO 9    //Pin on the board SO
#define thermoCS 10   //Pin on the board CS
#define thermoSCK 11  //Pin on the board SCK
int currentTemperatureMAX6675;

//Set pin for relay in Array
int RelayPins[] = { 23, 25, 27, 29 };

//Set pin for button rottery encoder in Array (Digital Pins)
int InputPinsButton[] = { 4, 7 };

//Define Rotteri encoder set hronometer (Digital Pins)
#define TimerCLK 2                  //Pin on the boardclockwise detection
#define TimerDT 3                   //Pin on the board counter clockwise detection
#define TimerSW InputPinsButton[0]  //Pin on the board Switch button

int CounterTimer = 0;  //Variable countering Timer and Set Value
int currentTimerCLK;   //Variable cureent countering  value Timer
int previousTimerCLK;  //Variable for previous value

// ? Variable for choise timer ? what taype ? how many variables ? i don't know at this stage
int ChoisetTime;

//Define rottery encoder set temperature (Digital Pins)
#define TemperatureCLK 5                  //Pin on the board clockwise detection
#define TemperatureDT 6                   //Pin on the board counter clockwise detection
#define TemperatureSW InputPinsButton[1]  //Pin on the board Switch button

int CounterTemperature = 0;  //Variable countering temperature and Set Value
int currentTemperatureCLK;   //Variable cureent countering  value temperature
int previousTemperatureCLK;  //Variable for previous value temperature
int choisetTemperature;      //Variable for Need temperature

//define Pin for the Piezo buzer
#define Buzzer 8  // Pin on the board piezobuzer +

//Increase or decrease setting value ie. step
#define step 10

//define Text Variables
String strTemperature = "Temperature:";
String strTime = "Time       :";

//Create object OLED display, SSD1306 chip
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         OLED_SDA, OLED_SCL, OLED_DC, OLED_RES, OLED_CS);

//Create object MAX6675 chip, K-type Termocuple
MAX6675 thermocouple(thermoSCK, thermoCS, thermoSO);

//choise what type of timer use from Countimer Class


void setup() {
  Serial.begin(9600);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }
  //Setings Here pins mode OUTPUT, INPUTS

  //OUTPUT General ordinary
  for (int i = 0; i < 4; i++) {
    pinMode(RelayPins[i], OUTPUT);
    digitalWrite(RelayPins[i], HIGH);
  }
  //INPUT Generaly General ordinary
  for (int i = 0; i < 2; i++) {
    pinMode(InputPinsButton[i], INPUT);
  }

  //rottery encoder Timer set pins Mode INPUT
  pinMode(TimerCLK, INPUT);
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


  //Code for Temperature Read parameters from Roterey encoder Temperature
  if (digitalRead(TemperatureSW) == LOW) {
    CounterTemperature = 0;
    choisetTemperature = CounterTemperature;
    OLED_Dispaly();
  }
  currentTemperatureCLK = digitalRead(TemperatureCLK);

  if (currentTemperatureCLK != previousTemperatureCLK) {
    if (digitalRead(TemperatureDT) != currentTemperatureCLK) {
      CounterTemperature = (CounterTemperature + step);
      choisetTemperature = CounterTemperature;
    } else {
      if (CounterTemperature > 0) {
        CounterTemperature = (CounterTemperature - step);
        choisetTemperature = CounterTemperature;
      } else {
        CounterTemperature = 0;
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
  }
  currentTimerCLK = digitalRead(TimerCLK);
  if (currentTimerCLK != previousTimerCLK) {
    if (digitalRead(TimerDT) != currentTimerCLK) {
      CounterTimer = (CounterTimer + step);
      ChoisetTime = CounterTimer;
    } else {
      if (CounterTimer > 0) {
        CounterTimer = (CounterTimer - step);
        ChoisetTime = CounterTimer;
      } else {
        CounterTimer = 0;
      }
    }
    OLED_Dispaly();
  }
  previousTimerCLK = currentTimerCLK;
  MainScreen();
}

//Operating parameters setting screen
void OLED_Dispaly() {
  display.clearDisplay();  //Clearing Display
  display.setTextColor(WHITE);
  display.setTextSize(1);    //Font Size
  display.setCursor(20, 0);  //Sting posiston cursor
  display.print("S E T U P");
  display.setCursor(0, 10);
  display.print("---------------------");
  display.setCursor(0, 20);           //Sting posiston cursor
  display.print(strTemperature);      //showing Text
  display.print(CounterTemperature);  // Showing Variable Value
  display.setCursor(0, 30);           //Sting posiston cursor
  display.print("Variable   :");      //showing Text
  display.print(choisetTemperature);  //Showing Variable Value
  display.setCursor(0, 40);           //Sting posiston cursor
  display.print(strTime);
  display.print(ChoisetTime);  //Showing Variable Value
  display.setCursor(0, 50);    //Sting posiston cursor
  display.print(currentTemperatureMAX6675);
  display.print(F(" C"));
  display.display();
  delay(1000);
}
//MainScreen
void MainScreen() {
  currentTemperatureMAX6675 = (int)thermocouple.readCelsius();
  //Serial.println(thermocouple.readCelsius());
  //Serial.println(currentTemperatureMAX6675);
  display.clearDisplay();
  display.setTextSize(1);       // Normal 1:1 pixel scale
  display.setTextColor(WHITE);  // Draw white text
  display.setCursor(0, 0);      // Start at top-left corner
  display.print(F("temperatura :"));
  display.print(currentTemperatureMAX6675);
  display.print(F(" C"));
  display.display();
  display.clearDisplay();
  delay(500);
  //OLED_Dispaly();
}
//When time is end 00:00 turn off Oven
