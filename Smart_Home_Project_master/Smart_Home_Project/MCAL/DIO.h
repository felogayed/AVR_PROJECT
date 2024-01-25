/*
 * DIO.h
 *
 * Created: 1/22/2024 4:13:34 PM
 *  Author: philo
 */ 


#ifndef DIO_H_
#define DIO_H_


#define F_CPU 8000000UL
#include <util/delay.h>
#include "DIO_config_master.h"
#include "../LIB/STD_Types.h"


void DIO_vsetPINDir(uint8 portname,uint8 pinnumber,uint8 direction);
void DIO_write(uint8 portname,uint8 pinnumber,uint8 outputvalue);
uint8 DIO_u8read(uint8 portname,uint8 pinnumber);
void DIO_toggle(uint8 portname,uint8 pinnumber);
void DIO_write_port(uint8 portname,uint8 portvalue);
void clear_high_nibble(uint8 portname) ;
void dio_write_highnibble(uint8 portname,uint8 value);
void DIO_vconnectpullup(uint8 portname ,uint8 pinnumber, uint8 connect_pullup);

#endif /* DIO_H_ */