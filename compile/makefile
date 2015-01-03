# can this be set globally in the xcodeproj file?

CPPC=$(HOME)/Development/yagarto/yagarto-4.7.2/bin/arm-none-eabi-g++
ASMC=$(HOME)/Development/yagarto/yagarto-4.7.2/bin/arm-none-eabi-as
LINKER=$(HOME)/Development/yagarto/yagarto-4.7.2/bin/arm-none-eabi-g++
OBJCOPY=$(HOME)/Development/yagarto/yagarto-4.7.2/bin/arm-none-eabi-objcopy

SOURCE=../source
BUILD=../build

#sources to compile:
CPPSRC=$(wildcard $(SOURCE)/*.cpp)
ASMSRC=$(wildcard $(SOURCE)/*.S)

#linkscript
LINKSCRIPT=linker.ld

#generated objects:
CPP_OBJECTS=$(addprefix $(BUILD)/,$(notdir $(CPPSRC:.cpp=.o)))
ASM_OBJECTS=$(addprefix $(BUILD)/,$(notdir $(ASMSRC:.S=.o)))


###### TARGETS

all: IMAGE

CPP: $(CPPSRC)
	$(CPPC) -ffreestanding -nostdlib -fno-builtin -fno-rtti -fno-exceptions -nostartfiles $(CPPSRC) -o $(CPP_OBJECTS)

ASM: $(ASMSRC)
	$(ASMC) $(ASMSRC) -o $(ASM_OBJECTS)

LINK: CPP ASM
	$(LINKER) -nostdlib -nostartfiles -O2 -T $(LINKSCRIPT)  $(CPP_OBJECTS) $(ASM_OBJECTS) -o $(BUILD)/kernel.elf

IMAGE: LINK
	$(OBJCOPY) $(BUILD)/kernel.elf -O binary $(BUILD)/kernel.img