/*
 * main_config.h
 *
 * Created: 1/22/2024 4:36:08 PM
 *  Author: philo
 */ 


#ifndef MAIN_CONFIG_H_
#define MAIN_CONFIG_H_

#include "../LIB/STD_Types.h"

#define NOT_STORED   0xFF
#define NOT_SELECTED 0xFF

#define BLOCK_MODE_TIME		   (uint32)20
#define CHARACTER_PREVIEW_TIME (uint16)300
#define DEGREES_SYMBOL		   (uint8)0xDF

//PIN Configuration 
#define PASS_SIZE       (uint8)4
#define TRIES_ALLOWED   (uint8)3
#define PASSWORD_SYMBOL (uint8)'*'
#define ASCII_ZERO      (uint8)'0'

#define PASS_NOT_SET (uint8)0xFF
#define PASS_SET     (uint8)0x50

#define RESET_VALUE  (uint8)'A'

#define ADMIN_PASS_STATUS_ADDRESS (uint16)0XE0
#define GUEST_PASS_STATUS_ADDRESS (uint16)0XE1

#define EEPROM_ADMIN_ADDRESS_one      (uint16)0XE2
#define EEPROM_ADMIN_ADDRESS_two      (uint16)0XE3
#define EEPROM_ADMIN_ADDRESS_three    (uint16)0XE4
#define EEPROM_ADMIN_ADDRESS_four     (uint16)0XE5

#define EEPROM_GUEST_ADDRESS_one      (uint16)0XE6
#define EEPROM_GUEST_ADDRESS_two      (uint16)0XE7
#define EEPROM_GUEST_ADDRESS_three    (uint16)0XE8
#define EEPROM_GUEST_ADDRESS_four     (uint16)0XE9

#define LOGIN_BLOCKED_ADDRESS     (uint16)0XEA


//Login configurations
#define NO_MODE (uint8)0
#define ADMIN   (uint8)1
#define GUEST   (uint8)2


// Logic values 
#define FALSE   (uint8)0
#define TRUE    (uint8)1


#define CHECK_ADMIN_MODE        (uint8)'0'
#define CHECK_GUEST_MODE        (uint8)'1'

#define SELECT_ROOM1            (uint8)'1'
#define SELECT_ROOM2            (uint8)'2'
#define SELECT_TV            (uint8)'3'
#define SELECT_FAN            (uint8)'4' 
#define ADMIN_MORE_OPTION       (uint8)'4'

#define SELECT_FAN_ADMIN      (uint8)'1' // SELECT_ROOM4_ADMIN
#define SELECT_GARAGE               (uint8)'2' 
#define SELECT_AIR_CONDITIONING (uint8)'3'
#define ADMIN_RET_OPTION        (uint8)'4'

#define SELECT_SET_TEMPERATURE  (uint8)'1'
#define SELECT_AIR_COND_CTRL    (uint8)'2'
#define SELECT_AIR_COND_RET     (uint8)'0'

//   number of ticks to run timeout 
#define ADMIN_TIMEOUT (uint16)3000
#define GUEST_TIMEOUT (uint16)2000


//   Show menu codes 
#define MAIN_MENU            (uint8)1
#define MORE_MENU            (uint8)2
#define ROOM1_MENU           (uint8)3
#define ROOM2_MENU           (uint8)4
#define TV_MENU           (uint8)5 
#define FAN_MENU           (uint8)6 
#define GARAGE_MENU              (uint8)7 
#define AIRCONDITIONING_MENU (uint8)8
#define AIRCOND_CTRL_MENU    (uint8)9
#define TEMPERATURE_MENU     (uint8)10



#endif /* MAIN_CONFIG_H_ */