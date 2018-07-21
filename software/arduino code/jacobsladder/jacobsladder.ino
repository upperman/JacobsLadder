/****************************************************************************************************************************
 * PROGRAM: Jacob's Ladder
 * Designer: Nathen Upperman
 * Purpose of Program: This program is written to control a 120:10,000 step up transformer and allow an interface
 *                     between the user and the high voltage circuitry.
 * 
 */

 /************************************************Libraries************************************************/
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#include "ErrorHandler.h"
#include "ErrorScanning.h"
#include "NeoPixelControl.h"
/**********************************************Macros******************************************************/

#define NUMPIXELS 16 //The number of neopixels I am going to drive
#define CurrentMax 3.7 //Maximum current detected before an error occurs
#define VoltageMin 4.7 //minimum input voltage allowed
#define Volt_Ref 5.0 //analog voltage reference value Volt_Ref/1023= volt/ADC_Val
#define DelayVal 500 //delay value for ladder before it turns off
#define ButtonDelay 200 //delay for start button
#define ErrorCodeBlinkSpeed 2000


//DO NOT CHANGE THE FOLLOWING

#define ErrorLed 2 //This value is the digital port for the error led
#define StartButton 4 //This value is the digital input for the pushbutton that will activate the HV line
#define FlipFlopReset 5 //resets the switch once it has been pressed NOTE: THIS HAS TO TOGGLE OR IT WON'T WORK
#define NeoLED 6 //defines which line the neopixels are on
#define HVRelay1 8  //This value is the digital port assigned to one of two relays that activates the HV
                    //HV is on dual relay protection
#define HVRelay2 9 //This Value is the digital port assigned to the second relay to activate the HV
#define AC_current A0 // this line reads the current in the 120V side
#define DC_Input_Voltage A1

/***********************************************Prototypes**************************************************/
void MyErrorHandler();
int InputVoltageScanner();
void StartProgram(int ActivationVar);
int ButtonPressedCheck(int ActivationVar);
/***********************************************Structures*********************************************/
struct PlaceHolder {
   int temp = 0;
} PlaceHolder;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);          //  setup serial
  pinMode(FlipFlopReset, OUTPUT);
  digitalWrite(FlipFlopReset,0);
  delay(ButtonDelay); 
  digitalWrite(FlipFlopReset,1);
  pinMode(StartButton, INPUT); //Defines the StartButton as an input
  pinMode(HVRelay1, OUTPUT);  //Defines the HVRelay as an output
  digitalWrite(HVRelay1,0); //Initilizing the state for the HVRelay (off)
  pinMode(ErrorLed, OUTPUT); //Defines the ErrorLed as an output
  digitalWrite(ErrorLed,0); //Initializing the state for the ErrorLed (off)
}

void loop() 
{
  int ActivationVar = 0;
  StartProgram(ActivationVar); //sends the activation variable to the StartProgram
}

void StartProgram(int ActivationVar)
{
  int ErrorVal = 0;
  while (1)
  {
  int counter=0;
  ErrorVal=InputVoltageScanner();
  if (ErrorVal ==0)
  {
    ErrorVal=CurrentScanner();
  }
  MyErrorHandler(ErrorVal);
  ActivationVar=ButtonPressedCheck(ActivationVar);
  Serial.println("Error Code: ");
  Serial.println(ErrorVal);
   Serial.println("The button var:");
  Serial.println(ActivationVar);
 
   delay(1000);
  
  if (ActivationVar==1)
  {
   digitalWrite(FlipFlopReset,0);
   delay(ButtonDelay); 
   digitalWrite(FlipFlopReset,1);
   ActivationVar = 0;
   }
   /*
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
*/
  }
}

int ButtonPressedCheck(int ActivationVar)
{
  ActivationVar = digitalRead(StartButton);
  return ActivationVar;
}

