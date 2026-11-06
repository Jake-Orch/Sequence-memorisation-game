#include "mcc_generated_files/mcc.h"
#include "LCD_Display.h" 
#include "PeriphInt.h"
#include "helper.h"
#include "Definitions.h"
#include "lcd.h"


// Time game home page
void timeHomePage(void)
{
    char title1[] = "   Welcome To   ";
    char title2[] = "The Secret Game";
    char msg[] = "Press B1"; 
    
    LCD_Cmd(CLR_LCD);

    LCD_Cmd(LINE2_LCD);
    LCD_PrintS(title1);

    LCD_Cmd(LINE3_LCD);
    LCD_PrintS(title2);
    
    LCD_Cmd(LINE4_LCD);
    LCD_PrintS(msg);  
}

// Time game time display page
void timeDisplay(void)
{
    
    if (!timeLoadScreen)
    {
        LCD_Cmd(CLR_LCD);
        LCD_Cmd(CUR_OFF);
        LCD_Cmd(LINE2_LCD + 5);
        LCD_PrintS("00:00");
        delayAdjusted(1500);        
        // Used to count upto gameTime
        gameRunTime = 0;
        timeLoadScreen = 1;
        TMR3_Reload();
        TMR3_StartTimer(); 
        return;
    }         
    
   
    
    while (gameRunTime < gameTime * 100)
    {
        LCD_Cmd(LINE2_LCD + 6);
        LCD_PrintInt(gameRunTime / 100);
        LCD_PrintC(':');
        LCD_PrintInt((gameRunTime % 100) / 10);
        LCD_PrintInt(gameRunTime % 10);       
    }   

    TMR3_StopTimer();
    gameRunTime = 0;
    timeLoadScreen = 0;
    LCD_Cmd(LINE2_LCD + 6);
    LCD_PrintC('0');
    LCD_PrintInt(gameTime);
    LCD_PrintS(":00");    

    pageNumber = 4;
    pageChanged = 1;
}

// Time game result time (both time taken and time difference)
void timeResultDisplay(void)
{
    LCD_Cmd(CLR_LCD);
    LCD_Cmd(LINE2_LCD);
    if (playerCount == 1)
    {
        seperateInt(soloTime);
        LCD_PrintS("Your time: ");
        LCD_Cmd(LINE2_LCD + 11);
        LCD_PrintInt(timeNumSep[0]);
        LCD_Cmd(LINE2_LCD + 12);
        LCD_PrintInt(timeNumSep[1]);
        LCD_Cmd(LINE2_LCD + 13);
        LCD_PrintC(':');
        LCD_Cmd(LINE2_LCD + 14);
        LCD_PrintInt(timeNumSep[2]);
        LCD_Cmd(LINE2_LCD + 15);
        LCD_PrintInt(timeNumSep[3]);
        
        seperateInt(soloTimeDiff);
        LCD_Cmd(LINE3_LCD);
        LCD_PrintS("Off by ");
        
        LCD_Cmd(LINE3_LCD + 8);
        LCD_PrintInt(timeNumSep[1]);
        LCD_PrintC('.');
        LCD_PrintInt(timeNumSep[2]);
        LCD_PrintInt(timeNumSep[3]);
        LCD_PrintS("s");

    }
    else if (playerCount == 2)
    {        
        seperateInt(playerOneTime);
        LCD_Cmd(LINE1_LCD);
        LCD_PrintS(playerOneName);
        LCD_Cmd(LINE1_LCD + 4);
        LCD_PrintS(": ");
        LCD_Cmd(LINE1_LCD + 11);
        LCD_PrintInt(timeNumSep[0]);
        LCD_PrintInt(timeNumSep[1]);
        LCD_PrintC(':');
        LCD_PrintInt(timeNumSep[2]);
        LCD_PrintInt(timeNumSep[3]);
        
        seperateInt(playerOneDiff);
        LCD_Cmd(LINE2_LCD);
        LCD_PrintS("Off by ");
        
        LCD_Cmd(LINE2_LCD + 8);
        LCD_PrintInt(timeNumSep[1]);
        LCD_PrintC('.');
        LCD_PrintInt(timeNumSep[2]);
        LCD_PrintInt(timeNumSep[3]);
        LCD_PrintS("s");
        
        seperateInt(playerTwoTime);
        LCD_Cmd(LINE3_LCD);
        LCD_PrintS(playerTwoName);
        LCD_Cmd(LINE3_LCD + 4);
        LCD_PrintS(": ");
        LCD_Cmd(LINE3_LCD + 11);
        LCD_PrintInt(timeNumSep[0]);
        LCD_PrintInt(timeNumSep[1]);
        LCD_PrintC(':');
        LCD_PrintInt(timeNumSep[2]);
        LCD_PrintInt(timeNumSep[3]);
        
        
        seperateInt(playerTwoDiff);
        LCD_Cmd(LINE4_LCD);
        LCD_PrintS("Off by ");
        
        LCD_Cmd(LINE4_LCD + 8);
        LCD_PrintInt(timeNumSep[1]);
        LCD_PrintC('.');
        LCD_PrintInt(timeNumSep[2]);
        LCD_PrintInt(timeNumSep[3]);
        LCD_PrintS("s");
        
    }
}


// Sequential game home page
void homePage(void)
{
    char title1[] = "   Welcome To   ";
    char title2[] = "    The Game    ";
    char msg[] = "Press B1";

    LCD_Cmd(CLR_LCD);

    LCD_Cmd(LINE2_LCD);
    LCD_PrintS(title1);

    LCD_Cmd(LINE3_LCD);
    LCD_PrintS(title2);
    
    if (firstLoad)
    {
        delayAdjusted(1000);
        firstLoad = 0;
    }
    LCD_Cmd(LINE4_LCD);
    LCD_PrintS(msg);   
}

// Player quantity select page
void playerChoice(void)
{
    char msg[] = "How many players";
    char msg2[] = "Press B1 for 1";
    char msg3[] = "Press B2 for 2";

    LCD_Cmd(CLR_LCD);

    LCD_Cmd(LINE2_LCD);
    LCD_PrintS(msg);

    LCD_Cmd(LINE3_LCD);
    LCD_PrintS(msg2);

    LCD_Cmd(LINE4_LCD);
    LCD_PrintS(msg3);

    // Move cursor to line 3 for 1 player or 4 for 2 player
    if (playerCountCursor == 1) 
    {
        LCD_Cmd(LINE3_LCD + 15);
        LCD_PrintC(0);
    }
    else if (playerCountCursor == 2)
    {
        LCD_Cmd(LINE4_LCD + 15);
        LCD_PrintC(0);
    }
}

// Enter player name screen
void writeNames(void)
{
    char msg[] = "abcdefghijklmnop";
    char msg2[] = "qrstuvwxyz";
    char msg3[] = "    CONFIRM";

    LCD_Cmd(CLR_LCD);

    // Display alphabet
    LCD_Cmd(LINE1_LCD);
    LCD_PrintS(msg);

    LCD_Cmd(LINE2_LCD);
    LCD_PrintS(msg2);

    LCD_Cmd(LINE4_LCD);
    LCD_PrintS(selectedName);
    
    // Add "CONFIRM" option to screen
    if (selectedName[0] != '\0')
    {
        LCD_Cmd(LINE3_LCD);
        LCD_PrintS(msg3);
        
        // Move cursor to "CONFIRM"
        if (cursorY == 3)
        {
            LCD_Cmd(CUR_OFF);
            LCD_Cmd(LINE3_LCD);
            LCD_PrintS(msg3);
            
            LCD_Cmd(LINE3_LCD + 3);
            LCD_PrintC(1);
            LCD_Cmd(LINE3_LCD + 11);
            LCD_PrintC(0);

        }
    }
    
    if (cursorY != 3)
    {
        updateNameCursor();
    }
    
    playerCountCursor = 1;
}

// Update cursor placement (for writeNames function)
void updateNameCursor(void)
{
    LCD_Cmd(CUR_ON);
    LCD_Cmd(CUR_BLINK_ON);

    if (cursorY == 0)
    {
        LCD_Cmd(LINE1_LCD + cursorX);
    }
    else if (cursorY == 1)
    {
        LCD_Cmd(LINE2_LCD + cursorX);
    }
}

// Pre-Round count down
void countDown(void)
{
    
    LCD_Cmd(CLR_LCD);
    
    
    if (timeGameFlag)
    {
        timeLoadScreen = 0;
        LCD_Cmd(LINE2_LCD + 5);
        LCD_PrintC('0');
        LCD_Cmd(LINE2_LCD + 6);
        LCD_PrintInt(gameTime);
        LCD_Cmd(LINE2_LCD + 7);
        LCD_PrintS(":00");
        BUZZ = 1;
        delayAdjusted(500);
        BUZZ = 0;
        delayAdjusted(500);

    }

    LCD_Cmd(LINE3_LCD);
    LCD_PrintS("   Get ready!   ");

    delayAdjusted(2000);
        
    LCD_Cmd(LINE3_LCD);
    LCD_PrintS("                ");
    LCD_Cmd(LINE3_LCD + 7);
    LCD_PrintS("3");

    BUZZ = 1;
    delayAdjusted(500);
    BUZZ = 0;
    delayAdjusted(500);

    LCD_Cmd(LINE3_LCD + 7);
    LCD_PrintS("2");

    BUZZ = 1;
    delayAdjusted(500);
    BUZZ = 0;
    delayAdjusted(500);

    LCD_Cmd(LINE3_LCD + 7);
    LCD_PrintS("1");

    BUZZ = 1;
    delayAdjusted(500);
    BUZZ = 0;
    delayAdjusted(500);
    
    LCD_Cmd(LINE3_LCD + 6);
    LCD_PrintS("GO!");
    BUZZ = 1;
    delayAdjusted(1000);
    BUZZ = 0;
    delayAdjusted(1000);


    // Direct player to either time game or sequential game based on timeGameFlag
    if (!timeGameFlag)
    {    
        LCD_Cmd(CLR_LCD);
        pageNumber++;
        pageChanged = 1;
    }
    else 
    {
        LCD_Cmd(LINE3_LCD);
        LCD_PrintS("                ");
        pageNumber = 9;
        pageChanged = 1;
    }

}

// Post game score screen
void scoreScreen(void)
{
    char msg[] = "Your score:";

    LCD_Cmd(CLR_LCD);

    LCD_Cmd(LINE2_LCD);
    LCD_PrintS(msg);

    LCD_Cmd(LINE2_LCD + 12);

    if (playerCount == 1)
    {
        LCD_PrintInt(soloScore);        
    }

    if (playerCount == 2 && playerTurn == 1)
    {
        LCD_PrintInt(playerOneScore);
    }
    else if (playerCount == 2 && playerTurn == 2)
    {
        LCD_PrintInt(playerTwoScore);
    }
    
    delayAdjusted(1500);
}

// Previous game saves home screen
void savedScoresHome(void)
{
    char msg1[] = " View The Saved";
    char msg2[] = " Highest Scores";
    char msg3[] = "Press B1";
    
    LCD_Cmd(CLR_LCD);
    
    LCD_Cmd(LINE2_LCD);
    LCD_PrintS(msg1);
    
    LCD_Cmd(LINE3_LCD);
    LCD_PrintS(msg2);
    
    LCD_Cmd(LINE4_LCD);
    LCD_PrintS(msg3);
}

// Display saved scores from previous games
void savedScores(void)
{
    char msg[] = "Name:";
    char msg2[] = "High score:";
    char msg3[] = "Date:";
    char msg4[] = "Time:";
    char msg5[] = "No logged scores";
    char msg6[] = " Play the game! ";

    LCD_Cmd(CLR_LCD);
    
    // Reached the end of the saved scores, loop back to the first one
    if (HSScore == 255 && highScoreIteration != 0)
    {
        highScoreIteration = 0;
        pageChanged = 1;
    }
    // No saved scores
    else if (HSScore == 255)
    {
        LCD_Cmd(LINE1_LCD);
        LCD_PrintS(msg5);

        delayAdjusted(1000);

        LCD_Cmd(LINE3_LCD);
        LCD_PrintS(msg6);    
    }
    // Display saved scores
    else 
    {
        // Name
        LCD_Cmd(LINE1_LCD); 
        LCD_PrintS(msg);

        LCD_Cmd(LINE1_LCD + 6);
        LCD_PrintS(HSName);


        // Score
        LCD_Cmd(LINE2_LCD); 
        LCD_PrintS(msg2);

        LCD_Cmd(LINE2_LCD + 12);
        LCD_PrintInt(HSScore);


        // Date
        LCD_Cmd(LINE3_LCD);
        LCD_PrintS(msg3);

        LCD_Cmd(LINE3_LCD + 8);
        LCD_PrintBCD(HSdate);

        LCD_Cmd(LINE3_LCD + 10);
        LCD_PrintS("/");

        LCD_Cmd(LINE3_LCD + 11);
        LCD_PrintBCD(HSmonth);

        LCD_Cmd(LINE3_LCD + 13);
        LCD_PrintS("/");

        LCD_Cmd(LINE3_LCD + 14);
        LCD_PrintBCD(HSyear);


        // Time
        LCD_Cmd(LINE4_LCD);
        LCD_PrintS(msg4);

        LCD_Cmd(LINE4_LCD + 8);
        LCD_PrintBCD(HShour);

        LCD_Cmd(LINE4_LCD + 10);
        LCD_PrintS(":");

        LCD_Cmd(LINE4_LCD + 11);
        LCD_PrintBCD(HSmin);
    }
}

void changeDateTimeHome(void)
{
    LCD_Cmd(CLR_LCD);
    LCD_Cmd(LINE2_LCD + 6);
    
    LCD_PrintS("Edit");
    
    LCD_Cmd(LINE3_LCD + 3);
    LCD_PrintS("Date & Time");
    
    LCD_Cmd(LINE4_LCD);
    LCD_PrintS("Press B1");
}

void changeTimeDateScreen(void)
{
    LCD_Cmd(CLR_LCD);
    
    LCD_Cmd(LINE2_LCD + 1);
    LCD_PrintS("Time  Date");
    
    LCD_Cmd(LINE3_LCD + 1);
    for (int i = 0; i < 5; i++)
    {
        if (i == 1)
        {
            LCD_PrintC(':');
        }
        else if (i == 2)
        {
            LCD_PrintC(' ');
        }
        else if (i == 3 || i == 4)
        {
            LCD_PrintC('/');
        }
        
        if (setDateTimeVal[i] < 10)
        {
            LCD_PrintC('0');
        }
        
        LCD_PrintInt(setDateTimeVal[i]);
    }
    
    LCD_Cmd(LINE4_LCD+4);
    LCD_PrintS("CONFIRM");

    // Move cursor to "CONFIRM"
    if (cursorDT == 20)
    {
        LCD_Cmd(CUR_OFF);

        LCD_Cmd(LINE4_LCD + 3);
        LCD_PrintC(1);
        LCD_Cmd(LINE4_LCD + 11);
        LCD_PrintC(0);
    }
    else
    {
        LCD_Cmd(CUR_ON);
        LCD_Cmd(LINE3_LCD + cursorDT);    
    }
}

void changeDateTimeComplete(void)
{
    LCD_Cmd(CLR_LCD);
    LCD_Cmd(LINE2_LCD + 1);
    
    LCD_PrintS("Date and Time");
    
    LCD_Cmd(LINE3_LCD + 6);
    
    LCD_PrintS("Saved");
    
    delayAdjusted(3000);
    pageNumber = 13;
    pageChanged = 1;
}

// Game winner
void winnerScreen(void)
{
    char msg1[] = "The winner is...";
    char msg2[] = "no one,its a tie";

    LCD_Cmd(CLR_LCD);

    LCD_Cmd(LINE2_LCD);
    LCD_PrintS(msg1);

    LCD_Cmd(LINE3_LCD + 5);

    delayAdjusted(2000);
    if (playerOneScore > playerTwoScore || playerOneDiff < playerTwoDiff)
    {
        LCD_PrintS(playerOneName);
    }
    else if (playerOneScore < playerTwoScore || playerOneDiff > playerTwoDiff)
    {
        LCD_PrintS(playerTwoName);
    }
    else 
    {
        LCD_Cmd(LINE3_LCD);
        LCD_PrintS(msg2);
    }
}


void setBacklightDuty(uint8_t percent)
{
    uint16_t dutyVal =
        ((uint32_t)percent * 4UL * ((uint32_t)PR2 + 1UL)) / 100UL;

    PWM2_LoadDutyValue(dutyVal);

}


/// LCD CONVERSION HELPERS

void LCD_PrintInt(int val)
{
    if (val >= 1000)
    {
        LCD_PrintC(((val / 1000) % 10) + '0');
    }

    if (val >= 100)
    {
        LCD_PrintC(((val / 100) % 10) + '0');
    }

    if (val >= 10)
    {
        LCD_PrintC(((val / 10) % 10) + '0');
    }

    LCD_PrintC((val % 10) + '0');
}


void LCD_PrintBCD(char bcd)
{
    char high = (bcd >> 4) & 0x0F;
    char low = bcd & 0x0F;

    LCD_PrintC(high + '0');
    LCD_PrintC(low + '0');
}