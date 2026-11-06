#ifndef __LCD_H                         //                                                */
#define __LCD_H                         //                                                */
/*========================================================================================*/
//#define c18                           // Uncomment if C18 Compiler is used              */
#define xc8                             // Uncomment if XC8 Compiler is used              */
/*========================================================================================*/
#include "p18cxxx.h"                    // Include PIC18 related definitions              */
#include <stdlib.h>                     // Includes the itoa conversion functions         */
#ifdef c18                              // If C18 is used                                 */
#include <delays.h>                     // Include delays library                         */
#endif                                  //                                                */
/*============ LCD HARDWARE PARAMETERS, CHANGE AS NEEDED =================================*/
/*                                                                                        */
/*          The below characteristics must be defined in the lcd.h file!                  */
/*                                                                                        */
/* 1. Define the display type being used by uncommenting one of the statements below:     */
/*                                                                                        */
//#define LCD_16x1          1           // Uncomment if using LCD of type 16x1 = 0x01     */
//#define LCD_16x2          2           // Uncomment if using LCD of type 16x2 = 0x02     */
#define LCD_16x4            3           // Uncomment if using LCD of type 16x4 = 0x03     */
//#define LCD_20x1          4           // Uncomment if using LCD of type 20x1 = 0x04     */
//#define LCD_20x2          5           // Uncomment if using LCD of type 20x2 = 0x05     */
//#define LCD_20x4          6           // Uncomment if using LCD of type 20x4 = 0x06     */
/*=========MICROCONTROLLER SPECIFIC CONFIGURATIONS =======================================*/
/* 2. Define the port being used to control the LCD by uncommenting one statement below:  */
/*                                                                                        */
//#define DATA_PORTA        0           // Uncomment if using LCD on PORTA                */
//#define DATA_PORTB        1           // Uncomment if using LCD on PORTB                */
//#define DATA_PORTC        2           // Uncomment if using LCD on PORTC                */
#define DATA_PORTD          3           // Uncomment if using LCD on PORTD                */
/*                                                                                        */
/* DATA_PORT Can be set to be: LATA, LATB, LATC, or LATD <- lower nibble used             */
/* TRIS_DATA_PORT - is handled automatically by the library                               */
/* E_PIN  - is always the 4th bit of the selected port, handled automatically             */
/* RS_PIN - is always the 5th bit of the selected port, handled automatically             */
/* RW_PIN - is always the 6th bit of the selected port, unless PORTA is selected          */
/* In the case PORTA is used RW_PIN must be connected to GND, handled automatically       */
/*                                                                                        */
/* 3. Define the clock speed you are using for the PIC by uncommenting 1 statement below: */
/* Supported Clock speeds: 40MHz, 20MHz, 16MHz, 10MHz, 8MHz, 5MHz, 4MHz, 2MHz, 1MHz       */
/*                                                                                        */
//#define CLK_40             0         // Uncomment if using the 40 MHz clock source      */
#define CLK_20               1         // Uncomment if using the 20 MHz clock source      */
//#define CLK_16             2         // Uncomment if using the 16 MHz clock source      */
//#define CLK_10             3         // Uncomment if using the 10 MHz clock source      */
//#define CLK_8              4         // Uncomment if using the  8 MHz clock source      */
//#define CLK_5              5         // Uncomment if using the  5 MHz clock source      */
//#define CLK_4              6         // Uncomment if using the  4 MHz clock source      */
//#define CLK_2              7         // Uncomment if using the  2 MHz clock source      */
//#define CLK_1              8         // Uncomment if using the  1 MHz clock source      */
/*                                                                                        */
/* If different speed is desired, calculate 1ms delay based on that speed & replace       */
/* ALl instances of LCD_Wait() in this file with the newly calculated delay               */
/*                                                                                        */
/*=============== LIST OF LCD COMMANDS ===================================================*/
#define CLR_LCD           0x01          // Clear the LCD                                  */
#define HOME_LCD          0x02          // Reset LCD                                      */
                                        //                                                */
#define LCD_ON            0x0F          // Turn Display on                                */
#define LCD_OFF           0x0B          // Turn Display off                               */
#define CUR_ON            0x0F          // Cursor on                                      */
#define CUR_OFF           0x0C          // Cursor off                                     */
#define CUR_BLINK_ON      0x0F          // Cursor Blink on                                */
#define CUR_BLINK_OFF     0x0E          // Cursor Blink off                               */
                                        //                                                */
#ifdef LCD_16x1                         // If user is using 16x1 LCD                      */
#   define LINE1_LCD      0x80          // Move cursor to line 1 of LCD command is 80     */
#endif                                  //                                                */
#ifdef LCD_16x2                         // If user is using 16x2 LCD                      */
#   define LINE1_LCD      0x80          // Move cursor to line 1 of LCD command is 80     */
#   define LINE2_LCD      0xC0          // Move cursor to line 2 of LCD command is C0     */
#endif                                  //                                                */
#ifdef LCD_16x4                         // If user is using 16x4 LCD                      */
#   define LINE1_LCD      0x80          // Move cursor to line 1 of LCD command is 80     */
#   define LINE2_LCD      0xC0          // Move cursor to line 2 of LCD command is C0     */
#   define LINE3_LCD      0x90          // Move cursor to line 3 of LCD command is 90     */
#   define LINE4_LCD      0xD0          // Move cursor to line 4 of LCD command is D0     */
#endif                                  //                                                */
#ifdef LCD_20x1                         // If user is using 20x1 LCD                      */
#   define LINE1_LCD      0x80          // Move cursor to line 1 of LCD command is 80     */
#endif                                  //                                                */
#ifdef LCD_20x2                         // If user is using 20x2 LCD                      */
#   define LINE1_LCD      0x80          // Move cursor to line 1 of LCD command is 80     */
#   define LINE2_LCD      0xC0          // Move cursor to line 2 of LCD command is C0     */
#endif                                  //                                                */
#ifdef LCD_20x4                         // If user is using 20x4 LCD                      */
#   define LINE1_LCD      0x80          // Move cursor to line 1 of LCD command is 80     */
#   define LINE2_LCD      0xC0          // Move cursor to line 2 of LCD command is C0     */
#   define LINE3_LCD      0x94          // Move cursor to line 3 of LCD command is 94     */
#   define LINE4_LCD      0xD4          // Move cursor to line 4 of LCD command is D4     */
#endif                                  //                                                */
                                        // Cursor/Display Shift command definitions       */
#define SHIFT_CUR_LEFT    0x10          // Cursor shifts to the left                      */
#define SHIFT_CUR_RIGHT   0x14          // Cursor shifts to the right                     */
#define SHIFT_DISP_LEFT   0x18          // Display shifts to the left                     */
#define SHIFT_DISP_RIGHT  0x1C          // Display shifts to the right                    */
                                        //                                                */
#define LCD_ADDR0         0x00          // Memory address 0 available for custom chars    */
#define LCD_ADDR1         0x01          // Memory address 1 available for custom chars    */
#define LCD_ADDR2         0x02          // Memory address 2 available for custom chars    */
#define LCD_ADDR3         0x03          // Memory address 3 available for custom chars    */
#define LCD_ADDR4         0x04          // Memory address 4 available for custom chars    */
#define LCD_ADDR5         0x05          // Memory address 5 available for custom chars    */
#define LCD_ADDR6         0x06          // Memory address 6 available for custom chars    */
#define LCD_ADDR7         0x07          // Memory address 7 available for custom chars    */
/*========================================================================================*/
/* LCD_Init                                                                               */
/* Initialises the LCD, library does not support 8-bit mode. Font settings affect only the*/
/* custom generated characters                                                            */
void LCD_Init(void);                    // Initialise the LCD                             */
/*========================================================================================*/
/* LCD_Cmd                                                                                */
/* Handles the functional commands for the LCD                                            */
void LCD_Cmd(unsigned char cmd);        // Call function & pass one of the commands listed*/
/* Example:                                                                               */
/* LCD_Cmd(CLR_LCD);                    // Commands the LCD to clear all text             */
/*========================================================================================*/
/* LCD_PrintC                                                                             */
/* Writes a single character to the LCD                                                   */
void LCD_PrintC(unsigned char byte);    // Display single character on cursor position    */
/* Example:                                                                               */
/* Input parameter "byte"  has to be ASCII                                                */
/* LCD_PrintC('h')                      // Prints lower case h on cursor position         */
/*========================================================================================*/
/* LCD_PrintS                                                                             */
/* Writes a string of characters to the LCD from Data memory                              */
void LCD_PrintS(char *buf);             // Prints contents of "buf" on the LCD            */
/* Example:                                                                               */
/* Input parameter 1: char msg[] = "MESSAGE"; // Array variable declared & defined        */
/* LCD_PrintS(msg);                     // Print the contents of msg array on LCD         */
/*========================================================================================*/
#ifdef c18                               //                                               */
/* LCD_PrintRS                                                                            */
/* Writes a string of characters from the PIC's ROM to the LCD                            */
void LCD_PrintRS(const rom char *buf);  // Print a buffer from ROM to LCD                 */
/* Example:                                                                               */
/* Input parameter 1: "ANY STRING"      // Type the text you want printed inside ""       */
/* LCD_PrintRS("My string");            // Prints "My string" on LCD on cursor position   */
/*========================================================================================*/
/* LCD_CreateC                                                                            */
/* Function used to create & store custom characters to LCD RAM                           */
void LCD_CreateC(unsigned int DRAM_pos, const rom char *char_data); // Write char at addr */
/* Example:                                                                               */
/* Input parameter 1: Any of the above-defined LCD addresses                              */
/* Input parameter 2: char array 8x8 i.e:                                                 */
/* char heart[8] = {                     // Full Heart custom character pixel data        */
/*        0b00000000,                    // 1st row     ________                          */
/*        0b00000000,                    // 2nd row     ________                          */
/*        0b00001010,                    // 3rd row     ____*_*_                          */
/*        0b00011111,                    // 4th row     ___*****                          */
/*        0b00011111,                    // 5th row     ___*****                          */
/*        0b00001110,                    // 6th row     ____***_                          */
/*        0b00000100,                    // 7th row     _____*__                          */
/*        0b00000000                     // 8th row - reserved for cursor DO NOT USE      */
/*        };                             //                                               */
/* LCD_CreateC(LCD_ADDR0, heart);        // Stores heart char data into ADDR0 of LCD RAM  */
/* To print the custom char:             //                                               */
/* LCD_PrintC(ADDR0);                    // Prints the char stored in address 0x00        */
/*========================================================================================*/
/* LCD_Wait_C18                                                                           */
/* Delay used to communicate with LCD, System CLK dependant                               */
void LCD_Wait_C18(void);                 // Based on the system clock it delays for 1ms   */
#endif                                   //                                               */
#ifdef xc8                               //                                               */
/* LCD_PrintRS                                                                            */
/* Writes a string of characters from the PIC's ROM to the LCD                            */
void LCD_PrintRS(const char *buf);      // Print a buffer from ROM to LCD                 */
/* Example:                                                                               */
/* Input parameter 1: "ANY STRING"      // Type the text you want printed inside ""       */
/* LCD_PrintRS("My string");            // Prints "My string" on LCD on cursor position   */
/*========================================================================================*/
/* LCD_CreateC                                                                            */
/* Function used to create & store custom characters to LCD RAM                           */
void LCD_CreateC(unsigned int DRAM_pos, const char *char_data);     // Write char at addr */
/* Example:                                                                               */
/* Input parameter 1: Any of the above-defined LCD addresses                              */
/* Input parameter 2: char array 8x8 i.e:                                                 */
/* char heart[8] = {                     // Full Heart custom character pixel data        */
/*        0b00000000,                    // 1st row     ________                          */
/*        0b00000000,                    // 2nd row     ________                          */
/*        0b00001010,                    // 3rd row     ____*_*_                          */
/*        0b00011111,                    // 4th row     ___*****                          */
/*        0b00011111,                    // 5th row     ___*****                          */
/*        0b00001110,                    // 6th row     ____***_                          */
/*        0b00000100,                    // 7th row     _____*__                          */
/*        0b00000000                     // 8th row - reserved for cursor DO NOT USE      */
/*        };                             //                                               */
/* LCD_CreateC(LCD_ADDR0, heart);        // Stores heart char data into ADDR0 of LCD RAM  */
/* To print the custom char:             //                                               */
/* LCD_PrintC(ADDR0);                    // Prints the char stored in address 0x00        */
/*========================================================================================*/
/* LCD_Wait_XC8                                                                           */
/* Delay used to communicate with LCD, System CLK dependant                               */
void LCD_Wait_XC8(void);                 // Based on the system clock it delays for 1ms   */
#endif                                   //                                               */
/*========================================================================================*/
/*                      CUSTOM LCD SYMBOLS                                                */
/*========================================================================================*/
#ifdef c18                                   // If C18 is used                            */
static const rom char full_heart[8] = {      // Full Heart custom character pixel data    */
  0b00000000,                                // 1st row     ________                      */
  0b00000000,                                // 2nd row     ________                      */
  0b00001010,                                // 3rd row     ____*_*_                      */
  0b00011111,                                // 4th row     ___*****                      */
  0b00011111,                                // 5th row     ___*****                      */
  0b00001110,                                // 6th row     ____***_                      */
  0b00000100,                                // 7th row     _____*__                      */
  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
};                                           //                                           */
static const rom char half_full_heart[8] = { // Half-Full Heart custom char data          */
  0b00000000,                                // 1st row     ________                      */
  0b00000000,                                // 2nd row     ________                      */
  0b00001010,                                // 3rd row     ____*_*_                      */
  0b00010101,                                // 4th row     ___*_*_*                      */
  0b00011111,                                // 5th row     ___*****                      */
  0b00001110,                                // 6th row     ____***_                      */
  0b00000100,                                // 7th row     _____*__                      */
  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
};                                           //                                           */
static const rom char qtr_full_heart[8] = {  // Quarter-Full Heart custom char data       */
  0b00000000,                                // 1st row     ________                      */
  0b00000000,                                // 2nd row     ________                      */
  0b00001010,                                // 3rd row     ____*_*_                      */
  0b00010101,                                // 4th row     ___*_*_*                      */
  0b00010001,                                // 5th row     ___*___*                      */
  0b00001110,                                // 6th row     ____***_                      */
  0b00000100,                                // 7th row     _____*__                      */
  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
};                                           //                                           */
static const rom char empty_heart[8]={       // Empty Heart custom character pixel data   */
  0b00000000,                                // 1st row     ________                      */
  0b00000000,                                // 2nd row     ________                      */
  0b00001010,                                // 3rd row     ____*_*_                      */
  0b00010101,                                // 4th row     ___*_*_*                      */
  0b00010001,                                // 5th row     ___*___*                      */
  0b00001010,                                // 6th row     ____*_*_                      */
  0b00000100,                                // 7th row     _____*__                      */
  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
};                                           //                                           */
static const rom char smiley[8] = {          // Smiley custom character pixel data        */
  0b00000000,                                // 1st row          ________                 */
  0b00001010,                                // 2nd row          ____*_*_                 */
  0b00001010,                                // 3rd row          ____*_*_                 */
  0b00000000,                                // 4th row          ________                 */
  0b00000100,                                // 5th row          _____*__                 */
  0b00010001,                                // 6th row          ___*___*                 */
  0b00001110,                                // 7th row          ____***_                 */
  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
};                                           //                                           */
static const rom char frownie[8] = {         // Frownie custom character pixel data       */
  0b00000000,                                // 1st row          ________                 */
  0b00001010,                                // 2nd row          ____*_*_                 */
  0b00000000,                                // 3rd row          ________                 */
  0b00000100,                                // 4th row          _____*__                 */
  0b00000000,                                // 5th row          ________                 */
  0b00001110,                                // 6th row          ____***_                 */
  0b00010001,                                // 7th row          ___*___*                 */
  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
};                                           //                                           */
static const rom char armsDown[8] = {        // Arms down human character data            */
  0b00000100,                                // 1st row          _____*__                 */
  0b00001010,                                // 2nd row          ____*_*_                 */
  0b00000100,                                // 3rd row          _____*__                 */
  0b00001110,                                // 4th row          ____***_                 */
  0b00010101,                                // 5th row          ___*_*_*                 */
  0b00000100,                                // 6th row          _____*__                 */
  0b00001010,                                // 7th row          ____*_*_                 */
  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
};                                           //                                           */
static const rom char armsUp[8] = {          // Arms up human character data              */
  0b00000100,                                // 1st row          _____*__                 */
  0b00001010,                                // 2nd row          ____*_*_                 */
  0b00000100,                                // 3rd row          _____*__                 */
  0b00010101,                                // 4th row          ___*_*_*                 */
  0b00001110,                                // 5th row          ____***_                 */
  0b00000100,                                // 6th row          _____*__                 */
  0b00001010,                                // 7th row          ____*_*_                 */
  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
};                                           //                                           */
static const rom char arrowUp[8] = {         // Arrow facing up character data            */
  0b00000100,                                // 1st row          _____*__                 */
  0b00001110,                                // 2nd row          ____***_                 */
  0b00010101,                                // 3rd row          ___*_*_*                 */
  0b00000100,                                // 4th row          _____*__                 */
  0b00000100,                                // 5th row          _____*__                 */
  0b00000100,                                // 6th row          _____*__                 */
  0b00000100,                                // 7th row          _____*__                 */
  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
};                                           //                                           */
static const rom char arrowDown[8] = {       // Arrow facing down character data          */
  0b00000100,                                // 1st row          _____*__                 */
  0b00001110,                                // 2nd row          _____*__                 */
  0b00010101,                                // 3rd row          _____*__                 */
  0b00000100,                                // 4th row          _____*__                 */
  0b00000100,                                // 5th row          ___*_*_*                 */
  0b00000100,                                // 6th row          ____***_                 */
  0b00000100,                                // 7th row          _____*__                 */
  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
};                                           //                                           */
static const rom char padlock_l[8] = {       // Locked padlock character data             */
  0b00001110,                                // 1st row          ____***_                 */
  0b00010001,                                // 2nd row          ___*___*                 */
  0b00010001,                                // 3rd row          ___*___*                 */
  0b00011111,                                // 4th row          ___*****                 */
  0b00011011,                                // 5th row          ___**_**                 */
  0b00011011,                                // 6th row          ___**_**                 */
  0b00011111,                                // 7th row          ___*****                 */
  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
};                                           //                                           */
static const rom char padlock_u[8] = {       // Unlocked padlock character data           */
  0b00001110,                                // 1st row          ____***_                 */
  0b00010000,                                // 2nd row          ___*____                 */
  0b00010000,                                // 3rd row          ___*____                 */
  0b00011111,                                // 4th row          ___*****                 */
  0b00011011,                                // 5th row          ___**_**                 */
  0b00011011,                                // 6th row          ___**_**                 */
  0b00011111,                                // 7th row          ___*****                 */
  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
};                                           //                                           */
static const rom char bell[8] = {            // Bell character data                       */
  0b00000100,                                // 1st row          _____*__                 */
  0b00001110,                                // 2nd row          ____***_                 */
  0b00001110,                                // 3rd row          ____***_                 */
  0b00001110,                                // 4th row          ____***_                 */
  0b00011111,                                // 5th row          ___*****                 */
  0b00000000,                                // 6th row          ________                 */
  0b00000100,                                // 7th row          _____*__                 */
  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
};                                           //                                           */
static const rom char plug[8] = {            // Plug character data                       */
  0b00001010,                                // 1st row          ____*_*_                 */
  0b00001010,                                // 2nd row          ____*_*_                 */
  0b00011111,                                // 3rd row          ___*****                 */
  0b00010001,                                // 4th row          ___*___*                 */
  0b00001110,                                // 5th row          ____***_                 */
  0b00000100,                                // 6th row          _____*__                 */
  0b00000100,                                // 7th row          _____*__                 */
  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
};                                           //                                           */
static const rom char note[8] = {            // Note character data                       */
  0b00000010,                                // 1st row          ______*_                 */
  0b00000011,                                // 2nd row          ______**                 */
  0b00000010,                                // 3rd row          ______*_                 */
  0b00000010,                                // 4th row          ______*_                 */
  0b00001110,                                // 5th row          ______*_                 */
  0b00011110,                                // 6th row          ____***_                 */
  0b00001100,                                // 7th row          ___****_                 */
  0b00000000                                 // 8th row          ____**__                 */
};                                           //                                           */
static const rom char notes[8] = {           // Notes character data                      */
  0b00000001,                                // 1st row          _______*                 */
  0b00000011,                                // 2nd row          ______**                 */
  0b00000101,                                // 3rd row          _____*_*                 */
  0b00001001,                                // 4th row          ____*__*                 */
  0b00001001,                                // 5th row          ____*__*                 */
  0b00001011,                                // 6th row          ____*_**                 */
  0b00011011,                                // 7th row          ___**_**                 */
  0b00011000                                 // 8th row          ___**___                 */
};                                           //                                           */
static const rom char arrowRight[8] ={       // Arrow Right character data                */
  0b00000000,                                // 1st row          ________                 */
  0b00000100,                                // 2nd row          _____*__                 */
  0b00000010,                                // 3rd row          ______*_                 */
  0b00011111,                                // 4th row          ___*****                 */
  0b00000010,                                // 5th row          ______*_                 */
  0b00000100,                                // 6th row          _____*__                 */
  0b00000000,                                // 7th row          ________                 */
  0b00000000                                 // 8th row          ________                 */
};                                           //                                           */
static const rom char arrowLeft[8] ={        // Arrow left character data                 */
  0b00000000,                                // 1st row          ________                 */
  0b00000100,                                // 2nd row          _____*__                 */
  0b00001000,                                // 3rd row          ____*___                 */
  0b00011111,                                // 4th row          ___*****                 */
  0b00001000,                                // 5th row          ____*___                 */
  0b00000100,                                // 6th row          _____*__                 */
  0b00000000,                                // 7th row          ________                 */
  0b00000000                                 // 8th row          ________                 */
};                                           //                                           */
static const rom char tick[8] = {            // Tick character data                       */
  0b00000000,                                // 1st row          ________                 */
  0b00000001,                                // 2nd row          _______*                 */
  0b00000011,                                // 3rd row          ______**                 */
  0b00010110,                                // 4th row          ___*_**_                 */
  0b00011100,                                // 5th row          ___***__                 */
  0b00001000,                                // 6th row          ____*___                 */
  0b00000000,                                // 7th row          ________                 */
  0b00000000                                 // 8th row          ________                 */
};                                           //                                           */
static const rom char spkr_on[8] = {         // Speaker_on character data                 */
  0b00000010,                                // 1st row          ______*_                 */
  0b00000110,                                // 2nd row          _____**_                 */
  0b00011110,                                // 3rd row          ___****_                 */
  0b00011110,                                // 4th row          ___****_                 */
  0b00011110,                                // 5th row          ___****_                 */
  0b00000110,                                // 6th row          _____**_                 */
  0b00000010,                                // 7th row          ______*_                 */
  0b00000000                                 // 8th row          ________                 */
};                                           //                                           */
static const rom char spkr_off[8] = {        // Speaker_off character data                */
  0b00000010,                                // 1st row          ______*_                 */
  0b00000110,                                // 2nd row          _____**_                 */
  0b00011010,                                // 3rd row          ___**_*_                 */
  0b00010010,                                // 4th row          ___*__*_                 */
  0b00011010,                                // 5th row          ___**_*_                 */
  0b00000110,                                // 6th row          _____**_                 */
  0b00000010,                                // 7th row          ______*_                 */
  0b00000000                                 // 8th row          ________                 */
};                                           //                                           */
static const rom char skull[8] = {           // Skull character data                      */
  0b00000000,                                // 1st row          ________                 */
  0b00000000,                                // 2nd row          ________                 */
  0b00001110,                                // 3rd row          ____***_                 */
  0b00010101,                                // 4th row          ___*_*_*                 */
  0b00011011,                                // 5th row          ___**_**                 */
  0b00001110,                                // 6th row          ____***_                 */
  0b00001110,                                // 7th row          ____***_                 */
  0b00000000                                 // 8th row          ________                 */
};                                           //                                           */
static const rom char empty_drop[8]={        // Empty Drop character data                 */
  0b00000100,                                // 1st row          _____*__                 */
  0b00000100,                                // 2nd row          _____*__                 */
  0b00001010,                                // 3rd row          ____*_*_                 */
  0b00001010,                                // 4th row          ____*_*_                 */
  0b00010001,                                // 5th row          ___*___*                 */
  0b00010001,                                // 6th row          ___*___*                 */
  0b00010001,                                // 7th row          ___*___*                 */
  0b00001110                                 // 8th row          ____***_                 */
};                                           //                                           */
static const rom char full_drop[8] = {       // Full Drop character data                  */
  0b00000100,                                // 1st row          _____*__                 */
  0b00000100,                                // 2nd row          _____*__                 */
  0b00001110,                                // 3rd row          ____***_                 */
  0b00001110,                                // 4th row          ____***_                 */
  0b00011111,                                // 5th row          ___*****                 */
  0b00011111,                                // 6th row          ___*****                 */
  0b00011111,                                // 7th row          ___*****                 */
  0b00001110                                 // 8th row          ____***_                 */
};                                           //                                           */
static const rom char termomtr_empty[8] = {  // Empty termometer character data           */
  0b00000100,                                // 1st row          _____*__                 */
  0b00001010,                                // 2nd row          ____*_*_                 */
  0b00001010,                                // 3rd row          ____*_*_                 */
  0b00001010,                                // 4th row          ____*_*_                 */
  0b00001010,                                // 5th row          ____*_*_                 */
  0b00010001,                                // 6th row          ___*___*                 */
  0b00010001,                                // 7th row          ___*___*                 */
  0b00001110                                 // 8th row          ____***_                 */
};                                           //                                           */
static const rom char termomtr_full[8] = {   // Full termometer character data            */
  0b00000100,                                // 1st row          _____*__                 */
  0b00001110,                                // 2nd row          ____***_                 */
  0b00001110,                                // 3rd row          ____***_                 */
  0b00001110,                                // 4th row          ____***_                 */
  0b00001110,                                // 5th row          ____***_                 */
  0b00011111,                                // 6th row          ___*****                 */
  0b00011111,                                // 7th row          ___*****                 */
  0b00001110                                 // 8th row          ____***_                 */
};                                           //                                           */
static const rom char termomtr_half[8] = {   // Half-Full termometer character data       */
  0b00000100,                                // 1st row          _____*__                 */
  0b00001010,                                // 2nd row          ____*_*_                 */
  0b00001010,                                // 3rd row          ____*_*_                 */
  0b00001010,                                // 4th row          ____*_*_                 */
  0b00001010,                                // 5th row          ____*_*_                 */
  0b00011111,                                // 6th row          ___*****                 */
  0b00011111,                                // 7th row          ___*****                 */
  0b00001110                                 // 8th row          ____***_                 */
};                                           //                                           */
static const rom char termomtr_qtr[8] = {    // Quarter-Full termometer char data         */
  0b00000100,                                // 1st row          _____*__                 */
  0b00001010,                                // 2nd row          ____*_*_                 */
  0b00001010,                                // 3rd row          ____*_*_                 */
  0b00001010,                                // 4th row          ____*_*_                 */
  0b00001010,                                // 5th row          ____*_*_                 */
  0b00011011,                                // 6th row          ___**_**                 */
  0b00011111,                                // 7th row          ___*****                 */
  0b00001110                                 // 8th row          ____***_                 */
};                                           //                                           */
static const rom char termomtr_3qtr[8] = {   // 3Quarter-Full termometer char data        */
  0b00000100,                                // 1st row          _____*__                 */
  0b00001010,                                // 2nd row          ____*_*_                 */
  0b00001010,                                // 3rd row          ____*_*_                 */
  0b00001110,                                // 4th row          ____***_                 */
  0b00001110,                                // 5th row          ____***_                 */
  0b00011111,                                // 6th row          ___*****                 */
  0b00011111,                                // 7th row          ___*****                 */
  0b00001110                                 // 8th row          ____***_                 */
};                                           //                                           */
static const rom char bat_empty[8] = {       // Battery empty character data              */
  0b00001110,                                // 1st row          ____***_                 */
  0b00011011,                                // 2nd row          ___**_**                 */
  0b00010001,                                // 3rd row          ___*___*                 */
  0b00010001,                                // 4th row          ___*___*                 */
  0b00010001,                                // 5th row          ___*___*                 */
  0b00010001,                                // 6th row          ___*****                 */
  0b00011111,                                // 7th row          ___*****                 */
  0b00000000                                 // 8th row          ________                 */
};                                           //                                           */
static const rom char bat_1bar[8] = {        // Battery at 1bar character data            */
  0b00001110,                                // 1st row          ____***_                 */
  0b00011011,                                // 2nd row          ___**_**                 */
  0b00010001,                                // 3rd row          ___*___*                 */
  0b00010001,                                // 4th row          ___*___*                 */
  0b00010001,                                // 5th row          ___*___*                 */
  0b00011111,                                // 6th row          ___*****                 */
  0b00011111,                                // 7th row          ___*****                 */
  0b00000000                                 // 8th row          ________                 */
};                                           //                                           */
static const rom char bat_2bar[8] = {        // Battery at 1bar character data            */
  0b00001110,                                // 1st row          ____***_                 */
  0b00011011,                                // 2nd row          ___**_**                 */
  0b00010001,                                // 3rd row          ___*___*                 */
  0b00010001,                                // 4th row          ___*___*                 */
  0b00011111,                                // 5th row          ___*****                 */
  0b00011111,                                // 6th row          ___*****                 */
  0b00011111,                                // 7th row          ___*****                 */
  0b00000000                                 // 8th row          ________                 */
};                                           //                                           */
static const rom char bat_3bar[8] = {        // Battery at 1bar character data            */
  0b00001110,                                // 1st row          ____***_                 */
  0b00011011,                                // 2nd row          ___**_**                 */
  0b00010001,                                // 3rd row          ___*___*                 */
  0b00011111,                                // 4th row          ___*****                 */
  0b00011111,                                // 5th row          ___*****                 */
  0b00011111,                                // 6th row          ___*****                 */
  0b00011111,                                // 7th row          ___*****                 */
  0b00000000                                 // 8th row          ________                 */
};                                           //                                           */
static const rom char bat_4bar[8] = {        // Battery at 1bar character data            */
  0b00001110,                                // 1st row          ____***_                 */
  0b00011011,                                // 2nd row          ___**_**                 */
  0b00011111,                                // 3rd row          ___*****                 */
  0b00011111,                                // 4th row          ___*****                 */
  0b00011111,                                // 5th row          ___*****                 */
  0b00011111,                                // 6th row          ___*****                 */
  0b00011111,                                // 7th row          ___*****                 */
  0b00000000                                 // 8th row          ________                 */
};                                           //                                           */
static const rom char bat_full[8] = {        // Battery at 1bar character data            */
  0b00001110,                                // 1st row          ____***_                 */
  0b00011111,                                // 2nd row          ___*****                 */
  0b00011111,                                // 3rd row          ___*****                 */
  0b00011111,                                // 4th row          ___*****                 */
  0b00011111,                                // 5th row          ___*****                 */
  0b00011111,                                // 6th row          ___*****                 */
  0b00011111,                                // 7th row          ___*****                 */
  0b00000000                                 // 8th row          ________                 */
};                                           //                                           */
static const rom char hourglass_empty[8] = { // Hour glass empty character data           */
  0b00011111,                                // 1st row          ___*****                 */
  0b00010001,                                // 2nd row          ___*___*                 */
  0b00001010,                                // 3rd row          ____*_*_                 */
  0b00000100,                                // 4th row          _____*__                 */
  0b00001010,                                // 5th row          ____*_*_                 */
  0b00010001,                                // 6th row          ___*___*                 */
  0b00010101,                                // 7th row          ___*_*_*                 */
  0b00011111                                 // 8th row          ___*****                 */
};                                           //                                           */
static const rom char hourglass_full[8] = {  // Hour glass full character data            */
  0b00011111,                                // 1st row          ___*****                 */
  0b00010001,                                // 2nd row          ___*___*                 */
  0b00001010,                                // 3rd row          ____*_*_                 */
  0b00000100,                                // 4th row          _____*__                 */
  0b00001110,                                // 5th row          ____***_                 */
  0b00011111,                                // 6th row          ___*****                 */
  0b00011111,                                // 7th row          ___*****                 */
  0b00011111                                 // 8th row          ___*****                 */
};                                           //                                           */
static const rom char ohms[8] = {            // Ohms symbol character data                */
  0b00000000,                                // 1st row          ________                 */
  0b00000000,                                // 2nd row          ________                 */
  0b00001110,                                // 3rd row          ____***_                 */
  0b00010001,                                // 4th row          ___*___*                 */
  0b00010001,                                // 5th row          ___*___*                 */
  0b00001010,                                // 6th row          ____*_*_                 */
  0b00011011,                                // 7th row          ___**_**                 */
  0b00000000                                 // 8th row          ________                 */
};                                           //                                           */
static const rom char percentage[8] = {      // Percentage symbol character data          */
  0b00000000,                                // 1st row          ________                 */
  0b00000000,                                // 2nd row          ________                 */
  0b00011001,                                // 3rd row          ___**__*                 */
  0b00011010,                                // 4th row          ___**_*_                 */
  0b00000100,                                // 5th row          _____*__                 */
  0b00001011,                                // 6th row          ____*_**                 */
  0b00010011,                                // 7th row          ___*__**                 */
  0b00000000                                 // 8th row          ________                 */
};                                           //                                           */
#endif                                       //                                           */
#ifdef xc8                                   // If XC8 is used                            */
//static const char full_heart[8] = {          // Full Heart custom character pixel data    */
//  0b00000000,                                // 1st row     ________                      */
//  0b00000000,                                // 2nd row     ________                      */
//  0b00001010,                                // 3rd row     ____*_*_                      */
//  0b00011111,                                // 4th row     ___*****                      */
//  0b00011111,                                // 5th row     ___*****                      */
//  0b00001110,                                // 6th row     ____***_                      */
//  0b00000100,                                // 7th row     _____*__                      */
//  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
//};                                           //                                           */
//static const char half_full_heart[8] = {     // Half-Full Heart custom char data          */
//  0b00000000,                                // 1st row     ________                      */
//  0b00000000,                                // 2nd row     ________                      */
//  0b00001010,                                // 3rd row     ____*_*_                      */
//  0b00010101,                                // 4th row     ___*_*_*                      */
//  0b00011111,                                // 5th row     ___*****                      */
//  0b00001110,                                // 6th row     ____***_                      */
//  0b00000100,                                // 7th row     _____*__                      */
//  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
//};                                           //                                           */
//static const char qtr_full_heart[8] = {      // Quarter-Full Heart custom char data       */
//  0b00000000,                                // 1st row     ________                      */
//  0b00000000,                                // 2nd row     ________                      */
//  0b00001010,                                // 3rd row     ____*_*_                      */
//  0b00010101,                                // 4th row     ___*_*_*                      */
//  0b00010001,                                // 5th row     ___*___*                      */
//  0b00001110,                                // 6th row     ____***_                      */
//  0b00000100,                                // 7th row     _____*__                      */
//  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
//};                                           //                                           */
//static const char empty_heart[8]={           // Empty Heart custom character pixel data   */
//  0b00000000,                                // 1st row     ________                      */
//  0b00000000,                                // 2nd row     ________                      */
//  0b00001010,                                // 3rd row     ____*_*_                      */
//  0b00010101,                                // 4th row     ___*_*_*                      */
//  0b00010001,                                // 5th row     ___*___*                      */
//  0b00001010,                                // 6th row     ____*_*_                      */
//  0b00000100,                                // 7th row     _____*__                      */
//  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
//};                                           //                                           */
//static const char smiley[8] = {              // Smiley custom character pixel data        */
//  0b00000000,                                // 1st row          ________                 */
//  0b00001010,                                // 2nd row          ____*_*_                 */
//  0b00001010,                                // 3rd row          ____*_*_                 */
//  0b00000000,                                // 4th row          ________                 */
//  0b00000100,                                // 5th row          _____*__                 */
//  0b00010001,                                // 6th row          ___*___*                 */
//  0b00001110,                                // 7th row          ____***_                 */
//  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
//};                                           //                                           */
//static const char frownie[8] = {             // Frownie custom character pixel data       */
//  0b00000000,                                // 1st row          ________                 */
//  0b00001010,                                // 2nd row          ____*_*_                 */
//  0b00000000,                                // 3rd row          ________                 */
//  0b00000100,                                // 4th row          _____*__                 */
//  0b00000000,                                // 5th row          ________                 */
//  0b00001110,                                // 6th row          ____***_                 */
//  0b00010001,                                // 7th row          ___*___*                 */
//  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
//};                                           //                                           */
//static const char armsDown[8] = {            // Arms down human character data            */
//  0b00000100,                                // 1st row          _____*__                 */
//  0b00001010,                                // 2nd row          ____*_*_                 */
//  0b00000100,                                // 3rd row          _____*__                 */
//  0b00001110,                                // 4th row          ____***_                 */
//  0b00010101,                                // 5th row          ___*_*_*                 */
//  0b00000100,                                // 6th row          _____*__                 */
//  0b00001010,                                // 7th row          ____*_*_                 */
//  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
//};                                           //                                           */
//static const char armsUp[8] = {              // Arms up human character data              */
//  0b00000100,                                // 1st row          _____*__                 */
//  0b00001010,                                // 2nd row          ____*_*_                 */
//  0b00000100,                                // 3rd row          _____*__                 */
//  0b00010101,                                // 4th row          ___*_*_*                 */
//  0b00001110,                                // 5th row          ____***_                 */
//  0b00000100,                                // 6th row          _____*__                 */
//  0b00001010,                                // 7th row          ____*_*_                 */
//  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
//};                                           //                                           */
//static const char arrowUp[8] = {             // Arrow facing up character data            */
//  0b00000100,                                // 1st row          _____*__                 */
//  0b00001110,                                // 2nd row          ____***_                 */
//  0b00010101,                                // 3rd row          ___*_*_*                 */
//  0b00000100,                                // 4th row          _____*__                 */
//  0b00000100,                                // 5th row          _____*__                 */
//  0b00000100,                                // 6th row          _____*__                 */
//  0b00000100,                                // 7th row          _____*__                 */
//  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
//};                                           //                                           */
//static const char arrowDown[8] = {           // Arrow facing down character data          */
//  0b00000100,                                // 1st row          _____*__                 */
//  0b00001110,                                // 2nd row          _____*__                 */
//  0b00010101,                                // 3rd row          _____*__                 */
//  0b00000100,                                // 4th row          _____*__                 */
//  0b00000100,                                // 5th row          ___*_*_*                 */
//  0b00000100,                                // 6th row          ____***_                 */
//  0b00000100,                                // 7th row          _____*__                 */
//  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
//};                                           //                                           */
//static const char padlock_l[8] = {           // Locked padlock character data             */
//  0b00001110,                                // 1st row          ____***_                 */
//  0b00010001,                                // 2nd row          ___*___*                 */
//  0b00010001,                                // 3rd row          ___*___*                 */
//  0b00011111,                                // 4th row          ___*****                 */
//  0b00011011,                                // 5th row          ___**_**                 */
//  0b00011011,                                // 6th row          ___**_**                 */
//  0b00011111,                                // 7th row          ___*****                 */
//  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
//};                                           //                                           */
//static const char padlock_u[8] = {           // Unlocked padlock character data           */
//  0b00001110,                                // 1st row          ____***_                 */
//  0b00010000,                                // 2nd row          ___*____                 */
//  0b00010000,                                // 3rd row          ___*____                 */
//  0b00011111,                                // 4th row          ___*****                 */
//  0b00011011,                                // 5th row          ___**_**                 */
//  0b00011011,                                // 6th row          ___**_**                 */
//  0b00011111,                                // 7th row          ___*****                 */
//  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
//};                                           //                                           */
//static const char bell[8] = {                // Bell character data                       */
//  0b00000100,                                // 1st row          _____*__                 */
//  0b00001110,                                // 2nd row          ____***_                 */
//  0b00001110,                                // 3rd row          ____***_                 */
//  0b00001110,                                // 4th row          ____***_                 */
//  0b00011111,                                // 5th row          ___*****                 */
//  0b00000000,                                // 6th row          ________                 */
//  0b00000100,                                // 7th row          _____*__                 */
//  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
//};                                           //                                           */
//static const char plug[8] = {                // Plug character data                       */
//  0b00001010,                                // 1st row          ____*_*_                 */
//  0b00001010,                                // 2nd row          ____*_*_                 */
//  0b00011111,                                // 3rd row          ___*****                 */
//  0b00010001,                                // 4th row          ___*___*                 */
//  0b00001110,                                // 5th row          ____***_                 */
//  0b00000100,                                // 6th row          _____*__                 */
//  0b00000100,                                // 7th row          _____*__                 */
//  0b00000000                                 // 8th row - reserved for cursor DO NOT USE  */
//};                                           //                                           */
//static const char note[8] = {                // Note character data                       */
//  0b00000010,                                // 1st row          ______*_                 */
//  0b00000011,                                // 2nd row          ______**                 */
//  0b00000010,                                // 3rd row          ______*_                 */
//  0b00000010,                                // 4th row          ______*_                 */
//  0b00001110,                                // 5th row          ______*_                 */
//  0b00011110,                                // 6th row          ____***_                 */
//  0b00001100,                                // 7th row          ___****_                 */
//  0b00000000                                 // 8th row          ____**__                 */
//};                                           //                                           */
//static const char notes[8] = {               // Notes character data                      */
//  0b00000001,                                // 1st row          _______*                 */
//  0b00000011,                                // 2nd row          ______**                 */
//  0b00000101,                                // 3rd row          _____*_*                 */
//  0b00001001,                                // 4th row          ____*__*                 */
//  0b00001001,                                // 5th row          ____*__*                 */
//  0b00001011,                                // 6th row          ____*_**                 */
//  0b00011011,                                // 7th row          ___**_**                 */
//  0b00011000                                 // 8th row          ___**___                 */
//};                                           //                                           */
//static const char arrowRight[8] ={           // Arrow Right character data                */
//  0b00000000,                                // 1st row          ________                 */
//  0b00000100,                                // 2nd row          _____*__                 */
//  0b00000010,                                // 3rd row          ______*_                 */
//  0b00011111,                                // 4th row          ___*****                 */
//  0b00000010,                                // 5th row          ______*_                 */
//  0b00000100,                                // 6th row          _____*__                 */
//  0b00000000,                                // 7th row          ________                 */
//  0b00000000                                 // 8th row          ________                 */
//};                                           //                                           */
//static const char arrowLeft[8] ={            // Arrow left character data                 */
//  0b00000000,                                // 1st row          ________                 */
//  0b00000100,                                // 2nd row          _____*__                 */
//  0b00001000,                                // 3rd row          ____*___                 */
//  0b00011111,                                // 4th row          ___*****                 */
//  0b00001000,                                // 5th row          ____*___                 */
//  0b00000100,                                // 6th row          _____*__                 */
//  0b00000000,                                // 7th row          ________                 */
//  0b00000000                                 // 8th row          ________                 */
//};                                           //                                           */
//static const char tick[8] = {                // Tick character data                       */
//  0b00000000,                                // 1st row          ________                 */
//  0b00000001,                                // 2nd row          _______*                 */
//  0b00000011,                                // 3rd row          ______**                 */
//  0b00010110,                                // 4th row          ___*_**_                 */
//  0b00011100,                                // 5th row          ___***__                 */
//  0b00001000,                                // 6th row          ____*___                 */
//  0b00000000,                                // 7th row          ________                 */
//  0b00000000                                 // 8th row          ________                 */
//};                                           //                                           */
//static const char spkr_on[8] = {             // Speaker_on character data                 */
//  0b00000010,                                // 1st row          ______*_                 */
//  0b00000110,                                // 2nd row          _____**_                 */
//  0b00011110,                                // 3rd row          ___****_                 */
//  0b00011110,                                // 4th row          ___****_                 */
//  0b00011110,                                // 5th row          ___****_                 */
//  0b00000110,                                // 6th row          _____**_                 */
//  0b00000010,                                // 7th row          ______*_                 */
//  0b00000000                                 // 8th row          ________                 */
//};                                           //                                           */
//static const char spkr_off[8] = {            // Speaker_off character data                */
//  0b00000010,                                // 1st row          ______*_                 */
//  0b00000110,                                // 2nd row          _____**_                 */
//  0b00011010,                                // 3rd row          ___**_*_                 */
//  0b00010010,                                // 4th row          ___*__*_                 */
//  0b00011010,                                // 5th row          ___**_*_                 */
//  0b00000110,                                // 6th row          _____**_                 */
//  0b00000010,                                // 7th row          ______*_                 */
//  0b00000000                                 // 8th row          ________                 */
//};                                           //                                           */
//static const char skull[8] = {               // Skull character data                      */
//  0b00000000,                                // 1st row          ________                 */
//  0b00000000,                                // 2nd row          ________                 */
//  0b00001110,                                // 3rd row          ____***_                 */
//  0b00010101,                                // 4th row          ___*_*_*                 */
//  0b00011011,                                // 5th row          ___**_**                 */
//  0b00001110,                                // 6th row          ____***_                 */
//  0b00001110,                                // 7th row          ____***_                 */
//  0b00000000                                 // 8th row          ________                 */
//};                                           //                                           */
//static const char empty_drop[8]={            // Empty Drop character data                 */
//  0b00000100,                                // 1st row          _____*__                 */
//  0b00000100,                                // 2nd row          _____*__                 */
//  0b00001010,                                // 3rd row          ____*_*_                 */
//  0b00001010,                                // 4th row          ____*_*_                 */
//  0b00010001,                                // 5th row          ___*___*                 */
//  0b00010001,                                // 6th row          ___*___*                 */
//  0b00010001,                                // 7th row          ___*___*                 */
//  0b00001110                                 // 8th row          ____***_                 */
//};                                           //                                           */
//static const char full_drop[8] = {           // Full Drop character data                  */
//  0b00000100,                                // 1st row          _____*__                 */
//  0b00000100,                                // 2nd row          _____*__                 */
//  0b00001110,                                // 3rd row          ____***_                 */
//  0b00001110,                                // 4th row          ____***_                 */
//  0b00011111,                                // 5th row          ___*****                 */
//  0b00011111,                                // 6th row          ___*****                 */
//  0b00011111,                                // 7th row          ___*****                 */
//  0b00001110                                 // 8th row          ____***_                 */
//};                                           //                                           */
//static const char termomtr_empty[8] = {      // Empty termometer character data           */
//  0b00000100,                                // 1st row          _____*__                 */
//  0b00001010,                                // 2nd row          ____*_*_                 */
//  0b00001010,                                // 3rd row          ____*_*_                 */
//  0b00001010,                                // 4th row          ____*_*_                 */
//  0b00001010,                                // 5th row          ____*_*_                 */
//  0b00010001,                                // 6th row          ___*___*                 */
//  0b00010001,                                // 7th row          ___*___*                 */
//  0b00001110                                 // 8th row          ____***_                 */
//};                                           //                                           */
//static const char termomtr_full[8] = {       // Full termometer character data            */
//  0b00000100,                                // 1st row          _____*__                 */
//  0b00001110,                                // 2nd row          ____***_                 */
//  0b00001110,                                // 3rd row          ____***_                 */
//  0b00001110,                                // 4th row          ____***_                 */
//  0b00001110,                                // 5th row          ____***_                 */
//  0b00011111,                                // 6th row          ___*****                 */
//  0b00011111,                                // 7th row          ___*****                 */
//  0b00001110                                 // 8th row          ____***_                 */
//};                                           //                                           */
//static const char termomtr_half[8] = {       // Half-Full termometer character data       */
//  0b00000100,                                // 1st row          _____*__                 */
//  0b00001010,                                // 2nd row          ____*_*_                 */
//  0b00001010,                                // 3rd row          ____*_*_                 */
//  0b00001010,                                // 4th row          ____*_*_                 */
//  0b00001010,                                // 5th row          ____*_*_                 */
//  0b00011111,                                // 6th row          ___*****                 */
//  0b00011111,                                // 7th row          ___*****                 */
//  0b00001110                                 // 8th row          ____***_                 */
//};                                           //                                           */
//static const char termomtr_qtr[8] = {        // Quarter-Full termometer char data         */
//  0b00000100,                                // 1st row          _____*__                 */
//  0b00001010,                                // 2nd row          ____*_*_                 */
//  0b00001010,                                // 3rd row          ____*_*_                 */
//  0b00001010,                                // 4th row          ____*_*_                 */
//  0b00001010,                                // 5th row          ____*_*_                 */
//  0b00011011,                                // 6th row          ___**_**                 */
//  0b00011111,                                // 7th row          ___*****                 */
//  0b00001110                                 // 8th row          ____***_                 */
//};                                           //                                           */
//static const char termomtr_3qtr[8] = {       // 3Quarter-Full termometer char data        */
//  0b00000100,                                // 1st row          _____*__                 */
//  0b00001010,                                // 2nd row          ____*_*_                 */
//  0b00001010,                                // 3rd row          ____*_*_                 */
//  0b00001110,                                // 4th row          ____***_                 */
//  0b00001110,                                // 5th row          ____***_                 */
//  0b00011111,                                // 6th row          ___*****                 */
//  0b00011111,                                // 7th row          ___*****                 */
//  0b00001110                                 // 8th row          ____***_                 */
//};                                           //                                           */
//static const char bat_empty[8] = {           // Battery empty character data              */
//  0b00001110,                                // 1st row          ____***_                 */
//  0b00011011,                                // 2nd row          ___**_**                 */
//  0b00010001,                                // 3rd row          ___*___*                 */
//  0b00010001,                                // 4th row          ___*___*                 */
//  0b00010001,                                // 5th row          ___*___*                 */
//  0b00010001,                                // 6th row          ___*****                 */
//  0b00011111,                                // 7th row          ___*****                 */
//  0b00000000                                 // 8th row          ________                 */
//};                                           //                                           */
//static const char bat_1bar[8] = {            // Battery at 1bar character data            */
//  0b00001110,                                // 1st row          ____***_                 */
//  0b00011011,                                // 2nd row          ___**_**                 */
//  0b00010001,                                // 3rd row          ___*___*                 */
//  0b00010001,                                // 4th row          ___*___*                 */
//  0b00010001,                                // 5th row          ___*___*                 */
//  0b00011111,                                // 6th row          ___*****                 */
//  0b00011111,                                // 7th row          ___*****                 */
//  0b00000000                                 // 8th row          ________                 */
//};                                           //                                           */
//static const char bat_2bar[8] = {            // Battery at 1bar character data            */
//  0b00001110,                                // 1st row          ____***_                 */
//  0b00011011,                                // 2nd row          ___**_**                 */
//  0b00010001,                                // 3rd row          ___*___*                 */
//  0b00010001,                                // 4th row          ___*___*                 */
//  0b00011111,                                // 5th row          ___*****                 */
//  0b00011111,                                // 6th row          ___*****                 */
//  0b00011111,                                // 7th row          ___*****                 */
//  0b00000000                                 // 8th row          ________                 */
//};                                           //                                           */
//static const char bat_3bar[8] = {            // Battery at 1bar character data            */
//  0b00001110,                                // 1st row          ____***_                 */
//  0b00011011,                                // 2nd row          ___**_**                 */
//  0b00010001,                                // 3rd row          ___*___*                 */
//  0b00011111,                                // 4th row          ___*****                 */
//  0b00011111,                                // 5th row          ___*****                 */
//  0b00011111,                                // 6th row          ___*****                 */
//  0b00011111,                                // 7th row          ___*****                 */
//  0b00000000                                 // 8th row          ________                 */
//};                                           //                                           */
//static const char bat_4bar[8] = {            // Battery at 1bar character data            */
//  0b00001110,                                // 1st row          ____***_                 */
//  0b00011011,                                // 2nd row          ___**_**                 */
//  0b00011111,                                // 3rd row          ___*****                 */
//  0b00011111,                                // 4th row          ___*****                 */
//  0b00011111,                                // 5th row          ___*****                 */
//  0b00011111,                                // 6th row          ___*****                 */
//  0b00011111,                                // 7th row          ___*****                 */
//  0b00000000                                 // 8th row          ________                 */
//};                                           //                                           */
//static const char bat_full[8] = {            // Battery at 1bar character data            */
//  0b00001110,                                // 1st row          ____***_                 */
//  0b00011111,                                // 2nd row          ___*****                 */
//  0b00011111,                                // 3rd row          ___*****                 */
//  0b00011111,                                // 4th row          ___*****                 */
//  0b00011111,                                // 5th row          ___*****                 */
//  0b00011111,                                // 6th row          ___*****                 */
//  0b00011111,                                // 7th row          ___*****                 */
//  0b00000000                                 // 8th row          ________                 */
//};                                           //                                           */
//static const char hourglass_empty[8] = {     // Hour glass empty character data           */
//  0b00011111,                                // 1st row          ___*****                 */
//  0b00010001,                                // 2nd row          ___*___*                 */
//  0b00001010,                                // 3rd row          ____*_*_                 */
//  0b00000100,                                // 4th row          _____*__                 */
//  0b00001010,                                // 5th row          ____*_*_                 */
//  0b00010001,                                // 6th row          ___*___*                 */
//  0b00010101,                                // 7th row          ___*_*_*                 */
//  0b00011111                                 // 8th row          ___*****                 */
//};                                           //                                           */
//static const char hourglass_full[8] = {      // Hour glass full character data            */
//  0b00011111,                                // 1st row          ___*****                 */
//  0b00010001,                                // 2nd row          ___*___*                 */
//  0b00001010,                                // 3rd row          ____*_*_                 */
//  0b00000100,                                // 4th row          _____*__                 */
//  0b00001110,                                // 5th row          ____***_                 */
//  0b00011111,                                // 6th row          ___*****                 */
//  0b00011111,                                // 7th row          ___*****                 */
//  0b00011111                                 // 8th row          ___*****                 */
//};                                           //                                           */
//static const char ohms[8] = {                // Ohms symbol character data                */
//  0b00000000,                                // 1st row          ________                 */
//  0b00000000,                                // 2nd row          ________                 */
//  0b00001110,                                // 3rd row          ____***_                 */
//  0b00010001,                                // 4th row          ___*___*                 */
//  0b00010001,                                // 5th row          ___*___*                 */
//  0b00001010,                                // 6th row          ____*_*_                 */
//  0b00011011,                                // 7th row          ___**_**                 */
//  0b00000000                                 // 8th row          ________                 */
//};                                           //                                           */
//static const char percentage[8] = {          // Percentage symbol character data          */
//  0b00000000,                                // 1st row          ________                 */
//  0b00000000,                                // 2nd row          ________                 */
//  0b00011001,                                // 3rd row          ___**__*                 */
//  0b00011010,                                // 4th row          ___**_*_                 */
//  0b00000100,                                // 5th row          _____*__                 */
//  0b00001011,                                // 6th row          ____*_**                 */
//  0b00010011,                                // 7th row          ___*__**                 */
//  0b00000000                                 // 8th row          ________                 */
//};                                           //                                           */
#endif
#endif