.section .text
.global main
.extern printf

main:
	push {ip, lr}
	mov r1, #2
	ldr r2, TEMP
	str r1, [r2]
	ldr r3, B_add
	str r1, [r3]
	ldr r4, B_add
	ldr r5, [r4]
	mov r6, #-3
	add r6, r6, r5
	ldr r7, TEMP
	str r6, [r7]
	ldr r8, A_add
	str r6, [r8]
	ldr r9, A_add
	ldr r10, [r9]
	ldr r11, TEMP
	str r10, [r11]
	ldr r2, A_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r1, A_add
	ldr r2, [r1]
	eor r12, r12
	cmp r12, r2
	beq FUNC0
	mov r3, #-13
	ldr r4, TEMP
	str r3, [r4]
	b FUNC1
	FUNC0:
	ldr r5, B_add
	ldr r6, [r5]
	ldr r7, TEMP
	str r6, [r7]
	mov r3, r6
	FUNC1:
	ldr r5, A_add
	str r3, [r5]
	ldr r6, A_add
	ldr r7, [r6]
	ldr r8, TEMP
	str r7, [r8]
	ldr r2, A_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r10, A_add
	ldr r11, [r10]
	eor r9, r9
	cmp r9, r11
	beq FUNC2
	ldr r12, B_add
	ldr r1, [r12]
	mov r2, #-3
	sub r2, r2, r1
	ldr r3, TEMP
	str r2, [r3]
	b FUNC3
	FUNC2:
	ldr r4, B_add
	ldr r5, [r4]
	ldr r6, TEMP
	str r5, [r6]
	mov r2, r5
	FUNC3:
	ldr r4, A_add
	str r2, [r4]
	ldr r5, A_add
	ldr r6, [r5]
	ldr r7, TEMP
	str r6, [r7]
	ldr r2, A_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	pop {ip, pc}

B_add: .word B_var

A_add: .word A_var

TEMP: .word TEMP1

string1: .word string_1

string2: .word string_2

.data

B_var: .word 0

A_var: .word 0

TEMP1: .word 0

string_1: .asciz "%i\n"

string_2: .asciz "%i" 
