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


###### TARGETS

all: IMAGE

$(BUILD)/%.o: $(SOURCE)/%.cpp
	$(CPPC) -c -std=c++14 -ffreestanding -nostdlib -fno-builtin -fno-rtti -fno-exceptions -nostartfiles -DVERSION=\"$(GIT_VERSION)\" -o $@ $^

$(BUILD)/%.o: $(SOURCE)/%.s
	$(ASMC) -o $@ $^

CPP: $(CPPSRC)
	$(CPPC) -c -std=c++14 -ffreestanding -nostdlib -fno-builtin -fno-rtti -fno-exceptions -nostartfiles $(CPPSRC) -o $(CPP_OBJECTS)

ASM: $(ASMSRC)
	$(ASMC) $(ASMSRC) -o $(ASM_OBJECTS)

LINK: $(CPP_OBJECTS) $(ASM_OBJECTS)
	$(LINKER) -nostdlib -nostartfiles -O2 -T $(LINKSCRIPT) $(ASM_OBJECTS) $(CPP_OBJECTS) -o $(BUILD)/kernel.elf

IMAGE: LINK
	$(OBJCOPY) $(BUILD)/kernel.elf -O binary $(BUILD)/kernel.img
	$(OBJDUMP) -D $(BUILD)/bootstrap.o > $(BUILD)/bootstrap.o.asm
	$(OBJCOPY) $(BUILD)/bootstrap.o -O srec $(BUILD)/bootstrap.srec
	hexdump -C $(BUILD)/kernel.elf > $(BUILD)/kernel.hex
	$(OBJDUMP) -D -S $(BUILD)/kernel.elf > $(BUILD)/kernel.elf.asm

clean:
	rm ../build/*