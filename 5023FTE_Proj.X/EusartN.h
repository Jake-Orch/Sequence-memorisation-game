#ifndef EUSARTN_H
#define	EUSARTN_H

void SendEusartString(char *str);
void SendEusartInt(int value);
void SendEusartBCD(uint8_t bcd);

bool EusartRxString(void);
void EusartPrintInput(void);

void EusartRX(void);

void EUtimeHomePage(void);
void EUtimeDisplay(void);
void EUtimeResultDisplay(void);

void EUhomePage(void);
void EUplayerChoice(void);
void EUwriteNames(void);
void EUcountDown(void);
void EUscoreScreen(void);
void EUsavedScoresHome(void);
void EUsavedScores(void);
void EUwinnerScreen(void);


#endif


