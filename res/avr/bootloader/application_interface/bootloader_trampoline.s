.section .trampolines,"ax",@progbits
.global _bootloader_trampoline
_bootloader_trampoline:
	jmp 0x3F9E0	;  Addresses of jumptable in bootloader for the ATmega2560
	jmp 0x3F9E4
	jmp 0x3F9E8
	jmp 0x3F9EC
