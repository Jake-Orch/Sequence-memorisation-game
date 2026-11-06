#include "simple_i2c.h" 
#include "mcc_generated_files/mcc.h"    // Include all MCC generated libraries

//==============================================================================================
void I2C_START_BIT(void)            //
{                                   // 
	PIR1bits.SSPIF = 0;             // Clear MSSP flag 
	SEN = 1;                        // Sends start bit 
	while(PIR1bits.SSPIF == 0);     // Wait for flag to be set high 
}							        //											 
//==============================================================================================
void I2C_STOP_BIT(void)             //
{                                   //
	PIR1bits.SSPIF = 0;             // Clear MSSP flag
	PEN = 1;                        // Sends stop bit
	while(PIR1bits.SSPIF == 0);     // Wait for flag to be set high
}                                   //                     
//==============================================================================================
void I2C_ACK_BIT(void)              //
{                                   // 
	PIR1bits.SSPIF = 0;             // Clear MSSP flag 
	ACKDT = 0;                      // Send acknowledge bit on the i2c bus 
	ACKEN = 1;                      // Use ACK to initiate transmission to slave 
	while(PIR1bits.SSPIF == 0);     // Wait for flag to be set high 
}							        // 
//==============================================================================================
void I2C_NACK_BIT(void)		        //                                          
{                                   //
    PIR1bits.SSPIF = 0;             // Clear MSSP flag							 
	ACKDT = 1;                      // Send no-acknowledge bit on i2c bus(NAK)  
	ACKEN = 1;                      // Use ACK to initiate transmission to slave
	while(PIR1bits.SSPIF == 0);     // Wait for flag to be set high			 
}                                   //											 
//==============================================================================================
void I2C_Write(char data)		    //
{                                   //                                          
	PIR1bits.SSPIF = 0; 	        // Clear MSSP flag							 
	SSPBUF = data;			        // Load buffer with data					 
	while(PIR1bits.SSPIF == 0);     // Wait for flag to be set high			 
}							        //											 
//==============================================================================================
char I2C_Read(void)                 //
{                                   //    
	PIR1bits.SSPIF = 0;             // Clear MSSP flag
	RCEN = 1;                       // Enable receiver-start reading from slave
	while(PIR1bits.SSPIF == 0);     // Wait for flag to be set high
	return SSPBUF;                  // Return the read data back
}							        //
//==============================================================================================
void I2C_COMMAND(char ctrl_code, char blk, char RW) //  
{                                   //
	PIR1bits.SSPIF = 0;             // Clear MSSP flag,send ctrl code,MSB first 
	SSPBUF =((ctrl_code<<4) | (blk<<1))+RW;               
	while(PIR1bits.SSPIF == 0);	    // Wait for flag to be set high			
}							        //											
//==============================================================================================
void I2C_POLL_LOOP(char ctrl_code, char block)      //
{                                   //    		                         
	char ACK = 1;                   // Variable to represent acknowledge        
	block = 0x00;                   // Set block address to 0x00               
	while(ACK)                      // While ACK = 1, execute the loop  
    {                               // 
		I2C_RESTART_BITT();          // Send a restart signal on i2c bus
		I2C_COMMAND(ctrl_code, block,0);       // Address the slave via its control code 
		ACK = ACKSTAT;              // When write is complete ACK returns 0
	}                               //                                     
}							        //										
//==============================================================================================
void I2C_RESTART_BITT(void)          //
{                                   //
	PIR1bits.SSPIF = 0; 		    // Clear MSSP flag							
	PEN = 1;				        // Sends stop bit                  
	while(PIR1bits.SSPIF == 0);     // Wait for flag to be set high
	PIR1bits.SSPIF = 0;             // Clear MSSP flag again
	SEN = 1;                        // Sends start bit
	while(PIR1bits.SSPIF == 0);     // Wait for flag to be set high
}	                                //