/*
 * HEEPROM_interface.h
 *
 * Created: 1/22/2024 4:19:29 PM
 *  Author: philo
 */ 


#ifndef HEEPROM_INTERFACE_H_
#define HEEPROM_INTERFACE_H_


void EEPROM_vRead(uint8 Copy_uint8LocationAddress , uint8 *Copy_puint8Data);

void EEPROM_vWrite(uint8 Copy_uint8LocationAddress , uint8 Copy_uint8Data);

void EEPROM_vWritePage(uint8 Copy_uint8LocationAddress , uint8 *Copy_uint8Data , uint8 Length);

void EEPROM_vReadPage(uint8 Copy_uint8LocationAddress , uint8 Length,uint8 *retArr);




#endif /* HEEPROM_INTERFACE_H_ */