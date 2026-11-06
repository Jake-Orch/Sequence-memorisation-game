#include "mcc_generated_files/mcc.h"
#include "Definitions.h"

void seperateInt(int val)
{
    timeNumSep[0] = (val % 10000) / 1000;
    timeNumSep[1] = (val % 1000) / 100;
    timeNumSep[2] = (val % 100) / 10;
    timeNumSep[3] = (val % 10);
}

void delayAdjusted(int ms)
{
    int adjusted = ms / clockFactor;

    for (int i = 0; i < adjusted; i ++)
    {
        __delay_ms(1);
    }
}

uint8_t decimalToBCD(uint8_t value)
{
    return ((value / 10) << 4) | (value % 10);
}