//Define variables pins e.t.
//Define Rotteri encoder set hronometer
#define TimerCLK    2
#define TimerDT     3
#define TimerSW     4
//Define rottery encoder set temperature

// Module Termocople connection pins (Digital Pins)
int thermoDO = 8;
int thermoCS = 9;
int thermoCLK = 10;
int currentTemperature;
int choisetTemperature;

//Set pin  for relay in arey
int RelayPins[] = { 2, 3, 4, 5 };
//set pin for button rottery encoder
int RottaryPinsButton[] = { 6, 7};

//includes
#include <arduino.h>
#include <max6675.h>
#include <Countimer.h>

//Code for Termocuple
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

//choise what type of timer use from Countimer Class
Countimer tDown;

void setup() {
    //Setings Here pins mode OUTPUT, INPUTS
    //OUTPUT
    for (int i = 0; i < 4; i++) {
      pinMode(RelayPins[i], OUTPUT);
      digitalWrite(RelayPins[i], HIGH);
    }
    //INPUT
    for (int i = 0; i < 2; i++)
    {
      pinMode(RottaryPinsButton[i], INPUT);
    }
  delay(500);  // wait for MAX chip to stabilize  
}

void loop() {
  //here is main loping runining program go in everi functions one by one
    funcTimer();
    funcHeating();
    func3();
}

void funcTimer() {
  //functione when pres furst buttone set time conter down
  
  tDown.setCounter(00, 10, 00, tDown.COUNT_DOWN , tDownComplete);
  tDown.run();
  tDown.start();
}

void funcHeating() {
  //functione when press second buttone set off teperature
 //Create Variable for temperatore store
  currentTemperature = (int)thermocouple.readCelsius();
//------------------------------------------------------------------
  // Degree Mark, length=1, position=3 (right)
  //display1.showString("\xB0", 1, 3);
  //display2.showString("\xB0", 1, 3);
  // Number, length=3, position=0 (left)
  //display1.showNumber(temp, false, 3, 0);
  //display2.showNumber(temp, false, 3, 0);
  // Code for display end
  Serial.println(thermocouple.readCelsius());
  // if temprature goes above 27.0C, turn the relay ON

    if (thermocouple.readCelsius() > choisetTemperature) {
      digitalWrite(RelayPins[0], HIGH);  // set pin 10 LOW
    } else {
      digitalWrite(RelayPins[0], LOW);  // set pin 10 HIGH
    }
  // For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
  delay(3000);

}

void func3() {
  //main Functione where the run
  //read temperature and show on the display
  //Show set value of timer blinking 
  //turn on heating by relay to the chosen temperatura
  //run conterdown timer by triger
  //when conterdown time is 00:00 heating off
  delay(400);
}
void tDownComplete()
{
	digitalWrite(13, HIGH);
}