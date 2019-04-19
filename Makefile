# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#	2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------

######################################
# target
######################################
TARGET = bemf


######################################
# building variables
######################################
# debug build?
DEBUG = 0
# optimization
OPT = -Os


#######################################
# paths
#######################################
# source path
SOURCES_DIR =  \
pac55xx_sdk/boot_gcc \
pac55xx_sdk/driver \
pac55xx_sdk/peripheral \

# firmware library path
PERIFLIB_PATH =

# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES =  \
pac55xx_sdk/boot_gcc/startup_pac55xx_gcc.c \
pac55xx_sdk/driver/pac5xxx_driver_adc.c \
pac55xx_sdk/driver/pac5xxx_driver_gpio.c \
pac55xx_sdk/driver/pac5xxx_driver_socbridge.c \
pac55xx_sdk/driver/pac5xxx_driver_system.c \
pac55xx_sdk/driver/pac5xxx_driver_tile_socbridge.c \
pac55xx_sdk/driver/pac5xxx_driver_timer.c \
pac55xx_sdk/driver/pac5xxx_driver_uart.c \
src/beep_notes.c \
src/bldc_common.c \
src/diag_tunes.c \
src/fix16.c \
src/init.c \
src/isr_adc.c \
src/isr_Stubs.c \
src/isr_TimerA.c \
src/isr_TimerB.c \
src/isr_TimerC.c \
src/isr_TimerD.c \
src/main.c \
src/peripheral_init.c \
src/pid.c \
src/SineWaveLUT.c \
src/sl_functions.c \
src/sl_state_machine.c \
src/uart.c


# ASM sources
ASM_SOURCES =


######################################
# firmware library
######################################
PERIFLIB_SOURCES =


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
AR = $(PREFIX)ar
SZ = $(PREFIX)size
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S


#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS =


# AS includes
AS_INCLUDES =

# C includes
C_INCLUDES =  \
-Iinc \
-Ipac55xx_sdk/peripheral \
-Ipac55xx_sdk \
-Ipac55xx_sdk/driver \
-Ipac55xx_sdk/cmsis_core \

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections -std=gnu99
# CFLAGS += -Wfloat-conversion
CFLAGS += -fsingle-precision-constant
# CFLAGS += -ffast-math
CFLAGS += -ffinite-math-only
CFLAGS += -fno-trapping-math
CFLAGS += -fno-signaling-nans
CFLAGS += -fno-rounding-math
CFLAGS += -fno-signed-zeros
CFLAGS += -fno-math-errno

CFLAGS += -fmessage-length=0
CFLAGS += -fsigned-char

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = pac55xx.ld

# libraries
LIBS = -lc -lm -lnosys
LIBDIR =
LDFLAGS = $(MCU) -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections -u _printf_float

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@

$(BUILD_DIR):
	mkdir $@

#######################################
# clean up
#######################################
clean:
	-rm -fR .dep $(BUILD_DIR)

#######################################
# dependencies
#######################################
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

# *** EOF ***
