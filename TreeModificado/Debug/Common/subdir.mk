################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Common/FileManager.cpp \
../Common/Record.cpp \
../Common/ServiceClass.cpp 

OBJS += \
./Common/FileManager.o \
./Common/Record.o \
./Common/ServiceClass.o 

CPP_DEPS += \
./Common/FileManager.d \
./Common/Record.d \
./Common/ServiceClass.d 


# Each subdirectory must supply rules for building sources it contributes
Common/%.o: ../Common/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


