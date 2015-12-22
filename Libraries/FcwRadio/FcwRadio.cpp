#include <FcwRadio.h>
#include <SPI.h>
#include <NRF24.h>
//#include <Arduino.h>

//volatile

NRF24 radio;


const int radioInterrupt = 1; //This tranlates to Pin 3
volatile bool isSlaveMode = false;
String slaveCommand;


void check_radio()
{
    //Store the reg item
    uint8_t oldSREG = SREG;
    
    //Disable Interrupts while we are listen
    cli ();
    
    //If Radio is avaiable we processed.
    if (radio.available())
    {
        //Get the sent data and assign it.
        char buf[32];
        uint8_t numBytes = radio.read(buf, sizeof(buf));
        
        //Need to figure out what we need to do here for a output.
        String TempString = String(buf);
        slaveCommand = ( String)TempString;
     
    }
   // sei ();
    //Assign the reg the saved items.
    SREG = oldSREG;
}

void SetSlaveCommand(String command)
{
    slaveCommand = command;
}


bool SendCommand(char* command)
{
    //If we are sending command then we want to discount the Interrupt or we
    // will not be able to send data.
    detachInterrupt(radioInterrupt);
    bool sent = radio.send(0xD2, command);
    return sent;
}


void RadioSetup(int cePin, int csPin)
{
    //Setup the pin's and start to listen
    //and attach the interrupts.
    radio.begin(cePin, csPin);
    radio.setAddress(0xD2);
    radio.startListening();
    attachInterrupt(radioInterrupt, check_radio, LOW);
}

String GetSlaveCommand()
{
    //Parse the command from the received string.
    String command  = slaveCommand.substring(0, 1);
    
    //Test to make sure we hae an command if not then send the freeRange command.
    if(command.length() > 0)
    {
        return command;
    }
    return "A";
}


String GetMoveCommand()
{
    
    //Parse out the move command.
    String moveCommand = slaveCommand.substring(slaveCommand.indexOf(':'),slaveCommand.indexOf('['));
    
    //Test for a NULL command
    if(moveCommand != "NULL")
    {
        return moveCommand;
    }
    return "";
    
}

int GetMoveTimer()
{
    //Parse the int timer from the string
    String moveTimerString = slaveCommand.substring(slaveCommand.indexOf('[') + 1 ,slaveCommand.indexOf(']'));
    //Convert the string into a int.
    int moveTimerInt = moveTimerString.toInt();
    return moveTimerInt;
}


