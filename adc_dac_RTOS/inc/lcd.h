/*
 * lcd.h
 *
 *  Created on: 4/9/2015
 *  Author: Matias Leandro Ferraro
 */
#include "lpc_types.h"

typedef struct __LCD_DATA_Type {
	bool D4;
	bool D3;
	bool D2;
	bool D1;
	bool RS;
	bool EN;
} LCD_DATA_Type;

#define LCD_PORT 4	// Donde esta el LCD
#define LCD4     10	// Pines del puerto
#define LCD3     6
#define LCD2     5
#define LCD1     4
#define LCD_RS   8
#define LCD_EN   9

void lcd_init_port(void);
void lcd_init(void);
void lcd_gotoxy(int x, int y);
void lcd_putc(char c);
void enviar_lcd (LCD_DATA_Type data);
void printf_lcd(char * string);
void delay(void);


