#ifndef FcwHelper_h
#define FcwHelper_h
#include "Arduino.h"


void FreeRangeMode();
void MasterMode();
void DanceMode();
void DanceMoveProcessing(int danceMove, int danceTimer);
void ResetToStartUpMode();
void DebugSetUp(bool setup, int debugLevel = 1);
void DebugOutput(String  stringOutType ,String outputString, int debugLevel = 1);

#endif