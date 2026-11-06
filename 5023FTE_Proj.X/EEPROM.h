#ifndef EEPROM_H
#define	EEPROM_H

void checkHighScore(char name[], int score);
void retrieveHighScores(int iteration);

void setDateTime(void);
void getDateTime(void);
void saveDateTime(uint8_t byteIteration);

#endif	/* EEPROM_H */

