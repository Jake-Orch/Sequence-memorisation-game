#include "mcc_generated_files/mcc.h"
#include "Definitions.h"
#include "lcd.h"
#include "LCD_Display.h"
#include "helper.h"
#include "EusartN.h"
#include "power.h"

void checkBattery(void)
{
    
    ADC_StartConversion();
    while (!ADC_IsConversionDone());

    adc_result_t vBatt = ADC_GetConversionResult();

    float batteryVoltage = (vBatt / 1023.0f) * 3.3f * 2.8f;
    batteryVoltageAcc = batteryVoltageAcc + batteryVoltage;
    
    if (adcCheck != 3)
    {
        adcCheck++;
        return;
    }
    else
    {
        batteryVoltage = batteryVoltageAcc / 4;
        // Convert to integer with 2 decimal places        
//        int voltage = (int)(batteryVoltage * 100.0f);
//        LCD_Cmd(CLR_LCD);
//
//        LCD_PrintInt(voltage / 100);
//        LCD_PrintC('.');
//        LCD_PrintC(((voltage / 10) % 10) + '0');
//        LCD_PrintC((voltage % 10) + '0');
//        LCD_PrintC('V');
        
        if (batteryVoltage >= 6.8 && currentBattState != 1)
        {
            currentBattState = 1;
            enterNormalPower();
        }
        else if (batteryVoltage < 6.8 && currentBattState != 2)
        {
            currentBattState = 2;
            enterLowPower();
        }
        
        if (batteryVoltage <= 6.25 && currentBattState !=3)
        {
            currentBattState = 3;
            wakeFlag = 0;
        }
//        LCD_PrintInt((int)currentBattState); 
        
        
        
        batteryVoltageAcc = 0.0;
        adcCheck = 0;
        
    }     
}


void customSleep(void)
{
    /// DEBUG
    SendEusartString("ENTERING SLEEP\r\n");
    SendEusartString("\r\nBefore sleep RX ready = ");
    SendEusartInt(EUSART_is_rx_ready());
    
    // Turn off LCD
    LCD_Cmd(LCD_OFF);
    delayAdjusted(50);
    setBacklightDuty(0);
    
    // Disable external interrupts (except for INT0)
    EXT_INT1_InterruptDisable();
    EXT_INT2_InterruptDisable();
    
    // Stop TMR0 & TMR1
    TMR0_StopTimer();
    TMR1_StopTimer();
    TMR3_StopTimer();
    
    WAKEUP = 1;
    
    delayAdjusted(20);

    SLEEP();  
    NOP();
}

void customWake(void)
{
    WAKEUP = 0;
    
    // Re-enable external interrupts
    EXT_INT1_InterruptEnable();
    EXT_INT2_InterruptEnable();
    
    // Turn on LCD
    LCD_Cmd(LCD_ON);
    delayAdjusted(50);
    LCD_Cmd(CUR_OFF);
    setBacklightDuty(100);

    
    // Reload/start TMR0 & TMR1
    TMR0_Reload();
    TMR0_StartTimer();
    TMR1_Reload();
    TMR1_StartTimer();
    
    // Reset wakeFlag
    wakeFlag = 1;
    
    /// DEBUG
    SendEusartString("\r\nAfter wake RX ready = ");
    SendEusartInt(EUSART_is_rx_ready());
    SendEusartString("Waking up...");
}

void enterNormalPower(void)
{
    // Wait for EUSART to finish transmission
    while (!EUSART_is_tx_done());

    // Switch back to primary oscillator (20 MHz)
    OSCCONbits.SCS = 0b00;

    // Wait until primary oscillator is active
    while (!OSCCONbits.OSTS);
    
    // Set baud rate
    SPBRGH = 0x02;
    SPBRG = 0x08;
    
    // I2C at 100 kHz
    SSPADD = 0x31;
    
    // Set TMR1
    T1CONbits.TMR1ON = 0;       // Stop TMR1
    timer1ReloadVal = 0x0BDC;   // Set TMR1 preload
    TMR1_Reload();              // Update TMR1 hardware
    TMR1_StopTimer();
    T1CONbits.TMR1ON = 1;       // Restart TMR1   
    
    PR2 = 155;  // ~2 kHz PWM at 20 MHz
    setBacklightDuty(100);
    
    // Set TMR3
    T3CONbits.TMR3ON = 0;       // Stop TMR3
    timer3ReloadVal = 0x3CB0;   // Set TMR3 preload
    TMR3_Reload();              // Update TMR3 hardware
    TMR3_StopTimer();

    
    // Set clockFactor for delays
    clockFactor = 1;
}

void enterLowPower(void)
{
    // Wait for EUSART to finish transmission
    while (!EUSART_is_tx_done());
    
    // Configure clock
    OSCCONbits.IRCF = 0b101;    // Set clock speed (4MHz)
    OSCCONbits.SCS = 0b10;      // Select internal clock
    
    // Wait until internal oscillator is stable
    while (!OSCCONbits.IOFS);
    
    // Set baud rate
    SPBRGH = 0x00;
    SPBRG = 0x67;
    
    // I2C at 100 kHz
    SSPADD = 0x09;
    
    // Set TMR1
    T1CONbits.TMR1ON = 0;       // Stop TMR1
    timer1ReloadVal = 0xCF2C;   // Set TMR1 preload
    TMR1_Reload();              // Update TMR1 hardware
    TMR1_StopTimer();
    T1CONbits.TMR1ON = 1;       // Restart TMR1
    
    PR2 = 30;   // ~2 kHz PWM at 4 MHz
    setBacklightDuty(25);
    
    // Set TMR3
    T3CONbits.TMR3ON = 0;       // Stop TMR3
    timer3ReloadVal = 0xD8F0;   // Set TMR3 preload
    TMR3_Reload();              // Update TMR3 hardware
    TMR3_StopTimer();

    
    // Set clockFactor for delays
    clockFactor = 5;

}


