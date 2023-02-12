# 1 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino"
//Includes
# 3 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino" 2
# 4 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino" 2

# 6 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino" 2
# 7 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino" 2
# 8 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino" 2


//Define SSD1309 ZJY_M242'OLED display connected using software SPI case
# 19 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino"
//Create object OLED display, SSD1306 chip
Adafruit_SSD1306 display(128 /* OLED display width, in pixels*/, 64 /* OLED display height, in pixels*/,
 28, 29, 30, 32, 31);


//Set pin for relay in Array
int RelayPins[] = { 22, 23, 24, 25 };

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


//define Module Termocople connection pins (Digital Pins)



int currentTemperatureMAX6675;

//define Text Variables
String strTemperature = "Temperature:";
String strTime = "Time       :";

//Create object MAX6675 chip, K-type Termocuple 
MAX6675 thermocouple(11 /*Pin on the board SCK*/, 10 /*Pin on the board CS*/, 9 /*Pin on the board SO*/);


//choise what type of timer use from Countimer Class




static const unsigned char 
# 73 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino" 3
                          __attribute__((__progmem__)) 
# 73 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino"
                                  logo_bmp[] =
{ 0b00000000, 0b11000000,
  0b00000001, 0b11000000,
  0b00000001, 0b11000000,
  0b00000011, 0b11100000,
  0b11110011, 0b11100000,
  0b11111110, 0b11111000,
  0b01111110, 0b11111111,
  0b00110011, 0b10011111,
  0b00011111, 0b11111100,
  0b00001101, 0b01110000,
  0b00011011, 0b10100000,
  0b00111111, 0b11100000,
  0b00111111, 0b11110000,
  0b01111100, 0b11110000,
  0b01110000, 0b01110000,
  0b00000000, 0b00110000 };

void setup() {
   Serial.begin(9600);
   // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
   if(!display.begin(0x02 /*|< Gen. display voltage from 3.3V*/)) {
    Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 95 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino" 3
                  (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 95 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino"
                  "SSD1306 allocation failed"
# 95 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino" 3
                  ); &__c[0];}))
# 95 "d:\\Documents\\Arduino\\OvenControlArduino\\OvenControlArduino.ino"
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
    // Termocuple set pins Mode INPUT
    pinMode(11 /*Pin on the board SCK*/, 0x0);
    pinMode(9 /*Pin on the board SO*/, 0x0);
    pinMode(11 /*Pin on the board SCK*/, 0x0);
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

  delay(500); // wait for MAX chip to stabilize  
}

void loop() {
  //here is main loping runining program go in everi functions one by one
    //funcTimer();
    //funcHeating();
    //func3();
  //Code for Temperature Read parameters from Roterey encoder Temperature
  if (digitalRead(InputPinsButton[1] /*Pin on the board Switch button*/) == 0x0) {
    CounterTemperature = 0;
    choisetTemperature = CounterTemperature;
    OLED_Dispaly();
    tone(8 /* Pin on the board piezobuzer +*/, 300);
    delay(200);
    noTone(8 /* Pin on the board piezobuzer +*/);
  }
  //variable = value from pin
  currentTemperatureCLK = digitalRead(5 /*Pin on the board clockwise detection*/);

  if (currentTemperatureCLK != previousTemperatureCLK) {
    if (digitalRead(6 /*Pin on the board counter clockwise detection*/) != currentTemperatureCLK) {
      CounterTemperature = (CounterTemperature + 10);
      choisetTemperature = CounterTemperature;
      tone(8 /* Pin on the board piezobuzer +*/, 600);
      delay(200);
      noTone(8 /* Pin on the board piezobuzer +*/);
    } else {
      if (CounterTemperature > 0) {
        CounterTemperature = (CounterTemperature - 10);
        choisetTemperature = CounterTemperature;
        tone(8 /* Pin on the board piezobuzer +*/, 500);
        delay(200);
        noTone(8 /* Pin on the board piezobuzer +*/);
      } else {
        CounterTemperature = 0;
        tone(8 /* Pin on the board piezobuzer +*/, 1000);
        delay(500);
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
     delay(300);
     noTone(8 /* Pin on the board piezobuzer +*/);
   }
   currentTimerCLK = digitalRead(2 /*Pin on the boardclockwise detection*/);
   if (currentTimerCLK != previousTimerCLK) {
     if (digitalRead(3 /*Pin on the board counter clockwise detection*/) != currentTimerCLK) {
       CounterTimer = (CounterTimer + 10);
       ChoisetTime = CounterTimer;
       tone(8 /* Pin on the board piezobuzer +*/, 700);
       delay(300);
       noTone(8 /* Pin on the board piezobuzer +*/);
     } else {
       if (CounterTimer > 0) {
         CounterTimer = (CounterTimer - 10);
         ChoisetTime = CounterTimer;
         tone(8 /* Pin on the board piezobuzer +*/, 600);
         delay(300);
         noTone(8 /* Pin on the board piezobuzer +*/);
       } else {
         CounterTimer = 0;
         tone(8 /* Pin on the board piezobuzer +*/, 900);
         delay(500);
         noTone(8 /* Pin on the board piezobuzer +*/);
       }
     }
     OLED_Dispaly();
   }
   previousTimerCLK = currentTimerCLK;



}
//At this time i don'tknow work this?

void OLED_Dispaly() {

  display.setTextColor(1 /*|< Draw 'on' pixels*/ /*|< Draw 'on' pixels*/);
  display.clearDisplay();//Clearing Display
  display.setTextSize(1);//Font Size
  display.setTextColor(1 /*|< Draw 'on' pixels*/);
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
  delay(500);

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
      digitalWrite(RelayPins[0], 0x1); // set pin 22 LOW
    } else {
      digitalWrite(RelayPins[0], 0x0); // set pin 22 HIGH
    }
  // For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
  delay(100);

}
//When time is end 00:00 turn off Oven
