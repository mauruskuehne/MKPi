# can this be set globally in the xcodeproj file?

CPPC=/usr/local/bin/arm-none-eabi-g++
ASMC=/usr/local/bin/arm-none-eabi-as
LINKER=/usr/local/bin/arm-none-eabi-g++
OBJCOPY=/usr/local/bin/arm-none-eabi-objcopy
OBJDUMP=/usr/local/bin/arm-none-eabi-objdump

SOURCE=../source
BUILD=../build

#sources to compile:
CPPSRC=$(wildcard $(SOURCE)/*.cpp)
ASMSRC=$(wildcard $(SOURCE)/*.s)

#linkscript
LINKSCRIPT=kernel.ld

#generated objects:
CPP_OBJECTS=$(addprefix $(BUILD)/,$(notdir $(CPPSRC:.cpp=.o)))
ASM_OBJECTS=$(addprefix $(BUILD)/,$(notdir $(ASMSRC:.s=.o)))

GIT_VERSION := $(shell git describe --abbrev=4 --dirty --always --tags)

#external libraries

EXTERNAL_LIB_DIR=-L../external/newlib/arm-none-eabi/armv6-m/newlib
EXTERNAL_INC_DIR=-I

LIBS=-lgcc -lc -lgcc

CPPCARGS=-std=c++14 -ffreestanding -nostdlib -fno-builtin -fno-rtti -fno-exceptions -nostartfiles -Wall  $(LIBS) -DVERSION=\"$(GIT_VERSION)\"

###### TARGETS

all: IMAGE

$(BUILD)/%.o: $(SOURCE)/%.cpp
	$(CPPC) -v -c $(CPPCARGS)  -o $@ $^

$(BUILD)/%.o: $(SOURCE)/%.s
	$(ASMC) -o $@ $^

CPP: $(CPPSRC)
	$(CPPC) -c $(CCPCARGS) $(CPPSRC) -o $(CPP_OBJECTS)

ASM: $(ASMSRC)
	$(ASMC) $(ASMSRC) -o $(ASM_OBJECTS)

LINK: $(CPP_OBJECTS) $(ASM_OBJECTS)
	$(LINKER) -v -O2 -T $(LINKSCRIPT) $(ASM_OBJECTS) $(CPP_OBJECTS) $(CPPCARGS) -o $(BUILD)/kernel.elf

IMAGE: LINK
	$(OBJCOPY) $(BUILD)/kernel.elf -O binary $(BUILD)/kernel.img
	$(OBJDUMP) -D $(BUILD)/bootstrap.o > $(BUILD)/bootstrap.o.asm
	$(OBJCOPY) $(BUILD)/bootstrap.o -O srec $(BUILD)/bootstrap.srec
	hexdump -C $(BUILD)/kernel.elf > $(BUILD)/kernel.hex
	$(OBJDUMP) -D -S $(BUILD)/kernel.elf > $(BUILD)/kernel.elf.asm

clean:
	rm ../build/*