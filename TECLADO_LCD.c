
#include "TECLADO_LCD.h"

void Teclado_config(void){
    TRISB   =   0XF0;
    INTCON2bits.RBPU    =   0;
    INTCON2bits.RBIP    =   1;
    LATB    =   0XF0;
    INTCONbits.RBIF    =    0;
    INTCONbits.RBIE    =    1;
}

void    leer_teclado (void){
    unsigned char   aux_portb=0;
    Aux_T = 0X80;
    LATB    =   0XF7;
    aux_portb   = PORTB;
    aux_portb   &=  0XF0;
    if  (aux_portb == 0X70)
        Aux_T   = 1;
    else    if  (aux_portb == 0XB0)
        Aux_T   = 4;
    else    if  (aux_portb == 0XD0)
        Aux_T   = 7;
    else    if  (aux_portb == 0XE0)
        Aux_T   = 0X0F;
    else{
        LATB    =   0XFB;
        __delay_us(2);
        aux_portb   = PORTB;
        aux_portb   &=  0XF0;
        if  (aux_portb == 0X70)
            Aux_T   = 2;
        else    if  (aux_portb == 0XB0)
            Aux_T   = 5;
        else    if  (aux_portb == 0XD0)
            Aux_T   = 8;
        else    if  (aux_portb == 0XE0)
            Aux_T   = 0X00;
        else{
            LATB    =   0XFD;
            aux_portb   = PORTB;
            aux_portb   &=  0XF0;
            if  (aux_portb == 0X70)
                Aux_T   = 3;
            else    if  (aux_portb == 0XB0)
                Aux_T   = 6;
            else    if  (aux_portb == 0XD0)
                Aux_T   = 9;
            else    if  (aux_portb == 0XE0)
                Aux_T   = 0X0E;
            else{
                LATB    =   0XFE;
                aux_portb   = PORTB;
                aux_portb   &=  0XF0;
                if  (aux_portb == 0X70)
                    Aux_T   = 0X0A;
                else    if  (aux_portb == 0XB0)
                    Aux_T   = 0X0B;
                else    if  (aux_portb == 0XD0)
                    Aux_T   = 0X0C;
                else    if  (aux_portb == 0XE0)
                    Aux_T   = 0X0D;

            }
        }
    }
}

void    setup_LCD   (void){
    TRISD   =   0;
    TRISE   =   0;
    LATD    =   0;
    LATE    =   0;
    CCP1CONbits.P1M = 0;
    SSPCON1bits.SSPEN = 0;
    SPPCFGbits.CLK1EN   =0;
}

void    ini_LCD     (void){
    __delay_ms  (40);
    setup_LCD   ();
    LCD_cmd     (0X30);
    __delay_ms  (10);
    LCD_cmd     (0X30);
    __delay_ms  (10);
    LCD_cmd     (0X30);
    __delay_ms  (10);
    LCD_cmd     (0X3F);
    LCD_cmd     (0X0C);
    LCD_cmd     (0X06);
    LCD_cmd     (0X01);
}

void    LCD_cmd     (unsigned char  dato){
    LATD    =   dato;
    LATEbits.LATE0 = 0;
    LATEbits.LATE1 = 0;
    __delay_us (10);
    LATEbits.LATE2 = 1;
    __delay_us (10);
    LATEbits.LATE2 = 0;
    esperar_LCD ();
}

void    LCD_dato    (unsigned char  dato){
    LATD    =   dato;
    LATEbits.LATE0 = 1;
    LATEbits.LATE1 = 0;
    __delay_us (10);
    LATEbits.LATE2 = 1;
    __delay_us (10);
    LATEbits.LATE2 = 0;
    LATEbits.LATE0 = 0;
    esperar_LCD ();
}

void    esperar_LCD ()  {
    unsigned char bussy = 1;
    TRISD   =   0XFF;
    while   (bussy){
        LATEbits.LATE0 = 0;
        LATEbits.LATE1 = 1;
        __delay_us (10);
        LATEbits.LATE2 = 1;
        __delay_us (10);
        bussy = PORTD;
        __delay_us (10);
        LATEbits.LATE2 = 0;
        bussy   =   bussy>>7;
    }
    TRISD   =   0;
    LATEbits.LATE1 = 0;
}

void    shift_screen_D (void){
    LCD_cmd (0X18);
}

void    shift_screen_I (void){
    LCD_cmd (0X1C);
}

void    clr_screen (void){
    LCD_cmd (0X01);
}

void    enter       (void){
    LCD_cmd (0XC0);
}

void    cursor_D    (void){
    LCD_cmd (0X14);
}

void    cursor_I    (void){
    LCD_cmd (0X10);
}



/*
    #define RS        PORTE,0           ;leer datos de la LCD   
    #define RW        PORTE,1           ;escribir datos
    #define E         PORTE,2           ;enable
 */

