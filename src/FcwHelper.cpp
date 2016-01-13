#include "FcwHelper.h"
#include "Arduino.h"
#include "FcwServo.h"
#include "FcwRadio.h"
#include "ModeButton.h"
#include "PingSensor.h"
#include "PiezoBuzzer.h"
#include "FcwDebug.h"

//The distance from object before we change direction
const int TooClose = 300;
const int BeepCommand = 5;
int _debugLevel;

typedef  struct {
    int DMove; //Movement Id
    int DNum; //Delay for the movement
} DanceMove;

#define DanceListArray 3
#define DanceListMoves 8

#define DelayFiller  0
#define DForward 1
#define DBackward 2
#define DRight 3
#define DLeft 4
#define BeepCommand 5
#define EndCommand 6


 DanceMove DanceMoveList[DanceListArray][DanceListMoves] = {
    {
        {DelayFiller,2000},{BeepCommand, 500},{DForward, 2000}, {DBackward,1500}, {DRight,1500}, {DLeft,1000},{BeepCommand, 500},{EndCommand, 500}

    },
    {
        {DelayFiller,2000},{DRight, 500},{DLeft, 500}, {DForward,200}, {DLeft,1000}, {DBackward,800},{DForward, 800},{EndCommand, 500}
    },
    {
        {DelayFiller,2000},{BeepCommand, 500},{DRight, 2000}, {DBackward,500}, {DLeft,1500}, {DRight,1500},{BeepCommand, 300},{EndCommand, 500}
    },
};


bool _debugMode = false;

void FreeRangeMode()
{
    if (CurrentDuration() < TooClose)
    {
        Beep(1);
        
        //Avoid Obstacle()
        AvoidObstacle();
        
        DebugOutput("AvoidObstacle","");
        DebugOutput("Dur:",String(CurrentDuration()));
    }
    else
    {
        //Run straight
        Run(1);
        DebugOutput("Run","");
        DebugOutput("Dur:",String(CurrentDuration()));
    }
}




void MasterMode()
{
    
    DebugOutput("Enter MasterMode","");

    //Random number from 1-3 (tech 0-2)
    int randomDanceMove = (rand() % DanceListArray);
    
    
    for (int i; i < (sizeof(DanceMoveList[randomDanceMove])/sizeof(DanceMove)); i++)
    {
        DanceMove move1 = DanceMoveList[randomDanceMove][i];
        
        //Convert string command to char* command to send.
        String command = "B";
        command.concat(":");
        command.concat(String(move1.DMove));
        command.concat("[");
        command.concat(String(move1.DNum));
        command.concat("]");
        
        char commandToSend[command.length() + 1];
        command.toCharArray(commandToSend, command.length() + 1);
        
        //Send Command to the Slave bots
        bool sent = SendCommand(commandToSend);
        
        //Debug item
        DebugOutput("DanceMove SendCommand:",commandToSend);
        
        //Process the dance move for the master
        DanceMoveProcessing(move1.DMove, move1.DNum);
        
    }
 
   

}



void DanceMoveProcessing(int danceMove, int danceTimer)
{
     DebugOutput("DanceMove Moving"," MoveCommand:" + String(danceMove) + " MoveTimer:" + String(danceTimer));

    //We only looking for movement Int's from 1-4 for movement
    if(danceMove > 0 && danceMove <= 4 )
    {
        ProcessMove(danceMove);
    }
    else if(danceMove == BeepCommand) //5 repersents a beep command
    {
        Beep(1);
    }
    else if(danceMove == EndCommand)
    {
        ResetToStartUpMode();
    }
    
    
    delay(danceTimer);
}


void DanceMode()
{
    DanceMoveProcessing(GetMoveCommand(),GetMoveTimer());
}

void DebugSetUp(bool setup, int debugLevel)
{
    if(setup)
    {
        _debugMode = setup;
        Serial.begin (115200);
    }

    
    _debugLevel = debugLevel;
    
    
}


void DebugOutput(String  stringOutType ,String outputString, int debugLevel)
{
    if(debugLevel >= _debugLevel)
    {
        if(_debugMode)
        {
            Serial.print(stringOutType);
            Serial.println(outputString);
        }
        
        if(CardStoreEnabled())
        {
            WriteToCard(stringOutType,outputString);
        }
        
                    
    }
 
}

void ResetToStartUpMode()
{
    
    DebugOutput("Reset to StartMode","",4);
    //Reset the robot back to startup mode.
    SetButtonCount(0); //Set button count to 0
    SetSlaveCommand("A"); //Set the Command to A which is Self Master.
   
}


