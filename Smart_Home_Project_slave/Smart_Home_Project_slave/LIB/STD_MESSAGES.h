/*
 * STD_MESSAGES.h
 *
 * Created: 1/23/2024 9:54:54 PM
 *  Author: philo
 */ 


#ifndef STD_MESSAGES_H_
#define STD_MESSAGES_H_

#define ROOM1_STATUS    0x11
#define ROOM2_STATUS    0x12
#define TV_STATUS    0x13 // ROOM3_STATUS
#define FAN_STATUS    0x14    
#define GARAGE_DOOR_STATUS 		0x15
#define AIR_COND_STATUS 0x16

#define ROOM1_TURN_ON    0x21
#define ROOM2_TURN_ON    0x22
#define TV_TURN_ON    0x23 
#define FAN_TURN_ON    0x24   
#define OPEN_GARAGE 		 0x25
#define AIR_COND_TURN_ON 0x26

#define ROOM1_TURN_OFF    0x31
#define ROOM2_TURN_OFF    0x32
#define TV_TURN_OFF    0x33 
#define FAN_TURN_OFF    0x34 
#define CLOSE_GARAGE	  0x35
#define AIR_COND_TURN_OFF 0x36

#define SET_TEMPERATURE 0x40

#define DEFAULT_ACK    0xFF
#define DEMAND_RESPONSE 0xFF

#define ON_STATUS   0x01
#define OFF_STATUS  0x00

#define OPEN_STATUS   0x55
#define CLOSED_STATUS  0x56

#endif /* STD_MESSAGES_H_ */