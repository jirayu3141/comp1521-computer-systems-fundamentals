#PRINTING ARRAY WITH WHILE LOOP

.data

	array:	.space 12
	newLine: .asciiz "\n"
.text
	main:
		#initialize array
		addi $s0, $zero, 4
		addi $s1, $zero, 10
		addi $s2, $zero, 12
		
		
		#save value to ram
		addi $t0, $zero, 0
		
		sw $s0, array($t0)
			addi $t0, $t0, 4
		sw $s1, array($t0)
			addi $t0, $t0, 4
		sw $s2, array($t0)
		
		
		#print values with while loop
		addi $t0, $zero, 0	#init i = 0
		while:
			beq $t0, 12, exit
			
			#load to reigister
 			lw $t6, array($t0)
			#print current number
			li $v0, 1
			move $a0, $t6
			syscall
			#print new line
			li $v0, 4
			la $a0, newLine
			syscall
			
			#i++
			addi $t0, $t0, 4
			
			j while
		exit:
			#end of program
			la $v0, 10
			syscall