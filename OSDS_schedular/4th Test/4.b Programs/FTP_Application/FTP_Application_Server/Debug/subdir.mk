################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Dir.c \
../FTP_App_Server.c \
../FTP_Functions.c 

OBJS += \
./Dir.o \
./FTP_App_Server.o \
./FTP_Functions.o 

C_DEPS += \
./Dir.d \
./FTP_App_Server.d \
./FTP_Functions.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


