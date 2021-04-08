.section .text
.global main
.extern printf

main:
	push {ip, lr}
	ldr r0, string2
	ldr r1, A_add
	bl scanf
	ldr r0, string2
	ldr r1, B_add
	bl scanf
	ldr r1, B_add
	ldr r2, [r1]
	mov r3, #7
	sub r3, r2, r3
	ldr r4, TEMP
	str r3, [r4]
	ldr r5, TEMP
	ldr r6, [r5]
	mov r7, #3
	add r7, r6, r7
	ldr r8, TEMP
	str r7, [r8]
	ldr r9, C_add
	str r7, [r9]
	ldr r10, C_add
	ldr r11, [r10]
	mov r12, #20
	add r12, r12, r11
	ldr r1, TEMP
	str r12, [r1]
	ldr r2, A_add
	str r12, [r2]
	ldr r3, A_add
	ldr r4, [r3]
	ldr r5, TEMP
	str r4, [r5]
	ldr r2, A_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r6, B_add
	ldr r7, [r6]
	ldr r8, TEMP
	str r7, [r8]
	ldr r2, B_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r9, C_add
	ldr r10, [r9]
	ldr r11, TEMP
	str r10, [r11]
	ldr r2, C_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r12, A_add
	ldr r1, [r12]
	ldr r2, B_add
	ldr r3, [r2]
	sub r3, r1, r3
	ldr r4, TEMP
	str r3, [r4]
	ldr r5, TEMP
	ldr r6, [r5]
	ldr r7, C_add
	ldr r8, [r7]
	add r8, r6, r8
	ldr r9, TEMP
	str r8, [r9]
	ldr r10, D_add
	str r8, [r10]
	ldr r0, string2
	ldr r1, E_add
	bl scanf
	ldr r12, E_add
	ldr r1, [r12]
	eor r11, r11
	cmp r11, r1
	beq FUNC0
	ldr r2, D_add
	ldr r3, [r2]
	ldr r4, E_add
	ldr r5, [r4]
	add r5, r3, r5
	ldr r6, TEMP
	str r5, [r6]
	b FUNC1
	FUNC0:
	ldr r7, B_add
	ldr r8, [r7]
	mov r9, #2
	add r9, r8, r9
	ldr r10, TEMP
	str r9, [r10]
	mov r5, r9
	FUNC1:
	ldr r7, C_add
	str r5, [r7]
	ldr r8, D_add
	ldr r9, [r8]
	ldr r10, TEMP
	str r9, [r10]
	ldr r2, D_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r11, C_add
	ldr r12, [r11]
	ldr r1, TEMP
	str r12, [r1]
	ldr r2, C_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	mov r2, #29
	ldr r3, TEMP
	str r2, [r3]
	ldr r4, TEMP
	ldr r5, [r4]
	mov r6, #7
	sub r6, r5, r6
	ldr r7, TEMP
	str r6, [r7]
	ldr r8, TEMP
	ldr r9, [r8]
	mov r10, #13
	add r10, r9, r10
	ldr r11, TEMP
	str r10, [r11]
	ldr r12, A_add
	str r10, [r12]
	ldr r1, A_add
	ldr r2, [r1]
	ldr r3, TEMP
	str r2, [r3]
	ldr r2, A_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r4, A_add
	ldr r5, [r4]
	ldr r6, A_add
	ldr r7, [r6]
	add r7, r5, r7
	ldr r8, TEMP
	str r7, [r8]
	ldr r9, A_add
	str r7, [r9]
	ldr r10, A_add
	ldr r11, [r10]
	ldr r12, TEMP
	str r11, [r12]
	ldr r2, A_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r1, A_add
	ldr r2, [r1]
	ldr r3, B_add
	ldr r4, [r3]
	add r4, r2, r4
	ldr r5, TEMP
	str r4, [r5]
	ldr r6, TEMP
	ldr r7, [r6]
	ldr r8, C_add
	ldr r9, [r8]
	add r9, r7, r9
	ldr r10, TEMP
	str r9, [r10]
	ldr r11, TEMP
	ldr r12, [r11]
	ldr r1, D_add
	ldr r2, [r1]
	add r2, r12, r2
	ldr r3, TEMP
	str r2, [r3]
	ldr r4, A_add
	str r2, [r4]
	ldr r5, B_add
	ldr r6, [r5]
	ldr r7, B_add
	ldr r8, [r7]
	sub r8, r6, r8
	ldr r9, TEMP
	str r8, [r9]
	ldr r11, TEMP
	ldr r12, [r11]
	eor r10, r10
	cmp r10, r12
	beq FUNC2
	mov r1, #62
	ldr r2, TEMP
	str r1, [r2]
	b FUNC3
	FUNC2:
	ldr r3, A_add
	ldr r4, [r3]
	ldr r5, B_add
	ldr r6, [r5]
	add r6, r4, r6
	ldr r7, TEMP
	str r6, [r7]
	ldr r8, TEMP
	ldr r9, [r8]
	ldr r10, C_add
	ldr r11, [r10]
	add r11, r9, r11
	ldr r12, TEMP
	str r11, [r12]
	ldr r1, TEMP
	ldr r2, [r1]
	ldr r3, D_add
	ldr r4, [r3]
	add r4, r2, r4
	ldr r5, TEMP
	str r4, [r5]
	mov r1, r4
	FUNC3:
	ldr r3, C_add
	str r1, [r3]
	ldr r4, A_add
	ldr r5, [r4]
	ldr r6, TEMP
	str r5, [r6]
	ldr r2, A_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r7, C_add
	ldr r8, [r7]
	ldr r9, TEMP
	str r8, [r9]
	ldr r2, C_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	pop {ip, pc}

A_add: .word A_var

B_add: .word B_var

C_add: .word C_var

D_add: .word D_var

E_add: .word E_var

TEMP: .word TEMP1

string1: .word string_1

string2: .word string_2

.data

A_var: .word 0

B_var: .word 0

C_var: .word 0

D_var: .word 0

E_var: .word 0

TEMP1: .word 0

string_1: .asciz "%i\n"

string_2: .asciz "%i" 
