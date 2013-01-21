.section .shared_jumptable,"ax",@progbits
.global _jumptable
_jumptable:
	jmp boot_mark_clean_BL
	jmp get_bootloader_information_BL
	jmp boot_mark_dirty_BL

