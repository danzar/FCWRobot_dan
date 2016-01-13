
#ifndef PingSensor_h
#define PingSensor_h


    void PingSensorSetup(int trigPinId, int echoPinId);
    long CurrentDuration();

void Manual_trigger_pulse();
void echo_interrupt();
void trigger_pulse();

#endif
