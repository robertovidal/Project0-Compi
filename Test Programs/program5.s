.section .text
.global main
.extern printf

main:
	push {ip, lr}
	mov r1, #-5
	ldr r2, TEMP
	str r1, [r2]
	ldr r3, A_add
	str r1, [r3]
	ldr r4, A_add
	ldr r5, [r4]
	mov r6, #12
	add r6, r5, r6
	ldr r7, TEMP
	str r6, [r7]
	ldr r8, TEMP
	ldr r9, [r8]
	mov r10, #-3
	sub r10, r10, r9
	ldr r11, TEMP
	str r10, [r11]
	ldr r12, TEMP
	ldr r1, [r12]
	ldr r2, A_add
	ldr r3, [r2]
	add r3, r1, r3
	ldr r4, TEMP
	str r3, [r4]
	ldr r5, TEMP
	ldr r6, [r5]
	ldr r7, TEMP
	str r6, [r7]
	ldr r8, B_add
	str r6, [r8]
	ldr r9, B_add
	ldr r10, [r9]
	ldr r11, TEMP
	str r10, [r11]
	ldr r2, B_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r12, A_add
	ldr r1, [r12]
	ldr r2, TEMP
	str r1, [r2]
	ldr r3, B_add
	ldr r4, [r3]
	ldr r5, A_add
	ldr r6, [r5]
	sub r6, r4, r6
	ldr r7, TEMP
	str r6, [r7]
	ldr r8, B_add
	str r6, [r8]
	ldr r9, B_add
	ldr r10, [r9]
	ldr r11, TEMP
	str r10, [r11]
	ldr r2, B_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r12, B_add
	ldr r1, [r12]
	ldr r2, TEMP
	str r1, [r2]
	ldr r3, B_add
	ldr r4, [r3]
	ldr r5, B_add
	ldr r6, [r5]
	add r6, r4, r6
	ldr r7, TEMP
	str r6, [r7]
	ldr r8, B_add
	str r6, [r8]
	ldr r9, B_add
	ldr r10, [r9]
	ldr r11, TEMP
	str r10, [r11]
	ldr r2, B_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	pop {ip, pc}

A_add: .word A_var

B_add: .word B_var

TEMP: .word TEMP1

string1: .word string_1

string2: .word string_2

.data

A_var: .word 0

B_var: .word 0

TEMP1: .word 0

string_1: .asciz "%i\n"

string_2: .asciz "%i" 
