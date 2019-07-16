# board2.s ... Game of Life on a 15x15 grid

	.data

N:	.word 15  # gives board dimensions

board:
	.byte 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0
	.byte 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0
	.byte 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0
	.byte 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0
	.byte 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1
	.byte 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0
	.byte 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0
	.byte 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0
	.byte 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0
	.byte 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0
	.byte 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1
	.byte 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0
	.byte 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0
	.byte 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0
	.byte 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0

newBoard: .space 225


.text
	main:
	# Set up stack frame.
	sw $fp, -4($sp)		# push $fp onto stack
	la $fp, -4($sp)		# set up $fp for this function
	sw $ra, -4($fp)		# save return address
	sw $s0, -8($fp)		# save $s0 to use as ... int nn
	sw $s1, -12($fp)	# save $s1 to use as ... int x
	sw $s2, -16($fp)	# save $s2 to use as ... int y
	addi $sp, $sp, -20	# move $sp to top of stack
	
	#load all the arguments
	addi $a0, $zero, 0	#i
	addi $a1, $zero, 0	#j
	lw $a2, N		#N
	addi $t7, $a2, -1		# $t7 as N-1
	la $a3, board
	#addi $a2, $a2, -1
	addi $s0, $zero, 0	# int nn = 0
	addi $s1, $zero, -1	# int x = -1
	
	

	while_neighbours0:
	bgt $s1, 1, exit_neighbours0	# for (int x = -1; x <= 1; x++)
		addi $s2, $zero, -1 	#int y = -1
		while_neighbours1: 	# for (int y = -1; y <= 1; y++)
		bgt $s2, 1, exit_neighbours1
			add $t0, $a0, $s1	#if (i + x < 0 || i + x > N - 1) continue;
			bltz $t0, y_plus_plus
			bgt $t0, $t7 , y_plus_plus
			
			add $t1, $a1, $s2	#if (j + y < 0 || j + y > N - 1) continue;
			bltz $t1, y_plus_plus
			bgt $t1, $t7, y_plus_plus
			
			
			beqz $s1, ZERO	#if (x == 0 && y == 0) continue;
			bnez $s1, ELSE_NOT_ZERO
			ZERO:
			beqz $s2, y_plus_plus
			ELSE_NOT_ZERO:
			
			# $t2 = row 
			#i + x
			add $t2, $a0, $s1
			mul $t2, $t2, $a2
			# $t3 = column
			add $t3, $a1, $s2
			
			#$t4 = address index
			add $t4, $t2, $t3
			#$t4 = actual address
			add $t4, $a3, $t4
			lb $t4, ($t4)
			bne $t4, 1, y_plus_plus	# if (board[i + x][j + y] == 1) nn++;
			addi $s0, $s0, 1		
			
		y_plus_plus:
		addi $s2, $s2, 1	#y++
		j while_neighbours1
		
		exit_neighbours1:

		
	addi $s1, $s1, 1	# x++
	j while_neighbours0
	exit_neighbours0:
	
	#return value
	move $v0, $s0


	# clean up stack frame
	lw $s2, -16($fp)	# restore $s2 value
	lw $s1, -12($fp)	# restore $s1 value
	lw $s0, -8($fp)		# restore $s0 value
	lw $ra, -4($fp)		# restore $ra for return
	la $sp, 4($fp)		# restore $sp (remove stack frame)
	lw $fp, ($fp)		# restore $fp (remove stack frame)

	#jr $ra		# return 0