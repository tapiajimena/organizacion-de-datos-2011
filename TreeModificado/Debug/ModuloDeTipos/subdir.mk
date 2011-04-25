################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ModuloDeTipos/Dato.cpp \
../ModuloDeTipos/DatoElementoNodo.cpp \
../ModuloDeTipos/FrontCodedString.cpp 

OBJS += \
./ModuloDeTipos/Dato.o \
./ModuloDeTipos/DatoElementoNodo.o \
./ModuloDeTipos/FrontCodedString.o 

CPP_DEPS += \
./ModuloDeTipos/Dato.d \
./ModuloDeTipos/DatoElementoNodo.d \
./ModuloDeTipos/FrontCodedString.d 


# Each subdirectory must supply rules for building sources it contributes
ModuloDeTipos/%.o: ../ModuloDeTipos/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


