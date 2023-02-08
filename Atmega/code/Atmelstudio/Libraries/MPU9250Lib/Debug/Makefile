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
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../Include \
../src


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../src/arduino_mpu9250_clk.c \
../src/arduino_mpu9250_i2c.cpp \
../src/arduino_mpu9250_log.cpp \
../src/inv_mpu.c \
../src/inv_mpu_dmp_motion_driver.c \
../src/SparkFunMPU9250-DMP.cpp


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
src/arduino_mpu9250_clk.o \
src/arduino_mpu9250_i2c.o \
src/arduino_mpu9250_log.o \
src/inv_mpu.o \
src/inv_mpu_dmp_motion_driver.o \
src/SparkFunMPU9250-DMP.o

OBJS_AS_ARGS +=  \
src/arduino_mpu9250_clk.o \
src/arduino_mpu9250_i2c.o \
src/arduino_mpu9250_log.o \
src/inv_mpu.o \
src/inv_mpu_dmp_motion_driver.o \
src/SparkFunMPU9250-DMP.o

C_DEPS +=  \
src/arduino_mpu9250_clk.d \
src/arduino_mpu9250_i2c.d \
src/arduino_mpu9250_log.d \
src/inv_mpu.d \
src/inv_mpu_dmp_motion_driver.d \
src/SparkFunMPU9250-DMP.d

C_DEPS_AS_ARGS +=  \
src/arduino_mpu9250_clk.d \
src/arduino_mpu9250_i2c.d \
src/arduino_mpu9250_log.d \
src/inv_mpu.d \
src/inv_mpu_dmp_motion_driver.d \
src/SparkFunMPU9250-DMP.d

OUTPUT_FILE_PATH +=libMPU9250Lib.a

OUTPUT_FILE_PATH_AS_ARGS +=libMPU9250Lib.a

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+=  \
C:/Data/infotek/svn/2012/gat/Projects/Atmega/code/Atmelstudio/Libraries/ArduinoCore/Debug/libArduinoCore.a

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler













src/%.o: ../src/%.c
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\Atmel\ATmega_DFP\1.2.132\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega328p -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\Atmel\ATmega_DFP\1.2.132\gcc\dev\atmega328p" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/%.o: ../src/%.cpp
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\Atmel\ATmega_DFP\1.2.132\include" -I"../../ArduinoCore/include/core" -I"../../ArduinoCore/include/variants/standard" -I"../Include" -I"../src" -I"../util"  -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega328p -B "C:\Program Files (x86)\Atmel\Studio\7.0\Packs\Atmel\ATmega_DFP\1.2.132\gcc\dev\atmega328p" -c -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
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
	@echo Invoking: AVR8/GNU Archiver : 4.9.2
	$(QUOTE)C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-ar.exe$(QUOTE) -r  -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) 
	@echo Finished building target: $@
	
	




# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "libMPU9250Lib.elf" "libMPU9250Lib.a" "libMPU9250Lib.hex" "libMPU9250Lib.lss" "libMPU9250Lib.eep" "libMPU9250Lib.map" "libMPU9250Lib.srec" "libMPU9250Lib.usersignatures"
	