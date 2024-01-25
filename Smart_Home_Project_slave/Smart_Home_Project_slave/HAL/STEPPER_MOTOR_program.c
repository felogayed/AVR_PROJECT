#include "../LIB/STD_Types.h"
#include "../MCAL/DIO.h"
#include "STEPPER_MOTOR_config.h"
#include "STEPPER_MOTOR_interface.h"
#include "STEPPER_MOTOR_private.h"
#include "util/delay.h"

void StepperMotor_voidRotateCloclWise(uint16 Copy_u16Angle){
	Copy_u16Angle /= 0.7 ;
	uint16 Local_u16Counter = 0 ;
	while(Local_u16Counter < Copy_u16Angle){
		DIO_write(ULN_Port,ULN_Base0,0);
		DIO_write(ULN_Port,ULN_Base1,0);
		DIO_write(ULN_Port,ULN_Base2,0);
		DIO_write(ULN_Port,ULN_Base3,1);
		_delay_ms(2);
		DIO_write(ULN_Port,ULN_Base0,0);
		DIO_write(ULN_Port,ULN_Base1,0);
		DIO_write(ULN_Port,ULN_Base2,1);
		DIO_write(ULN_Port,ULN_Base3,0);
		_delay_ms(2);
		DIO_write(ULN_Port,ULN_Base0,0);
		DIO_write(ULN_Port,ULN_Base1,1);
		DIO_write(ULN_Port,ULN_Base2,0);
		DIO_write(ULN_Port,ULN_Base3,0);
		_delay_ms(2);
		DIO_write(ULN_Port,ULN_Base0,1);
		DIO_write(ULN_Port,ULN_Base1,0);
		DIO_write(ULN_Port,ULN_Base2,0);
		DIO_write(ULN_Port,ULN_Base3,0);
		_delay_ms(2);
		Local_u16Counter ++ ;
	}
}

void StepperMotor_voidRotateCounterCloclWise(uint16 Copy_u16Angle){
	Copy_u16Angle /= 0.7 ;
	uint16 Local_u16Counter = 0 ;
	while(Local_u16Counter < Copy_u16Angle){
		DIO_write(ULN_Port,ULN_Base0,1);
		DIO_write(ULN_Port,ULN_Base1,0);
		DIO_write(ULN_Port,ULN_Base2,0);
		DIO_write(ULN_Port,ULN_Base3,0);
		_delay_ms(2);
		DIO_write(ULN_Port,ULN_Base0,0);
		DIO_write(ULN_Port,ULN_Base1,1);
		DIO_write(ULN_Port,ULN_Base2,0);
		DIO_write(ULN_Port,ULN_Base3,0);
		_delay_ms(2);
		DIO_write(ULN_Port,ULN_Base0,0);
		DIO_write(ULN_Port,ULN_Base1,0);
		DIO_write(ULN_Port,ULN_Base2,1);
		DIO_write(ULN_Port,ULN_Base3,0);
		_delay_ms(2);
		DIO_write(ULN_Port,ULN_Base0,0);
		DIO_write(ULN_Port,ULN_Base1,0);
		DIO_write(ULN_Port,ULN_Base2,0);
		DIO_write(ULN_Port,ULN_Base3,1);
		_delay_ms(2);
		Local_u16Counter ++ ;
	}
}

void StepperMotor_voidStop(void){
	DIO_write(ULN_Port,ULN_Base0,0);
	DIO_write(ULN_Port,ULN_Base1,0);
	DIO_write(ULN_Port,ULN_Base2,0);
	DIO_write(ULN_Port,ULN_Base3,0);
}



