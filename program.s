.section .text
.global main
.extern printf

main:
	push {ip, lr}
	mov r1, #0
	ldr r2, TEMP
	str r1, [r2]
	ldr r3, A_add
	str r1, [r3]
	mov r4, #1
	ldr r5, TEMP
	str r4, [r5]
	ldr r6, b_add
	str r4, [r6]
	ldr r8, b_add
	ldr r9, [r8]
	eor r7, r7
	cmp r7, r9
	beq FUNC0
	ldr r10, A_add
	ldr r11, [r10]
	ldr r12, TEMP
	str r11, [r12]
	b FUNC1
	FUNC0:
	ldr r1, b_add
	ldr r2, [r1]
	mov r3, #5
	sub r3, r3, r2
	ldr r4, TEMP
	str r3, [r4]
	mov r11, r3
	FUNC1:
	ldr r1, C_add
	str r11, [r1]
	ldr r2, C_add
	ldr r3, [r2]
	ldr r4, TEMP
	str r3, [r4]
	ldr r2, C_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r6, b_add
	ldr r7, [r6]
	eor r5, r5
	cmp r5, r7
	beq FUNC2
	ldr r8, A_add
	ldr r9, [r8]
	ldr r10, TEMP
	str r9, [r10]
	b FUNC3
	FUNC2:
	mov r11, #5
	ldr r12, TEMP
	str r11, [r12]
	mov r9, r11
	FUNC3:
	ldr r11, C_add
	str r9, [r11]
	ldr r12, C_add
	ldr r1, [r12]
	ldr r2, TEMP
	str r1, [r2]
	ldr r2, C_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r4, b_add
	ldr r5, [r4]
	eor r3, r3
	cmp r3, r5
	beq FUNC4
	ldr r6, A_add
	ldr r7, [r6]
	ldr r8, TEMP
	str r7, [r8]
	b FUNC5
	FUNC4:
	ldr r9, b_add
	ldr r10, [r9]
	mov r11, #5
	sub r11, r10, r11
	ldr r12, TEMP
	str r11, [r12]
	mov r7, r11
	FUNC5:
	ldr r9, C_add
	str r7, [r9]
	ldr r10, C_add
	ldr r11, [r10]
	ldr r12, TEMP
	str r11, [r12]
	ldr r2, C_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r2, b_add
	ldr r3, [r2]
	eor r1, r1
	cmp r1, r3
	beq FUNC6
	ldr r4, A_add
	ldr r5, [r4]
	ldr r6, TEMP
	str r5, [r6]
	b FUNC7
	FUNC6:
	ldr r7, b_add
	ldr r8, [r7]
	ldr r9, TEMP
	str r8, [r9]
	mov r5, r8
	FUNC7:
	ldr r7, C_add
	str r5, [r7]
	ldr r8, C_add
	ldr r9, [r8]
	ldr r10, TEMP
	str r9, [r10]
	ldr r2, C_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r12, b_add
	ldr r1, [r12]
	eor r11, r11
	cmp r11, r1
	beq FUNC8
	ldr r2, A_add
	ldr r3, [r2]
	mov r4, #2
	add r4, r4, r3
	ldr r5, TEMP
	str r4, [r5]
	b FUNC9
	FUNC8:
	ldr r6, b_add
	ldr r7, [r6]
	mov r8, #5
	sub r8, r8, r7
	ldr r9, TEMP
	str r8, [r9]
	mov r4, r8
	FUNC9:
	ldr r6, C_add
	str r4, [r6]
	ldr r7, C_add
	ldr r8, [r7]
	ldr r9, TEMP
	str r8, [r9]
	ldr r2, C_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r11, b_add
	ldr r12, [r11]
	eor r10, r10
	cmp r10, r12
	beq FUNC10
	ldr r1, A_add
	ldr r2, [r1]
	mov r3, #2
	add r3, r3, r2
	ldr r4, TEMP
	str r3, [r4]
	b FUNC11
	FUNC10:
	mov r5, #5
	ldr r6, TEMP
	str r5, [r6]
	mov r3, r5
	FUNC11:
	ldr r5, C_add
	str r3, [r5]
	ldr r6, C_add
	ldr r7, [r6]
	ldr r8, TEMP
	str r7, [r8]
	ldr r2, C_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r10, b_add
	ldr r11, [r10]
	eor r9, r9
	cmp r9, r11
	beq FUNC12
	ldr r12, A_add
	ldr r1, [r12]
	mov r2, #2
	add r2, r2, r1
	ldr r3, TEMP
	str r2, [r3]
	b FUNC13
	FUNC12:
	ldr r4, b_add
	ldr r5, [r4]
	mov r6, #5
	sub r6, r5, r6
	ldr r7, TEMP
	str r6, [r7]
	mov r2, r6
	FUNC13:
	ldr r4, C_add
	str r2, [r4]
	ldr r5, C_add
	ldr r6, [r5]
	ldr r7, TEMP
	str r6, [r7]
	ldr r2, C_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r9, b_add
	ldr r10, [r9]
	eor r8, r8
	cmp r8, r10
	beq FUNC14
	ldr r11, A_add
	ldr r12, [r11]
	mov r1, #2
	add r1, r1, r12
	ldr r2, TEMP
	str r1, [r2]
	b FUNC15
	FUNC14:
	ldr r3, b_add
	ldr r4, [r3]
	ldr r5, TEMP
	str r4, [r5]
	mov r1, r4
	FUNC15:
	ldr r3, C_add
	str r1, [r3]
	ldr r4, C_add
	ldr r5, [r4]
	ldr r6, TEMP
	str r5, [r6]
	ldr r2, C_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r8, b_add
	ldr r9, [r8]
	eor r7, r7
	cmp r7, r9
	beq FUNC16
	ldr r10, A_add
	ldr r11, [r10]
	mov r12, #2
	add r12, r11, r12
	ldr r1, TEMP
	str r12, [r1]
	b FUNC17
	FUNC16:
	ldr r2, b_add
	ldr r3, [r2]
	mov r4, #5
	sub r4, r4, r3
	ldr r5, TEMP
	str r4, [r5]
	mov r12, r4
	FUNC17:
	ldr r1, C_add
	str r12, [r1]
	ldr r2, C_add
	ldr r3, [r2]
	ldr r4, TEMP
	str r3, [r4]
	ldr r2, C_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r6, b_add
	ldr r7, [r6]
	eor r5, r5
	cmp r5, r7
	beq FUNC18
	ldr r8, A_add
	ldr r9, [r8]
	mov r10, #2
	add r10, r9, r10
	ldr r11, TEMP
	str r10, [r11]
	b FUNC19
	FUNC18:
	mov r12, #5
	ldr r1, TEMP
	str r12, [r1]
	mov r10, r12
	FUNC19:
	ldr r12, C_add
	str r10, [r12]
	ldr r1, C_add
	ldr r2, [r1]
	ldr r3, TEMP
	str r2, [r3]
	ldr r2, C_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r5, b_add
	ldr r6, [r5]
	eor r4, r4
	cmp r4, r6
	beq FUNC20
	ldr r7, A_add
	ldr r8, [r7]
	mov r9, #2
	add r9, r8, r9
	ldr r10, TEMP
	str r9, [r10]
	b FUNC21
	FUNC20:
	ldr r11, b_add
	ldr r12, [r11]
	mov r1, #5
	sub r1, r12, r1
	ldr r2, TEMP
	str r1, [r2]
	mov r9, r1
	FUNC21:
	ldr r11, C_add
	str r9, [r11]
	ldr r12, C_add
	ldr r1, [r12]
	ldr r2, TEMP
	str r1, [r2]
	ldr r2, C_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r4, b_add
	ldr r5, [r4]
	eor r3, r3
	cmp r3, r5
	beq FUNC22
	ldr r6, A_add
	ldr r7, [r6]
	mov r8, #2
	add r8, r7, r8
	ldr r9, TEMP
	str r8, [r9]
	b FUNC23
	FUNC22:
	ldr r10, b_add
	ldr r11, [r10]
	ldr r12, TEMP
	str r11, [r12]
	mov r8, r11
	FUNC23:
	ldr r10, C_add
	str r8, [r10]
	ldr r11, C_add
	ldr r12, [r11]
	ldr r1, TEMP
	str r12, [r1]
	ldr r2, C_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r3, b_add
	ldr r4, [r3]
	eor r2, r2
	cmp r2, r4
	beq FUNC24
	mov r5, #2
	ldr r6, TEMP
	str r5, [r6]
	b FUNC25
	FUNC24:
	ldr r7, b_add
	ldr r8, [r7]
	mov r9, #5
	sub r9, r9, r8
	ldr r10, TEMP
	str r9, [r10]
	mov r5, r9
	FUNC25:
	ldr r7, C_add
	str r5, [r7]
	ldr r8, C_add
	ldr r9, [r8]
	ldr r10, TEMP
	str r9, [r10]
	ldr r2, C_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r12, b_add
	ldr r1, [r12]
	eor r11, r11
	cmp r11, r1
	beq FUNC26
	mov r2, #2
	ldr r3, TEMP
	str r2, [r3]
	b FUNC27
	FUNC26:
	mov r4, #5
	ldr r5, TEMP
	str r4, [r5]
	mov r2, r4
	FUNC27:
	ldr r4, C_add
	str r2, [r4]
	ldr r5, C_add
	ldr r6, [r5]
	ldr r7, TEMP
	str r6, [r7]
	ldr r2, C_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r9, b_add
	ldr r10, [r9]
	eor r8, r8
	cmp r8, r10
	beq FUNC28
	mov r11, #2
	ldr r12, TEMP
	str r11, [r12]
	b FUNC29
	FUNC28:
	ldr r1, b_add
	ldr r2, [r1]
	mov r3, #5
	sub r3, r2, r3
	ldr r4, TEMP
	str r3, [r4]
	mov r11, r3
	FUNC29:
	ldr r1, C_add
	str r11, [r1]
	ldr r2, C_add
	ldr r3, [r2]
	ldr r4, TEMP
	str r3, [r4]
	ldr r2, C_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	ldr r6, b_add
	ldr r7, [r6]
	eor r5, r5
	cmp r5, r7
	beq FUNC30
	mov r8, #2
	ldr r9, TEMP
	str r8, [r9]
	b FUNC31
	FUNC30:
	ldr r10, b_add
	ldr r11, [r10]
	ldr r12, TEMP
	str r11, [r12]
	mov r8, r11
	FUNC31:
	ldr r10, C_add
	str r8, [r10]
	ldr r11, C_add
	ldr r12, [r11]
	ldr r1, TEMP
	str r12, [r1]
	ldr r2, C_add
	ldr r1, [r2]
	ldr r0, string1
	bl printf
	pop {ip, pc}

A_add: .word A_var

b_add: .word b_var

C_add: .word C_var

TEMP: .word TEMP1

string1: .word string_1

string2: .word string_2

.data

A_var: .word 0

b_var: .word 0

C_var: .word 0

TEMP1: .word 0

string_1: .asciz "%i\n"

string_2: .asciz "%i" 
