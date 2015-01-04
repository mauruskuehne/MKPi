# can this be set globally in the xcodeproj file?

CPPC=$(HOME)/Development/yagarto/yagarto-4.7.2/bin/arm-none-eabi-g++
ASMC=$(HOME)/Development/yagarto/yagarto-4.7.2/bin/arm-none-eabi-as
LINKER=$(HOME)/Development/yagarto/yagarto-4.7.2/bin/arm-none-eabi-g++
OBJCOPY=$(HOME)/Development/yagarto/yagarto-4.7.2/bin/arm-none-eabi-objcopy
OBJDUMP=$(HOME)/Development/yagarto/yagarto-4.7.2/bin/arm-none-eabi-objdump

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


###### TARGETS

all: IMAGE

CPP: $(CPPSRC)
	$(CPPC) -c -std=c++11 -ffreestanding -nostdlib -fno-builtin -fno-rtti -fno-exceptions -nostartfiles $(CPPSRC) -o $(CPP_OBJECTS)

ASM: $(ASMSRC)
	$(ASMC) $(ASMSRC) -o $(ASM_OBJECTS)

LINK: CPP ASM
	$(LINKER) -nostdlib -nostartfiles -O2 -T $(LINKSCRIPT) $(ASM_OBJECTS) $(CPP_OBJECTS) -o $(BUILD)/kernel.elf

IMAGE: LINK
	$(OBJCOPY) $(BUILD)/kernel.elf -O binary $(BUILD)/kernel.img
	$(OBJDUMP) -D $(BUILD)/bootstrap.o > $(BUILD)/bootstrap.o.asm
	$(OBJCOPY) $(BUILD)/bootstrap.o -O srec $(BUILD)/bootstrap.srec
	hexdump -C $(BUILD)/kernel.elf > $(BUILD)/kernel.hex
#	$(OBJDUMP) -D irq.o > $(BUILD)/irq.o.asm
#	$(OBJDUMP) -D kmain.o > $(BUILD)/kmain.o.asm
	$(OBJDUMP) -D $(BUILD)/kernel.elf > $(BUILD)/kern.elf.asm