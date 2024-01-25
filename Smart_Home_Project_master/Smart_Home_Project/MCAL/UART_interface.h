/*
 * UART_interface.h
 *
 * Created: 1/22/2024 4:54:56 PM
 *  Author: philo
 */ 


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_


void UART_VoidInit(void);
void UART_VoidSendData(const uint8 Cpy_u8Data);
void UART_vDisableEmptyInterrupt(void);
void UART_vEnableEmptyInterrupt(void);
uint8 UART_U8ReceiveData(void);
void SendCallBack(void (*pf)(void));
void ReceiveCallBack(void (*pf)(void));




#endif /* UART_INTERFACE_H_ */