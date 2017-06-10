#include    "Lib_generador.h"

void    Freq_charge (void)  {
    unsigned char   flag_nZ = 0, flag_OF = 0;
    for (unsigned char   i = 0; i<3; i++){
        if  (Tecla [i]!=0)
            flag_nZ  = 1;
    }
    if  (Tecla [0] >    2){
        flag_OF = 1;
    }
    else{
        if (Tecla [0] == 2){
            if (Tecla [1] > 5){
                flag_OF = 1;
            }
            else{
                if (Tecla [1] == 5){
                    if (Tecla [2] > 5){
                        flag_OF = 1;
                    }
                }
            }
        }
    }    
    if  (flag_nZ    ==  0){
        Freq [0]    =   0;
        Freq [1]    =   0;
        Freq [2]    =   1;
    }
    else {
        if  (flag_OF    ==  1){
            Freq [0]    =   2;
            Freq [1]    =   5;
            Freq [2]    =   5;
        }
        else{
            Freq [0]    =   Tecla[0];
            Freq [1]    =   Tecla[1];
            Freq [2]    =   Tecla[2];
        }
    }
}

void    cambio_frec     (void){
    unsigned char    Freq_aux    [3] = "";
    unsigned char    Frec_aux    =  0;
    Freq_aux[0] =   Freq[0];
    Freq_aux[1] =   Freq[1];
    Freq_aux[2] =   Freq[2];
    Freq_aux[0] =   Freq_aux[0]*100;
    Freq_aux[1] =   Freq_aux[1]*10;
    Frec_aux    =   Freq_aux[0]+Freq_aux[1]+Freq_aux[2];
    Frecuencia  =   Frec_aux;
}

void    retardos    (void){
    unsigned char   M_Aux   =   0;
    M_Aux   =   Frecuencia;
    if  (M_Aux > 0  &&  M_Aux <= 12)
        T2CON   =   0X3A;
    else if (M_Aux > 12 && M_Aux <= 24)
        T2CON   =   0X48;
    else if (M_Aux > 24 && M_Aux <= 60)
        T2CON   =   0X20;
    else if (M_Aux > 60 && M_Aux <= 121)
        T2CON   =   0X08;
    else if (M_Aux > 121 && M_Aux <= 255)
        T2CON   =   0;
    else
        T2CON   =   0;
    PR2 = V_Time[M_Aux-1];
}

void    conf_timer  (void){
    IPR1bits.TMR2IP =   0;
    PIE1bits.TMR2IE =   1;
    PIR1bits.TMR2IF =   0;
    T2CONbits.TMR2ON    =   1;
}

void    conversor   (void){
    int frec_m      =   0;
    frec_m          =   Frecuencia;
    unsigned char   n[3]    =   {0,0,0};
    while   (frec_m > 100){
        frec_m  =   frec_m-100;
        n[0]++;
    }
    while   (frec_m > 10){
        frec_m  =   frec_m-10;
        n[1]++;
    }
    while   (frec_m >0){
        frec_m  =   frec_m-1;
        n[2]++;
    }
    Freq[0] =   n[0];
    Freq[1] =   n[1];
    Freq[2] =   n[2];
}

unsigned char   port    (unsigned char v_puerto){
    unsigned char M1    =   0;
    unsigned char M2    =   0;
    
    M1  =   v_puerto & 0XC0; 
    M2  =   v_puerto & 0X30;
    M2  =   M2 >> 4;
    M1  =   M1 | M2;    
    
    return M1;    
}