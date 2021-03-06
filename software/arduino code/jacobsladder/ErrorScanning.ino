//The purpose of this section of the code is to do 5 scans and average the values for voltage and current.
//If a problem is detected then it will return an error code of that problem.

int CurrentScanner()
{
  float average = 0.0;
  int ErrorCode = 0;
  average = AverageCalculation (AC_current);
  if (average > CurrentMax)
  {
    ErrorCode = 1;
  }
  return ErrorCode;
}

int InputVoltageScanner()
{
  float average = 0.0;
  int ErrorCode = 0;
  average = AverageCalculation (DC_Input_Voltage);
  if (average < VoltageMin)
  {
    ErrorCode = 2;
  }
  return ErrorCode;
}


float AverageCalculation(int AnalogChannel)
{
    float Average = 0.0;
    int ScannedValues[5];
    int counter = 0;

    while (counter < 5)
    {
    ScannedValues[counter] = analogRead(AnalogChannel);
    counter ++;
    }
    Average = (ScannedValues[0]+ScannedValues[1]+ScannedValues[2]+ScannedValues[3]+ScannedValues[4])/5;
   Serial.println("The voltage average is:");
  Serial.println(Average);
   return Average;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
