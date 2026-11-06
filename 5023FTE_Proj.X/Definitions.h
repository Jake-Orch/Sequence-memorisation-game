#ifndef DEFINITIONS_H
#define	DEFINITIONS_H

#include <stdint.h>
#include <stdbool.h>
/*==============================================================================
 * HARDWARE PIN DEFINITIONS
 *==============================================================================*/
#define BTN1            PORTBbits.RB0   
#define BTN2            PORTBbits.RB1   
#define BTN3            PORTBbits.RB2   
#define BTN4            PORTBbits.RB3   

#define ENC1            PORTBbits.RB4
#define ENC2            PORTBbits.RB5
#define BTNR            PORTBbits.RB6

#define BUZZ            LATCbits.LC2


#define LED1            LATAbits.LA1
#define LED2            LATAbits.LA2        
#define LED3            LATAbits.LA4
#define LED4            LATAbits.LA5

#define WAKEUP          BAUDCONbits.WUE // Wakeup mode

/*==============================================================================
 * DS3231 DEFINITIONS
 *==============================================================================*/
#define DS3231_CTRL_CODE        0x0D
#define DS3231_BLOCK            0x00

#define I2C_WRITE               0
#define I2C_READ                1

#define DS3231_ADDRESS          0x68

#define DS3231_WRITE            0xD0                // DS3231 Slave address + Write bit
#define DS3231_READ             0xD1                // DS3231 Slave address + Read bit
#define hour_12_PM              0x60                // Value that configures 12PM 
#define hour_12_AM              0x40                // Value that configures 12AM
#define hour_10                 0x10                // Value that configures hours between 10 and 19
#define hour_20                 0x20                // Value that configures hours between 20 and 23 
#define DS3231_CLOCK_ADDR       0                   // DS3231 register address for accessing the Time data
#define DS3231_CALENDAR_ADDR    3                   // DS3231 register address for accessing the Date data


/*==============================================================================
 * SYSTEM DEFINITIONS
 *==============================================================================*/

#define MAX_SCORES      10
#define NAME_LENGTH     4

#define MIN_BATT        715         // Critically low battery value - shut off system
#define MED_BATT        775         // Middling battery value - Assume low power mode

/*==============================================================================
 * SYSTEM STATE
 *==============================================================================*/
extern volatile uint8_t pageNumber;
extern volatile bool pageChanged;
extern volatile bool wakeFlag;

extern bool firstLoad;
extern volatile int inactiveTime;


/*==============================================================================
 * INPUT / NAVIGATION
 *==============================================================================*/
extern uint8_t lastENC1;

extern uint8_t cursorX;
extern uint8_t cursorY;
extern uint8_t nameIndex;

extern uint8_t playerCountCursor;


/*==============================================================================
 * EUSART
 *==============================================================================*/
extern bool usartName;

extern uint8_t index;
extern char inputString[10];


/*==============================================================================
 * PLAYER INFORMATION
 *==============================================================================*/
extern uint8_t playerCount;
extern uint8_t playerTurn;

extern bool nameConfirm;

extern char selectedName[10];
extern char soloName[5];
extern char playerOneName[5];
extern char playerTwoName[5];


/*==============================================================================
 * SEQUENTIAL GAME
 *==============================================================================*/
extern uint8_t gameNumbers[10];

extern uint8_t roundNum;
extern uint8_t correctAnswer;

extern uint8_t soloScore;
extern uint8_t playerOneScore;
extern uint8_t playerTwoScore;


/*==============================================================================
 * TIME GAME
 *==============================================================================*/
extern bool timeGameFlag;
extern bool timeEggEnable;
extern bool timeLoadScreen;

extern uint8_t timeGameSeq;
extern uint8_t gameTime;

extern volatile int gameRunTime;

extern int soloTime;
extern int playerOneTime;
extern int playerTwoTime;

extern int soloTimeDiff;
extern int playerOneDiff;
extern int playerTwoDiff;

extern uint8_t timeNumSep[4];


/*==============================================================================
 * HIGH SCORES / EEPROM
 *==============================================================================*/
extern uint8_t highScoreIteration;

extern char savedName[5];
extern char HSName[5];

extern uint8_t HSScore;

extern char HSmin;
extern char HShour;
extern char HSdate;
extern char HSmonth;
extern char HSyear;


/*==============================================================================
 * RTC / DATE AND TIME
 *==============================================================================*/
extern unsigned char seconds;
extern unsigned char minute;
extern unsigned char hour;
extern unsigned char date;
extern unsigned char month;
extern unsigned char year;

extern uint8_t setDateTimeVal[5];
extern uint8_t cursorDT;


/*==============================================================================
 * POWER MANAGEMENT / ADC
 *==============================================================================*/
extern float batteryVoltageAcc;

extern uint8_t adcCheck;
extern uint8_t adcCheckTime;

extern uint8_t clockFactor;
extern uint8_t currentBattState;


/*==============================================================================
 * LCD CUSTOM CHARACTERS
 *==============================================================================*/
extern const char arrowLeft[8];
extern const char arrowRight[8];


/*==============================================================================
 * SHARED VARIABLES DEFINED IN OTHER MODULES
 *==============================================================================*/
extern volatile char userInput;


extern const char arrowLeft[8];
extern const char arrowRight[8];


void retrieveHighScores(int iteration);

void nameHandler(void);

#endif	/* DEFINITIONS_H */

