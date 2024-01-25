/*
 * APP_slave_Macros.h
 *
 * Created: 1/23/2024 10:10:39 PM
 *  Author: philo
 */ 


#ifndef APP_SLAVE_MACROS_H_
#define APP_SLAVE_MACROS_H_

#include "../LIB/STD_Types.h"

#define AIR_CONDTIONING_ON          (uint8)0x01
#define AIR_CONDTIONING_OFF			(uint8)0x00

#define AIR_COND_PIN				(uint8)2

#define ROOM1_PIN					(uint8)4
#define ROOM2_PIN					(uint8)5
#define TV_PIN					(uint8)6 //ROOM3_PIN
#define FAN_PIN					(uint8)7 

#define AIR_COND_PORT 				(uint8)'D'

#define ROOM1_PORT    				(uint8)'D'
#define ROOM2_PORT   				(uint8)'D'
#define TV_PORT   				(uint8)'D' //ROOM3_PORT
#define FAN_PORT    				(uint8)'D' 

#define ULN_Port          (uint8)'C'
#define ULN_Base0         (uint8)4
#define ULN_Base1         (uint8)5
#define ULN_Base2         (uint8)6
#define ULN_Base3         (uint8)7
#endif /* APP_SLAVE_MACROS_H_ */