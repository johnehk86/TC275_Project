################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/App/MotorControl/MotorControl.c 

OBJS += \
./Src/App/MotorControl/MotorControl.o 

COMPILED_SRCS += \
./Src/App/MotorControl/MotorControl.src 

C_DEPS += \
./Src/App/MotorControl/MotorControl.d 


# Each subdirectory must supply rules for building sources it contributes
Src/App/MotorControl/%.src: ../Src/App/MotorControl/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc27xd "-fD:/00_TEST/01_WorkPlace/TC275_Project/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Src/App/MotorControl/%.o: ./Src/App/MotorControl/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


