#include "PiezoBuzzer.h"
#include "Arduino.h"


//Pin to use for the buzzer
int _BeeperPinId;;
int _beepLength = 100;

//Set the pin to use for the buzzer on the construtor
void PiezoBuzzerSetup(int pinId)
{
  //Set the pinId to output.
  pinMode(pinId, OUTPUT);
  _BeeperPinId = pinId;
}
void SetBuzzerLength(int beepLength)
{
    _beepLength = beepLength;
}

//Create a short burst of buzzer sound.
void Beep(int amount, int beepLength)
{
  //Check to make sure that the pinId is valid to use.
  if(_BeeperPinId > 0)
  {
      for (int i = 0; i < amount; i++)
      {
          digitalWrite(_BeeperPinId, HIGH);
          if(beepLength > 0)
          {
              delay(beepLength);
          }
          else
          {
              delay(_beepLength);
          }
          digitalWrite(_BeeperPinId, LOW);
      }
     
  }
}


