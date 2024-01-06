# Makefile for building EFI application
TARGET = myworld
EFI_TARGET = $(TARGET).efi

CC = gcc
LD = ld
OBJCOPY = objcopy
ARCH = $(shell uname -m)
TMP_DIR := $(shell mktemp -d /tmp/efi.XXXXXXXX)

GNUEFI = /usr/include/efi
GNUEFI_INC = -I$(GNUEFI) -I$(GNUEFI)/$(ARCH) -I$(GNUEFI)/protocol

LIB             = /usr/lib
EFI_CRT_OBJS    = $(LIB)/crt0-efi-$(ARCH).o
EFI_LDS         = $(LIB)/elf_$(ARCH)_efi.lds


EFI_SRC_FILES = \
	main.c

EFI_SRC_OBJS = \
	$(EFI_SRC_FILES:.c=.o)

CFLAGS = \
	$(GNUEFI_INC) \
	-fno-stack-protector -fpic \
	-fshort-wchar -mno-red-zone -Wall \
	-DEFI_FUNCTION_WRAPPER

LDFLAGS = \
	-nostdlib -znocombreloc -T $(EFI_LDS) -shared \
	-Bsymbolic -L $(LIB) $(EFI_CRT_OBJS)


all: $(EFI_TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET).so: $(EFI_SRC_OBJS)
	$(LD) $(LDFLAGS) $^ -o $@ -lefi -lgnuefi

$(EFI_TARGET): $(TARGET).so
	$(OBJCOPY) -j .text -j .sdata -j .data -j .dynamic -j .dynsym -j .rel -j .rela -j .reloc --target=efi-app-x86_64 $^ $@

run:
	mkdir -p $(TMP_DIR)
	cp $(EFI_TARGET) $(TMP_DIR)/
	qemu-system-x86_64 \
		-enable-kvm \
		-cpu host \
		-bios /usr/share/OVMF/OVMF_CODE.fd \
		-smp 6 \
		-m 4G \
		-drive file=fat:rw:$(TMP_DIR)/,format=raw \
		-serial stdio \
		-nodefaults
#		-nodefaults \
#		-vga std \
#		-display gtk

clean:
	rm -f *.o *.so $(EFI_TARGET)

.PHONY: all
.PHONY: run
.PHONY: clean
