/*
 * LED.h
 *
 * Created: 1/22/2024 4:34:01 PM
 *  Author: philo
 */ 


#ifndef LED_H_
#define LED_H_
#include "../MCAL/DIO.h"
#include "../LIB/STD_Types.h"


void LED_vInit(uint8 portname,uint8 pinnumber);
void LED_vTurnOn(uint8 portname,uint8 pinnumber);//
void LED_vTurnOff(uint8 portname,uint8 pinnumber);
void LED_vToggle(uint8 portname,uint8 pinnumber);//
uint8 LED_u8ReadStatus(uint8 portname,uint8 pinnumber);
#endif /* LED_H_ */