#include "mcc_generated_files/mcc.h"
#include "EEPROM.h"
#include "simple_i2c.h"
#include "helper.h"
#include "Definitions.h"
#include <string.h>

void checkHighScore(char name[], int score)
{
    int byteQuant = 256;
    
    // Iterate through the EEPROM bytes
    for (int i = 0; i <= byteQuant - 5; i += 10)
    {
        uint8_t byteIteration = i;
        
        // Retrieve the players name saved in the current EEPROM location
        for (int j = 0; j < 4; j++)
        {
            savedName[j] = DATAEE_ReadByte(byteIteration + j);
        }
        
        savedName[4] = '\0';
        
        // If the name matches the current players name
        if (strcmp(name, savedName) == 0) 
        {
            uint8_t savedScore = DATAEE_ReadByte(byteIteration + 4);
            
            // If their score is higher than their previous highest score, save their new score
            if (score > savedScore)
            {
                DATAEE_WriteByte(byteIteration + 4, score);
                
                saveDateTime(byteIteration);
            }
            return;
        }
        
        // If their name isnt found
        if ((uint8_t)savedName[0] == 0x00 || (uint8_t)savedName[0] == 0xFF)
        {
            // Save their name
            for (int j = 0; j < 4; j++)
            {
                DATAEE_WriteByte(byteIteration + j, name[j]);
            }
            
            // Save their score
            DATAEE_WriteByte(byteIteration + 4, score);
            saveDateTime(byteIteration);

            return;
        }
    }
}

void retrieveHighScores(int iteration)
{
//    // Reached the end of the EEPROM storage
//    if (iteration >= 25)
//    {
//        return;
//    }
//    
//    // Each group of data is 10 bytes, so iterate through 10 bytes of data (name (4 bytes), score, date, month, year, hours, minutes) at a time
//    iteration = iteration*10;   
    
    
    int newestIndex = -1;

    // Find the newest saved high score
    for (int i = 0; i < 25; i++)
    {
        uint8_t firstByte = DATAEE_ReadByte(i * 10);

        // Check whether EEPROM entry contains data
        if (firstByte == 0x00 || firstByte == 0xFF)
        {
            break;
        }

        newestIndex = i;
    }

    // Ensure requested entry exists
    if (iteration < 0)
    {
        highScoreIteration = 0;
        return;
    }
    else if (iteration > newestIndex)
    {
        highScoreIteration = newestIndex;
        return;
    }

    // Calculate EEPROM address, starting from newest entry
    int address = (newestIndex - iteration) * 10;
    
    // Retrieve each character of the name
    for (int i = 0; i < 4; i++) 
    {
        HSName[i] = DATAEE_ReadByte(address+i);
    }
    
    // Add "end of string" symbol
    HSName[4] = '\0';
    
    // Retrieve rest of data
    HSScore = DATAEE_ReadByte(address+4);
    
    HSmin = DATAEE_ReadByte(address+5);
    HShour = DATAEE_ReadByte(address+6);
    HSdate = DATAEE_ReadByte(address+7);
    HSmonth = DATAEE_ReadByte(address+8);
    HSyear = DATAEE_ReadByte(address+9);
}

// To be used for setting the RTC time (ONLY USED ONCE)
void setDateTime(void)
{
    I2C_START_BIT();
    I2C_COMMAND(DS3231_CTRL_CODE, DS3231_BLOCK, I2C_WRITE);
    I2C_Write(DS3231_CLOCK_ADDR);

    I2C_Write(0x00);
    I2C_Write(decimalToBCD(setDateTimeVal[1]));    // Minutes
    I2C_Write(decimalToBCD(setDateTimeVal[0]));    // Hours

    I2C_Write(0x01);    // Day (mon, tue, etc.)
    I2C_Write(decimalToBCD(setDateTimeVal[2]));    // Date
    I2C_Write(decimalToBCD(setDateTimeVal[3]));    // Month
    I2C_Write(decimalToBCD(setDateTimeVal[4]));    // Years

    I2C_STOP_BIT();
}

void getDateTime()
{
    I2C_START_BIT();
    
    I2C_COMMAND(DS3231_CTRL_CODE, DS3231_BLOCK, I2C_WRITE);
    I2C_Write(DS3231_CLOCK_ADDR);       // Register 0x00

    
    I2C_RESTART_BITT();

    I2C_COMMAND(DS3231_CTRL_CODE, DS3231_BLOCK, I2C_READ);

    seconds = I2C_Read();
    I2C_ACK_BIT();
    
    minute = I2C_Read();
    I2C_ACK_BIT();
    
    hour = I2C_Read();
    I2C_ACK_BIT();
    
    seconds = I2C_Read();
    I2C_ACK_BIT();
    
    date = I2C_Read();
    I2C_ACK_BIT();
    
    month = I2C_Read();
    I2C_ACK_BIT();
    
    year = I2C_Read();
    I2C_NACK_BIT();
    
    I2C_STOP_BIT();

}

void saveDateTime(uint8_t byteIteration)
{
    
    getDateTime();
    
    DATAEE_WriteByte(byteIteration + 5, minute);
    DATAEE_WriteByte(byteIteration + 6, hour);
    DATAEE_WriteByte(byteIteration + 7, date);
    DATAEE_WriteByte(byteIteration + 8, month);
    DATAEE_WriteByte(byteIteration + 9, year);
}
