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
	ldr r0, string2
	ldr r1, C_add
	bl scanf
	ldr r0, string2
	ldr r1, D_add
	bl scanf
	ldr r1, A_add
	ldr r2, [r1]
	ldr r3, B_add
	ldr r4, [r3]
	add r4, r2, r4
	ldr r5, TEMP
	str r4, [r5]
	ldr r6, D_add
	str r4, [r6]
	ldr r7, B_add
	ldr r8, [r7]
	ldr r9, C_add
	ldr r10, [r9]
	add r10, r8, r10
	ldr r11, TEMP
	str r10, [r11]
	ldr r12, E_add
	str r10, [r12]
	ldr r1, C_add
	ldr r2, [r1]
	ldr r3, D_add
	ldr r4, [r3]
	add r4, r2, r4
	ldr r5, TEMP
	str r4, [r5]
	ldr r6, F_add
	str r4, [r6]
	ldr r0, string2
	ldr r1, G_add
	bl scanf
	ldr r8, G_add
	ldr r9, [r8]
	eor r7, r7
	cmp r7, r9
	beq FUNC0
	ldr r10, D_add
	ldr r11, [r10]
	ldr r12, E_add
	ldr r1, [r12]
	add r1, r11, r1
	ldr r2, TEMP
	str r1, [r2]
	b FUNC1
	FUNC0:
	ldr r3, E_add
	ldr r4, [r3]
	ldr r5, F_add
	ldr r6, [r5]
	add r6, r4, r6
	ldr r7, TEMP
	str r6, [r7]
	mov r1, r6
	FUNC1:
	ldr r3, H_add
	str r1, [r3]
	ldr r4, D_add
	ldr r5, [r4]
	ldr r6, TEMP
	str r5, [r6]
	ldr r2, D_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r7, E_add
	ldr r8, [r7]
	ldr r9, TEMP
	str r8, [r9]
	ldr r2, E_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r10, F_add
	ldr r11, [r10]
	ldr r12, TEMP
	str r11, [r12]
	ldr r2, F_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r1, H_add
	ldr r2, [r1]
	ldr r3, TEMP
	str r2, [r3]
	ldr r2, H_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	mov r4, #37
	ldr r5, TEMP
	str r4, [r5]
	ldr r6, C_add
	str r4, [r6]
	ldr r7, C_add
	ldr r8, [r7]
	ldr r9, C_add
	ldr r10, [r9]
	add r10, r8, r10
	ldr r11, TEMP
	str r10, [r11]
	ldr r12, TEMP
	ldr r1, [r12]
	ldr r2, C_add
	ldr r3, [r2]
	sub r3, r1, r3
	ldr r4, TEMP
	str r3, [r4]
	ldr r5, D_add
	str r3, [r5]
	ldr r6, C_add
	ldr r7, [r6]
	ldr r8, TEMP
	str r7, [r8]
	ldr r2, C_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r9, D_add
	ldr r10, [r9]
	ldr r11, TEMP
	str r10, [r11]
	ldr r2, D_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	mov r12, #1
	ldr r1, TEMP
	str r12, [r1]
	ldr r2, A_add
	str r12, [r2]
	ldr r4, A_add
	ldr r5, [r4]
	eor r3, r3
	cmp r3, r5
	beq FUNC2
	mov r6, #1
	ldr r7, TEMP
	str r6, [r7]
	b FUNC3
	FUNC2:
	mov r8, #0
	ldr r9, TEMP
	str r8, [r9]
	mov r6, r8
	FUNC3:
	ldr r8, B_add
	str r6, [r8]
	ldr r9, A_add
	ldr r10, [r9]
	ldr r11, TEMP
	str r10, [r11]
	ldr r2, A_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r12, B_add
	ldr r1, [r12]
	ldr r2, TEMP
	str r1, [r2]
	ldr r2, B_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	pop {ip, pc}

A_add: .word A_var

B_add: .word B_var

C_add: .word C_var

D_add: .word D_var

E_add: .word E_var

F_add: .word F_var

G_add: .word G_var

H_add: .word H_var

TEMP: .word TEMP1

string1: .word string_1

string2: .word string_2

.data

A_var: .word 0

B_var: .word 0

C_var: .word 0

D_var: .word 0

E_var: .word 0

F_var: .word 0

G_var: .word 0

H_var: .word 0

TEMP1: .word 0

string_1: .asciz "%i\n"

string_2: .asciz "%i" 
