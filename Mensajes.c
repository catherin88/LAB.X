#include    "Mensajes.h"
#include    "TECLADO_LCD.h" 

void    Mensaje_LCD     (void){
    unsigned char   Numeros [3]={0, 0, 0};
    for     (unsigned char   i = 0; i<3; i++)
        Numeros [i] = 48 + Freq[i];
    clr_screen      ();
    switch (Senal){
        case 1:
            LCD_dato (' ');
            LCD_dato ('S');
            LCD_dato ('e');
            LCD_dato (0XEE);
            LCD_dato ('a');
            LCD_dato ('l');
            LCD_dato (' ');
            LCD_dato ('S');
            LCD_dato ('e');
            LCD_dato ('n');
            LCD_dato ('o');
            LCD_dato ('i');
            LCD_dato ('d');
            LCD_dato ('a');
            LCD_dato ('l');
        break;
        case 2:
            LCD_dato (' ');
            LCD_dato ('S');
            LCD_dato ('e');
            LCD_dato (0XEE);
            LCD_dato ('a');
            LCD_dato ('l');
            LCD_dato (' ');
            LCD_dato ('C');
            LCD_dato ('u');
            LCD_dato ('a');
            LCD_dato ('d');
            LCD_dato ('r');
            LCD_dato ('a');
            LCD_dato ('d');
            LCD_dato ('a');
        break;
        case 3:
            LCD_dato (' ');
            LCD_dato ('S');
            LCD_dato ('e');
            LCD_dato (0XEE);
            LCD_dato ('a');
            LCD_dato ('l');
            LCD_dato (' ');
            LCD_dato ('D');
            LCD_dato ('.');
            LCD_dato ('S');
            LCD_dato ('i');
            LCD_dato ('e');
            LCD_dato ('r');
            LCD_dato ('r');
            LCD_dato ('a');
        break;
        default:
            
        break;
    }
    enter ();
    LCD_dato (' ');
    LCD_dato (' ');
    LCD_dato ('F');
    LCD_dato ('r');
    LCD_dato ('e');
    LCD_dato ('c');
    LCD_dato (':');
    LCD_dato (' ');
    for     (unsigned char   i = 0; i<3; i++)
        LCD_dato (Numeros [i]);
    LCD_dato (' ');
    LCD_dato ('H');
    LCD_dato ('z');
}
