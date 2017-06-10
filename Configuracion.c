
#include <pic18f4550.h>


void osc_config(unsigned char parametro){
    OSCCON=parametro;
}

void conf_puertos(void){
    ADCON1  = 0X0F;
    CMCON   = 0X07;
    CVRCONbits.CVREN    =   0;
    CVRCONbits.CVROE    =   0;
    UCONbits.USBEN      =   0;
    TRISA   =   0XF0;
    TRISC   =   0X3C;
}