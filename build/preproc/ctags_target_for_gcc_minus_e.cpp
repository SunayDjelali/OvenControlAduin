# 1 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino"
//Includes
# 3 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino" 2
# 4 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino" 2
# 5 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino" 2
# 6 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino" 2
# 7 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino" 2


//Define SSD1309 ZJY_M242'OLED display connected using software SPI case
# 18 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino"
//Create object OLED display, SSD1306 chip
Adafruit_SSD1306 display(128 /* OLED display width, in pixels*/, 64 /* OLED display height, in pixels*/,
 28, 30, 24, 26, 22);

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



int CounterTimer = 0; //Variable countering Timer
int currentTimerCLK; //Variable cureent countering  value Timer
int previousTimerCLK; //Variable for previous value
// ? Variable for choise timer ? what taype ? how many variables ? i don't know at this stage
int ChoisetTime;

//Define rottery encoder set temperature (Digital Pins)



int CounterTemperature = 0; //Variable countering temperature
int currentTemperatureCLK; //Variable cureent countering  value temperature
int previousTemperatureCLK; //Variable for previous value temperature
int choisetTemperature; //Variable for Need temperature

//define Pin for the Piezo buzer  

//Increase or decrease setting value ie. step 



//define Text Variables
String strTemperature = "Temperature:";
String strTime = "Time       :";

//choise what type of timer use from Countimer Class


void setup() {
   Serial.begin(9600);
   // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
   if(!display.begin(0x02 /*|< Gen. display voltage from 3.3V*/)) {
    Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 74 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino" 3
                  (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 74 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino"
                  "SSD1306 allocation failed"
# 74 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino" 3
                  ); &__c[0];}))
# 74 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino"
                  )));
    for(;;); // Don't proceed, loop forever
  }
    //Setings Here pins mode OUTPUT, INPUTS

    //OUTPUT General ordinary
    for (int i = 0; i < 4; i++) {
      pinMode(RelayPins[i], 0x1);
      digitalWrite(RelayPins[i], 0x1);
    }
    //INPUT Generaly General ordinary
    for (int i = 0; i < 2; i++)
    {
      pinMode(InputPinsButton[i], 0x0);
    }

    //rottery encoder Timer set pins Mode INPUT
    pinMode(2 /*Pin on the boardclockwise detection*/,0x0);
    pinMode(3 /*Pin on the board counter clockwise detection*/, 0x0);
    pinMode(InputPinsButton[0] /*Pin on the board Switch button*/, 0x0);
    //Rottery Encoder Temperatura set pins Mode INPUT
    pinMode(5 /*Pin on the board clockwise detection*/, 0x0);
    pinMode(6 /*Pin on the board counter clockwise detection*/, 0x0);
    pinMode(InputPinsButton[1] /*Pin on the board Switch button*/, 0x0);

    display.clearDisplay();
    //variable = value from pin
    previousTimerCLK = digitalRead(2 /*Pin on the boardclockwise detection*/);
    previousTemperatureCLK = digitalRead(5 /*Pin on the board clockwise detection*/);


}

void loop() {
  //here is main loping runining program go in everi functions one by one
    //funcTimer();
    funcHeating();
    //func3();
  //Code for Temperature Read parameters from Roterey encoder Temperature
  if (digitalRead(InputPinsButton[1] /*Pin on the board Switch button*/) == 0x0) {
    CounterTemperature = 0;
    choisetTemperature = CounterTemperature;
    OLED_Dispaly();
    tone(8 /* Pin on the board piezobuzer +*/, 300);
    delay(100);
    noTone(8 /* Pin on the board piezobuzer +*/);
  }
  //variable = value from pin
  currentTemperatureCLK = digitalRead(5 /*Pin on the board clockwise detection*/);

  if (currentTemperatureCLK != previousTemperatureCLK) {
    if (digitalRead(6 /*Pin on the board counter clockwise detection*/) != currentTemperatureCLK) {
      CounterTemperature = (CounterTemperature + 10);
      choisetTemperature = CounterTemperature;
      tone(8 /* Pin on the board piezobuzer +*/, 600);
      delay(100);
      noTone(8 /* Pin on the board piezobuzer +*/);
    } else {
      if (CounterTemperature > 0) {
        CounterTemperature = (CounterTemperature - 10);
        choisetTemperature = CounterTemperature;
        tone(8 /* Pin on the board piezobuzer +*/, 500);
        delay(100);
        noTone(8 /* Pin on the board piezobuzer +*/);
      } else {
        CounterTemperature = 0;
        tone(8 /* Pin on the board piezobuzer +*/, 1000);
        delay(100);
        noTone(8 /* Pin on the board piezobuzer +*/);
      }
    }
    OLED_Dispaly();
  }
  previousTemperatureCLK = currentTemperatureCLK;

 //Code for Timer Read parameters from Roterey encoder Timer 
     if (digitalRead(InputPinsButton[0] /*Pin on the board Switch button*/) == 0x0) {
     CounterTimer = 0;
     ChoisetTime = CounterTimer;
     OLED_Dispaly();
     tone(8 /* Pin on the board piezobuzer +*/, 400);
     delay(100);
     noTone(8 /* Pin on the board piezobuzer +*/);
   }
   currentTimerCLK = digitalRead(2 /*Pin on the boardclockwise detection*/);
   if (currentTimerCLK != previousTimerCLK) {
     if (digitalRead(3 /*Pin on the board counter clockwise detection*/) != currentTimerCLK) {
       CounterTimer = (CounterTimer + 10);
       ChoisetTime = CounterTimer;
       tone(8 /* Pin on the board piezobuzer +*/, 700);
       delay(100);
       noTone(8 /* Pin on the board piezobuzer +*/);
     } else {
       if (CounterTimer > 0) {
         CounterTimer = (CounterTimer - 10);
         ChoisetTime = CounterTimer;
         tone(8 /* Pin on the board piezobuzer +*/, 600);
         delay(100);
         noTone(8 /* Pin on the board piezobuzer +*/);
       } else {
         CounterTimer = 0;
         tone(8 /* Pin on the board piezobuzer +*/, 900);
         delay(100);
         noTone(8 /* Pin on the board piezobuzer +*/);
       }
     }

     OLED_Dispaly();
   }
   previousTimerCLK = currentTimerCLK;

}
//At this time i don'tknow work this?

void OLED_Dispaly(void) {
  display.clearDisplay();//Clearing Display
  display.setTextColor(1 /*|< Draw 'on' pixels*/ /*|< Draw 'on' pixels*/);
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
  display.print((reinterpret_cast<const __FlashStringHelper *>(
# 207 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 207 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino"
               " C"
# 207 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino" 3
               ); &__c[0];}))
# 207 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino"
               )));
  display.display();
  delay(1000);
}

void funcHeating(void) {
 currentTemperatureMAX6675 = (int)thermocouple.readCelsius();
 //Serial.println(thermocouple.readCelsius());
 //Serial.println(currentTemperatureMAX6675);
  display.clearDisplay();
  display.setTextSize(1); // Normal 1:1 pixel scale
  display.setTextColor(1 /*|< Draw 'on' pixels*/ /*|< Draw 'on' pixels*/); // Draw white text
  display.setCursor(0, 0); // Start at top-left corner
  display.print((reinterpret_cast<const __FlashStringHelper *>(
# 220 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 220 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino"
               "temperatura :"
# 220 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino" 3
               ); &__c[0];}))
# 220 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino"
               )));
  display.print(currentTemperatureMAX6675);
  display.print((reinterpret_cast<const __FlashStringHelper *>(
# 222 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino" 3
               (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 222 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino"
               " C"
# 222 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino" 3
               ); &__c[0];}))
# 222 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino"
               )));
  display.display();
  display.clearDisplay();
  delay(1000);
//OLED_Dispaly();
}
//When time is end 00:00 turn off Oven
