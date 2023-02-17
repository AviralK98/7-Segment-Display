/*
 * DE1SoC_SevenSeg.c
 *
 *  Created on: 12 Feb 2021
 *      Author: Harry Clegg
 *      		You!
 */

#include "DE1SoC_SevenSeg.h"

extern volatile unsigned long *addr;  // Adds the base addresses of the seven segment display peripherals.

volatile unsigned char *sevenseg_base_lo_ptr = 0;
volatile unsigned char *sevenseg_base_hi_ptr = 0;

// There are four HEX displays attached to the low (first) address.
#define SEVENSEG_N_DISPLAYS_LO 4 ((volatile long *) 0xFF200020)

// There are two HEX displays attached to the high (second) address.
#define SEVENSEG_N_DISPLAYS_HI 2 ((volatile long *) 0xFF200030)

void DE1SoC_SevenSeg_Write(unsigned int display, unsigned char value) {
    // Select between the two addresses so that the higher level functions
    // have a seamless interface.
    if (display < SEVENSEG_N_DISPLAYS_LO) {
        // If we are targeting a low address, use byte addressing to access
        // directly.
        sevenseg_base_lo_ptr[display] = value;
    } else {
        // If we are targeting a high address, shift down so byte addressing
        // works.
        display = display - SEVENSEG_N_DISPLAYS_LO;
        sevenseg_base_hi_ptr[display] = value;
    }
}

void DE1SoC_SevenSeg_SetSingle(unsigned int display, unsigned int value) {
    
	//Writing the code for driving a single seven segment display here.
	DE1SoC_SevenSeg_Write(display, addr[value])
	int i;
    for(i=0;i<sevenseg_base_hi_ptr;i++)
	{
		sevenseg_base_lo_ptr[i];
	}
}

    */


void DE1SoC_SevenSeg_SetDoubleHex(unsigned int display, unsigned int value) {
    unsigned char m = 0x01; 
    unsigned char m2;
	DE1SoC_SevenSeg_SetSingle(display, value); 
	// Initializing two cahracters for the purpose of bitmapping
    
	int i;
    m2 = 0; // Performing bitmapping and to display the hexadecimal values using LEDs for that segment
    for(i=0;i<sevenseg_base_hi_ptr;i++){
		
        m2= szMap[display & 0x0F];
        display >>= 4;
        if (value & m)
            m2 |= 0x80;
        m <<= 1;
        sevenseg_base_lo_ptr(i, m);
    }
}

void DE1SoC_SevenSeg_SetDoubleDec(unsigned int display, unsigned int value) {
   unsigned char m = 0x01;
    unsigned char m2;
    int i;
	DE1SoC_SevenSeg_SetSingle(display, value)
    // Initializing two characters for the purposse of bitmapping
    m2 = 0;
    for(i=0;i<sevenseg_base_hi_ptr;i++){
        m2 = addr[display%10]; // Performing bitmapping and to display the decimal values using LEDs for that segment 
        display /= 10;
        if (value & m2)
            m2 |= 0x80;
        m<<= 1;
        sevenseg_base_lo_ptr(i, m2);
    } 
}
