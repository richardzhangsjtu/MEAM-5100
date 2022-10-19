/* Name: main.c
 * Author: <Richard Zhang>
 * Copyright(C): 2022 Richard Zhang - All Rights Reserved
 * You may use, distribute and modify this code under the terms
 * of the MIT license
 */

#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file
#include "m_usb.h"         // includes the resources for USB communication included in the m_usb.h file

#define PRINTNUM(x) m_usb_tx_uint(x); m_usb_tx_char(10); m_usb_tx_char(13);

// Subroutine for setting up ADC channel
void ADC_setup(int ADCchannel){

    if(ADCchannel > 13 || ADCchannel < 0 || ADCchannel==2 || ADCchannel==3) {            // when input is illegal
        m_usb_tx_string("Your input channel is illegal! Please choose a correct channel");
        exit(1);                    // exit the subroutine illegally
    }

    set(ADMUX,REFS0);
    clear(ADMUX,REFS1);            // set the voltage to Vcc

    set(ADCSRA,ADPS0);
    set(ADCSRA,ADPS1);
    set(ADCSRA,ADPS2);             // set the prescaler to be 1/128

    if(ADCchannel == 0){
        set(DIDR0,ADC0D);   //disable digital input for ADC0
        clear(ADMUX,MUX0);  //choose ADC channel 0
        clear(ADMUX,MUX1);
        clear(ADMUX,MUX2);
        clear(ADCSRB,MUX5);
    }
    if(ADCchannel == 1){
        set(DIDR0,ADC1D);   //disable digital input for ADC1
        set(ADMUX,MUX0);    //choose ADC channel 1
        clear(ADMUX,MUX1);
        clear(ADMUX,MUX2);
        clear(ADCSRB,MUX5);
    }
    if(ADCchannel == 4){
        set(DIDR0,ADC4D);   //disable digital input for ADC4
        clear(ADMUX,MUX0);  //choose ADC channel 4
        clear(ADMUX,MUX1);
        set(ADMUX,MUX2);
        clear(ADCSRB,MUX5);
    }
    if(ADCchannel == 5){
        set(DIDR0,ADC5D);   //disable digital input for ADC5
        set(ADMUX,MUX0);    //choose ADC channel 5
        clear(ADMUX,MUX1);
        set(ADMUX,MUX2);
        clear(ADCSRB,MUX5);
    }
    if(ADCchannel == 6){
        set(DIDR0,ADC6D);   //disable digital input for ADC6
        clear(ADMUX,MUX0);  //choose ADC channel 6
        set(ADMUX,MUX1);
        set(ADMUX,MUX2);
        clear(ADCSRB,MUX5);
    }
    if(ADCchannel == 7){
        set(DIDR0,ADC7D);   //disable digital input for ADC7
        set(ADMUX,MUX0);    //choose ADC channel 7
        set(ADMUX,MUX1);
        set(ADMUX,MUX2);
        clear(ADCSRB,MUX5);
    }
    if(ADCchannel == 8){
        set(DIDR2,ADC8D);   //disable digital input for ADC8
        clear(ADMUX,MUX0);  //choose ADC channel 8
        clear(ADMUX,MUX1);
        clear(ADMUX,MUX2);
        set(ADCSRB,MUX5);
    }
    if(ADCchannel == 9){
        set(DIDR2,ADC9D);   //disable digital input for ADC9
        set(ADMUX,MUX0);    //choose ADC channel 9
        clear(ADMUX,MUX1);
        clear(ADMUX,MUX2);
        set(ADCSRB,MUX5);
    }
    if(ADCchannel == 10){
        set(DIDR2,ADC10D);   //disable digital input for ADC10
        clear(ADMUX,MUX0);   //choose ADC channel 10
        set(ADMUX,MUX1);
        clear(ADMUX,MUX2);
        set(ADCSRB,MUX5);
    }
    if(ADCchannel == 11){
        set(DIDR2,ADC11D);   //disable digital input for ADC11
        set(ADMUX,MUX0);     //choose ADC channel 11
        set(ADMUX,MUX1);
        clear(ADMUX,MUX2);
        set(ADCSRB,MUX5);
    }
    if(ADCchannel == 12){
        set(DIDR2,ADC12D);   //disable digital input for ADC12
        clear(ADMUX,MUX0);   //choose ADC channel 12
        clear(ADMUX,MUX1);
        set(ADMUX,MUX2);
        set(ADCSRB,MUX5);
    }
    if(ADCchannel == 13){
        set(DIDR2,ADC13D);   //disable digital input for ADC13
        set(ADMUX,MUX0);     //choose ADC channel 13
        clear(ADMUX,MUX1);
        set(ADMUX,MUX2);
        set(ADCSRB,MUX5);
    }

    set(ADCSRA,ADEN);       // enable ADC
    set(ADCSRA,ADSC);       // start conversion
}

// Subroutine for reading one ADC channel
void ADC_read(){
    while(!bit_is_set(ADCSRA,ADIF));    //

     if(bit_is_set(ADCSRA,ADIF)){       // judge whether ADC conversion is complete or not
         set(ADCSRA,ADIF);              // reset the flag

         m_usb_tx_string("\rADC=");     // use "\r" to erase former output
         m_usb_tx_uint(ADC);            // print ADC value from register at once

         set(ADCSRA,ADSC);              // start converting again
     }
}

int main(void)
{
    _clockdivide(0);         // set the system clock speed to 16Mhz
    set_led(ON);             // turn on the on board LED
    _delay_ms(1000);         // wait 1000 ms when at 16 MHz

    m_usb_init();

    for(;;){
        int Channel;         // choose ADC13
        Channel = 13;

        ADC_setup(Channel);   //initialize ADC13
        ADC_read();                      // print the value of ADC
    }


    return 0;              //never reaches
}
