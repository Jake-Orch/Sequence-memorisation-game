# 1 "Definitions.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "Definitions.c" 2
# 1 "./Definitions.h" 1



# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\stdint.h" 1 3



# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\musl_xc8.h" 1 3
# 4 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\stdint.h" 2 3
# 22 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 135 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long uintptr_t;
# 150 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long intptr_t;
# 166 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\bits/alltypes.h" 3
typedef signed char int8_t;




typedef short int16_t;




typedef __int24 int24_t;




typedef long int32_t;





typedef long long int64_t;
# 196 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long long intmax_t;





typedef unsigned char uint8_t;




typedef unsigned short uint16_t;




typedef __uint24 uint24_t;




typedef unsigned long uint32_t;





typedef unsigned long long uint64_t;
# 237 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long long uintmax_t;
# 22 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\stdint.h" 2 3


typedef int8_t int_fast8_t;

typedef int64_t int_fast64_t;


typedef int8_t int_least8_t;
typedef int16_t int_least16_t;

typedef int24_t int_least24_t;

typedef int32_t int_least32_t;

typedef int64_t int_least64_t;


typedef uint8_t uint_fast8_t;

typedef uint64_t uint_fast64_t;


typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;

typedef uint24_t uint_least24_t;

typedef uint32_t uint_least32_t;

typedef uint64_t uint_least64_t;
# 155 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\bits/stdint.h" 1 3
typedef int32_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint32_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
# 155 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\stdint.h" 2 3
# 4 "./Definitions.h" 2

# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.05\\pic\\include\\c99\\stdbool.h" 1 3
# 5 "./Definitions.h" 2
# 62 "./Definitions.h"
extern volatile uint8_t pageNumber;
extern volatile _Bool pageChanged;
extern volatile _Bool wakeFlag;

extern _Bool firstLoad;
extern volatile int inactiveTime;





extern uint8_t lastENC1;

extern uint8_t cursorX;
extern uint8_t cursorY;
extern uint8_t nameIndex;

extern uint8_t playerCountCursor;





extern _Bool usartName;

extern uint8_t index;
extern char inputString[10];





extern uint8_t playerCount;
extern uint8_t playerTurn;

extern _Bool nameConfirm;

extern char selectedName[10];
extern char soloName[5];
extern char playerOneName[5];
extern char playerTwoName[5];





extern uint8_t gameNumbers[10];

extern uint8_t roundNum;
extern uint8_t correctAnswer;

extern uint8_t soloScore;
extern uint8_t playerOneScore;
extern uint8_t playerTwoScore;





extern _Bool timeGameFlag;
extern _Bool timeEggEnable;
extern _Bool timeLoadScreen;

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





extern uint8_t highScoreIteration;

extern char savedName[5];
extern char HSName[5];

extern uint8_t HSScore;

extern char HSmin;
extern char HShour;
extern char HSdate;
extern char HSmonth;
extern char HSyear;





extern unsigned char seconds;
extern unsigned char minute;
extern unsigned char hour;
extern unsigned char date;
extern unsigned char month;
extern unsigned char year;

extern uint8_t setDateTimeVal[5];
extern uint8_t cursorDT;





extern float batteryVoltageAcc;

extern uint8_t adcCheck;
extern uint8_t adcCheckTime;

extern uint8_t clockFactor;
extern uint8_t currentBattState;





extern const char arrowLeft[8];
extern const char arrowRight[8];





extern volatile char userInput;


extern const char arrowLeft[8];
extern const char arrowRight[8];


void retrieveHighScores(int iteration);

void nameHandler(void);
# 1 "Definitions.c" 2


volatile char userInput = 0;

const char arrowLeft[8] = {
  0b00000010,
  0b00000100,
  0b00001000,
  0b00010000,
  0b00001000,
  0b00000100,
  0b00000010,
  0b00000000
};
const char arrowRight[8] = {
  0b00001000,
  0b00000100,
  0b00000010,
  0b00000001,
  0b00000010,
  0b00000100,
  0b00001000,
  0b00000000
};
