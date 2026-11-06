#include "mcc_generated_files/mcc.h"
#include "EusartN.h" 
#include "LCD_Display.h"
#include "helper.h"
#include "Definitions.h"
#include <stdio.h>
#include <string.h>

void EusartRX(void)
{      
    // Check for received string
    if (!EusartRxString())
    {
        return;
    }
    
    // Clear users screen and return cursor
    SendEusartString("\033[2J\033[H");
    EusartPrintInput();
    
    if (strcmp(inputString, "sleep") == 0)
    {
        while (EUSART_is_rx_ready())
        {
            EUSART_Read();
        }
        wakeFlag = 0;
        inputString[0] = '\0';
        index = 0;

        return;
    }

    if (pageNumber == 1)
    {
        if (strcmp(inputString, "l") == 0 || strcmp(inputString, "left") == 0)
        {
            if (timeGameSeq == 1 || timeGameSeq == 3 || timeGameSeq == 4)
            {
                timeGameSeq++;
            }
            else if (timeGameSeq == 5)
            {
                timeGameSeq = 0;
                timeEggEnable = 1;
                pageNumber = 7;
                pageChanged = 1;
            }
            else 
            {
                timeGameSeq = 0;
            }
            inputString[0] = '\0';
            index = 0;
            return;
        }
        else if (strcmp(inputString, "r") == 0 || strcmp(inputString, "right") == 0)
        {
            if (timeGameSeq == 2)
            {
                timeGameSeq++;
            }
            else
            {
                timeGameSeq = 1;
            }
            inputString[0] = '\0';
            index = 0;
            return;
        }
        
        if (strcmp(inputString, "saves") == 0)
        {
            pageNumber = 20;
            pageChanged = 1;
        }
        else if (timeEggEnable && strcmp(inputString, "time") == 0)
        {
            pageNumber = 7;
            pageChanged = 1;
        }
        else
        {
            pageNumber = 2;
            pageChanged = 1;
        }
    }
    else if (pageNumber == 2)
    {
        if (strcmp(inputString, "1") == 0)
        {
            playerCount = 1;
            pageNumber = 3;
            pageChanged = 1;
        }
        else if (strcmp(inputString, "2") == 0)
        {
            playerCount = 2;
            pageNumber = 3;
            pageChanged = 1;
        }
    }
    else if (pageNumber == 3)
    {
        nameConfirm = 1;
        usartName = 1;
        nameHandler();
    }
    else if (pageNumber == 4)
    {
    
    }
    else if (pageNumber == 6)
    {
        if (playerCount == 1)
        {
            SendEusartString("Your Score: ");
            SendEusartInt(soloScore);
        }
        else if (playerCount == 2 && playerTurn == 1)
        {
            SendEusartString(playerOneName);
            SendEusartString("'s Score: ");
            SendEusartInt(playerOneScore);
        }
        else if (playerCount == 2 && playerTurn == 2)
        {
            SendEusartString(playerTwoName);
            SendEusartString("'s Score: ");
            SendEusartInt(playerTwoScore);
        }
    
    }
    else if (pageNumber == 7)
    {
        if (strcmp(inputString, "home") == 0)
        {
            pageNumber = 1;
            pageChanged = 1;
        }
        else if (strcmp(inputString, "saves") == 0)
        {
            pageNumber = 20;
            pageChanged = 1;
        }
        else 
        {
            timeGameFlag = 1;
            pageNumber = 2;
            pageChanged = 1;
        }
    }
    else if (pageNumber == 16)
    {
    
    }
    else if (pageNumber == 19)
    {
        if(strcmp(inputString, "home") == 0)
        {
            pageNumber = 1;
            pageChanged = 1;
        }
        else if (timeEggEnable)
        {
            if (strcmp(inputString, "time") == 0)
            {
                pageNumber = 7;
                pageChanged = 1;
            }
        }
    }
    else if (pageNumber == 20)
    {
        if(strcmp(inputString, "next") == 0)
        {
            highScoreIteration++;
            pageChanged = 1;
        }
        else if (strcmp(inputString, "prev") == 0)
        {
            highScoreIteration--;
            pageChanged = 1;
        }
        else if (strcmp(inputString, "home") == 0)
        {
            pageNumber = 1;
            pageChanged = 1;
        }
        else if (timeEggEnable)
        {
            if (strcmp(inputString, "time") == 0)
            {
                pageNumber = 7;
                pageChanged = 1;
            }
        }
    }
    inputString[0] = '\0';
    index = 0;
}


/// PAGES

void EUtimeHomePage(void)
{
    SendEusartString("\r\r\nWelcome to The Secret Game");
    SendEusartString("\r\r\nType anything to continue");
    SendEusartString("\r\r\nType 'home' to go back to the home page");
    SendEusartString("\r\r\nType 'saves' to view the saved scores");
}

void EUtimeDisplay(void)
{
    SendEusartString("\r\r\n0");
    SendEusartInt(gameTime);
    SendEusartString(":00");
}

void EUtimeResultDisplay(void)
{
    if (playerCount == 1)
    {
        seperateInt(soloTime);
        SendEusartString("\r\r\nYour time: ");
        SendEusartInt(timeNumSep[0]);
        SendEusartInt(timeNumSep[1]);
        SendEusartString(":");
        SendEusartInt(timeNumSep[2]);
        SendEusartInt(timeNumSep[3]);
        
        seperateInt(soloTimeDiff);
        SendEusartString("\r\r\nYou were off by ");        
        SendEusartInt(timeNumSep[1]);
        SendEusartString(".");
        SendEusartInt(timeNumSep[2]);
        SendEusartInt(timeNumSep[3]);
        SendEusartString("s");


    }
    else if (playerCount == 2)
    {
        seperateInt(playerOneTime);
        SendEusartString("\r\r\n");
        SendEusartString(playerOneName);
        SendEusartString("'s Time: ");

        SendEusartInt(timeNumSep[0]);
        SendEusartInt(timeNumSep[1]);
        SendEusartString(":");
        SendEusartInt(timeNumSep[2]);
        SendEusartInt(timeNumSep[3]);
        
        seperateInt(playerOneDiff);
        SendEusartString("\r\r\nOff by ");     
        SendEusartInt(timeNumSep[1]);
        SendEusartString(".");
        SendEusartInt(timeNumSep[2]);
        SendEusartInt(timeNumSep[3]);
        SendEusartString("s");

        
        seperateInt(playerTwoTime);
        SendEusartString("\r\r\n");
        SendEusartString(playerTwoName);
        SendEusartString("'s Time: ");

        SendEusartInt(timeNumSep[0]);
        SendEusartInt(timeNumSep[1]);
        SendEusartString(":");
        SendEusartInt(timeNumSep[2]);
        SendEusartInt(timeNumSep[3]);
        
        seperateInt(playerTwoDiff);
        SendEusartString("\r\r\nOff by ");     
        SendEusartInt(timeNumSep[1]);
        SendEusartString(".");
        SendEusartInt(timeNumSep[2]);
        SendEusartInt(timeNumSep[3]);
        SendEusartString("s");
        
    }
}

void EUhomePage(void)
{
    SendEusartString("\r\r\nWelcome to The Game");
    SendEusartString("\r\r\nType anything to continue");
    SendEusartString("\r\r\nType 'saves' to view the saved scores");
    if (timeEggEnable)
    {
        SendEusartString("\r\r\nType 'time' to go to the secret game");
    }
}

void EUplayerChoice(void)
{
    SendEusartString("\r\r\nType 1 for one player or 2 for 2 players");
}

void EUwriteNames(void)
{
    if (playerCount == 1)
    {
        SendEusartString("\r\r\nEnter your name\r\r\n");        
    }
    else 
    {
        if (playerTurn == 1)
        {
            SendEusartString("\r\nEnter player 1's name\r\r\n");
        }
        else if (playerTurn == 2)
        {
            SendEusartString("\r\nEnter player 2's name\r\r\n");
        }
    }
    SendEusartString("\r\r\nMAX 4 CHARACTERS");
}

void EUcountDown(void)
{
    SendEusartString("\r\r\nGAME IN PROGRESS\r\r\n");
}

void EUscoreScreen(void)
{    
    if (playerCount == 1)
    {
        SendEusartString("\r\r\nYour score:");
        SendEusartInt(soloScore);
    }
    else if (playerCount == 2 && playerTurn == 1)
    {
        SendEusartString("\r\r\n");
        SendEusartString(playerOneName);
        SendEusartString("s score: ");
        SendEusartInt(playerOneScore);
    }
    else if (playerCount == 2 && playerTurn == 2)
    {
        SendEusartString("\r\r\n");
        SendEusartString(playerTwoName);
        SendEusartString("s score: ");
        SendEusartInt(playerTwoScore);
    }
}

void EUwinnerScreen(void)
{        
    if (playerOneScore > playerTwoScore)
    {
        SendEusartString(playerOneName);
    }
    else if (playerOneScore < playerTwoScore)
    {
        SendEusartString(playerTwoName);
    }
    else
    {
        SendEusartString("\r\r\nNo one, its a tie");
    }
}

void EUsavedScores()
{   
    if (HSScore == 225 && highScoreIteration != 0)
    {
        highScoreIteration = 0;
        pageChanged = 1;
    }
    else if (HSScore == 255)
    {
        SendEusartString("\r\r\nNo logged scores");
        SendEusartString("\r\r\nPlay the game!");
        SendEusartString("\r\r\nType 'home' to go back to the home page");
    }
    else
    {
        SendEusartString("\r\r\nName:");
        SendEusartString(HSName);
        
        SendEusartString("\r\r\nHigh score:");
        SendEusartInt(HSScore);
        
        SendEusartString("\r\r\nDate:");
        SendEusartBCD(HSdate);
        SendEusartString("/");
        SendEusartBCD(HSmonth);
        SendEusartString("/");
        SendEusartBCD(HSyear);
        
        SendEusartString("\r\r\nTime:");
        SendEusartBCD(HShour);
        SendEusartString(":");
        SendEusartBCD(HSmin);
        
        SendEusartString("\r\r\nType 'home' to go back to the home page");
        SendEusartString("\r\r\nType 'next' for the next saved score");
        SendEusartString("\r\r\nType 'prev' for the previous saved score");
    }
    
    if (timeEggEnable)
    {
        SendEusartString("\r\r\nType 'time' to go to the secret game");
    }
}

/// HELPER FUNCTIONS

void SendEusartString(char *str)
{
    while(*str)//while the pointer doesn't point to a memory location with \0 in it
    {
        EUSART_Write(*str++);//The letters from the string are printed
    }
    while(!EUSART_is_tx_done());//Waits until Tx register is empty
}

void SendEusartInt(int value)
{
    char buffer[8];

    sprintf(buffer, "%d", value);
    SendEusartString(buffer);
}

void SendEusartBCD(uint8_t bcd)
{
    char tens = ((bcd >> 4) & 0x0F) + '0';
    char ones = (bcd & 0x0F) + '0';

    EUSART_Write(tens);
    EUSART_Write(ones);
}

bool EusartRxString(void)
{
    while (EUSART_is_rx_ready())
    {
        char input = EUSART_Read();

        if (input == '\n')
        {
            continue;
        }

        if (input == '\r')
        {
            if (index == 0)
            {
                return false;
            }

            inputString[index] = '\0';
            inactiveTime = 0;

            return true;        // COMPLETE STRING
        }

        if (index < sizeof(inputString) - 1)
        {
            inputString[index] = input;
            index++;
        }
    }

    return false;               // NOT COMPLETE YET
}

// DEBUG FUNCTION
void EusartPrintInput(void)
{
    SendEusartString("\r\nString: ");
    SendEusartString(inputString);
    SendEusartString("\r\n");
}