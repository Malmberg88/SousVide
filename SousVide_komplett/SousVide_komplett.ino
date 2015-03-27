// ------------------------- LIBRARIES
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
#include <PID.h>

#define RELAY_PIN 7

// temperature sensor
#define ONE_WIRE_BUS 9  //pin som sensorn sitter p
#define TEMPERATURE_PRECISION 9
#define SAMPLE_DELAY 5000
#define OUTPUT_TO_SERIAL true


OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensor(&oneWire);
DeviceAddress TempAddress;

//Define Variables we'll be connecting to and specify the links and initial tuning parameters
double Setpoint, Input, Output;
PID myPID(&Input, &Output, &Setpoint,2,5,1, DIRECT);
int WindowSize = 5000;
unsigned long windowStartTime;


void setup()
{
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
  Input = analogRead(0);
  myPID.Compute();
  
  
  
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

void displayParams(){
  lcd.setCursor(0,0);
  lcd.print("Parameters: ");
  lcd.setCursor(0,1);
  lcd.print("P: "+myPID.GetKp()+" I: "+myPID.GetKi()+" D: "+myPID.GetKd());
}
