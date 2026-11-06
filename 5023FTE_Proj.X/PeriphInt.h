#ifndef PERIPHINT_H
#define	PERIPHINT_H

void INT0_CustomISR(void);
void INT1_CustomISR(void);
void INT2_CustomISR(void);

void TMR1_CustomISR(void);
void TMR3_CustomISR(void);


void rotaryEncoderPolling(void);

void BTN1_Ctrl(void);
void BTN2_Ctrl(void);
void BTN3_Ctrl(void);

#endif	/* PERIPHINT_H */

