################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Drv/DrvAdc.c \
../Src/Drv/DrvAsc.c \
../Src/Drv/DrvDio.c \
../Src/Drv/DrvGtm.c \
../Src/Drv/DrvStm.c \
../Src/Drv/DrvSys.c \
../Src/Drv/DrvWatchdog.c 

OBJS += \
./Src/Drv/DrvAdc.o \
./Src/Drv/DrvAsc.o \
./Src/Drv/DrvDio.o \
./Src/Drv/DrvGtm.o \
./Src/Drv/DrvStm.o \
./Src/Drv/DrvSys.o \
./Src/Drv/DrvWatchdog.o 

COMPILED_SRCS += \
./Src/Drv/DrvAdc.src \
./Src/Drv/DrvAsc.src \
./Src/Drv/DrvDio.src \
./Src/Drv/DrvGtm.src \
./Src/Drv/DrvStm.src \
./Src/Drv/DrvSys.src \
./Src/Drv/DrvWatchdog.src 

C_DEPS += \
./Src/Drv/DrvAdc.d \
./Src/Drv/DrvAsc.d \
./Src/Drv/DrvDio.d \
./Src/Drv/DrvGtm.d \
./Src/Drv/DrvStm.d \
./Src/Drv/DrvSys.d \
./Src/Drv/DrvWatchdog.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Drv/%.src: ../Src/Drv/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc27xd "-fD:/00_TEST/01_WorkPlace/TC275_Project/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Src/Drv/%.o: ./Src/Drv/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


