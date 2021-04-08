# Makefile to assemble the arm program
# The name of the file should be without extension
program:
	as ${name}.s -o ${name}.o
	gcc ${name}.o -o ${name} -g
