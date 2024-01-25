/*
 * HEEPROM_program.c
 *
 * Created: 1/22/2024 4:20:36 PM
 *  Author: philo
 */ 


#include "../LIB/STD_Types.h"
#include "../LIB/std_macros.h"
#include <util/delay.h>

#include "../MCAL/MTWI_interface.h"
#include "HEEPROM_interface.h"
#include "HEEPROM_pivate.h"
#include "HEEPROM_config.h"



void EEPROM_vRead(uint8 Copy_uint8LocationAddress , uint8 *Copy_puint8Data)
{
	/* Start condition  */
	TWI_enStartCondition();
	/* Send SLA With Write */
	TWI_enSetSlaveAddressWithWrite(SLAVE_ADDRESS);
	/* Send Memory location */
	TWI_enMasterWriteData(Copy_uint8LocationAddress);
	/* Repeat Start to change Write operation to Read operation */
	TWI_enRepeateStart();
	TWI_enSetSlaveAddressWithRead(SLAVE_ADDRESS);
	/* Master Receive Data*/
	TWI_enMasterReadData(Copy_puint8Data);
	TWI_vStopCondition();

}

void EEPROM_vWrite(uint8 Copy_uint8LocationAddress , uint8 Copy_uint8Data)
{
	/* Start condition  */
	TWI_enStartCondition();
	/* Send SLA With Write */
	TWI_enSetSlaveAddressWithWrite(SLAVE_ADDRESS);
	/* Send Memory location */
	TWI_enMasterWriteData(Copy_uint8LocationAddress);
	/* Master Send Data*/
	TWI_enMasterWriteData(Copy_uint8Data);
	TWI_vStopCondition();

	_delay_ms(10);

}



void EEPROM_vWritePage(uint8 Copy_uint8LocationAddress , uint8 *Copy_uint8Data , uint8 Length)
{
	uint8 i = 0;
	for(i = 0; i <Length; i++)
	{
		/* Start condition  */
		TWI_enStartCondition();
		/* Send SLA With Write */
		TWI_enSetSlaveAddressWithWrite(SLAVE_ADDRESS);
		/* Send Memory location */
		TWI_enMasterWriteData(Copy_uint8LocationAddress + i);
		/* Master Send Data*/

		TWI_enMasterWriteData(Copy_uint8Data[i]);

		_delay_ms(10);
	}

	TWI_vStopCondition();
}
void EEPROM_vReadPage(uint8 Copy_uint8LocationAddress , uint8 Length,uint8 *retArr)
{
	uint8 i = 0;
	for(i = 0; i <Length; i++)
	{
		/* Start condition  */
		TWI_enStartCondition();
		/* Send SLA With Write */
		TWI_enSetSlaveAddressWithWrite(SLAVE_ADDRESS);
		/* Send Memory location */
		TWI_enMasterWriteData(Copy_uint8LocationAddress + i);
		/* Repeat Start to change Write operation to Read operation */
		TWI_enRepeateStart();
		TWI_enSetSlaveAddressWithRead(SLAVE_ADDRESS);
		/* Master Receive Data*/

		TWI_enMasterReadData(retArr[i]);

		_delay_ms(10);
	}

	TWI_vStopCondition();
}

