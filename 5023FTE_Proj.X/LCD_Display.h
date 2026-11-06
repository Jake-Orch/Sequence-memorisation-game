#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

void displayMainPages(void);
void displaySMPages(void);

void homePage(void);
void playerChoice(void);
void writeNames(void);
void countDown(void);
void scoreScreen(void);
void savedScoresHome(void);
void savedScores(void);
void winnerScreen(void);

void timeHomePage(void);
void timeDisplay(void);
void timeResultDisplay(void);

void updateNameCursor(void);

void setBacklightDuty(uint8_t percent);

void changeTimeDateScreen(void);
void changeDateTimeHome(void);
void changeDateTimeComplete(void);

void LCD_PrintBCD(char bcd);    // convert and print BCD values to the LCD display
void LCD_PrintInt(int val); // convert and print intager values to the LCD display
#endif // LCD_DISPLAY_H
