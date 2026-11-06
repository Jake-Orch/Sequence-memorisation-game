/*==================================================================================*/
/*                               LCD Library                                        */
/*                                created by                                        */
/*                      Slavi Popov @ ab7332@coventry.ac.uk                         */
/*                                                                                  */
/* Created to provide maximum flexibility for driving LCD modules based on standard */
/* Hitachi HD44780 MCU. This code has been tested and confirmed to work on multiple */
/* different sized LCD modules such as 16x1, 16x2, 16x4, 20x1, 24x1, 20x2 and 20x4. */
/* The library does not support 8-bit interface & only uses 5x8 character generation*/
/* Supports both C18 and XC8 compilers (tested on v2.05)                            */
/*                                                                                  */
/* The user must define multiple hardware-related characteristics of the system they*/
/* are developing. The library is targeted  for all PIC18 families of 8-bit MCUs &  */
/* because of this the user must define the LCD Data pins & LCD Control pins. Also, */
/* the user must specify the clock frequency of the PIC18 used in the project and   */
/* if it is derived from an external oscillator or the built-in oscillator circuit  */
/*                                                                                  */
/* A typical 40-pin PIC18 has 5 ports & 4 of which can be used to drive an LCD with */
/* this library. Here are all user options for a PIC18F4520 & 18F45K20 based work:  */
/*                                                                                  */
/*          The below characteristics must be defined in the lcd.h file!            */
/*                                                                                  */
/* 1. Define the display type being used by uncommenting one of the statements on   */
/* lines 13 to 18 in the lcd.h. Default is LCD_16x4                                 */
/*                                                                                  */
/* 2. Define the port being used to control the LCD by uncommenting one statement   */
/* between lines 22 and 25 in the lcd.h. Default is DATA_PORTB                      */
/*                                                                                  */
/* DATA_PORT Can be set to be: LATA, LATB, LATC, or LATD <- lower nibble used       */
/* TRIS_DATA_PORT - is handled automatically by the library                         */
/* E_PIN  - is always the 4th bit of the selected port, handled automatically       */
/* RS_PIN - is always the 5th bit of the selected port, handled automatically       */
/* RW_PIN - is always the 6th bit of the selected port, unless PORTA is selected    */
/* In the case PORTA is used RW_PIN must be connected to GND, handled automatically */
/*                                                                                  */
/* 3. Define the clock speed you are using for the PIC by uncommenting one of the   */
/* statements between lines 37 and 45 in the lcd.h. Default is CLK_20               */
/* Supported Clock speeds: 40MHz, 20MHz, 16MHz, 10MHz, 8MHz, 5MHz, 4MHz, 2MHz, 1MHz */
/* If different speed is desired, calculate 1ms delay based on that speed & replace */
/* All instances of LCD_Wait_C18() in this file with the newly calculated delay     */
/*==================================================================================*/
#include "lcd.h"                            // Include LCD library file             */
#ifdef xc8                                  // If XC8 Compiler is used              */
#include "mcc_generated_files/mcc.h"        // Include generated libraries if used  */
#endif                                      //                                      */
/*==================================================================================*/
void LCD_Init()                             // Function to initialise the LCD. Only */
{                                           // 4-bit mode is supported              */
    int i = 0;                              // Counter variable                     */
#ifdef DATA_PORTA                           // If LCD is used on PORTA              */
#ifdef c18                                  // If C18 is used - supports PIC18F4520 */
    ADCON1           = 0x0F;                // Analogue pins On PORTA set to digital*/
    CMCON            = 0b111;               // Disable PORTA Comparators            */
#endif                                      //                                      */
#ifdef xc8                                  // If XC8 is used - no support for F4520*/
    ANSELbits.ANS0   = 0;                   // Disable analogue functions on RA0    */
    ANSELbits.ANS1   = 0;                   // Disable analogue functions on RA1    */
    ANSELbits.ANS2   = 0;                   // Disable analogue functions on RA2    */
    ANSELbits.ANS3   = 0;                   // Disable analogue functions on RA3    */
    ANSELbits.ANS4   = 0;                   // Disable analogue functions on RA5    */
    SLRCONbits.SLRA  = 0;                   // Set PORTA slew rate to standard      */
#endif                                      //                                      */
#   define  DATA_PORT        LATA           // DATA_PORT macro is LATA              */
#   define  TRIS_DATA_PORT   TRISA          // TRIS_DATA_PORT macro is TRISA        */
#   define  RS_PIN           LATAbits.LATA5 // Register Select pin is RA5 on PORTA  */
#   define  E_PIN            LATAbits.LATA4 // Enable pin is RA4 on PORTA           */
#endif                                      //                                      */
                                            //                                      */
#ifdef DATA_PORTB                           // If LCD is used on PORTB              */
#ifdef c18                                  // If C18 is used - supports PIC18F4520 */
    ADCON1           = 0x07;                // Analogue pins On PORTB set to digital*/
#endif                                      //                                      */
#ifdef xc8                                  // If XC8 is used - no support for F4520*/
    ANSELH = 0;                             // Set all PORTB pins to digital        */
    SLRCONbits.SLRB = 0;                    //                                      */
#endif                                      //                                      */
    INTCON2bits.RBPU = 1;                   // Internal port B Pull-Ups off         */
#   define  DATA_PORT        LATB           // DATA_PORT macro is LATB              */
#   define  TRIS_DATA_PORT   TRISB          // TRIS_DATA_PORT macro is TRISA        */
#   define  RW_PIN           LATBbits.LATB6 // Read/Write pin is RB6 on PORTB       */
#   define  RS_PIN           LATBbits.LATB5 // Register Select pin is RB5 on PORTB  */
#   define  E_PIN            LATBbits.LATB4 // Enable pin is RB4 on PORTB           */
#endif                                      //                                      */
#ifdef DATA_PORTC                           // If LCD is used on PORTC              */
#   define  DATA_PORT        LATC           // DATA_PORT macro is LATC              */
#   define  TRIS_DATA_PORT   TRISC          // TRIS_DATA_PORT macro is TRISC        */
#   define  RW_PIN           LATCbits.LATC6 // Read/Write pin is RB6 on PORTB       */
#   define  RS_PIN           LATCbits.LATC5 // Register Select pin is RB5 on PORTB  */
#   define  E_PIN            LATCbits.LATC4 // Enable pin is RB4 on PORTB           */
#endif                                      //                                      */
                                            //                                      */
#ifdef DATA_PORTD                           // If LCD is used on PORTD              */
#   define  DATA_PORT        LATD           // DATA_PORT macro is LATD              */
#   define  TRIS_DATA_PORT   TRISD          // TRIS_DATA_PORT macro is TRISD        */
#   define  RW_PIN           LATDbits.LATD6 // Read/Write pin is RB6 on PORTB       */
#   define  RS_PIN           LATDbits.LATD5 // Register Select pin is RB5 on PORTB  */
#   define  E_PIN            LATDbits.LATD4 // Enable pin is RB4 on PORTB           */
#endif                                      //                                      */
    DATA_PORT      = 0;                     // Latch DATA_PORT to 0                 */
    TRIS_DATA_PORT = 0;                     // Make DATA_PORT all output            */
    RS_PIN         = 0;                     // Pull Register Select pin of LCD low  */
#ifndef DATA_PORTA                          // If DATA_PORT is not LATA             */
    RW_PIN = 0;                             // Pull Read/Write pin of LCD low       */
#endif                                      // If LATA is used, connect RW to GND   */
#ifdef c18                                  // If C18 is used - supports PIC18F4520 */
    for(i = 0; i < 10; i++)                 // For loop for extra delay upon LCD    */
    {                                       // Inititialisation as per the datasheet*/
        LCD_Wait_C18();                     // 10 ms delay                          */
    }                                       // This is done 3 times per datasheet   */
#endif                                      //                                      */
#ifdef xc8                                  // If XC8 is used - no support for F4520*/
    __delay_ms(10);                         // Delay for 10 ms                      */
#endif                                      //                                      */
    LCD_Cmd(0x30);                          // Try to initialise 4-bit mode         */
    LCD_Cmd(0x30);                          // Try to initialise 4-bit mode         */
    LCD_Cmd(0x30);                          // Try to initialise 4-bit mode         */
                                            //                                      */
    LCD_Cmd(HOME_LCD);                      // Home the LCD cursor                  */
    LCD_Cmd(0x28);                          // 4-bit mode, 1/16 duty, 5x8 font for  */
    LCD_Cmd(CUR_ON);                        // Enable the cursor                    */
                                            // Font affects custom chars only       */
    LCD_Cmd(CLR_LCD);                       // Clear all text from LCD              */
}                                           //                                      */
/*==================================================================================*/
void LCD_Cmd(unsigned char cmd)             // Function to send commands to the LCD */
{                                           //                                      */
    DATA_PORT = cmd >> 4;                   // Latch-shifted command value 4 times  */
    RS_PIN = 0;                             // Pull Register Select LCD pin low     */
#ifndef DATA_PORTA                          // If DATA_PORT is not LATA             */
    RW_PIN = 0;                             // Pull Read/Write LCD pin low, RW = GND*/
#endif                                      // If LATA is used, connect RW to GND   */
    E_PIN = 1;                              // Pull Enable LCD pin high             */
    E_PIN = 0;                              // Pull Enable LCD pin low              */
                                            //                                      */
    DATA_PORT = cmd & 0x0F;                 // AND 0F with command & output to LCD  */
    E_PIN = 1;                              // Pull Enable LCD pin high             */
    E_PIN = 0;                              // Pull Enable LCD pin low              */
#ifdef c18                                  // If C18 is used - supports PIC18F4520 */
        LCD_Wait_C18();                     // 1 ms delay                           */
        LCD_Wait_C18();                     // 1 ms delay                           */
#endif                                      //                                      */
#ifdef xc8                                  // If XC8 is used - no support for F4520*/
        LCD_Wait_XC8();                     // 1 ms delay                           */
        LCD_Wait_XC8();                     // 1 ms delay                           */
#endif                                      //                                      */
}                                           //                                      */
/*==================================================================================*/
void LCD_PrintC(unsigned char chartr)       // Function that prints single character*/
{                                           // on LCD                               */
    DATA_PORT = chartr >> 4;                // Latch-shifted character value 4 times*/
                                            //                                      */
    RS_PIN = 1;                             // Pull Register Select LCD pin high    */
    E_PIN  = 1;                             // Pull Enable LCD pin high             */
    E_PIN  = 0;                             // Pull Enable LCD pin low              */
    RS_PIN = 0;                             // Pull Register Select LCD pin low     */
                                            //                                      */
    DATA_PORT = chartr & 0x0F;              //                                      */
                                            //                                      */
    RS_PIN = 1;                             // Pull Register Select LCD pin high    */
    E_PIN  = 1;                             // Pull Enable LCD pin high             */
    E_PIN  = 0;                             // Pull Enable LCD pin low              */
    RS_PIN = 0;                             // Pull Register Select LCD pin low     */
#ifdef c18                                  // If C18 is used - supports PIC18F4520 */
        LCD_Wait_C18();                     // 1 ms delay                           */
#endif                                      //                                      */
#ifdef xc8                                  // If XC8 is used - no support for F4520*/
        LCD_Wait_XC8();                     //                                      */
#endif                                      //                                      */
}                                           //                                      */
/*==================================================================================*/
void LCD_PrintS(char *buf)                  // Prints DRRAM buffer of chars to LCD  */
{                                           //                                      */
    unsigned int count = 0;                 // Array index variable                 */
    while(buf[count] != '\0')               // Loop while the end of EOF            */
    {                                       // character is encountered             */
        LCD_PrintC(buf[count]);             // Print one indexed character          */
        count++;                            // Increment array index                */
    }                                       //                                      */
}                                           //                                      */
/*==================================================================================*/
#ifdef xc8                                  // If XC8 is used - no support for F4520*/
void LCD_PrintRS(const char *buf)           // Prints ROM buffer of chars to LCD    */
{                                           //                                      */
    unsigned int count = 0;                 // Array index variable                 */
    while(buf[count] != '\0')               // Loop while the end of EOF            */
    {                                       // character is encountered             */
        LCD_PrintC(buf[count]);             // Print one indexed character          */
        count++;                            // Increment array index                */
    }                                       //                                      */
}                                           //                                      */
/*==================================================================================*/
void LCD_CreateC(unsigned int addr,         // Creates custom character in LCD RAM  */
         const char *char_data)             //                                      */
{                                           //                                      */
    int i = 0;                              // Counter variable; Ensures addr input */
    addr = (addr & 0x07) << 3;              // can only store in correct locations  */
    LCD_Cmd(0x40 | addr);                   // Write to the address                 */
                                            //                                      */
    for(i = 0; i < 8; i++)                  //                                      */
    {                                       //                                      */
        LCD_PrintC(char_data[i]);           // Feed char data into address location */
    }                                       //                                      */
}                                           //                                      */
/*==================================================================================*/
void LCD_Wait_XC8(void)                     //                                      */
{                                           //                                      */
    __delay_ms(1);                          // 1 ms delay                           */
}                                           //                                      */
#endif                                      //                                      */
/*==================================================================================*/
#ifdef c18                                  // If C18 is used - supports PIC18F4520 */
void LCD_PrintRS(const rom char *buf)       // Prints ROM buffer of chars to LCD    */
{                                           //                                      */
    unsigned int count = 0;                 // Array index variable                 */
    while(buf[count] != '\0')               // Loop while the end of EOF            */
    {                                       // character is encountered             */
        LCD_PrintC(buf[count]);             // Print one indexed character          */
        count++;                            // Increment array index                */
    }                                       //                                      */
}                                           //                                      */
/*==================================================================================*/
void LCD_CreateC(unsigned int addr,         // Creates custom character in LCD RAM  */
         const rom char *char_data)         //                                      */
{                                           //                                      */
    int i = 0;                              // Counter variable; Ensures addr input */
    addr = (addr & 0x07) << 3;              // can only store in correct locations  */
    LCD_Cmd(0x40 | addr);                   // Write to the address                 */
                                            //                                      */
    for(i = 0; i < 8; i++)                  //                                      */
    {                                       //                                      */
        LCD_PrintC(char_data[i]);           // Feed char data into address location */
    }                                       //                                      */
}                                           //                                      */
/*==================================================================================*/
void LCD_Wait_C18()                         // Delay function based on system clock */
{                                           // If the system clock is defined as:   */
#ifdef CLK_40                               // 40MHz                                */
    Delay1KTCYx(10);                        // At 40MHz this delay will be ~1ms     */
#endif                                      //                                      */
#ifdef CLK_20                               // 20MHz                                */
    Delay1KTCYx(5);                         // At 20MHz this delay will be ~1ms     */
#endif                                      //                                      */
#ifdef CLK_16                               // 16 MHz                               */
    Delay1KTCYx(4);                         // At 16MHz this delay will be ~1ms     */
#endif                                      //                                      */
#ifdef CLK_10                               // 10MHz                                */
    Delay100TCYx(25);                       // At 10MHz this delay will be ~1ms     */
#endif                                      //                                      */
#ifdef CLK_8                                // 8 MHz                                */
    Delay10TCYx(198);                       // At 8MHz this delay will be ~1ms      */
#endif                                      //                                      */
#ifdef CLK_5                                // 5MHz                                 */
    Delay10TCYx(125);                       // At 5MHz this delay will be ~1ms      */
#endif                                      //                                      */
#ifdef CLK_4                                // 4MHz                                 */
    Delay10TCYx(98);                        // At 4MHz this delay will be ~1ms      */
#endif                                      //                                      */
#ifdef CLK_2                                // 2MHz                                 */
    Delay10TCYx(48);                        // At 2MHz this delay will be ~5ms      */
#endif                                      //                                      */
#ifdef CLK_1                                // 1MHz                                 */
    Delay10TCYx(24);                        // At 1MHz this delay will be ~5ms      */
#endif                                      //                                      */
}                                           //                                      */
#endif
