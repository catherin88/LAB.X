/*
 * File:   Main.c
 * Author: Catherin Correa
 *
 * Created on 7 de mayo de 2017, 04:10 PM
 */


#include    <xc.h>
#include    "Configuracion.h"
#include    "TECLADO_LCD.h"
#include    "Mensajes.h"
#include    "Lib_generador.h"
#include    "Memoria.h"
#define     _XTAL_FREQ 8000000

const   unsigned char  sine[64]    =   {128, 140, 152, 165, 176, 188, 198, 208, 218, 226, 234, 240, 245, 250, 253, 254, 255, 254, 
253, 250, 245, 240, 234, 226, 218, 208, 198, 188, 176, 165, 152, 140, 128, 115, 103, 91, 79, 67, 57, 47, 37, 29, 22, 15, 10, 5, 
2, 1, 0, 1, 2, 5, 10, 15, 21, 29, 37, 47, 57, 67, 79, 90, 103, 115};

unsigned    char    V_Puerto1       =   0;
unsigned    char    V_Puerto2       =   0;
unsigned    char    flag_cambio     =   0;
unsigned    char    j = 0;


void interrupt high_priority ISR_H(void){
    unsigned char   aux_portb   = 0;
    Aux_T   = 0;
    if (INTCONbits.RBIF == 1){
        aux_portb   = PORTB;
        aux_portb   &=  0XF0;
        if  (aux_portb != 0xF0){
            leer_teclado ();
            if  (Aux_T != 0x80){
                switch  (Aux_T){
                    case    0X0F:
                        //Inhabilitado
                    break;
                    case    0X0E:
                        //Inhabilitado
                    break;
                    case    0X0A:
                        Senal   =   1;
                        Mensaje_LCD ();
                        E_Write   (1, Senal);
                    break;
                    case    0X0B:
                        Senal   =   2;
                        Mensaje_LCD ();
                        E_Write   (1, Senal);
                    break;
                    case    0X0C:
                        Senal   =   3;
                        Mensaje_LCD ();
                        E_Write   (1, Senal);
                        V_Puerto1 = 0;
                        V_Puerto2 = 0;
                    break;
                    case    0X0D:
                        Freq_charge     ();
                        cambio_frec     ();
                        Mensaje_LCD     ();
                        E_Write   (0, Frecuencia);
                        retardos        ();
                        Tecla [0]   =   0;
                        Tecla [1]   =   0;
                        Tecla [2]   =   0;
                        T2CONbits.TMR2ON    =   1;
                    break;
                    default:
                        Tecla [0]   = Tecla [1];
                        Tecla [1]   = Tecla [2];
                        Tecla [2]   = Aux_T;
                    break;
                }
            }
        }
        LATB    = 0XF0;
        INTCONbits.RBIF = 0;
    }
}

void interrupt low_priority ISR_L(void){
        LATA    =   V_Puerto1;
        LATC    =   V_Puerto2;
        PIR1bits.TMR2IF     =   0;        
        if  (j == 63)
            j  = 0;
        else
            j++;
        switch (Senal){
            case    1:
                V_Puerto1 = sine[j];
                V_Puerto2 = port (V_Puerto1);
            break;
            case    2:
                if (j>=31){
                    V_Puerto1 = 0;
                    V_Puerto2 = 0;
                }
                else{    
                    V_Puerto1 = 255;
                    V_Puerto2 = 0XC3;
                }
            break;
            case 3:
                V_Puerto1 = V_Puerto1 + 4;
                V_Puerto2 = port (V_Puerto1);
            break;
            default:
            break;
        }
}  


void main(void) {
    unsigned char   Senal_m =   0;
    osc_config      (0X73);
    conf_puertos    ();
    Teclado_config  ();
    ini_LCD         ();
    Senal_m             =   E_Read (1);
    if  (Senal_m == 1   ||  Senal_m == 2    ||  Senal_m == 3)
        Senal   =   Senal_m;
    else
        Senal   =   3;
    Frecuencia      =   E_Read (0);
    conversor       ();
    INTCONbits.GIEH     =   1;
    INTCONbits.GIEL     =   1;
    RCONbits.IPEN       =   1;
    Mensaje_LCD     ();
    retardos        ();
    conf_timer      ();
    while (1);
    
}
