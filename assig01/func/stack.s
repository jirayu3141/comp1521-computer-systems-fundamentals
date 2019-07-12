.data
	newLine: .asciiz "\n"
.text
	main:
		addi $s0, $zero, 10

		
		jal allocateStack
		
		#print new line
		li $v0, 4
		la $a0, newLine
		syscall

		#print value
		li $v0, 1
		move $a0, $s0
		syscall

		#print new line
		li $v0, 4
		la $a0, newLine
		syscall



	li $v0, 10
	syscall

	##allocate stack##

	allocateStack:
		addi $sp, $sp, -4
		sw $s0, 0($sp)

		#after this point, s0 is saved onto the stack, we are allowed to do whatever we want to s0.

		addi $s0, $s0, 30

		#print new value in funciton
		li $v0, 1
		move $a0, $s0
		syscall

		lw $s0, 0($sp)	#load back the data from ram
		addi $sp, $sp, 4	#change the stack pointer back to original value
	
		jr $raa