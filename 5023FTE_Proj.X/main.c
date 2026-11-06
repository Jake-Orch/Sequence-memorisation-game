#include "mcc_generated_files/mcc.h"     // Include all MCC generated libraries */
#include "lcd.h"                         // Include LCD library                 */
#include "LCD_Display.h"
#include "simple_i2c.h"
#include "helper.h"
#include "EusartN.h"
#include "PeriphInt.h"
#include "EEPROM.h"
#include "seqGameLogic.h"
#include "timeGameLogic.h"
#include "power.h"
#include "Definitions.h"
#include <stdint.h>
#include <string.h>

// FUNCTION INITIALIZERS

void resetValues(void);

// VARIABLE INITIALISERS
/*==============================================================================
 * SYSTEM STATE
 *==============================================================================*/
volatile uint8_t pageNumber = 1;
volatile bool pageChanged = true;
volatile bool wakeFlag = true;

bool firstLoad = true;
volatile int inactiveTime = 0;


/*==============================================================================
 * INPUT / NAVIGATION
 *==============================================================================*/
uint8_t lastENC1 = 0;

uint8_t cursorX = 0;
uint8_t cursorY = 0;
uint8_t nameIndex = 0;

uint8_t playerCountCursor = 1;


/*==============================================================================
 * EUSART
 *==============================================================================*/
bool usartName = false;

uint8_t index = 0;
char inputString[10] = "";


/*==============================================================================
 * PLAYER INFORMATION
 *==============================================================================*/
uint8_t playerCount = 0;
uint8_t playerTurn = 1;

bool nameConfirm = false;

char selectedName[10] = "";
char soloName[5] = "";
char playerOneName[5] = "";
char playerTwoName[5] = "";


/*==============================================================================
 * SEQUENTIAL GAME
 *==============================================================================*/
uint8_t gameNumbers[10] = {0};

uint8_t roundNum = 1;
uint8_t correctAnswer = 0;

uint8_t soloScore = 0;
uint8_t playerOneScore = 0;
uint8_t playerTwoScore = 0;


/*==============================================================================
 * TIME GAME
 *==============================================================================*/
bool timeGameFlag = false;
bool timeEggEnable = false;
bool timeLoadScreen = false;

uint8_t timeGameSeq = 0;
uint8_t gameTime = 0;

volatile int gameRunTime = 0;

int soloTime = 999;
int playerOneTime = 999;
int playerTwoTime = 999;

int soloTimeDiff = 999;
int playerOneDiff = 999;
int playerTwoDiff = 999;

uint8_t timeNumSep[4] = {0};


/*==============================================================================
 * HIGH SCORES / EEPROM
 *==============================================================================*/
uint8_t highScoreIteration = 0;

char savedName[5] = "";
char HSName[5] = "";

uint8_t HSScore = 0;

char HSmin = 0;
char HShour = 0;
char HSdate = 0;
char HSmonth = 0;
char HSyear = 0;


/*==============================================================================
 * RTC / DATE AND TIME
 *==============================================================================*/
unsigned char seconds = 0;
unsigned char minute = 0;
unsigned char hour = 0;
unsigned char date = 0;
unsigned char month = 0;
unsigned char year = 0;

uint8_t setDateTimeVal[5] = {0};
uint8_t cursorDT = 1;


/*==============================================================================
 * POWER MANAGEMENT / ADC
 *==============================================================================*/
float batteryVoltageAcc = 0.0f;

uint8_t adcCheck = 0;
uint8_t adcCheckTime = 0;

uint8_t clockFactor = 1;
uint8_t currentBattState = 0;



void main(void)
{
    
    SYSTEM_Initialize();
    
    WAKEUP = 0;          // Normal UART reception (disable wakeup mode)
    
    // Setup LCD
    delayAdjusted(100);
    LCD_Init();
    delayAdjusted(100);
    LCD_Cmd(CLR_LCD);
    LCD_Cmd(CUR_OFF);
    
    // Load LCD icons
    LCD_CreateC(LCD_ADDR0, arrowLeft);
    LCD_CreateC(LCD_ADDR1, arrowRight);
    
    // Setup timers
    TMR2_StartTimer();
    PWM2_LoadDutyValue(1000);
    TMR3_StopTimer();
    
    // Setup Interrupts
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
    INT0_SetInterruptHandler(INT0_CustomISR);
    INT1_SetInterruptHandler(INT1_CustomISR);
    INT2_SetInterruptHandler(INT2_CustomISR);
    
    TMR1_SetInterruptHandler(TMR1_CustomISR);
    TMR3_SetInterruptHandler(TMR3_CustomISR);

    
    I2C_Open(DS3231_ADDRESS);
    //    setDateTime();
    
    // initialise rotary encoder
    lastENC1 = ENC1;
//    setDateTime();
    
    while(1)
    {           
        // Only change page when pageChanged flag is set
        if (pageChanged)
        {
            
            pageChanged = 0;                    // Reset pageChanged flag
            SendEusartString("\033[2J\033[H");  // Clear terminal

            /// Page handling logic
            switch (pageNumber)
            {
                case 1:
                    EUhomePage();
                    homePage();
                    break;

                case 2:
                    EUplayerChoice();
                    playerChoice();
                    break;

                case 3:
                    EUwriteNames();
                    writeNames();
                    break;

                case 4:
                    EUcountDown();
                    countDown();
                    break;

                case 5:
                    seqGameHandler();
                    break;

                case 6:
                    EUscoreScreen();
                    scoreScreen();
                    break;
                case 7:
                    EUtimeHomePage();
                    timeHomePage();
                    break;
                case 8:
                    timeGameSeed();
                    EUtimeDisplay();
                    timeDisplay();
                    break;
                case 9:
                    timeGameResponseLogic();
                    break;
                case 10:
                    EUtimeResultDisplay();
                    timeResultDisplay();
                    break;
                case 11:
                    changeTimeDateScreen();
                    break;
                case 12:
                    changeDateTimeComplete();
                    break;
                case 13:
                    changeDateTimeHome();
                    break;
                case 16:
                    EUwinnerScreen();
                    winnerScreen();
                    break;
                case 19:
                    savedScoresHome();
                    break;
                case 20:
                    retrieveHighScores(highScoreIteration);
                    EUsavedScores();
                    savedScores();
                    break;
            }
        }
        
        if (pageNumber == 3)
        {
            nameHandler();
        }
        
        // Poll over EUSART and rotary encoder for inputs
        EusartRX();
        rotaryEncoderPolling();
        
        // Poll over wake flag to send system to sleep
        while (!wakeFlag)
        {
            customSleep();
            customWake();
        }
    };
}

// To reset all game values - Unused
void resetValues(void)
{
    selectedName[0] = '\0';
    savedName[0] = '\0';

    soloName[0] = '\0';
    playerOneName[0] = '\0';
    playerTwoName[0] = '\0';
    
    nameConfirm = 0;
    correctAnswer = 0;
    soloScore = 0;
    playerOneScore = 0;
    playerTwoScore = 0;
    
    highScoreIteration = 0;
    playerCountCursor = 0;
    playerCount = 0;
    firstLoad = 1;

    nameIndex = 0;
    cursorX = 0;
    cursorY = 0;
}

// To handle the assignment of player names through USART and LCD
void nameHandler(void)
{
    // Use USART name
    if (usartName)
    {
        selectedName[0] = inputString[0];
        selectedName[1] = inputString[1];
        selectedName[2] = inputString[2];
        selectedName[3] = inputString[3];
        usartName = 0;
    }
    
    if (nameConfirm)
    {
        if (playerCount == 2 && playerTurn == 1)
        {
            // Assign playerOneName
            playerOneName[0] = selectedName[0];
            playerOneName[1] = selectedName[1];
            playerOneName[2] = selectedName[2];
            playerOneName[3] = selectedName[3];
            playerOneName[4] = selectedName[4];

            // Reset values
            nameConfirm = 0;            
            selectedName[0] = '\0';     

            nameIndex = 0;
            cursorX = 0;
            cursorY = 0;

            playerTurn = 2;
            
            // Clear name from LCD
            pageChanged = 1;
            LCD_Cmd(LINE4_LCD);
            LCD_PrintS("                ");

            updateNameCursor();     // Return cursor on LCD
        }
        else if (playerCount == 2 && playerTurn == 2)
        {
            // Assign playerTwoName
            playerTwoName[0] = selectedName[0];
            playerTwoName[1] = selectedName[1];
            playerTwoName[2] = selectedName[2];
            playerTwoName[3] = selectedName[3];
            playerTwoName[4] = selectedName[4];
            
            // Reset values
            nameConfirm = 0;
            selectedName[0] = '\0';

            nameIndex = 0;
            cursorX = 0;
            cursorY = 0;

            playerTurn = 1;
            
            // Route to the correct game based on timeGameFlag
            if (timeGameFlag)
            {
                pageNumber = 8; // timeGame page
            }
            else 
            {
                pageNumber++;   // seqGame page
            }
            pageChanged = 1;

            LCD_Cmd(CUR_OFF);
        }
        else
        {
            // Assign soloName
            soloName[0] = selectedName[0];
            soloName[1] = selectedName[1];
            soloName[2] = selectedName[2];
            soloName[3] = selectedName[3];
            soloName[4] = selectedName[4];
            
            // Reset values
            nameConfirm = 0;
            selectedName[0] = '\0';
            
            nameIndex = 0;
            cursorX = 0;
            cursorY = 0;
            
            // Route to the correct game based on timeGameFlag
            if (timeGameFlag)
            {
                pageNumber = 8;     // timeGame page
            }
            else 
            {
                pageNumber++;       // seqGame page
            }
            pageChanged = 1;

            LCD_Cmd(CUR_OFF);
        }
    }   
}