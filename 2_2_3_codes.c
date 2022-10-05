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
unsigned long int oldtime = 0;

void waitforpress(){
    while(!bit_is_set(TIFR3,ICF3)) _delay_ms(500);    //timer3 ICP3(Pin C7)
    // default mode: store time value on falling edge
    set(TIFR3,ICF3);
    tperiod = ICR3 - oldtime;
    oldtime = ICR3;
    tperiod = tperiod*1000/15625; // to calculate the time it takes under /1024 prescaler in ms
    m_usb_tx_uint(tperiod);
    m_usb_tx_string("ms");
    m_usb_tx_char(10); m_usb_tx_char(13);
}

void check(){
    
    if(bit_is_set(PINC,7)){
        set(PORTC,6);                   //turn on C6 LED
    }
    else{
        clear(PORTC,6)                      // turn off C6 LED
    }
}

int main(void)
{
    _clockdivide(0);         // set the system clock speed to 16Mhz
    set_led(ON);          // turn on the on board LED
    _delay_ms(1000);       // wait 1000 ms when at 16 MHz

    m_usb_init();          // initialize usb communication

    clear(DDRC,7);
    set(DDRC,6);

    set(TCCR3B,CS30);
    set(TCCR3B,CS32);         //set the prescaler to be /1024, and the frequency is  15.625kHz

    for(;;){
        check();
    }

    return 0;               /* never reached */
}
