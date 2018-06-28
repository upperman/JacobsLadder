
int CurrentScanner()
{
  float CurrentVal[5];
  float CurrentAve = 0.0;
  int ReturnVal=0;
  CurrentVal[0]=analogRead(AC_current);
  delay(10);
  CurrentVal[1]=analogRead(AC_current);
  delay(10);
  CurrentVal[2]=analogRead(AC_current);
  delay(10);
  CurrentVal[3]=analogRead(AC_current);
  delay(10);
  CurrentVal[4]=analogRead(AC_current);
  CurrentAve = (Volt_Ref/1023.0)*((CurrentVal[0]+CurrentVal[1]+CurrentVal[2]+CurrentVal[3]+CurrentVal[4])/5);
 Serial.println("The Current Average:");
  Serial.println(CurrentAve);
  if (CurrentAve >= CurrentMax)
  {
    ReturnVal = 1;
  }
  return ReturnVal;
}

int InputVoltageScanner()
{
  float VoltageVal[5];
  float VoltageAve = 0.0;
  int ReturnVal=0;
  VoltageVal[0]=analogRead(DC_Input_Voltage);
  delay(10);
  VoltageVal[1]=analogRead(DC_Input_Voltage);
  delay(10);
  VoltageVal[2]=analogRead(DC_Input_Voltage);
  delay(10);
  VoltageVal[3]=analogRead(DC_Input_Voltage);
  delay(10);
  VoltageVal[4]=analogRead(DC_Input_Voltage);
  VoltageAve = (Volt_Ref/1023.0)*((VoltageVal[0]+VoltageVal[1]+VoltageVal[2]+VoltageVal[3]+VoltageVal[4])/5);
  Serial.println("The Voltage Average:");
  Serial.println(VoltageAve);
  if (VoltageAve < VoltageMin)
  {
    ReturnVal = 2;
  }
  return ReturnVal;
}

