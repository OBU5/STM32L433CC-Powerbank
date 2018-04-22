################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ADC.c \
../src/GPIO.c \
../src/TMR.c \
../src/cell.c \
../src/config.c \
../src/events.c \
../src/lcd.c \
../src/main.c \
../src/power.c \
../src/stm32l4xx_hal_msp.c \
../src/stm32l4xx_it.c 

OBJS += \
./src/ADC.o \
./src/GPIO.o \
./src/TMR.o \
./src/cell.o \
./src/config.o \
./src/events.o \
./src/lcd.o \
./src/main.o \
./src/power.o \
./src/stm32l4xx_hal_msp.o \
./src/stm32l4xx_it.o 

C_DEPS += \
./src/ADC.d \
./src/GPIO.d \
./src/TMR.d \
./src/cell.d \
./src/config.d \
./src/events.d \
./src/lcd.d \
./src/main.d \
./src/power.d \
./src/stm32l4xx_hal_msp.d \
./src/stm32l4xx_it.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32L433xx -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/l4xx" -I"../system/include/stm32l4xx" -I"../system/include/cmsis/device" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


