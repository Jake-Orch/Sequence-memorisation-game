#ifndef POWER_H
#define	POWER_H

extern volatile uint16_t timer1ReloadVal;
extern volatile uint16_t timer3ReloadVal;

void checkBattery(void);

void customSleep(void);
void customWake(void);
void enterLowPower(void);
void enterNormalPower(void);

#endif	/* POWER_H */

