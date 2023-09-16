global _start
_start:
	call main
	mov eax, 1
	xor ebx, ebx
	int 0x80
;std_test.jaspl
section .text
main:
	mov eax, 0
	mov dword[main_i], eax
	mov eax, main_i
	push eax
	call input
	mov eax, dword[main_i]
	push eax
	call print
	mov eax, 10
	push eax
	call print
	mov ebx, 0
	ret
section .bss
	main_i resd 1
section .data
;std_io.jaspl
section .text
input:
	pop ebx
	pop eax
	push ebx
	mov dword[input_chptr], eax
	mov eax, 3
	mov ebx, 0
	mov ecx, input_chptr
	mov edx, 1
	int 0x80
	mov ebx, 0
	ret
print:
	pop ebx
	pop eax
	push ebx
	mov dword[print_ch], eax
	mov eax, 4
	mov ebx, 1
	mov ecx, print_ch
	mov edx, 1
	int 0x80
	mov ebx, 0
	ret
section .bss
	print_ch resd 1
	input_chptr resd 1
section .data
