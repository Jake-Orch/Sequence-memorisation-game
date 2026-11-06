#include "mcc_generated_files/mcc.h"
#include "seqGameLogic.h"
#include "helper.h"
#include "EEPROM.h"
#include "Definitions.h"

// Sequential game round handler
void seqGameHandler(void)
{
    switch (roundNum)
    {
        case 1:
            seqGameLogic(3, 1);
            seqGameResponseLogic(3);
            break;

        case 2:
            seqGameLogic(4, 1);
            seqGameResponseLogic(4);
            break;

        case 3:
            seqGameLogic(5, 1);
            seqGameResponseLogic(5);
            break;

        case 4:
            seqGameLogic(4, 2);
            seqGameResponseLogic(4);
            break;

        case 5:
            seqGameLogic(5, 2);
            seqGameResponseLogic(5);
            break;
        case 6:
            seqGameLogic(7, 2);
            seqGameResponseLogic(7);
            break;
        case 7:
            seqGameLogic(9, 2);
            seqGameResponseLogic(9);
            break;
        case 8:
            seqGameLogic(3, 3);
            seqGameResponseLogic(3);
            break;
        case 9:
            seqGameLogic(6, 3);
            seqGameResponseLogic(6);
            break;
        case 10:
            seqGameLogic(9, 3);
            seqGameResponseLogic(9);
            break;
    }
}

// Handle LED choice and timing for sequential game
void seqGameLogic(int lightCount, int speed)
{
    // Use TMR0 to seed random number generator
    uint8_t digit = TMR0_ReadTimer();
    srand(digit);
    
    for (int i = 0; i < lightCount; i++)
    {
        gameNumbers[i] = rand() % 4;    // Retrieve random number (0-3)
        switch(gameNumbers[i])
        {
            case 0:
                LED1 = 1;
                break;
            case 1:
                LED2 = 1;
                break;
            case 2:
                LED3 = 1;
                break;
            case 3:
                LED4 = 1;
                break;
        }
        
        // LED on speed settings
        if (speed == 1)
        {
            delayAdjusted(250);
        }
        else if (speed == 2)
        {
            delayAdjusted(100);        
        } 
        else if (speed == 3)
        {
            delayAdjusted(15);
        }
        
        // Turn off all LEDs
        LED1 = 0;
        LED2 = 0;
        LED3 = 0;
        LED4 = 0;

        delayAdjusted(250);    // Time between LED activations to allow user to keep up
        
    }
}

// Handle user input for sequential game
void seqGameResponseLogic(int lightCount)
{
    for (int i = 0; i < lightCount; i++)
    {
        int playerInput = -1;
        
                // DEBUG - to allow me to see which buttons correspond to which LED
//        LCD_Cmd(LINE4_LCD);

//        if (gameNumbers[i] == 0)
//            LCD_PrintS("Expected: BTN1");
//        else if (gameNumbers[i] == 1)
//            LCD_PrintS("Expected: BTN2");
//        else if (gameNumbers[i] == 2)
//            LCD_PrintS("Expected: BTN3");
//        else if (gameNumbers[i] == 3)
//            LCD_PrintS("Expected: BTN4");
        
        while (playerInput == -1)
        {
            // Assign button input number to playerInput
            if (!BTN1)
            {
                playerInput = 0;
            }
            else if (!BTN2)
            {
                playerInput = 1;
            }
            else if (!BTN3)
            {
                playerInput = 2;
            }
            else if (!BTN4)
            {
                playerInput = 3;
            }
        }
        
        delayAdjusted(20);
        
        // Wait for button release
        while (!BTN1 || !BTN2 || !BTN3 || !BTN4)
        {
        }
        
        delayAdjusted(20);
        
        // User pressed the incorrect button
        if (playerInput != gameNumbers[i])
        {
            BUZZ = 1;           // Activate buzzer
            for (int i = 1; i < 7 ; i++)
            {
                LED1 = i % 2;
                LED2 = i % 2;
                LED3 = i % 2;
                LED4 = i % 2;
                delayAdjusted(50);
            }
            BUZZ = 0;
            
            if (playerCount == 2 && playerTurn == 1)
            {
                playerOneScore = correctAnswer;                 // Set playerOneScore to their current correctAnswer count
                checkHighScore(playerOneName, correctAnswer);   // Compare their score with EEPROM data to update high score database
            }
            else if (playerCount == 2 && playerTurn == 2)
            {
                playerTwoScore = correctAnswer;
                checkHighScore(playerTwoName, correctAnswer);
            }
            else 
            {
                soloScore = correctAnswer;
                checkHighScore(soloName, correctAnswer);
            }
            
            correctAnswer = 0;      // Reset correctAnswer
            roundNum = 1;           // Reset roundNum

            pageNumber++;           // Direct system to scoreScreen
            pageChanged = 1;
                
            return;
        }
    }
    correctAnswer++;        // Increase correctAnswer (current user score)
    roundNum++;             // Increase to next round
    pageChanged = 1;
    delayAdjusted(500);        // Round delay
}