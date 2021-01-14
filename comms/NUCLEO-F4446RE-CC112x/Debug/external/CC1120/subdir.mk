################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../external/CC1120/cc1120.c 

OBJS += \
./external/CC1120/cc1120.o 

C_DEPS += \
./external/CC1120/cc1120.d 


# Each subdirectory must supply rules for building sources it contributes
external/CC1120/cc1120.o: ../external/CC1120/cc1120.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I/Users/sean/STM32CubeIDE/workspace_1.4.0/NUCLEO-F4446RE-CC1120/external/includes -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"external/CC1120/cc1120.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

