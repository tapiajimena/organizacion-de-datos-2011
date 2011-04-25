################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BPlusTree.cpp \
../src/InternalNode.cpp \
../src/LeafNode.cpp \
../src/Node.cpp \
../src/NodeFactory.cpp \
../src/Tree.cpp \
../src/main.cpp \
../src/tests.cpp 

OBJS += \
./src/BPlusTree.o \
./src/InternalNode.o \
./src/LeafNode.o \
./src/Node.o \
./src/NodeFactory.o \
./src/Tree.o \
./src/main.o \
./src/tests.o 

CPP_DEPS += \
./src/BPlusTree.d \
./src/InternalNode.d \
./src/LeafNode.d \
./src/Node.d \
./src/NodeFactory.d \
./src/Tree.d \
./src/main.d \
./src/tests.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


