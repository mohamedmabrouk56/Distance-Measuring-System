################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../gpio.c \
../icu.c \
../icu_Cfg.c \
../lcd.c \
../main.c \
../timer.c \
../timer_Cfg.c \
../ultrasonic.c 

OBJS += \
./gpio.o \
./icu.o \
./icu_Cfg.o \
./lcd.o \
./main.o \
./timer.o \
./timer_Cfg.o \
./ultrasonic.o 

C_DEPS += \
./gpio.d \
./icu.d \
./icu_Cfg.d \
./lcd.d \
./main.d \
./timer.d \
./timer_Cfg.d \
./ultrasonic.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


