.section .bootloader_trampoline,"ax",@progbits
.global _bootloader_trampoline
_bootloader_trampoline:
	jmp 0x3F9E0
	jmp 0x3F9E4
	jmp 0x3F9E8
	jmp 0x3F9EC
