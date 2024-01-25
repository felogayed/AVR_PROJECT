/*
 * MTWI_program.c
 *
 * Created: 1/22/2024 4:50:38 PM
 *  Author: philo
 */ 


#include "../LIB/STD_Types.h"
#include "../LIB/std_macros.h"

#include "MTWI_interface.h"
#include "MTWI_private.h"
#include "MTWI_config.h"


void TWI_vMasterInit(void)
{
	/* Set Clock configuration  TWBR = 2 */
	TWBR = 2;
	CLR_BIT(TWSR , TWSR_TWPS0);
	CLR_BIT(TWSR , TWSR_TWPS1);

	/* Enable Acknowledge bit */
	//SET_BIT(TWCR , TWCR_TWEA);
	/* Set my own Address */
	TWAR = MASTER_ADDRESS << 1;
	/* Enable TWI */
	SET_BIT(TWCR , TWCR_TWEN);
}
void TWI_vSlaveInit(void)
{
	/* Enable Acknowledge bit */
	SET_BIT(TWCR , TWCR_TWEA);
	/* Set my own Address */
	TWAR = SLAVE_ADDRESS << 1;
	/* Enable TWI */
	SET_BIT(TWCR , TWCR_TWEN);
}

TWI_ErrorState_t TWI_enStartCondition(void)
{
	TWI_ErrorState_t Local_ErrorState = NO_ERROR;

	/* enable start condition */
	SET_BIT(TWCR , TWCR_TWSTA);
	/* Clear interrupt flag to start the operation */
	SET_BIT(TWCR , TWCR_TWINT);
	/* Enable TWI */
	SET_BIT(TWCR , TWCR_TWEN);

	/*Wait until the interrupt flag us raised again  */
	while(Read_bIT(TWCR , TWCR_TWINT) == 0);

	if((TWSR & 0XF8) != START_CONDITION)
	{
		Local_ErrorState = START_CONDTITION_ERR;
	}
	else
	{
		/* Do Nothing */
	}

	return Local_ErrorState;
}
TWI_ErrorState_t TWI_enRepeateStart(void)
{
	TWI_ErrorState_t Local_ErrorState = NO_ERROR;
	/* enable start condition */
	SET_BIT(TWCR , TWCR_TWSTA);
	/* Clear interrupt flag to start the operation */
	SET_BIT(TWCR , TWCR_TWINT);
	/* Enable TWI */
	SET_BIT(TWCR , TWCR_TWEN);

	/*Wait until the interrupt flag us raised again  */
	while(Read_bIT(TWCR , TWCR_TWINT) == 0);

	if((TWSR & 0XF8) != REPEATE_START_CONDITION)
	{
		Local_ErrorState = REPEAT_START_ERR;
	}
	else
	{
		/* Do Nothing */
	}

	return Local_ErrorState;
}
TWI_ErrorState_t TWI_enSetSlaveAddressWithWrite(uint8 Copy_uint8SlaveAddress)
{
	TWI_ErrorState_t Local_ErrorState = NO_ERROR;
	/* Set Slave address in TWDR register */
	TWDR = Copy_uint8SlaveAddress ;
	/* Clear the start condition bit */
	CLR_BIT(TWCR , TWCR_TWSTA);
	/* Clear bit 0 to make write operation */
	CLR_BIT(TWDR , TWDR_TWD0);

	/* Clear interrupt flag to start the operation */
	SET_BIT(TWCR , TWCR_TWINT);
	/* Enable TWI */
	SET_BIT(TWCR , TWCR_TWEN);

	//TWCR = 0b10000100;

	/*Wait until the interrupt flag us raised again  */
	while(Read_bIT(TWCR , TWCR_TWINT) == 0);

	if((TWSR & 0XF8) == SLA_WITH_W_NOAK)
	{
		Local_ErrorState = SLA_W_NOACK_ERR;
	}
	else
	{
		/* Do Nothing */
	}
	return Local_ErrorState;

}
TWI_ErrorState_t TWI_enSetSlaveAddressWithRead(uint8 Copy_uint8SlaveAddress)
{
	TWI_ErrorState_t Local_ErrorState = NO_ERROR;

	/* Set Slave address in TWDR register */
	TWDR = Copy_uint8SlaveAddress | 1;

	/* Clear the start condition bit */
	CLR_BIT(TWCR , TWCR_TWSTA);
	/* Set bit 0 to make Read operation */
	SET_BIT(TWDR , TWDR_TWD0);
	/* Clear interrupt flag to start the operation */
	SET_BIT(TWCR , TWCR_TWINT);
	/* Enable TWI */
	SET_BIT(TWCR , TWCR_TWEN);



	/*Wait until the interrupt flag us raised again  */
	while(Read_bIT(TWCR , TWCR_TWINT) == 0);

	if((TWSR & 0XF8) == SLA_WITH_R_NOAK)
	{
		Local_ErrorState = SLA_R_NOACK_ERR;
	}
	else
	{
		/* Do Nothing */
	}
	return Local_ErrorState;

}
TWI_ErrorState_t TWI_enMasterWriteData(uint8 Copy_uint8Data)
{
	TWI_ErrorState_t Local_ErrorState = NO_ERROR;
	/* Write data to TWDR */
	TWDR = Copy_uint8Data;
	/* Clear interrupt flag to start the operation */
	SET_BIT(TWCR , TWCR_TWINT);
	/* Enable TWI */
	SET_BIT(TWCR , TWCR_TWEN);

	/*Wait until the interrupt flag us raised again  */
	while(Read_bIT(TWCR , TWCR_TWINT) == 0);

	if((TWSR & 0XF8) == MASTER_SEND_DATA_NOAK)
	{
		Local_ErrorState = MASTER_SEND_DATA_ERR;
	}
	else
	{
		/* Do Nothing */
	}

	return Local_ErrorState;

}
TWI_ErrorState_t TWI_enMasterReadData(uint8 *Copy_uint8Data)
{
	TWI_ErrorState_t Local_ErrorState = NO_ERROR;

	/* Enable TWI */
	SET_BIT(TWCR , TWCR_TWEN);
	/* Clear interrupt flag to start the operation */
	SET_BIT(TWCR , TWCR_TWINT);



	/*Wait until the interrupt flag us raised again  */
	while(Read_bIT(TWCR , TWCR_TWINT) == 0);

	if((TWSR & 0XF8) == MASTER_RECEIVE_DATA_NOAK)
	{
		Local_ErrorState = MASTER_RECEIVE_DATA_ERR;
	}
	else
	{

	}

	*Copy_uint8Data = TWDR;

	return Local_ErrorState;

}
void TWI_vStopCondition(void)
{

	/* Set bit TWSTO to make stop condition */
	SET_BIT(TWCR , TWCR_TWSTO);
	/* Clear interrupt flag to start the operation */
	SET_BIT(TWCR , TWCR_TWINT);
	/* Enable TWI */
	SET_BIT(TWCR , TWCR_TWEN);
}
