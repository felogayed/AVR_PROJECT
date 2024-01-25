/*
 * LCD.h
 *
 * Created: 1/22/2024 4:29:35 PM
 *  Author: philo
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "../MCAL/DIO.h"
#include "LCD_config.h"
#define CLR_SCREEN           0X01
#define DISPLAY_ON_CURSOR_ON 0X0E
#define EIGHT_BIT_MODE       0X38
#define FOUR_BIT_MODE_I      0X02
#define FOUR_BIT_MODE_II     0X28


void LCD_vInit(void);
void LCD_vSend_cmd(uint8 cmd);
void LCD_vSend_char(uint8 data);
void LCD_vSend_string(char *data);
void LCD_clearscreen(void);
void LCD_movecursor(uint8 row,uint8 column);
void LCD_PrintNumber(uint8 num);
#endif /* LCD_H_ */