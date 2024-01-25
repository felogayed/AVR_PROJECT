/*
 * timer_driver.h
 *
 * Created: 1/23/2024 10:01:14 PM
 *  Author: philo
 */ 


#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../LIB/std_macros.h"
#include "../LIB/STD_Types.h"


void timer0_initializeCTC(void);
void timer0_stop(void);
void timer_initializefastpwm(void);
void change_dutycycle(float64 duty);




#endif /* TIMER_DRIVER_H_ */