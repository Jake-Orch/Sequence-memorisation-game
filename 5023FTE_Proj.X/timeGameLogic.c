#include "mcc_generated_files/mcc.h"
#include "timeGameLogic.h"
#include "EEPROM.h"
#include "Definitions.h"

// Generate random time value (1 - 9 seconds) using tmr0 and rand()
void timeGameSeed(void)
{
    gameTime = 0;
    while (gameTime < 1 || gameTime > 9)
    {
        uint8_t timeDigit = TMR0_ReadTimer();
        srand(timeDigit);
        gameTime = rand() % 10;  
    }
    
}

void timeGameResponseLogic(void)
{
    TMR3_StartTimer();          // Begin tmr3 to track time taken for user input
    int playerInput = -1;
    int playerOneInput = 0;
    int playerTwoInput = 0;
    while (playerInput < 1)
    {    
        int calcGameTime = gameTime * 100;      // gameRunTime tics every 10ms, multiply gameTime by 100 for comparison check
        
        if (playerCount == 1 && !BTN1)
        {
            
            soloTime = gameRunTime;
            
            soloTimeDiff = abs(calcGameTime - soloTime);
            
            playerInput = 1;
        }
        if (playerCount == 2 && !BTN2 && !playerOneInput)
        {
            
            playerOneTime = gameRunTime;
            playerOneInput = 1;
            
            playerOneDiff = abs(calcGameTime - playerOneTime);
            
        }
        if (playerCount == 2 && !BTN3 && !playerTwoInput)
        {
            
            playerTwoTime = gameRunTime;
            playerTwoInput = 1;
            
            playerTwoDiff = abs(calcGameTime - playerTwoTime);
            
        }
        // Both players have now responded
        if (playerCount == 2 && playerOneInput && playerTwoInput)
        {
            playerInput = 1;
        }
    }
    // Wait until user has released the button
    while (!BTN1 || !BTN2 || !BTN3 || !BTN4)
    {
    
    }
    timeGameFlag = 0;
    gameRunTime = 0;
    playerInput = -1;
    TMR3_StopTimer();
    TMR3_Reload();
    pageNumber = 10;
    pageChanged = 1;
}