/*
 * Smart_Home_Project_slave.c
 *
 * Created: 1/23/2024 9:37:21 PM
 *  Author: philo
 */ 
#include "../MCAL/SPI.h"
#include "../LIB/STD_MESSAGES.h"
#include "../MCAL/DIO.h"
#include "../HAL/LED.h"
#include "../MCAL/ADC_driver.h"
#include "../MCAL/timer_driver.h"
#include "APP_slave_Macros.h"
#include "../HAL/STEPPER_MOTOR_interface.h"




void USART_ISR(void);

uint8 garage_door = 0;

volatile uint16 required_temperature=24;                                          // the required temperature which sent from Master with initial value 24
volatile uint16 temp_sensor_reading=0;                                           // the temperature of the room
volatile uint8 counter=0;                                                       // the counter which determine the periodic time of implementing ISR
volatile uint8 last_air_conditioning_value=AIR_CONDTIONING_OFF;                // last air conditioning value which will help in hysteresis

int main(void)
{
	ADC_vinit();                                                           //initialize the ADC of the micro controller
	timer0_initializeCTC();                                               //Initialize the timer zero of the micro controller
	SPI_vInitSlave();                                                    //initialize the SPI as a slave
	
	
	//initialization of output pins of connected Leds or devices 
	
	LED_vInit(AIR_COND_PORT,AIR_COND_PIN);
	LED_vInit(TV_PORT,TV_PIN);
	LED_vInit(ROOM1_PORT,ROOM1_PIN);
	LED_vInit(ROOM2_PORT,ROOM2_PIN);
	LED_vInit(TV_PORT,TV_PIN);
	LED_vInit(ULN_Port,ULN_Base0);
	LED_vInit(ULN_Port,ULN_Base1);
	LED_vInit(ULN_Port,ULN_Base2);
	LED_vInit(ULN_Port,ULN_Base3);
	LED_vInit(FAN_PORT,FAN_PIN);
	
	uint8 request = DEFAULT_ACK;                                         //the value that is received from the master
	uint8 response = DEFAULT_ACK;                                       //the values that is sent back to the master
	
	
	
	while(1)  // --------------------------------> start of the while(1)
	{

		request = SPI_ui8TransmitRecive(DEFAULT_ACK);              //wait for the master to start the transmitting
		switch (request)//-----------------------------------------> start of big switch
		{
			                                                      //commands related to send the current status back to the master
			case ROOM1_STATUS:
			if (LED_u8ReadStatus(ROOM1_PORT,ROOM1_PIN)==0)       //if the led is turned off
			{
				response = OFF_STATUS;                          //set the response as off status
			}
			else if (LED_u8ReadStatus(ROOM1_PORT,ROOM1_PIN)==1)//if the led is turned on
			{
				response = ON_STATUS;                         //set the response as on status
			}
			else
			{
			}
			SPI_ui8TransmitRecive(response);                   //response to the transmitter with the status
			break;                                            //break the switch case
			case ROOM2_STATUS:
			if (LED_u8ReadStatus(ROOM2_PORT,ROOM2_PIN)==0)  //if the led is turned off
			{
				response = OFF_STATUS;                    //set the response as off status
			}
			else if (LED_u8ReadStatus(ROOM2_PORT,ROOM2_PIN)==1)//if the led is turned on
			{
				response = ON_STATUS;                         //set the response as on status
			}
			else
			{
			}
			SPI_ui8TransmitRecive(response);         //response to the transmitter with the status
			break;                                  //break the switch case
			case TV_STATUS:
			if (LED_u8ReadStatus(TV_PORT,TV_PIN)==0)//if the led is turned off
			{
				response = OFF_STATUS;                   //set the response as off status
			}
			else if (LED_u8ReadStatus(TV_PORT,TV_PIN)==1)//if the led is turned on
			{
				response = ON_STATUS;                         //set the response as on status
			}
			else
			{
			}
			SPI_ui8TransmitRecive(response);                //response to the transmitter with the status
			break;                                         //break the switch case
			case FAN_STATUS:
			if (LED_u8ReadStatus(FAN_PORT,FAN_PIN)==0)//if the led is turned off
			{
				response = OFF_STATUS;                   //set the response as off status
			}
			else if (LED_u8ReadStatus(FAN_PORT,FAN_PIN)==1)//if the led is turned on
			{
				response = ON_STATUS;                        //set the response as on status
			}
			else
			{
			}
			SPI_ui8TransmitRecive(response);                      //response to the transmitter with the status
			break;                                               //break the switch case
			case AIR_COND_STATUS:
			if (LED_u8ReadStatus(AIR_COND_PORT,AIR_COND_PIN)==0)//if the led is turned off
			{
				response = OFF_STATUS;                         //set the response as off status
			}
			else if (LED_u8ReadStatus(AIR_COND_PORT,AIR_COND_PIN)==1)//if the led is turned on
			{
				response = ON_STATUS;                              //set the response as on status
			}
			else
			{
			}
			SPI_ui8TransmitRecive(response);                      //response to the transmitter with the status
			break;
			case GARAGE_DOOR_STATUS://------------------------------------------>
			if (garage_door==0)            //if the led is turned off
			{
				response = CLOSED_STATUS;                         //set the response as off status
			}
			else if (garage_door==1)    //if the led is turned on
			{
				response = OPEN_STATUS;                      //set the response as on status
			}
			else
			{
			}
			SPI_ui8TransmitRecive(response);             //response to the transmitter with the status
			break;                                      //break the switch case
			
			//TURN ON COMMANDS 
			case ROOM1_TURN_ON:
			LED_vTurnOn(ROOM1_PORT,ROOM1_PIN);                                //turn on the led of room 1
			break;                                                           //break the switch case
			case ROOM2_TURN_ON:
			LED_vTurnOn(ROOM1_PORT,ROOM2_PIN);                             //turn on the led of room 2
			break;                                                        //break the switch case
			case TV_TURN_ON:
			LED_vTurnOn(TV_PORT,TV_PIN);                           //turn on the led of TV
			break;                                                      //break the switch case
			case FAN_TURN_ON:
			LED_vTurnOn(FAN_PORT,FAN_PIN);                         //turn on the led of FAN
			break;                                                    //break the switch case
			case AIR_COND_TURN_ON:
			timer0_initializeCTC();
			LED_vTurnOn(AIR_COND_PORT,AIR_COND_PIN);                //turn on the led of air conditioning
			break;                                                 //break the switch case
			case OPEN_GARAGE:
			StepperMotor_voidRotateCloclWise(420);	              // open the garage door
			StepperMotor_voidStop();                             //break the switch case
			garage_door = 1;					                // set the garage door to one
			break;                                              
			
			//TURN OFF COMMANDS 
			case ROOM1_TURN_OFF:
			LED_vTurnOff(ROOM1_PORT,ROOM1_PIN);                         //turn off the led of room 1
			break;                                                     //break the switch case
			case ROOM2_TURN_OFF:
			LED_vTurnOff(ROOM2_PORT,ROOM2_PIN);                      //turn off the led of room 2
			break;                                                  //break the switch case
			case TV_TURN_OFF:
			LED_vTurnOff(TV_PORT,TV_PIN);                   //turn off the led of TV
			break;                                               //break the switch case
			case FAN_TURN_OFF:
			LED_vTurnOff(FAN_PORT,FAN_PIN);                //turn off the led of FAN
			break;                                            //break the switch case
			case AIR_COND_TURN_OFF:
			timer0_stop();
			LED_vTurnOff(AIR_COND_PORT,AIR_COND_PIN);      //turn off the led of air conditioning
			break;                                        //break the switch case
			case CLOSE_GARAGE:
			StepperMotor_voidRotateCounterCloclWise(420); // close the garage door
			StepperMotor_voidStop();					 // break the switch case
			garage_door = 0;
			break;                                     
			
			// Set temperature
			case SET_TEMPERATURE:
			required_temperature = SPI_ui8TransmitRecive(DEFAULT_ACK);    //get the temperature from the master and store the temperature in required temperature
			break;                                                       //break the switch case
		}
		
		
		
	}
}




ISR(TIMER0_COMP_vect)
{
	counter++;                                                                    //count the ticks of the timer zero
	if(counter>=10)                                                              //do that code every 10 ticks
	{
		counter=0;                                                             //clear the counter of ticks
		temp_sensor_reading=(0.25*ADC_u16Read());                      //read the temperature from the temperature sensor connected to the ADC of the micro controller
		if (temp_sensor_reading>=(required_temperature+1))            //do that code if the read temperature if greater than required temperature by one or more
		{
			LED_vTurnOn(AIR_COND_PORT,AIR_COND_PIN);                 //turn on the led of the air conditioning
			last_air_conditioning_value=AIR_CONDTIONING_ON;         //save the value of the state of the air conditioning
		}
		else if (temp_sensor_reading<=(required_temperature-1))    //do that code if the read temperature if lesser than required temperature by one or more
		{
			LED_vTurnOff(AIR_COND_PORT,AIR_COND_PIN);             //turn off the led of the air conditioning
			last_air_conditioning_value=AIR_CONDTIONING_OFF;     //save the value of the state of the air conditioning
		}
		else if (required_temperature==temp_sensor_reading)      //do that code if the read temperature is equal to the required temperature
		{
			if (last_air_conditioning_value==AIR_CONDTIONING_ON)//in the case of the last saved status of the air conditioning was on
			{
				LED_vTurnOn(AIR_COND_PORT,AIR_COND_PIN);       //turn on the led of the air conditioning
			}
			else if (last_air_conditioning_value==AIR_CONDTIONING_OFF)//in the case of the last saved status of the air conditioning was off
			{
				LED_vTurnOff(AIR_COND_PORT,AIR_COND_PIN);//turn off the led of the air conditioning
			}
		}
	}
}


