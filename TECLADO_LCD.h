/* 
 * File:   TECLADO_LCD.h
 * Author: Catherin Correa
 *
 * Created on 10 de mayo de 2017, 02:52 PM
 */

#ifndef TECLADO_LCD_H
#define	TECLADO_LCD_H

#include "Configuracion.h"
#include    <xc.h>
#define     _XTAL_FREQ 8000000

unsigned char Tecla[3] = {0, 0, 0};     // Tecla [0] + significativo
unsigned char Aux_T = 0;
unsigned char Frecuencia = 0;
unsigned char Freq[3] = {0, 0, 0};      // Freq [0] + significativo
unsigned char Senal = 0;                

void    Teclado_config(void);

void    leer_teclado (void);

void    setup_LCD   (void);

void    ini_LCD     (void);

void    LCD_cmd     (unsigned char  dato);

void    LCD_dato    (unsigned char  dato);

void    esperar_LCD (void);

void    shift_screen_D (void);

void    shift_screen_I (void);

void    clr_screen (void);

void    enter       (void);

void    cursor_D    (void);

void    cursor_I    (void);

#endif	/* TECLADO_LCD_H */

