// ------------------------- LIBRARIES
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
#include <PID.h>
#include "menu.h"

#define RELAY_PIN 7

// temperature sensor
#define ONE_WIRE_BUS 9  //pin som sensorn sitter p
#define TEMPERATURE_PRECISION 9
#define SAMPLE_DELAY 5000
#define OUTPUT_TO_SERIAL true


OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensor(&oneWire);
DeviceAddress TempAddress;



//Set up LCD
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

//Pushbutton related set up
const int buttonPlusPin = 12;
const int buttonMinusPin = 11;
const int backLight = 8;          // pin 13 will control the backlight
int buttonPlusState = 0;          // variable for reading the pushbutton status
int buttonMinusState = 0;         // variable for reading the pushbutton status

//Start temperature
int temp = 53;
  
//Define Variables we'll be connecting to and specify the links and initial tuning parameters
double Setpoint, Input, Output;
PID myPID(&Input, &Output, &Setpoint,2,5,1, DIRECT);
int WindowSize = 5000;
unsigned long windowStartTime;


void setup()
{
  /*---Init LCD---*/
  pinMode(backLight, HIGH);
  digitalWrite(backLight, HIGH);  // turn backlight on. Replace 'HIGH' with 'LOW' to turn it off.
  lcd.begin(16,2);                // columns, rows.  use 16,2 for a 16x2 LCD, etc.
  lcd.clear();                    // start with a blank screen
  lcd.setCursor(0,0);             // set cursor to column 0, row 0 (the first row)
  lcd.print("Sous Vide");         // change this text to whatever you like. keep it clean.
  lcd.setCursor(0,1);             // set cursor to column 0, row 1
  lcd.print("Set Temp: "+temp);     
  pinMode(buttonPlusPin, INPUT);
  pinMode(buttonMinusPin, INPUT);
  
  /*--- Init Temperature Sensor---*/
  sensor.begin();
  delay(1000);   
  sensor.getAddress(TempAddress, 0);  
  delay(1000);   
  sensor.requestTemperaturesByIndex(0); // Send the command to get temperatures
  delay(1000);

  /*---Read temperature---*/
  double actualTemp =  sensor.getTempC(TempAddress);  

  //prepare Relay port for writing
  pinMode(RELAY_PIN, OUTPUT);  
  digitalWrite(RELAY_PIN,LOW);




  windowStartTime = millis();

  //initialize the variables we're linked to
  Setpoint = 100;

  //tell the PID to range between 0 and the full window size
  myPID.SetOutputLimits(0, WindowSize);

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

void loop()
{
  sensor.requestTemperaturesByIndex(0);
  Input = sensor.getTempC(TempAddress);
  myPID.Compute();
  
  if(digitalRead(buttonMinusPin)) enter_meny();
  
  
  /************************************************
   * turn the output pin on/off based on pid output
   ************************************************/
  unsigned long now = millis();
  if(now - windowStartTime>WindowSize)
  { //time to shift the Relay Window
    windowStartTime += WindowSize;
  }
  if(Output > now - windowStartTime) digitalWrite(RELAY_PIN,HIGH);
  else digitalWrite(RELAY_PIN,LOW);

}

void display_params(){
  lcd.setCursor(0,0);
  lcd.print("Parameters: ");
  lcd.setCursor(0,1);
  lcd.print("P: ");
  lcd.print(myPID.GetKp());
  lcd.print(" I: ");
  lcd.print(myPID.GetKi());
  lcd.print(" D: ");
  lcd.print(myPID.GetKd());
}


void set_temp(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set temp");
}

void enter_meny(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Meny");
}
