/*
 * UART_program.c
 *
 * Created: 1/22/2024 4:56:09 PM
 *  Author: philo
 */ 
#include "../LIB/std_macros.h"
#include "../LIB/STD_Types.h"
#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"

void (*UART_TRANSMIT_CALLBACK)(void) = NULL_PTR;
void (*UART_RECEIVE_CALLBACK)(void) = NULL_PTR;
volatile uint8 Global_Data = 0;
volatile uint8 Global_Receive = 0;

void UART_VoidInit(void)
{
	uint8 Local_Temp = 0;
	/* Enable RXCIE */
	SET_BIT(UCSRB, UCSRB_RXCIE);
	/* Enable UDRIE */
	SET_BIT(UCSRB, UCSRB_UDRIE);
	/* Select UCSRC register */
	SET_BIT(Local_Temp, UCSRC_URSEL);
	/*Select 8-bit Data*/
	CLR_BIT(UCSRB, UCSRB_UCSZ2);
	SET_BIT(Local_Temp, UCSRC_UCSZ0);
	SET_BIT(Local_Temp, UCSRC_UCSZ1);
	/* Select UART Mode */
	CLR_BIT(Local_Temp, UCSRC_UMSEL);
	/* Select Parity Mode */
	CLR_BIT(Local_Temp, UCSRC_UPM0);
	CLR_BIT(Local_Temp, UCSRC_UPM1);
	/* Select Stop bit */
	CLR_BIT(Local_Temp, UCSRC_USBS);

	UCSRC = Local_Temp;

	/* Select Baud Rate */
	UBRRL = BAUD_RATE;
	/* Enable RX */
	SET_BIT(UCSRB, UCSRB_RXEN);
	/*Enable TX*/
	SET_BIT(UCSRB, UCSRB_TXEN);
}

void UART_vDisableEmptyInterrupt(void)
{
	CLR_BIT(UCSRB, UCSRB_UDRIE);
}
void UART_vEnableEmptyInterrupt(void)
{
	SET_BIT(UCSRB, UCSRB_UDRIE);
}

void UART_VoidSendData(uint8 Cpy_u8Data)
{
	#if UART_INTERRUPT_MODE == INTERRUPT_DISABLE
	while(Read_bIT(UCSRA, UCSRA_UDRE) == 1)
	UDR = Cpy_u8Data;
	#else
	UDR = Cpy_u8Data;
	#endif
}

uint8 UART_U8ReceiveData(void)
{
	uint8 localu8DataReceived;
	#if UART_INTERRUPT_MODE == INTERRUPT_DISABLE
	while(Read_bIT(UCSRA, UCSRA_RXC) == 1)
	localu8DataReceived = UDR;
	#else
	localu8DataReceived = UDR;
	#endif
	return localu8DataReceived;
}

void __vector_13 (void) __attribute__ ((signal, used));
void __vector_13(void)
{
	//Global_Data = UART_u8ReceiveData();
	UART_RECEIVE_CALLBACK();
}

void __vector_14 (void) __attribute__ ((signal, used));
void __vector_14(void)
{
	UART_TRANSMIT_CALLBACK();
}

void SendCallBack(void (*pf)(void))
{
	UART_TRANSMIT_CALLBACK = pf;
}

void ReceiveCallBack(void (*pf)(void))
{
	UART_RECEIVE_CALLBACK = pf;
}


