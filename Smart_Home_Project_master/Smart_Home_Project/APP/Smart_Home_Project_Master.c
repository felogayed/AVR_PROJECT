/*
 * Smart_Home_Project_Master.c
 *
 * Created: 1/22/2024 4:09:18 PM
 *  Author: philo
 */ 
#include "main_config.h"
#include "../HAL/LCD.h"
#include "../HAL/HEEPROM_interface.h"
#include "../MCAL/MTWI_interface.h"
#include "../MCAL/timer_driver.h"
#include "../HAL/keypad_driver.h"
#include "../MCAL/SPI.h"
#include "../HAL/LED.h"
#include "menu.h"
#include <avr/io.h>
#include "../MCAL/UART_interface.h"


uint8 UART_DATA = 0 ;
void USART_ISR(void);
void USART_ISR(void)                                           // UART ISR that resets in passwords for th MC
{
	//u8FlagGlb = 1;
	UART_DATA=UART_U8ReceiveData();
	if (UART_DATA==RESET_VALUE)
	{
		UART_DATA = 0;
		EEPROM_vWrite(ADMIN_PASS_STATUS_ADDRESS,PASS_NOT_SET);
		_delay_ms(100);
		EEPROM_vWrite(GUEST_PASS_STATUS_ADDRESS,PASS_NOT_SET);
		_delay_ms(100);
		LCD_clearscreen();
		LCD_movecursor(0,1);
		LCD_vSend_string("PLEASE RESET ");
		LCD_movecursor(2,1);
		LCD_vSend_string("THE POWER");
		_delay_ms(1000);
		while(1);
	}
}

volatile uint16 session_counter = 0;                                         //indicate session time
//uint8 u8FlagGlb=0;
uint8 timeout_flag = FALSE;                                                 //stores if the session is still valid or outdated




int main(void)
{
	// variables initialization
	uint8 temperature = 0;                                              //The average temperature of the room
	uint8 temp_ones = NOT_SELECTED;                                    //The entered right number of the temperature
	uint8 temp_tens = NOT_SELECTED;                                   //The entered left number of the temperature
	uint8 login_mode = NO_MODE;                                      //Store the current user mode admin or guest or not logged in
	uint8 block_mode_flag = FALSE;                                  //is true if the login is blocked or false if not blocked
	uint8 key_pressed = NOT_PRESSED;                               //set the first value of the key to 0xFF
	
	//  INITIALIZE 
	LED_vInit(SCL_PIN,SCL_PIN_NUMBER);                        // initializes the TWI PIN
	LED_vInit(SDA_PIN,SDA_PIN_NUMBER);                       // initializes the TWI PIN
	LCD_vInit();                                            //initializes the LCD screen
	keypad_vInit();                                        //initializes the keypad
	SPI_vInitMaster();                                    //initializes the communication protocol of SPI
	TWI_vMasterInit();                                   //initializes the communication protocol of TWI
	UART_VoidInit();                                    // initialize the UART
	ReceiveCallBack(USART_ISR);
	UART_vDisableEmptyInterrupt();
	sei();
	DIO_vsetPINDir('D',0,0);
	DIO_vsetPINDir('D',1,1);
	
	
	// Printing Welcome screen 
	LCD_vSend_string("Welcome Home ");
	_delay_ms(1000);                               //Halt the system for the given time in (ms)
	LCD_clearscreen();                            //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
	
	
	 // Setting Admin and Guest passwords if not set 
	//read the state of the the passwords of the admin and guest if both are set or not set
	uint8 STATUS_1;
	uint8 STATUS_2;
	EEPROM_vRead(ADMIN_PASS_STATUS_ADDRESS,&STATUS_1);
	EEPROM_vRead(GUEST_PASS_STATUS_ADDRESS,&STATUS_2);
	if ( ( STATUS_1 != PASS_SET) || ( STATUS_2 != PASS_SET) )
	{
		LCD_vSend_string("Login for");                                          //printing login menu
		LCD_movecursor(2,1);                                                   //move the cursor to the second line
		LCD_vSend_string("first time");
		_delay_ms(1000);                                                     //Halt the system for the given time in (ms)
		LCD_clearscreen();                                                  //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
		LCD_vSend_string("Set Family pass");                                //printing the set admin password menu
		LCD_movecursor(2,1);
		LCD_vSend_string("Family pass:");

		// setting Admin password 
		uint8 pass_counter=0;                                                         //the counter of the characters of the password
		uint8 pass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};         //the array where it stored the password
		while (pass_counter<PASS_SIZE)                                              //loop till the user finish inserting the pass
		{
			key_pressed = NOT_PRESSED;                                            //return the variable that holds the pressed key from keypad to its initial value
			while (key_pressed == NOT_PRESSED)                                   //repeat till the user press any key
			{
				key_pressed = keypad_u8check_press();                          //if the user pressed any button in keypad save the value in key_pressed
			}

			pass[pass_counter]=key_pressed;                                 //add the entered character to the pass array
			LCD_vSend_char(key_pressed);                                   //print the entered character
			_delay_ms(CHARACTER_PREVIEW_TIME);                            //Halt the system for the given time in (ms)
			LCD_movecursor(2,12+pass_counter);                           //move the lcd cursor to the previous location to write the password symbol over the character
			LCD_vSend_char(PASSWORD_SYMBOL);                            // to display (Password sign *)
			_delay_ms(100);                                            //Halt the system for the given time in (ms)
			pass_counter++;                                           //increase the characters count
		}
		EEPROM_vWrite(EEPROM_ADMIN_ADDRESS_one,pass[0]);                     // saving first number in the first place in EEPROM
		_delay_ms(100);
		EEPROM_vWrite(EEPROM_ADMIN_ADDRESS_two,pass[1]);                    // saving second number in the second place in EEPROM
		_delay_ms(100);
		EEPROM_vWrite(EEPROM_ADMIN_ADDRESS_three,pass[2]);				   // saving third number in the third place in EEPROM
		_delay_ms(100);
		EEPROM_vWrite(EEPROM_ADMIN_ADDRESS_four,pass[3]);                 //save the entire password as a block to the EEPROM
		_delay_ms(100);
		EEPROM_vWrite(ADMIN_PASS_STATUS_ADDRESS,PASS_SET);              //write the status of pass as it is set
		_delay_ms(100);
		LCD_clearscreen();                                            //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
		LCD_vSend_string("Pass Saved");                              // show pass saved message
		_delay_ms(500);                                             //Halt the system for the given time in (ms)
		LCD_clearscreen();                                         //remove all previously printed characters on the LCD and move the cursor to the first column of the first row

		// setting guest password 
		pass_counter=0;                                                          //reset password counter which count the characters of the pass
		LCD_vSend_string("Set Guest Pass");                                     //printing the set admin password menu
		LCD_movecursor(2,1);
		LCD_vSend_string("Guest Pass:");
		while (pass_counter<PASS_SIZE)                                        //loop till the user finish inserting the pass
		{
			key_pressed = NOT_PRESSED;                                       //return the variable that holds the pressed key from keypad to its initial value
			while (key_pressed == NOT_PRESSED)                              //repeat till the user press any key
			{
				key_pressed = keypad_u8check_press();                     //if the user pressed any button in keypad save the value in key_pressed
			}

			pass[pass_counter]=key_pressed;                             //add the entered character to the pass array
			LCD_vSend_char(key_pressed);                               //print the entered character
			_delay_ms(CHARACTER_PREVIEW_TIME);                        //Halt the system for the given time in (ms)
			LCD_movecursor(2,12+pass_counter);                       //move the lcd cursor to the previous location to write the password symbol over the character
			LCD_vSend_char(PASSWORD_SYMBOL);                        // to display (Password sign *)
			_delay_ms(100);                                        //Halt the system for the given time in (ms)
			pass_counter++;                                       //increase the characters count
		}
		EEPROM_vWrite(EEPROM_GUEST_ADDRESS_one,pass[0]);                     // saving first number in the first place in EEPROM
		_delay_ms(100);
		EEPROM_vWrite(EEPROM_GUEST_ADDRESS_two,pass[1]);	                // saving second number in the second place in EEPROM
		_delay_ms(100);
		EEPROM_vWrite(EEPROM_GUEST_ADDRESS_three,pass[2]);                 // saving third number in the third place in EEPROM
		_delay_ms(100);
		EEPROM_vWrite(EEPROM_GUEST_ADDRESS_four,pass[3]);                 //save the entire password as a block to the EEPROM
		_delay_ms(100);
		EEPROM_vWrite(GUEST_PASS_STATUS_ADDRESS,PASS_SET);               //write the status of pass as it is set
		_delay_ms(100);
		LCD_clearscreen();                                              //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
		LCD_vSend_string("Pass Saved");                                //move the lcd cursor to the previous location
		_delay_ms(500);                                               //Halt the system for the given time in (ms)
		LCD_clearscreen();                                           //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
		EEPROM_vWrite(LOGIN_BLOCKED_ADDRESS,FALSE);
	}// ------------------------------------------------> The end of if admin and guest password is set
	
	
	else              //this code of else run only if the system is not running for the first time (ADMIN and GUEST passwords are set)
	{
		 EEPROM_vRead(LOGIN_BLOCKED_ADDRESS,&block_mode_flag);                 //read the blocked location from EEPROM
	}
	while (1)//------------------------------------------> The start of the periodic code
	{
		key_pressed = NOT_PRESSED;                            //return the variable that holds the pressed key from keypad to its initial value
		uint8 pass_tries_count=0;                            //stores how many times the user tried to log in to the system and failed
		
		if ( timeout_flag==TRUE )                           //check for timeout
		{//if timeout flag was raised
			timer0_stop();                                                 //stop the timer that increase the session counter
			session_counter = 0;                                          //clear session counter
			timeout_flag=FALSE;                                          //clear time out flag
			login_mode=NO_MODE;                                         //log the user out
			key_pressed = NOT_PRESSED;                                 //clear the key_pressed to avoid unwanted selection in the menu switch
			LCD_clearscreen();                                      //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
			LCD_vSend_string("Session Timeout");                   //print session timeout message
			_delay_ms(1000);                                      //Halt the system for the given time in (ms)
		}
		while (login_mode==NO_MODE)                                      //The user can only leave the loop only in case of he was logged in as guest or admin
		{
			if(block_mode_flag==TRUE)                                   //if the login process was blocked wait till the end of the block period
			{
				LCD_clearscreen();                                     //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
				sint8 Block_Counter;
				for (Block_Counter=BLOCK_MODE_TIME;Block_Counter>0;Block_Counter--)  // printing the remaining time for the user to return to enter password
				{
					LCD_clearscreen();
					LCD_movecursor(0,0);
					LCD_vSend_string("Login blocked");
					LCD_movecursor(2,1);
					LCD_vSend_string("wait");
					LCD_movecursor(2,6);
					LCD_PrintNumber(Block_Counter);
					LCD_movecursor(2,9);
					LCD_vSend_string("seconds");
					_delay_ms(1000);
				}	                                                          //Halt the system for the given time in (ms)
				pass_tries_count = 0;                                        //Clear the count on number of wrong tries
				block_mode_flag = FALSE;                                    //Disable block of runtime
				EEPROM_vWrite(LOGIN_BLOCKED_ADDRESS,FALSE);               //write false at blocked location in EEPROM
			}
						//if (u8FlagGlb == 1)
						//{
							/*
							if (UART_DATA=='A')
							{
								LCD_clearscreen();
								LCD_movecursor(0,0);
								LCD_vSend_string("ana gwa el uart");
								_delay_ms(1000);
								UART_DATA = 0;
							}
							*/
							//u8FlagGlb=0;
						//}
			LCD_clearscreen();                                                     //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
			LCD_vSend_string("Select mode :");
			LCD_movecursor(2,1);
			LCD_vSend_string("0:Family 1:Guest");
			while(key_pressed==NOT_PRESSED)                                      //wait for the selection of the mode
			{
				
				key_pressed = keypad_u8check_press();                          //if the user pressed any button in keypad save the value in key_pressed
			}
			if ( key_pressed!=CHECK_ADMIN_MODE && key_pressed!=CHECK_GUEST_MODE )
			{
				LCD_clearscreen();                                          //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
				LCD_vSend_string("Wrong input.");                          //Prints error message on the LCD
				key_pressed = NOT_PRESSED;                                //return the variable that holds the pressed key from keypad to its initial value
				_delay_ms(1000);                                         //Halt the system for the given time in (ms)
				continue;                                               //return to the loop of login #while (login_mode==NO_MODE)# line 128
			}

			uint8 pass_counter=0;                                                            //counts the entered key of the password from the keypad
			uint8 pass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};            //temporarily hold the entire password that will be entered by the user to be check
			uint8 stored_pass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};    //temporarily hold the entire stored password that is written by the user for the first time
			
			switch(key_pressed)
			{
				// -----------------------------------------------> Admin login 
				
				
				case CHECK_ADMIN_MODE:
				while(login_mode!=ADMIN)                                               //this loop is to repeat the login for admin in case of wrong password
				{
					key_pressed = NOT_PRESSED;                                       //return the variable that holds the pressed key from keypad to its initial value
					LCD_clearscreen();                                              //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
					LCD_vSend_string("Family mode");
					LCD_movecursor(2,1);
					LCD_vSend_string("Enter Pass:");
					_delay_ms(200);                                              //Halt the system for the given time in (ms)
					pass_counter=0;                                             //counts the number of entered characters
					while(pass_counter<PASS_SIZE)
					{
						while (key_pressed == NOT_PRESSED)                    //repeat till the user press any key
						{
							key_pressed = keypad_u8check_press();           //if the user pressed any button in keypad save the value in key_pressed
						}
						pass[pass_counter]=key_pressed;                   //add the entered character to the pass array
						LCD_vSend_char(key_pressed);                     //print the entered character
						_delay_ms(CHARACTER_PREVIEW_TIME);              //Halt the system for the given time in (ms)
						LCD_movecursor(2,12+pass_counter);             //move the cursor of the lcd screen to the previous location
						LCD_vSend_char(PASSWORD_SYMBOL);              // to display (Password sign *)
						_delay_ms(100);                              //Halt the system for the given time in (ms)
						pass_counter++;                             //increase the password counter that count the characters of the pass
						key_pressed = NOT_PRESSED;                 //return the variable that holds the pressed key from keypad to its initial value
					}
					EEPROM_vRead(EEPROM_ADMIN_ADDRESS_one,&stored_pass[0]);            //read the stored pass from the EEPROM
					EEPROM_vRead(EEPROM_ADMIN_ADDRESS_two,&stored_pass[1]);           //read the stored pass from the EEPROM
					EEPROM_vRead(EEPROM_ADMIN_ADDRESS_three,&stored_pass[2]);        //read the stored pass from the EEPROM
					EEPROM_vRead(EEPROM_ADMIN_ADDRESS_four,&stored_pass[3]);        //read the stored pass from the EEPROM

					//------------------------------------------------> compare passwords
					if ((ui8ComparePass(pass,stored_pass,PASS_SIZE)) == TRUE)   //in case of right password
					{
						login_mode = ADMIN;                                               //set the login mode to admin mode
						pass_tries_count=0;                                              //clear the counter of wrong tries
						LCD_clearscreen();                                              //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
						LCD_vSend_string("Right pass");
						LCD_movecursor(2,1);
						LCD_vSend_string("Family mode");
						_delay_ms(500);                                              //Halt the system for the given time in (ms)
						timer0_initializeCTC();                                    //start the timer that counts the session time
						LCD_clearscreen();                                        //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
					}
					else                                                        //in case of wrong password
					{
						pass_tries_count++;                                      //increase the number of wrong tries to block login if it exceeds the allowed tries
						login_mode = NO_MODE;                                   //set the mode as not logged in
						LCD_clearscreen();                                     //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
						LCD_vSend_string("Wrong Pass");
						LCD_movecursor(2,1);
						LCD_vSend_string("Tries left:");
						LCD_vSend_char(TRIES_ALLOWED-pass_tries_count+ASCII_ZERO);//print the number of tries left before block mode to be activated
						_delay_ms(1000);                                         //Halt the system for the given time in (ms)
						LCD_clearscreen();                                      //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
						if (pass_tries_count>=TRIES_ALLOWED)                   //if the condition of the block mode is true
						{
							EEPROM_vWrite(LOGIN_BLOCKED_ADDRESS,TRUE);       //write to the EEPROM TRUE to the the block mode address
							block_mode_flag = TRUE;                         //turn on block mode
							break;                                         //break the loop of admin login #while(login_mode!=ADMIN)# at line 169
						}
					}
				}
				break;                                                   //bREAK SWITCH case
				//---------------------------------------------------->  Guest login
				case  CHECK_GUEST_MODE:
				while(login_mode != GUEST)
				{
					key_pressed = NOT_PRESSED;                                        //return the variable that holds the pressed key from keypad to its initial value
					LCD_clearscreen();                                               //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
					LCD_vSend_string("Guest mode");
					LCD_movecursor(2,1);
					LCD_vSend_string("Enter pass:");
					_delay_ms(200);                                               //Halt the system for the given time in (ms)
					pass_counter=0;                                              //counts the number of entered characters
					while(pass_counter<PASS_SIZE)
					{
						while (key_pressed == NOT_PRESSED)                      //repeat till the user press any key
						{
							key_pressed = keypad_u8check_press();              //if the user pressed any button in keypad save the value in key_pressed
						}
						pass[pass_counter]=key_pressed;                       //add the pressed key to the password string
						LCD_vSend_char(key_pressed);                         //print the entered character
						_delay_ms(CHARACTER_PREVIEW_TIME);                  //Halt the system for the given time in (ms)
						LCD_movecursor(2,12+pass_counter);                 //return the cursor to the location of the previous character to replace it with the password sign
						LCD_vSend_char(PASSWORD_SYMBOL);                  // to display (Password sign *)
						_delay_ms(100);                                  //Halt the system for the given time in (ms)
						pass_counter++;                                 //increase the password counter that count the characters of the pass
						key_pressed = NOT_PRESSED;                     //return the variable that holds the pressed key from keypad to its initial value
					}
					EEPROM_vRead(EEPROM_GUEST_ADDRESS_one,&stored_pass[0]);					//read the stored pass from the EEPROM
					EEPROM_vRead(EEPROM_GUEST_ADDRESS_two,&stored_pass[1]);                //read the stored pass from the EEPROM
					EEPROM_vRead(EEPROM_GUEST_ADDRESS_three,&stored_pass[2]);             //read the stored pass from the EEPROM
					EEPROM_vRead(EEPROM_GUEST_ADDRESS_four,&stored_pass[3]);             //read the stored pass from the EEPROM

					//------------------------------------------->      compare passwords
					if (ui8ComparePass(pass,stored_pass,PASS_SIZE)==TRUE)             //in case of right password
					{
						login_mode = GUEST;
						pass_tries_count=0;                                         //clear the counter of wrong tries
						LCD_clearscreen();                                         //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
						LCD_vSend_string("Right pass");
						LCD_movecursor(2,1);
						LCD_vSend_string("Guest mode");
						_delay_ms(500);                                          //Halt the system for the given time in (ms)
						timer0_initializeCTC();                                //start the counter of the session
						LCD_clearscreen();                                    //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
					}
					else                                                            //in case of wrong password
					{
						pass_tries_count++;                                         //increase the number of wrong tries to block login if it exceeds the allowed tries
						login_mode = NO_MODE;                                      //set the mode as not logged in
						LCD_clearscreen();                                        //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
						LCD_vSend_string("Wrong pass");
						LCD_movecursor(2,1);
						LCD_vSend_string("Tries left:");
						LCD_vSend_char(TRIES_ALLOWED-pass_tries_count+ASCII_ZERO);               //print the number of tries left before block mode to be activated
						_delay_ms(1000);                                                        //Halt the system for the given time in (ms)
						LCD_clearscreen();                                                     //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
						if (pass_tries_count>=TRIES_ALLOWED)                                  //if the condition of the block mode is true
						{
							EEPROM_vWrite(LOGIN_BLOCKED_ADDRESS,TRUE);                      //write to the EEPROM TRUE to the the block mode address
							block_mode_flag = TRUE;                                        //turn on block mode
							break;                                                        //breaks the loop of insert guest password #while(login_mode != GUEST)# line 228
						}
					}
				}// ---------------------> end of loop of guest login
				break;
			}//end of switch
			
		}
		
		
		
		uint8 show_menu = MAIN_MENU; //-------------------------------------------------> set the show menu to the main menu either in admin or guest mode 
		
		
		
		
		while(timeout_flag!=TRUE)                                            //Show the menu in case of the time is not out
		{
			key_pressed = NOT_PRESSED;                                     //Set the key pressed by the user to its default value
			switch (show_menu)
			{
				case MAIN_MENU:
				do
				{
					//  print main Menu 
					LCD_clearscreen();
					LCD_vSend_string("1:Room1 2:Room2");
					LCD_movecursor(2,1);
					if(login_mode==ADMIN)                                //check login mode
					{
						LCD_vSend_string("3:TV 4:More ");            //this menu options only printed if the logged in user is an admin
					}
					else if(login_mode==GUEST)                         //check login mode
					{
						LCD_vSend_string("3:TV 4:Fan");            //this menu options only printed if the logged in user is a guest
					}
					
					
					
					key_pressed = u8GetKeyPressed(login_mode);                           //wait for the user till key is pressed or the time is out
					_delay_ms(100);                                                     //to avoid the duplication of the pressed key
					
					if (key_pressed == SELECT_ROOM1 )                                  //If key pressed is 1
					{
						show_menu = ROOM1_MENU;                                       //Set the next menu to be shown to room1 menu
					}
					else if (key_pressed == SELECT_ROOM2)                            //If key pressed is 2
					{
						show_menu = ROOM2_MENU;                                     //Set the next menu to be shown to room2 menu
					}
					else if (key_pressed == SELECT_TV)                          //If key pressed is 3
					{
						show_menu = TV_MENU;                                   //Set the next menu to be shown to room3 menu
					}
					else if (key_pressed == SELECT_FAN && login_mode == GUEST) //If key pressed is 4 and the logged in user is guest
					{
						show_menu = FAN_MENU;                                 //Set the next menu to be shown to room4 menu
					}
					else if (key_pressed == ADMIN_MORE_OPTION && login_mode == ADMIN)//If key pressed is 4 and the logged in user is admin
					{
						show_menu = MORE_MENU;                                      //Set the next menu to be shown to more menu
					}
					else if(key_pressed != NOT_PRESSED)                            //show wrong input message if the user pressed wrong key
					{
						LCD_clearscreen();                                        //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
						LCD_vSend_string("Wrong input");                         //print error message
						_delay_ms(500);                                         //Halt the system for the given time in (ms)
					}
				} while ( ((key_pressed < '1') || (key_pressed > '4') ) && (timeout_flag == FALSE) );
				
				break;
				
				case MORE_MENU:
				do
				{
					// print more Menu 
					LCD_clearscreen();                //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
					LCD_vSend_string("1:Fan   2:Garage");
					LCD_movecursor(2,1);
					LCD_vSend_string("3:Air Cond.4:RET");
					
					
					key_pressed = u8GetKeyPressed(login_mode);                      //wait for the user till key is pressed or the time is out
					_delay_ms(100);                                                //to avoid the duplication of the pressed key
					
					if (key_pressed == SELECT_FAN_ADMIN)                       //If key pressed is 1
					{
						show_menu = FAN_MENU;                                //Set the next menu to be shown to room4 menu
					}
					else if (key_pressed == SELECT_GARAGE)                       //If key pressed is 2
					{
						show_menu = GARAGE_MENU;                               //Set the next menu to be shown to TV menu
					}
					else if (key_pressed == SELECT_AIR_CONDITIONING)      //If key pressed is 3
					{ 
						show_menu = AIRCONDITIONING_MENU;               //Set the next menu to be shown to Air conditioning menu
					}
					else if (key_pressed == ADMIN_RET_OPTION)          //If key pressed is 4 (RET)
					{
						show_menu = MAIN_MENU;                       //Set the next menu to be shown to main menu
					}
					else if(key_pressed != NOT_PRESSED)            //show wrong input message if the user pressed wrong key
					{
						LCD_clearscreen();                       //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
						LCD_vSend_string("Wrong input");        //print error message
						_delay_ms(500);                        //Halt the system for the given time in (ms)
					}
				} while (( (key_pressed < '1') || (key_pressed > '4') ) && (timeout_flag == FALSE));           
				
				break;                                                                                       
				
				case AIRCONDITIONING_MENU:
				do
				{
					// print more Menu 
					LCD_clearscreen();                      //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
					LCD_vSend_string("1:Set temperature ");
					LCD_movecursor(2,1);
					LCD_vSend_string("2:Control  0:RET");
					
					
					key_pressed = u8GetKeyPressed(login_mode);                                     //wait for the user till key is pressed or the time is out
					_delay_ms(100);                                                               //to avoid the duplication of the pressed key
					
					if (key_pressed == SELECT_SET_TEMPERATURE)                                  //If key pressed is 1
					{
						show_menu = TEMPERATURE_MENU;                                         //Set the next menu to be shown to set temperature menu
					}
					else if (key_pressed == SELECT_AIR_COND_CTRL)                           //If key pressed is 2
					{
						show_menu = AIRCOND_CTRL_MENU;                                    //Set the next menu to be shown to air conditioning control menu
					} 
					else if (key_pressed == SELECT_AIR_COND_RET)                        //If key pressed is 0
					{
						show_menu = MORE_MENU;                                        //Set the next menu to be shown to more menu
					}
					else if(key_pressed != NOT_PRESSED)                             //show wrong input message if the user pressed wrong key
					{
						LCD_clearscreen();                                        //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
						LCD_vSend_string("Wrong input");                         //print error message
						_delay_ms(500);                                         //Halt the system for the given time in (ms)
					}
				} while (( (key_pressed < '0') || (key_pressed > '2') ) && (timeout_flag == FALSE));
				break;
				
				case ROOM1_MENU:
				vMenuOption(ROOM1_MENU,login_mode);													//call the function that show the menu of room 1
				show_menu = MAIN_MENU;                                                             //Set the next menu to be shown to main menu
				break;                                                                            //End of room1 menu case
				
				case ROOM2_MENU:
				vMenuOption(ROOM2_MENU,login_mode);                                             //call the function that show the menu of room 2
				show_menu = MAIN_MENU;                                                         //Set the next menu to be shown to main menu
				break;                                                                        //End of room2 menu case
				
				case TV_MENU:
				vMenuOption(TV_MENU,login_mode);                                         //call the function that show the menu of tv
				show_menu = MAIN_MENU;                                                     //Set the next menu to be shown to main menu
				break;                                                                    //End of room3 menu case
				
				case FAN_MENU:
				vMenuOption(FAN_MENU,login_mode);                                     //call the function that show the menu of fan
				if (login_mode == GUEST)                                               //in case of guest is logged in
				{
					show_menu = MAIN_MENU;                                            //Set the next menu to be shown to main menu
				}
				else                                                                 //in case of admin is logged in
				{
					show_menu = MORE_MENU;                                          //Set the next menu to be shown to more menu
				}
				break;                                                             //End of FAN menu case
				
				case GARAGE_MENU:
				vMenuOption(GARAGE_MENU,login_mode);                                 //call the function that show the menu of garage
				show_menu = MORE_MENU;                                          //Set the next menu to be shown to more menu
				break;                                                         //End of garage menu case
				
				case AIRCOND_CTRL_MENU:
				vMenuOption(AIRCOND_CTRL_MENU,login_mode);                   //call the function that show the menu of Air conditioning control
				show_menu = AIRCONDITIONING_MENU;                           //Set the next menu to be shown to air conditioning menu
				break;                                                     //End of air conditioning control menu case
				
				case TEMPERATURE_MENU:
				temperature = 0;                                           //clear the value of temperature
				while (temperature==0 && timeout_flag == FALSE)           //start the loop that asks for the temperature from the user in case of the time is not out
				{
					key_pressed = NOT_PRESSED;                          //set the key pressed to the default value
					LCD_clearscreen();                                 //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
					LCD_vSend_string("Set temp.:__ ");                //print the format of inserting temperature
					LCD_vSend_char(DEGREES_SYMBOL);                  // print the symbol of degree
					LCD_vSend_char('C');                            // print the C character
					LCD_movecursor(1,11);                          //move the cursor to the place to write the entered temperature
					_delay_ms(200);                               //Halt the system for the given time in (ms)
		
		
					key_pressed = u8GetKeyPressed(login_mode);                        //wait for the user till key is pressed or the time is out
					_delay_ms(250);                                                  //to avoid the duplication of the pressed key

					if (timeout_flag == TRUE)                                      //in case of the time is out before the user press a key
					{
						break;                                                    //break the loop that ask for temperature
					}
					if (key_pressed <'0' || key_pressed >'9')                   //show wrong input message if the user entered non numeric value
					{
						LCD_clearscreen();                                    //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
						LCD_vSend_string("Wrong input");                     //print error message
						_delay_ms(500);                                     //Halt the system for the given time in (ms)
						continue;                                          //return to #while (temperature==0)# line 672
					}
					else                                                 //if the value is valid
					{
						LCD_vSend_char(key_pressed);                            //print the value on the lcd
						temp_tens = key_pressed-ASCII_ZERO;                    //save the entered value
						key_pressed = NOT_PRESSED;                            //set the key pressed to the default value
					}
		
		
					key_pressed = u8GetKeyPressed(login_mode);               //wait for the user till key is pressed or the time is out
					_delay_ms(250);                                         //to avoid the duplication of the pressed key
					
					if (timeout_flag == TRUE)                              //if the user session is timeout
					{
						break;                                            //break the loop that ask for temperature
					}
					if ((key_pressed <'0' || key_pressed >'9'))          //show wrong input message if the user entered non numeric value
					{
						LCD_clearscreen();                              //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
						LCD_vSend_string("Wrong input");               //print error message
						_delay_ms(500);                               //Halt the system for the given time in (ms)
						continue;                                    //repeat the loop that ask for the temperature
					}  
					else                                            //if the value is valid
					{
						LCD_vSend_char(key_pressed);                       //print the value on the lcd
						temp_ones = key_pressed-ASCII_ZERO;               //save the entered value
						key_pressed = NOT_PRESSED;                       //set the key pressed to the default value
					}
					temperature = temp_tens*10 + temp_ones;                         //set the value of the temperature from the given separated values
					SPI_ui8TransmitRecive(SET_TEMPERATURE);                        //Send the code of set temperature
					_delay_ms(200);                                               //Halt the system to prevent write collision
					SPI_ui8TransmitRecive(temperature);                          //send the entered temperature
					LCD_clearscreen();                                          //remove all previously printed characters on the LCD and move the cursor to the first column of the first row
					LCD_vSend_string("Temperature Sent");                      //show the message
					_delay_ms(500);                                           //Halt the system for the given time in (ms)
				}
				show_menu = AIRCONDITIONING_MENU;                           //Set the next menu to be shown to air conditioning menu
				break;
			}
		}
	}
}







ISR(TIMER0_COMP_vect)
{
	session_counter++;                                                       
}