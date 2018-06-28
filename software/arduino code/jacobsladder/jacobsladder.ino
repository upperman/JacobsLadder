#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#include "ErrorHandler.h"
#include "ErrorScanning.h"
#include "NeoPixelControl.h"

#define ErrorLed 2 //This value is the digital port for the error led
#define ActivationButton 4 //This value is the digital port for the pushbutton that will activate the HV line
#define NeoLED 6 //defines which line the neopixels are on
#define HVRelay 8  //This value is the digital port assigned to the relay that activates the HV
#define AC_current A0 // this line reads the current in the 120V side
#define DC_Input_Voltage A1

#define NUMPIXELS 16 //The number of neopixels I am going to drive
#define CurrentMax 3.7 //Maximum current detected before an error occurs
#define VoltageMin 4.7 //minimum input voltage allowed
#define Volt_Ref 5.0 //analog voltage reference value Volt_Ref/1023= volt/ADC_Val
#define DelayVal 500 //delay value for ladder before it turns off

/*Prototypes*/
void MyErrorHandler();
int InputVoltageScanner();



void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);          //  setup serial
  pinMode(ActivationButton, INPUT); //Defines the ActivationButton as an input
  pinMode(HVRelay, OUTPUT);  //Defines the HVRelay as an output
  digitalWrite(HVRelay,0); //Initilizing the state for the HVRelay (off)
  pinMode(ErrorLed, OUTPUT); //Defines the ErrorLed as an output
  digitalWrite(ErrorLed,0); //Initializing the state for the ErrorLed (off)
}

void loop() 
{
  int ActivationVar=0; //Defines a variable to activate the HV
  StartProgram(ActivationVar); //sends the activation variable to the StartProgram
}

void StartProgram(int ActivationVar)
{
  int ErrorVal = 0;
  int counter=0;
  ErrorVal=InputVoltageScanner();
  MyErrorHandler(ErrorVal);
  ActivationVar = digitalRead(ActivationButton);
  Serial.println("The Error Code:");
  Serial.println(ActivationVar);
  if (ActivationVar==1)
  {
    ActivationVar = 0;
    digitalWrite(HVRelay,1);
    while (counter < 50)
    {
     ErrorVal = CurrentScanner();
     ErrorVal = InputVoltageScanner();
     MyErrorHandler(ErrorVal);
     counter++;
     Serial.println("The Error Code:");
     Serial.println(ErrorVal);
     MyErrorHandler(ErrorVal);
     delay(100);
    }
    digitalWrite(HVRelay,0);
  }     
}

