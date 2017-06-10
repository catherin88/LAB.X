/* 
 * File:   Memoria.h
 * Author: Catherin Correa
 *
 * Created on 18 de mayo de 2017, 03:39 PM
 */

#ifndef MEMORIA_H
#define	MEMORIA_H

#include <pic18f4550.h>

unsigned char E_Read (unsigned char address);

void E_Write   (unsigned char address, unsigned char data);

#endif	/* MEMORIA_H */

