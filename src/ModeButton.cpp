#include <ModeButton.h>
#include <Arduino.h>
#include "FcwHelper.h"


int _buttonPin;
volatile int buttonCounter = 0;
volatile unsigned long Time;
volatile long startTime;


//The timer out for the button to being pressed.
int ButtonTimerOut = 2000;
const int DebounceTime = 200; //Button debounce milliseconds

void ModeButtonSetup(int buttonPin)
{
    _buttonPin = buttonPin;
    
    //Setup the Button Pin
    pinMode(buttonPin, INPUT_PULLUP);
    
    //We are only setting up the interrupt for button 8, if the pin is different then we
    //would need to alter the code.
    if(buttonPin == 8)
    {
        //We are setting the Pin and Inerrupt for the button on pin D8.
        //Setting up D8 for the button
        PCMSK0 |= (1 << PCINT0); // want pin D8
        PCIFR |= (1 << PCIF0); // clear any outstanding interrupts
        PCICR |= (1 << PCIE0); // enable pin change interrupts for D8 to D13
    }
    
}



ISR (PCINT0_vect) {
    // handle pin change interrupt for D8 to D13 here
  //  static unsigned long Time = 0;
    unsigned long Now = millis();
    
   
    //This only does something if the Button pin is HIGH.
    if(digitalRead(_buttonPin) == HIGH && (Now - Time) >= DebounceTime)
    {
        Time = Now;
        if(buttonCounter < 4)
        {
            buttonCounter++;

            if(buttonCounter == 1)
            {
                startTime = Now;
            }
        }
      
    }
    
    
    
} // end of PCINT0_vect


int GetButtonCount()
{
    if(buttonCounter > 0)
    {
        unsigned long Now = millis();
        
        if((Now - startTime) >= ButtonTimerOut)
        {
            return buttonCounter;
        }
        
    }
    return 0;
}


void SetButtonCount(int count)
{
    buttonCounter = count;
}
