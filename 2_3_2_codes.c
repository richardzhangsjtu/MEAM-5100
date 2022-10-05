/* Name: main.c
 * Author: <Richard Zhang>
 * Copyright(C): 2022 Richard Zhang - All Rights Reserved
 * You may use, distribute and modify this code under the terms
 * of the GNU GPLv3.0 license
 */
#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file
#include "m_usb.h"         // includes the resources for USB communication included in the m_usb.h file

#define PRINTNUM(x) m_usb_tx_uint(x); m_usb_tx_char(10); m_usb_tx_char(13);


unsigned int tperiod = 0;
unsigned int oldtime = 0;

void frequencydetect(){
    while(!bit_is_set(TIFR3,ICF3)) {
        clear(PORTC,6);
        clear(PORTB,6);
    } //timer3 ICP3(Pin C7), when there's no input remain the off status of each LED
    // default mode: store time value on falling edge
    set(TIFR3,ICF3);
    tperiod = ICR3 - oldtime;
    oldtime = ICR3;
    int Hz = 15625/tperiod;   //since the prescaler is set to 15.625khz, the frequency is determined by input capture and timer mode
    PRINTNUM(Hz)

    if(Hz >= 15 && Hz<= 30){                 // set the accuracy around 23HZ
        clear(PORTC,6);
        set(PORTB,6);                       // set PC6's LED ON and PB6's LED off
    }
    else if(Hz >= 600 && Hz <= 800){         // set the accuracy around 700HZ
        clear(PORTB,6);
        set(PORTC,6);                        // set PB6's LED ON and PC6's LED off
    }
    else{                                    // for noise or light's frequency other than 23 and 700Hz, turn offf both of the LEDs
        clear(PORTC,6);
        clear(PORTB,6);
    }
}




int main(void)
{
    _clockdivide(0);       // set the system clock speed to 16Mhz
    set_led(ON);           // turn on the on board LED
    _delay_ms(1000);       // wait 1000 ms when at 16 MHz

    m_usb_init();          // initialize usb communication

    set(TCCR3B,CS30);
    set(TCCR3B,CS32);         //set the prescaler to be /1024, and the frequency is  15.625kHz

    clear(DDRC,7);            //make sure Port C7 input is clear
    set(DDRC,6);             // reset the sixth bit of DDRC register as 1, Port C6 as output
    set(DDRB,6);              // reset the sixth bit of DDRB register as 1, Port B6 as output

    for(;;){
     frequencydetect();     // call subroutine to find out the frequency and light corresponding LEDs
    }

    return 0;               /* never reached */
}


