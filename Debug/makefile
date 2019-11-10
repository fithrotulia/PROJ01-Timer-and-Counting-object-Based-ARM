################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
UTS_TamiyaCounter.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
UTS_TamiyaCounter.list \


# All Target
all: UTS_TamiyaCounter.elf secondary-outputs

# Tool invocations
UTS_TamiyaCounter.elf: $(OBJS) $(USER_OBJS) D:\project\KULIAH\5\Sistem\ Embedded\UTS_TamiyaCounter\STM32F103C8TX_FLASH.ld
	arm-none-eabi-gcc -o "UTS_TamiyaCounter.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\project\KULIAH\5\Sistem Embedded\UTS_TamiyaCounter\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="UTS_TamiyaCounter.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

UTS_TamiyaCounter.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "UTS_TamiyaCounter.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
