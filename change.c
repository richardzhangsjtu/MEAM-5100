#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file
#include "m_usb.h"         

#define PRINTNUM(x) m_usb_tx_uint(x); m_usb_tx_char(10); m_usb_tx_char(13);

void statecheck(){
    if(bit_is_set(PINC,7)){
        set(PORTC,6);
        m_usb_tx_string("Logical High"); m_usb_tx_char(10); m_usb_tx_char(13);
    }
    else{
        clear(PORTC,6);
        m_usb_tx_string("Logical Low"); m_usb_tx_char(10); m_usb_tx_char(13);
    }
}

int main(void)
{
    _clockdivide(0);         // set the system clock speed to 16Mhz
    set_led(ON);          // turn on the on board LED
    _delay_ms(1000);       // wait 1000 ms when at 16 MHz

    m_usb_init();          // initialize usb communication

    clear(DDRC,7);        // clear input on PC7
    set(DDRC,6);

    while(1){
        statecheck();
    }
    return 0;             
}
