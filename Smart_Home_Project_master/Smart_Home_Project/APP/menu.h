/*
 * menu.h
 *
 * Created: 1/22/2024 4:38:45 PM
 *  Author: philo
 */ 


#ifndef MENU_H_
#define MENU_H_

#include "main_config.h"
#include "../LIB/STD_MESSAGES.h"
#include "../LIB/STD_Types.h"
#include "../HAL/keypad_driver.h"
#include "../MCAL/SPI.h"
#include "../HAL/LCD.h"





uint8 ui8ComparePass(const uint8* pass1,const uint8* pass2,const uint8 size);



void vMenuOption(const uint8 u8SelectedRoom,const uint8 u8LoginMode);

uint8 u8GetKeyPressed(const uint8 u8LoginMode);

#endif /* MENU_H_ */