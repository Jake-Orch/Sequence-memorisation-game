#include "mcc_generated_files/mcc.h"
#include "PeriphInt.h"
#include "lcd.h"
#include "LCD_Display.h"
#include "EEPROM.h"
#include "helper.h"
#include "power.h"
#include "Definitions.h"

void rotaryEncoderPolling(void)
{
    int currentENC1 = ENC1;

    if (currentENC1 != lastENC1)
    {
        // Only act on ENC1 rising edge
        if (currentENC1 == 1)
        {
            if (ENC2 == 1)
            {
                // LEFT
                BTN3_Ctrl();
            }
            else
            {
                // RIGHT
                BTN2_Ctrl();
            }
        }

        lastENC1 = currentENC1;
    }

    if (BTNR)
    {
        delayAdjusted(20);
        BTN1_Ctrl();
        while (BTNR)
        {
        }
    }
}

void BTN1_Ctrl(void)
{
    
    if (pageNumber != 4 && pageNumber != 5 && pageNumber != 9)
    {
        BUZZ = 1;
        delayAdjusted(10);
        BUZZ = 0;     
    }
    
    inactiveTime = 0;       // Reset inactive counter
    
    // Button 1 handler (page dependant)
    if(pageNumber == 1)
    {
        pageNumber++;
        pageChanged = 1;
    }
    else if(pageNumber == 2)
    {
        playerCount = playerCountCursor;        // Set player count
        pageNumber = 3;
        pageChanged = 1;
    }
    else if (pageNumber == 3)
    {
        // 
        if (cursorY == 3)
        {
            // Confirm player name
            nameConfirm = 1;
            pageChanged = 1;
            return;
        }
        char selectedChar;
        // Select character and add to selectedName (player name)
        if (cursorY == 0)
        {
            char row1[] = "abcdefghijklmnop";
            selectedChar = row1[cursorX]; 
        }
        else  if (cursorY == 1)
        {
            char row2[] = "qrstuvwxyz";
            selectedChar = row2[cursorX];    
        }
        if(nameIndex < 4)
        {
            selectedName[nameIndex] = selectedChar;
            nameIndex++;
            
            selectedName[nameIndex] = '\0';
        }
        pageChanged = 1;
    }
    else if (pageNumber == 6)
    {        
        // Select either home page or winner menu based on playerCount and playerTurn values
        if (playerCount == 1)
        {
            pageNumber = 1;
        }
        else if (playerCount == 2 && playerTurn == 1)
        {
            playerTurn = 2;
            pageNumber = 4;
        }
        else if (playerCount == 2 && playerTurn == 2)
        {
            playerTurn = 1;
            pageNumber = 16;
        }
        pageChanged = 1;
    }
    else if (pageNumber == 7)
    {
        timeGameFlag = 1;       // Set timeGameFlag (indicates time game is being used)
        pageNumber = 2;
        pageChanged = 1;
    }
    else if (pageNumber == 8)
    {
        pageNumber = 4;
        pageChanged = 1;
    }
    else if (pageNumber == 10)
    {        
        // Select either timeHomePage or winnerScreen pages depending on playerCount
        if (playerCount == 1)
        {
            pageNumber = 7;
            
        }
        else if (playerCount == 2)
        {
            pageNumber = 16;
        }
        pageChanged = 1;
    }
    else if (pageNumber == 11)
    {
        switch (cursorDT)
        {
            case 1:
                setDateTimeVal[0] = (setDateTimeVal[0] + 10 > 23) ? setDateTimeVal[0] % 10 : setDateTimeVal[0] + 10;
                break;
            case 2:
                setDateTimeVal[0] = (setDateTimeVal[0] >= 23) ? 0 : setDateTimeVal[0] + 1;
                break;
            case 4:
                setDateTimeVal[1] = (setDateTimeVal[1] + 10 > 59) ? setDateTimeVal[1] % 10 : setDateTimeVal[1] + 10;
                break;
            case 5:
                setDateTimeVal[1] = (setDateTimeVal[1] >= 59) ? 0 : setDateTimeVal[1] + 1;
                break;
            case 7:
                setDateTimeVal[2] = (setDateTimeVal[2] + 10 > 31) ? setDateTimeVal[2] % 10 : setDateTimeVal[2] + 10;
                break;
            case 8:
                setDateTimeVal[2] = (setDateTimeVal[2] >= 31) ? 0 : setDateTimeVal[2] + 1;
                break;
            case 10:
                setDateTimeVal[3] = (setDateTimeVal[3] + 10 > 12) ? setDateTimeVal[3] % 10 : setDateTimeVal[3] + 10;
                break;
            case 11:
                setDateTimeVal[3] = (setDateTimeVal[3] >= 12) ? 0 : setDateTimeVal[3] + 1;
                break;
            case 13:
                setDateTimeVal[4] = (setDateTimeVal[4] + 10 > 99) ? setDateTimeVal[4] % 10 : setDateTimeVal[4] + 10;
                break;
            case 14:
                setDateTimeVal[4] = (setDateTimeVal[4] >= 99) ? 0 : setDateTimeVal[4] + 1;
                break;
            case 20:
                
                setDateTime();
                pageNumber = 12;
                pageChanged = 1;
                break;
        }
        pageChanged = 1;
    }
    else if (pageNumber == 13)
    {
        pageNumber = 11;
        pageChanged = 1;
    }
    else if (pageNumber == 16)
    {            
        if (timeGameFlag)
        {
            timeGameFlag = 0;       // Disable timeGameFlag
            pageNumber = 7;         // Return to timeHomePage
        }
        else 
        {
            pageNumber = 1;         // Return to homePage
        }

        pageChanged = 1;
    }
    else if (pageNumber == 19)
    {
        pageNumber = 20;            // Select savedScores page
        pageChanged = 1;
    }
    else if (pageNumber == 20)
    {
        pageNumber = 19;            // select savedScoresHome page
        pageChanged = 1;
    }
}

void BTN2_Ctrl(void)
{
    
    if (pageNumber != 4 && pageNumber != 5 && pageNumber != 9)
    {
        BUZZ = 1;
        delayAdjusted(10);
        BUZZ = 0;     
    }
    
    inactiveTime = 0;       // Reset inactive counter
    
    // Easter egg sequence handling (enables time game)
    if (pageNumber == 1 || pageNumber == 19 || pageNumber == 13)
    {
        if (timeGameSeq == 1 || timeGameSeq == 3 || timeGameSeq == 4)
        {
            timeGameSeq++;
        }
        else if (timeGameSeq == 5)
        {
            timeGameSeq = 0;
            timeEggEnable = 1;      // Enables timeGame
            pageNumber = 7;
            pageChanged = 1;
            return;
        }
        else 
        {
            timeGameSeq = 0;
        }
    }
    
    // Select either timeHomePage or savedScoresHome pages depending on timeEggEnable
    if (pageNumber == 1)
    {
        pageNumber = 13;
        pageChanged = 1;
    }
    else if(pageNumber == 2)
    {
        playerCountCursor = 1;
        pageChanged = 1;
    }
    
    // Move cursor left on writeNames page
    else if (pageNumber == 3)
    {
        if (cursorX == 0 && cursorY == 1)
        {
            cursorX = 15;
            cursorY = 0;
        }
        else if (cursorX == 0 && cursorY == 0) 
        {
            // When a character has been selected allow the cursor to go to "CONFIRM"
            if (selectedName[0] != '\0')
            {
                cursorY = 3;
            }
            else 
            {
                cursorX = 9;
                cursorY = 1;
            }
        }
        else if (cursorY == 3)
        {
            cursorX = 9;
            cursorY = 1;
        }
        else
        {
            cursorX--;
        }
        pageChanged = 1;
    }
    else if (pageNumber == 7)
    {
        pageNumber = 1;
        pageChanged = 1;
    }
    else if (pageNumber == 11)
    {
        switch (cursorDT)
        {
            case 1:
                cursorDT = 20;
                break;
            case 2:
                cursorDT = 1;
                break;
            case 4:
                cursorDT = 2;
                break;
            case 5:
                cursorDT = 4;
                break;
            case 7:
                cursorDT = 5;
                break;
            case 8:
                cursorDT = 7;
                break;
            case 10:
                cursorDT = 8;
                break;
            case 11:
                cursorDT = 10;
                break;
            case 13:
                cursorDT = 11;
                break;
            case 14:
                cursorDT = 13;
                break;
            case 20:
                cursorDT = 14;
                break;
        }
        pageChanged = 1;
    }
    else if (pageNumber == 13)
    {
        pageNumber = 19;
        pageChanged = 1;
    }
    else if(pageNumber == 19)
    {
        if (timeEggEnable)
        {
            pageNumber = 7;
            pageChanged = 1;
        }
        else
        {
            pageNumber = 1;
            pageChanged = 1;  
        }
    }
    else if (pageNumber == 20)
    {
        highScoreIteration--;   // Iterate through savedScores EEPROM data
        pageChanged = 1;
    }
}


void BTN3_Ctrl(void)
{
    
    if (pageNumber != 4 && pageNumber != 5 && pageNumber != 9)
    {
        BUZZ = 1;
        delayAdjusted(10);
        BUZZ = 0;     
    }
    
    inactiveTime = 0;       // Reset inactive counter
    
    // Easter egg sequence handling (enables time game)
    if (pageNumber == 1 || pageNumber == 19 || pageNumber == 13)
    {
        if (timeGameSeq == 2)
        {
            timeGameSeq++;
        }
        else 
        {
            timeGameSeq = 1;
        }
    }
    
    if (pageNumber == 1)
    {
        if (timeEggEnable)
        {
            pageNumber = 7;
            pageChanged = 1;
        }
        else
        {
            pageNumber = 19;
            pageChanged = 1;
        }
    }
    else if(pageNumber == 2)
    {
        playerCountCursor = 2;
        pageChanged = 1;
    }
    
    // Move cursor right on writeNames page
    else if (pageNumber == 3)
    {
        if (cursorX == 15) 
        {
            cursorX = 0;
            cursorY = 1;
        }
        // When a character has been selected allow the cursor to go to "CONFIRM"
        else if (cursorY == 1 && cursorX == 9)
        {
            if (selectedName[0] != '\0')
            {
                cursorY = 3;
            }
            else 
            {
                cursorX = 0;
                cursorY = 0;
            }
        }
        else if (cursorY == 3)
        {
            cursorX = 0;
            cursorY = 0;
        }
        else 
        {
            cursorX++;
        }
        pageChanged = 1;
    }
    else if (pageNumber == 7)
    {
        pageNumber = 19;
        pageChanged = 1;
    }
    else if (pageNumber == 11)
    {
        switch (cursorDT)
        {
            case 1:
                cursorDT = 2;
                break;
            case 2:
                cursorDT = 4;
                break;
            case 4:
                cursorDT = 5;
                break;
            case 5:
                cursorDT = 7;
                break;
            case 7:
                cursorDT = 8;
                break;
            case 8:
                cursorDT = 10;
                break;
            case 10:
                cursorDT = 11;
                break;
            case 11:
                cursorDT = 13;
                break;
            case 13:
                cursorDT = 14;
                break;
            case 14: 
                cursorDT = 20;
                break;
            case 20:
                cursorDT = 1;
                break;
        }
        pageChanged = 1;
    }
    else if (pageNumber == 13)
    {
        pageNumber = 1;
        pageChanged = 1;
    }
    else if (pageNumber == 19)
    {
        pageNumber = 13;
        pageChanged = 1;
    }
    else if (pageNumber == 20)
    {
        highScoreIteration++;       // Iterate through savedScores EEPROM data
        pageChanged = 1;
    }
}

void TMR1_CustomISR(void)
{
    // When player is inactive for 2 minutes set wakeFlag to 0, sending system into sleep mode
    inactiveTime++;
    
    // Check ADC voltage level every second
    adcCheckTime++;
    if (adcCheckTime >= 10)
    {
        checkBattery();
        adcCheckTime = 0;
    }
    
    if (inactiveTime >= 1200)
    {
        wakeFlag = 0;
        inactiveTime = 0;
    }
}

void TMR3_CustomISR(void)
{
    // Used to calculate time taken to press button for timeGame
    gameRunTime++;
    
    if (timeLoadScreen)
    {
        pageChanged = 1;
    }
}


void INT0_CustomISR(void) 
{
    EXT_INT0_InterruptDisable();
    
    delayAdjusted(20);

    // When wakeFlag isnt set, only wake up the system, else use default BTN1_Ctrl functionality
    if (wakeFlag)
    {
        BTN1_Ctrl();
    }

    EXT_INT0_InterruptFlagClear();
    EXT_INT0_InterruptEnable();
}

void INT1_CustomISR(void)
{
    EXT_INT1_InterruptDisable();
    
    delayAdjusted(20);
    
    BTN2_Ctrl();
    
    EXT_INT1_InterruptFlagClear();
    EXT_INT1_InterruptEnable();
}

void INT2_CustomISR(void)
{
    EXT_INT2_InterruptDisable();
    
    delayAdjusted(20);

    BTN3_Ctrl();
    
    EXT_INT2_InterruptFlagClear();
    EXT_INT2_InterruptEnable();
}
