/*
 * 
 * PiezoBuzzer:
 *    PiezoBuzzerSetup(BuzzerPin);
 *    Beep(int amount);
 *    
 * PingSensor:   
 *    PingSensorSetup(TrigPin,EchoPin);
 *    int CurrentDuration();
 *    
 * ModeButton:   
 *    ModeButtonSetup(ModeButton);
 *    int GetButtonCount();
 *    
 * FcwRadio:   
 *     RadioSetup(radioPinCe, radioPinCs);
 *     SendCommand(String);
 *     String GetSlaveCommand();
 *     
 *     
 */


#include "PiezoBuzzer.h"
#include "PingSensor.h"
#include "ModeButton.h"
#include "FcwRadio.h"
#include "FcwServo.h"
#include "FcwHelper.h"
#include "FcwDebug.h"

//Debug Items
bool debugMode = true;
bool debugToSdCard = true;
const int chipSelect = A0;

//Pin Senor 
const int EchoPin = 2;
const int TrigPin = 4;

//Buzzer 
const int BuzzerPin = 7;

//Mode button
const int ModeButton = 8;

//Radio 
const int radioPinCe = 9;
const int radioPinCs = 10;

//Servo's
const int RServoPin = 5;
const int LServoPin = 6;

//Temp Modes
String FREERANGE = "A";
String DANCE = "B";
String MODE3 = "C";
const int NOCOMMANDMODE = 0;
const int MASTERMODE = 1;
const int SLAVEMODE = 2;



void setup() {
  // put your setup code here, to run once:

 
 //Setup PiezoBuzzer
 PiezoBuzzerSetup(BuzzerPin);

 //Setup ModeButton 
 ModeButtonSetup(ModeButton);

  //We are setting the radios to listen on the Channel.
 RadioSetup(radioPinCe, radioPinCs);

 //Setup the Servo's to be used
 FcwServoSetup(RServoPin, LServoPin);

 //Setup the Pin sensor for use. 
 PingSensorSetup(TrigPin,EchoPin);

 //Setup debug mode
 DebugSetUp(debugMode);
 SDCardSetup(chipSelect, debugToSdCard); 

 DebugOutput("Setup Complete","");
   
}

void loop() {
  // put your main code here, to run repeatedly:

  if( GetButtonCount() == NOCOMMANDMODE)
  {
    if(GetSlaveCommand() == FREERANGE)//We just moving at will
    {
      DebugOutput("FreeRangeMode","");
      FreeRangeMode();
    }
    else if(GetSlaveCommand() == DANCE)//We are listening for commands
    {
       DebugOutput("DanceMode","");
       DanceMode();       
    }
    else if(GetSlaveCommand() == MODE3)
    {
       DebugOutput("Mode3","");
       Beep(1);
       ResetToStartUpMode();
    }
    else
    {
      DebugOutput("Outer Else Mode","");
      ResetToStartUpMode();
    }
  }
  else if(GetButtonCount() == MASTERMODE) //We are the moster now
  {
     DebugOutput("MasterMode","");
    //Lets send some commands and Dance
     MasterMode();
  }
  else
  {
    DebugOutput("Outer Else Loop ButtonCount:",String(GetButtonCount()));
    ResetToStartUpMode();
  }
  
  
  delay(50);   
}






