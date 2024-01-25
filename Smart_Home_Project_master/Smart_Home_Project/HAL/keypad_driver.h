/*
 * keypad_driver.h
 *
 * Created: 1/22/2024 4:26:58 PM
 *  Author: philo
 */ 


#ifndef KEYPAD_DRIVER_H_
#define KEYPAD_DRIVER_H_


#define NOT_PRESSED 0xff
#include "../MCAL/DIO.h"


void keypad_vInit(void);

uint8 keypad_u8check_press(void);

#endif /* KEYPAD_DRIVER_H_ */