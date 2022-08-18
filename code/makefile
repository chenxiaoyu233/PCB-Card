AS = arm-none-eabi-as
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
BIN = arm-none-eabi-objcopy

CCFLAGS = -mcpu=cortex-m0plus 
ASFLAGS = -mcpu=cortex-m0plus 
LDFLAGS = -mcpu=cortex-m0

main:
	$(CC) $(CCFLAGS) -S led.c 
	$(CC) $(CCFLAGS) -c -o led.o led.c 
	$(AS) $(ASFLAGS) -o init.o init.s
	$(LD) -T link.ld -o led.elf init.o led.o
	$(BIN) -O binary led.elf led.bin 

flash:
	dfu-util -a 0 -D ./led.bin -s 0x08000000 -v

qemu:
	qemu-system-arm \
		-d 'in_asm,int,exec,cpu,guest_errors,unimp' \
		-M stm32vldiscovery \
		-kernel led.bin \
		-singlestep -nographic
