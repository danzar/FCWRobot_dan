#include <pins_arduino.h>
#include <Arduino.h>
#include "PingSensor.h"

int _trigPinId = 0;
int _echoPinId = 0;

//Set the values for the sending of the trigger pulse
#define TIMER_US 50                                   // 50 uS timer duration
#define TICK_COUNTS 20                              // 200 mS worth of timer ticks


volatile long echo_start = 0;                         // Records start of echo pulse
volatile long echo_end = 0;                           // Records end of echo pulse
volatile long echo_duration = 0;                      // Duration - difference between end and start
volatile int trigger_time_count = 0;                  // Count down counter to trigger pulse time

volatile long duration = 0;

void PingSensorSetup(int trigPinId, int echoPinId)
{
    _trigPinId = trigPinId;
    _echoPinId = echoPinId;
    
    //Setup the trigger pin
    pinMode(trigPinId, OUTPUT);
    digitalWrite(trigPinId, LOW);
    
    //Setup the echo pin
    pinMode(echoPinId, INPUT);
    digitalWrite(echoPinId, HIGH);


 
    //Attach the interrupt Pin2
    attachInterrupt(0, echo_interrupt, CHANGE);  // Attach interrupt to the sensor echo input
}




/*
  Get the current duration
 */
long CurrentDuration()
{
    Manual_trigger_pulse();
   
   // return echo_duration;
    return duration;
}

/*
 * Manually trigger the Sonic pulse
 */
void Manual_trigger_pulse()
{
    digitalWrite(_trigPinId, HIGH);              // Set the trigger output high
    delayMicroseconds(5);
    digitalWrite(_trigPinId, LOW);               // Set the trigger output low

}




// --------------------------
// echo_interrupt() External interrupt from HC-SR04 echo signal.
// Called every time the echo signal changes state.
//
// Note: this routine does not handle the case where the timer
//       counter overflows which will result in the occassional error.
// --------------------------
void echo_interrupt()
{
    uint8_t oldSREG = SREG;
    cli ();
    
    /*
    switch (digitalRead(_echoPinId))                     // Test to see if the signal is high or low
    {
        case HIGH:                                      // High so must be the start of the echo pulse
            echo_end = 0;                                 // Clear the end time
            echo_start = micros();                        // Save the start time
            break;
            
        case LOW:                                       // Low so must be the end of hte echo pulse
            echo_end = micros();                          // Save the end time
            echo_duration = echo_end - echo_start;        // Calculate the pulse duration
            break;
    }
     */
    
    if (digitalRead(2))
    {
        duration = micros();
    }
    else
    {
        duration = micros() - duration;
    }
    
    
    
    
    SREG = oldSREG;
    
    
}



