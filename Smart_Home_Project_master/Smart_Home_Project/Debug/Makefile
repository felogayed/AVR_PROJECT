################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../APP \
../HAL \
../MCAL \
../LIB


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../APP/menu.c \
../APP/Smart_Home_Project_Master.c \
../HAL/HEEPROM_program.c \
../HAL/keypad_driver.c \
../HAL/LCD.c \
../HAL/LED.c \
../MCAL/DIO.c \
../MCAL/MTWI_program.c \
../MCAL/SPI.c \
../MCAL/timer_driver.c \
../MCAL/UART_program.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
APP/menu.o \
APP/Smart_Home_Project_Master.o \
HAL/HEEPROM_program.o \
HAL/keypad_driver.o \
HAL/LCD.o \
HAL/LED.o \
MCAL/DIO.o \
MCAL/MTWI_program.o \
MCAL/SPI.o \
MCAL/timer_driver.o \
MCAL/UART_program.o


OBJS_AS_ARGS +=  \
APP/menu.o \
APP/Smart_Home_Project_Master.o \
HAL/HEEPROM_program.o \
HAL/keypad_driver.o \
HAL/LCD.o \
HAL/LED.o \
MCAL/DIO.o \
MCAL/MTWI_program.o \
MCAL/SPI.o \
MCAL/timer_driver.o \
MCAL/UART_program.o


C_DEPS +=  \
APP/menu.d \
APP/Smart_Home_Project_Master.d \
HAL/HEEPROM_program.d \
HAL/keypad_driver.d \
HAL/LCD.d \
HAL/LED.d \
MCAL/DIO.d \
MCAL/MTWI_program.d \
MCAL/SPI.d \
MCAL/timer_driver.d \
MCAL/UART_program.d


C_DEPS_AS_ARGS +=  \
APP/menu.d \
APP/Smart_Home_Project_Master.d \
HAL/HEEPROM_program.d \
HAL/keypad_driver.d \
HAL/LCD.d \
HAL/LED.d \
MCAL/DIO.d \
MCAL/MTWI_program.d \
MCAL/SPI.d \
MCAL/timer_driver.d \
MCAL/UART_program.d


OUTPUT_FILE_PATH +=Smart_Home_Project_Master.elf

OUTPUT_FILE_PATH_AS_ARGS +=Smart_Home_Project_Master.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

# AVR32/GNU C Compiler























APP/%.o: ../APP/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : (AVR_8_bit_GNU_Toolchain_3.4.1_830) 4.6.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -funsigned-char -funsigned-bitfields -O1 -fpack-struct -fshort-enums -g2 -Wall -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"  -mmcu=atmega32   -o"$@" "$<" 
	@echo Finished building: $<

HAL/%.o: ../HAL/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : (AVR_8_bit_GNU_Toolchain_3.4.1_830) 4.6.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -funsigned-char -funsigned-bitfields -O1 -fpack-struct -fshort-enums -g2 -Wall -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"  -mmcu=atmega32   -o"$@" "$<" 
	@echo Finished building: $<

MCAL/%.o: ../MCAL/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : (AVR_8_bit_GNU_Toolchain_3.4.1_830) 4.6.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -funsigned-char -funsigned-bitfields -O1 -fpack-struct -fshort-enums -g2 -Wall -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"  -mmcu=atmega32   -o"$@" "$<" 
	@echo Finished building: $<



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : (AVR_8_bit_GNU_Toolchain_3.4.1_830) 4.6.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="Smart_Home_Project_Master.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group  -mmcu=atmega32  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "Smart_Home_Project_Master.elf" "Smart_Home_Project_Master.hex"
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "Smart_Home_Project_Master.elf" "Smart_Home_Project_Master.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objdump.exe" -h -S "Smart_Home_Project_Master.elf" > "Smart_Home_Project_Master.lss"
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature  "Smart_Home_Project_Master.elf" "Smart_Home_Project_Master.srec"
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-size.exe" "Smart_Home_Project_Master.elf"
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS)$(C_DEPS_AS_ARGS) $(EXECUTABLES) 
	rm -rf "Smart_Home_Project_Master.elf" "Smart_Home_Project_Master.a" "Smart_Home_Project_Master.hex" "Smart_Home_Project_Master.lss" "Smart_Home_Project_Master.eep" "Smart_Home_Project_Master.map" "Smart_Home_Project_Master.srec"
	