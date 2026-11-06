#ifndef SIMPLE_I2C_H
#define SIMPLE_I2C_H

void I2C_START_BIT(void);
void I2C_STOP_BIT(void);
void I2C_RESTART_BITT(void);
void I2C_ACK_BIT(void);
void I2C_NACK_BIT(void);


void I2C_COMMAND(char control, char block, char rw);

void I2C_Write(char data);
char I2C_Read(void);

#endif