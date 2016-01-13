#include "FcwDebug.h"
#include <SPI.h>
#include <SD.h>
#include "Arduino.h"


int _chipSelect;
bool _storeToCard = false;
String FileName = "datalog.txt";

bool _displayToLCD = false;

void SDCardSetup(int chipSelect , bool storeToCard)
{
    _chipSelect = chipSelect;
   
    if (storeToCard && SD.begin(chipSelect))
    {
        _storeToCard = true;
        if(SD.exists(FileName))
        {
            SD.remove(FileName);
        }
        
    }
    
    
}


void WriteToCard(String  stringOutType ,String outputString)
{
    
    File dataFile = SD.open(FileName, FILE_WRITE);
    if (dataFile)
    {
        dataFile.print(stringOutType);
        dataFile.println(outputString);
        dataFile.close();
    }
    
}

bool LcdScreenEnabled()
{
    return _displayToLCD;
}

bool CardStoreEnabled()
{
    return _storeToCard;
}
