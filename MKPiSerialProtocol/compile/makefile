# can this be set globally in the xcodeproj file?

CPPC=/usr/local/bin/arm-none-eabi-g++
ASMC=/usr/local/bin/arm-none-eabi-as
AR=/usr/local/bin/arm-none-eabi-ar
LINKER=/usr/local/bin/arm-none-eabi-g++
OBJCOPY=/usr/local/bin/arm-none-eabi-objcopy
OBJDUMP=/usr/local/bin/arm-none-eabi-objdump

SOURCE=../
HEADERS=../include/
BUILD=../build

#sources to compile:
CPPSRC=$(wildcard $(SOURCE)/*.cpp)
ASMSRC=$(wildcard $(SOURCE)/*.s)

#generated objects:
CPP_OBJECTS=$(addprefix $(BUILD)/,$(notdir $(CPPSRC:.cpp=.o)))
ASM_OBJECTS=$(addprefix $(BUILD)/,$(notdir $(ASMSRC:.s=.o)))

GIT_VERSION := $(shell git describe --abbrev=4 --dirty --always --tags)

LIBS=-lgcc -lc -lgcc

CPPCARGS=-std=c++14 -ffreestanding -nostdlib -fno-builtin -fno-rtti -fno-exceptions -nostartfiles -shared -Wall  $(LIBS) -DVERSION=\"$(GIT_VERSION)\"

###### TARGETS

all: LIBRARY

$(BUILD)/%.o: $(SOURCE)/%.cpp
	$(CPPC) -v -c $(CPPCARGS)  -o $@ $^

$(BUILD)/%.o: $(SOURCE)/%.s
	$(ASMC) -o $@ $^

CPP: $(CPPSRC)
	$(CPPC) -c $(CCPCARGS) $(CPPSRC) -o $(CPP_OBJECTS)

ASM: $(ASMSRC)
	$(ASMC) $(ASMSRC) -o $(ASM_OBJECTS)

ARCHIVE: $(CPP_OBJECTS) $(ASM_OBJECTS)
	$(AR) rcs libMKPISerialProtocol_RBPI.a $(ASM_OBJECTS) $(CPP_OBJECTS)
	mv libMKPISerialProtocol_RBPI.a $(BUILD)/libMKPISerialProtocol_RBPI.a

HEADERS:
	cp -r $(HEADERS) $(BUILD)/include

LIBRARY: ARCHIVE HEADERS
	hexdump -C $(BUILD)/libMKPISerialProtocol_RBPI.a > $(BUILD)/libMKPISerialProtocol_RBPI.a.hex
	$(OBJDUMP) -D -S $(BUILD)/libMKPISerialProtocol_RBPI.a > $(BUILD)/libMKPISerialProtocol_RBPI.a.asm

clean:
	rm ../build/*