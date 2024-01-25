/*
 * SPI.h
 *
 * Created: 1/23/2024 10:03:17 PM
 *  Author: philo
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "../LIB/STD_Types.h"
#include "../LIB/STD_MESSAGES.h"
#include "../LIB/std_macros.h"

#define SPI_SCK  7
#define SPI_MISO 6
#define SPI_MOSI 5
#define SPI_SS   4



void SPI_vInitMaster (void);
void SPI_vInitSlave (void);
uint8 SPI_ui8TransmitRecive (uint8 data);




#endif /* SPI_H_ */