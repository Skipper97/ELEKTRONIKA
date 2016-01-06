################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Fat.c" \
"../Sources/FileList.c" \
"../Sources/SD.c" \
"../Sources/SPI.c" \
"../Sources/SSD1289.c" \
"../Sources/ads7843.c" \
"../Sources/console.c" \
"../Sources/fonts.c" \
"../Sources/heap.c" \
"../Sources/init.c" \
"../Sources/interrupt.c" \
"../Sources/main.c" \
"../Sources/sci.c" \
"../Sources/tempo.c" \
"../Sources/text.c" \
"../Sources/tools.c" \

C_SRCS += \
../Sources/Fat.c \
../Sources/FileList.c \
../Sources/SD.c \
../Sources/SPI.c \
../Sources/SSD1289.c \
../Sources/ads7843.c \
../Sources/console.c \
../Sources/fonts.c \
../Sources/heap.c \
../Sources/init.c \
../Sources/interrupt.c \
../Sources/main.c \
../Sources/sci.c \
../Sources/tempo.c \
../Sources/text.c \
../Sources/tools.c \

OBJS += \
./Sources/Fat_c.obj \
./Sources/FileList_c.obj \
./Sources/SD_c.obj \
./Sources/SPI_c.obj \
./Sources/SSD1289_c.obj \
./Sources/ads7843_c.obj \
./Sources/console_c.obj \
./Sources/fonts_c.obj \
./Sources/heap_c.obj \
./Sources/init_c.obj \
./Sources/interrupt_c.obj \
./Sources/main_c.obj \
./Sources/sci_c.obj \
./Sources/tempo_c.obj \
./Sources/text_c.obj \
./Sources/tools_c.obj \

OBJS_QUOTED += \
"./Sources/Fat_c.obj" \
"./Sources/FileList_c.obj" \
"./Sources/SD_c.obj" \
"./Sources/SPI_c.obj" \
"./Sources/SSD1289_c.obj" \
"./Sources/ads7843_c.obj" \
"./Sources/console_c.obj" \
"./Sources/fonts_c.obj" \
"./Sources/heap_c.obj" \
"./Sources/init_c.obj" \
"./Sources/interrupt_c.obj" \
"./Sources/main_c.obj" \
"./Sources/sci_c.obj" \
"./Sources/tempo_c.obj" \
"./Sources/text_c.obj" \
"./Sources/tools_c.obj" \

C_DEPS += \
./Sources/Fat_c.d \
./Sources/FileList_c.d \
./Sources/SD_c.d \
./Sources/SPI_c.d \
./Sources/SSD1289_c.d \
./Sources/ads7843_c.d \
./Sources/console_c.d \
./Sources/fonts_c.d \
./Sources/heap_c.d \
./Sources/init_c.d \
./Sources/interrupt_c.d \
./Sources/main_c.d \
./Sources/sci_c.d \
./Sources/tempo_c.d \
./Sources/text_c.d \
./Sources/tools_c.d \

C_DEPS_QUOTED += \
"./Sources/Fat_c.d" \
"./Sources/FileList_c.d" \
"./Sources/SD_c.d" \
"./Sources/SPI_c.d" \
"./Sources/SSD1289_c.d" \
"./Sources/ads7843_c.d" \
"./Sources/console_c.d" \
"./Sources/fonts_c.d" \
"./Sources/heap_c.d" \
"./Sources/init_c.d" \
"./Sources/interrupt_c.d" \
"./Sources/main_c.d" \
"./Sources/sci_c.d" \
"./Sources/tempo_c.d" \
"./Sources/text_c.d" \
"./Sources/tools_c.d" \

OBJS_OS_FORMAT += \
./Sources/Fat_c.obj \
./Sources/FileList_c.obj \
./Sources/SD_c.obj \
./Sources/SPI_c.obj \
./Sources/SSD1289_c.obj \
./Sources/ads7843_c.obj \
./Sources/console_c.obj \
./Sources/fonts_c.obj \
./Sources/heap_c.obj \
./Sources/init_c.obj \
./Sources/interrupt_c.obj \
./Sources/main_c.obj \
./Sources/sci_c.obj \
./Sources/tempo_c.obj \
./Sources/text_c.obj \
./Sources/tools_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/Fat_c.obj: ../Sources/Fat.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/Fat.args" -ObjN="Sources/Fat_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/FileList_c.obj: ../Sources/FileList.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/FileList.args" -ObjN="Sources/FileList_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/SD_c.obj: ../Sources/SD.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/SD.args" -ObjN="Sources/SD_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/SPI_c.obj: ../Sources/SPI.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/SPI.args" -ObjN="Sources/SPI_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/SSD1289_c.obj: ../Sources/SSD1289.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/SSD1289.args" -ObjN="Sources/SSD1289_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/ads7843_c.obj: ../Sources/ads7843.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/ads7843.args" -ObjN="Sources/ads7843_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/console_c.obj: ../Sources/console.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/console.args" -ObjN="Sources/console_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/fonts_c.obj: ../Sources/fonts.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/fonts.args" -ObjN="Sources/fonts_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/heap_c.obj: ../Sources/heap.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/heap.args" -ObjN="Sources/heap_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/init_c.obj: ../Sources/init.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/init.args" -ObjN="Sources/init_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/interrupt_c.obj: ../Sources/interrupt.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/interrupt.args" -ObjN="Sources/interrupt_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/main.args" -ObjN="Sources/main_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/sci_c.obj: ../Sources/sci.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/sci.args" -ObjN="Sources/sci_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/tempo_c.obj: ../Sources/tempo.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/tempo.args" -ObjN="Sources/tempo_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/text_c.obj: ../Sources/text.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/text.args" -ObjN="Sources/text_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/tools_c.obj: ../Sources/tools.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/tools.args" -ObjN="Sources/tools_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '


