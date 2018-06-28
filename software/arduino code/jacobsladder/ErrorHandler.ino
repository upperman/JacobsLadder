
//This section of the code translates any errors detected to the user in led form by bleeping out a code associated with each error.
//The error is also being transmitted on the TX port. If the TX port is monitored, you will be able to read the code.
void MyErrorHandler(int ErrorCode)
{
  if (ErrorCode == 1)
  {
    while (1==1)
    {
    digitalWrite(HVRelay,0);
    digitalWrite(ErrorLed,1);
    delay(200);
    digitalWrite(ErrorLed,0);
    delay(200);
    Serial.println("Error 1: OverCurrent");
    delay(3000);
    }
  }
    if (ErrorCode == 2)
    {
      while (1==1)
      {
        digitalWrite(HVRelay,0);
        digitalWrite(ErrorLed,1);
        delay(200);
        digitalWrite(ErrorLed,0);
        delay(200);
        digitalWrite(ErrorLed,1);
        delay(200);
        digitalWrite(ErrorLed,0);
        Serial.println("Error 2: Low DC Input Voltage");
        delay(3000);
      }
    }
    if (ErrorCode == 3)
    {
      while (1==1)
      {
        digitalWrite(HVRelay,0);
        digitalWrite(ErrorLed,1);
        delay(200);
        digitalWrite(ErrorLed,0);
        delay(200);
        digitalWrite(ErrorLed,1);
        delay(200);
        digitalWrite(ErrorLed,0);
        delay(200);
        digitalWrite(ErrorLed,1);
        delay(200);
        digitalWrite(ErrorLed,0);    
        Serial.println("Error 3: blablabla");
        delay(3000);
      }
    }
    delay(50);
}

