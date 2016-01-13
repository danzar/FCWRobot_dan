#ifndef FcwDebug_h
#define FcwDebug_h
#include "Arduino.h"

void SDCardSetup(int chipSelect , bool storeToCard = false);
void WriteToCard(String  stringOutType ,String outputString);
bool CardStoreEnabled();

void LCDFourLineSetup(bool displayToScreen);
void WriteToLCDSreen(String data);
bool LcdScreenEnabled();
#endif