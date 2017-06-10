
#include    "Memoria.h"

unsigned char E_Read    (unsigned char address){
    EEADR   =   address;
    EECON1bits.EEPGD    =   0;
    EECON1bits.CFGS     =   0;
    EECON1bits.RD       =   1;
    while   (EECON1bits.RD  ==  1);
    return  EEDATA;
}

void E_Write   (unsigned char address, unsigned char data){
    EEADR   =   address;
    EEDATA  =   data;
    EECON1bits.EEPGD    =   0;
    EECON1bits.CFGS     =   0;
    EECON1bits.WREN     =   1;
    
    EECON2  =   0X55;
    EECON2  =   0XAA;
    EECON1bits.WR       =   1;
    
    while   (EECON1bits.WR  ==  1);
    EECON1bits.WREN     =   0; 
}