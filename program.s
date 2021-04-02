.section .text
.global main
.extern printf

main:
	push {ip, lr}
	mov r1, #14
	ldr r2, TEMP
	str r1, [r2]
	ldr r3, A_add
	str r1, [r3]
	ldr r4, A_add
	ldr r5, [r4]
	mov r6, #12
	sub r6, r5, r6
	ldr r7, TEMP
	str r6, [r7]
	ldr r8, TEMP
	ldr r9, [r8]
	mov r10, #2
	sub r10, r9, r10
	ldr r11, TEMP
	str r10, [r11]
	ldr r1, TEMP
	ldr r2, [r1]
	eor r12, r12
	cmp r12, r2
	beq FUNC0
	ldr r3, A_add
	ldr r4, [r3]
	mov r5, #2
	add r5, r4, r5
	ldr r6, TEMP
	str r5, [r6]
	b FUNC1
	FUNC0:
	FUNC1:
	ldr r7, C_add
	str r5, [r7]
	pop {ip, pc}

A_add: .word A_var

C_add: .word C_var

TEMP: .word TEMP1

string1: .word string_1

string2: .word string_2

.data

A_var: .word 0

C_var: .word 0

TEMP1: .word 0

string_1: .asciz "%i\n"

string_2: .asciz "%i"