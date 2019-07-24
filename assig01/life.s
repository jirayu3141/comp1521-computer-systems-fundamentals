# board1.s ... Game of Life on a 10x10 grid

	.data

N:	.word 10  # gives board dimensions

board:
	.byte 1, 0, 0, 0, 0, 0, 0, 0, 0, 0
	.byte 1, 1, 0, 0, 0, 0, 0, 0, 0, 0
	.byte 0, 0, 0, 1, 0, 0, 0, 0, 0, 0
	.byte 0, 0, 1, 0, 1, 0, 0, 0, 0, 0
	.byte 0, 0, 0, 0, 1, 0, 0, 0, 0, 0
	.byte 0, 0, 0, 0, 1, 1, 1, 0, 0, 0
	.byte 0, 0, 0, 1, 0, 0, 1, 0, 0, 0
	.byte 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
	.byte 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
	.byte 0, 0, 1, 0, 0, 0, 0, 0, 0, 0

newBoard: .space 100
# COMP1521 19t2 ... Game of Life on a NxN grid
#
# Written by Jirayu Sirivorawong, June 2019

## Requires (from `boardX.s'):
# - N (word): board dimensions
# - board (byte[][]): initial board state
# - newBoard (byte[][]): next board state

## Provides:
	.globl	main
	.globl	decideCell
	.globl	neighbours
	.globl	copyBackAndShow
########################################################################
#.DATA
	.data
iteration: 	.asciiz "# Iterations: "
a_iteration: 	.asciiz "=== After iteration "
three_equal:	.asciiz " ===\n"
# .TEXT <main>
.text
main:
# Frame:	$fp, $ra, $s0, $s1, $s2, $s3, $s4, $s5, $s6, $s7
# Uses:		$a0, $a1, $v0, $s0, $s1, $s2, $s3, $s4, $s5, $s6, $s7
#main
# Clobbers:	$a0, $a1
# Locals:	
	#$s0 to use as N
	#$s0 to use as N
	#$s1 to use as maxiter
	#$s2 to use as n
	#$s3 to use as i
	#$s4 to use as j
	#$s5 to use as nn
	#$s6 to use as address of board
	#$s7 to use as address of newBoard

# Structure:
#	main
#	-> [prologue]
#	  -> main_n_cond  
#	    ->main_i_cond
#	      ->main_j_cond
#	    ->main_i_step
#	->main_n_step
#	-> [epilogue]
#
#	neighbours
#	-> [prologue]
#	  ->neighbours_x_cond
#	    ->neighbours_y_cond
#	      ->neighbours_eq_0
#	      ->neighbours_neq_0
#	    ->neighbours_y_step
#	  ->neighbours_x_step
#	-> [epilogue]
#
#	decideCell
#	-> [prologue]
#	-> decideCell_old_eq_1
#	  ->decideCell_old_eq_2
#	  ->decideCell_nn_lt_3
#	  ->decideCell_else1
#	->decideCell_else0
#	->decideCell_epi
#
#	copyBackAndShow
#	-> [prologue]
#	->copyBackAndShow_i_cond
#	  ->copyBackAndShow_j_cond
#	    ->copyBackAndShow_eq_0
#	    ->copyBackAndShow_neq_0
#	  ->copyBackAndShow_i_step
#	->copyBackAndShow_i_epi
#
#	print_string
#
#	print_int
# Code:
	#prologue
	sw 	$fp, -4($sp)
	la 	$fp, -4($sp)
	sw 	$ra, -4($fp)
	sw 	$s0, -8($fp)		# save $s0 to use as N
	sw 	$s1, -12($fp)		# save $s1 to use as maxiter
	sw 	$s2, -16($fp)		# save $s2 to use as n
	sw 	$s3, -20($fp)		# save $s3 to use as i
	sw 	$s4, -24($fp)		# save $s4 to use as j
	sw 	$s5, -28($fp)		# save $s5 to use as nn
	sw 	$s6, -32($fp)		# save $s6 to use as address of board
	sw 	$s7, -36($fp)		# save $s7 to use as address of newBoard
	addi 	$sp, $sp, -32		# move $sp to top of stack

	lw 	$s0, N			# load N
	la	$s6, board
	la 	$s7, newBoard

	
	#print iterations
	la 	$t0, iteration		
	move 	$a0, $t0		
	jal 	print_string		#13: printf("# Iterations: ")

	
	#maxiters is saved in $s1
	li 	$v0, 5		#14: scanf("%d", &maxiters);
	syscall
	move 	$s1, $v0

	#16: for (int n = 1; n <= maxiters; n++) 
	addi 	$s2, $zero, 1	# int n = 1 (saved in s2)
main_n_cond:	
	bgt 	$s2, $s1, main__post	#16: n <= maxiters

	## 2nd for loop ##
	# i = 0 (saved in s3)
	addi 	$s3, $zero, 0

main_i_cond:
	bge 	$s3, $s0, main_n_step	# 17: #for (int i = 0; j < N; j++) 
	addi	 $s4, $zero, 0		#int j = 0
main_j_cond:
	bge	 $s4, $s0, main_i_step	#for (int j = 0; j < N; j++) {

	#pass in arguments to neighbours(i, j)
	move 	$a0, $s3
	move 	$a1, $s4
	jal 	neighbours
	nop
	move 	$s5, $v0		# int nn = neighbours (i, j);

	#board[i][j]
	mul 	$t1, $s3, $s0 		#t1 is the row
	move 	$t2, $s4		#t2 is the column
	add 	$t2, $t2, $t1		#t2 is the array index
	add 	$t2, $t2, $s6		#t2 is now the address of board[i][j]
	lb 	$a0, ($t2)		#board[i][j] to be passed into decideCell
	move 	$a1, $s5		#nn to be passed to decideCell

	jal 	decideCell		#20: decideCell (board[i][j], nn)
	nop

	#organizing array index: line 20: newboard[i][j]
	mul 	$t1, $s3, $s0 		#t1 is the row
	move 	$t2, $s4		#t2 is the column
	add 	$t2, $t2, $t1		#t2 is the array index
	add 	$t2, $t2, $s7		#t2 is now the address of newBoard[i][j]
	sb 	$v1, ($t2)

	addi	 $s4, $s4, 1	#j++

	j 	main_j_cond
main_i_step:
	# } end of main_i_cond
	addi 	$s3, $s3, 1		#17: i++
	j 	main_i_cond		#22: }
main_n_step:
	la 	$a0, a_iteration	#23: printf ("=== After iteration ")
	jal 	print_string
	move 	$a0, $s2		#23: %d, n
	jal 	print_int
	la 	$a0, three_equal	#===\n"
	jal 	print_string				

	jal 	copyBackAndShow
	nop


	addi 	$s2, $s2, 1	#16: n++
	j 	main_n_cond
main__post:
	#epilogue
	lw 	$s7, -36($fp)	# restore $s7 value
	lw 	$s6, -32($fp)	# restore $s6 value
	lw 	$s5, -28($fp)	# restore $s5 value
	lw 	$s4, -24($fp)	# restore $s4 value
	lw 	$s3, -20($fp)	# restore $s3 value
	lw 	$s3, -20($fp)	# resture $s3 value
	lw 	$s2, -16($fp)	# restore $s2 value
	lw 	$s1, -12($fp)	# restore $s1 value
	lw 	$s0, -8($fp)	# restore $s0 value
	lw 	$ra, -4($fp)	# restore $ra for return
	la	 $sp, 4($fp)	# restore $sp (remove stack frame)
	lw 	$fp, ($fp)	# restore $fp (remove stack frame)

	#end program
	li 	$v0, 10
	syscall
	jr	$ra

neighbours:
	# Set up stack frame.
	sw 	$fp, -4($sp)		# push $fp onto stack
	la 	$fp, -4($sp)		# set up $fp for this function
	sw 	$ra, -4($fp)		# save return address
	sw 	$s0, -8($fp)		# save $s0 to use as ... int nn
	sw 	$s1, -12($fp)		# save $s1 to use as ... int x
	sw 	$s2, -16($fp)		# save $s2 to use as ... int y
	addi 	$sp, $sp, -20		# move $sp to top of stack

	#load all the arguments
	lw 	$a2, N		#N
	addi 	$t7, $a2, -1		# $t7 as N-1
	la 	$a3, board
	#addi $a2, $a2, -1
	addi 	$s0, $zero, 0	# int nn = 0
	addi 	$s1, $zero, -1	# int x = -1



neighbours_x_cond:
	bgt 	$s1, 1, neighbours_epi	# for (int x = -1; x <= 1; x++)
	addi	 $s2, $zero, -1 	#int y = -1
neighbours_y_cond: 	# for (int y = -1; y <= 1; y++)
	bgt 	$s2, 1, neighbours_x_step
	add 	$t0, $a0, $s1	#if (i + x < 0 || i + x > N - 1) continue;
	bltz	 $t0, neighbours_y_step
	bgt	 $t0, $t7 , neighbours_y_step

	add 	$t1, $a1, $s2	#if (j + y < 0 || j + y > N - 1) continue;
	bltz 	$t1, neighbours_y_step
	bgt 	$t1, $t7, neighbours_y_step


	beqz 	$s1, neighbours_eq_0	#if (x == 0 && y == 0) continue;
	bnez 	$s1, neighbours_neq_0
neighbours_eq_0:
	beqz 	$s2, neighbours_y_step
neighbours_neq_0:
	# $t2 = row 
	add 	$t2, $a0, $s1		#i + x
	mul	$t2, $t2, $a2
	add 	$t3, $a1, $s2		# $t3 = column
	add 	$t4, $t2, $t3		#$t4 = address index
	add 	$t4, $a3, $t4		#$t4 = actual address
	lb 	$t4, ($t4)
	bne 	$t4, 1, neighbours_y_step	# if (board[i + x][j + y] == 1) nn++;
	addi 	$s0, $s0, 1		#nn++	

neighbours_y_step:
	addi 	$s2, $s2, 1	#y++
	j 	neighbours_y_cond

neighbours_x_step:
	addi 	$s1, $s1, 1	# x++
	j 	neighbours_x_cond
neighbours_epi:
	#return value
	move $v0, $s0
	# clean up stack frame
	lw 	$s2, -16($fp)		# restore $s2 value
	lw 	$s1, -12($fp)		# restore $s1 value
	lw 	$s0, -8($fp)		# restore $s0 value
	lw 	$ra, -4($fp)		# restore $ra for return
	la 	$sp, 4($fp)		# restore $sp (remove stack frame)
	lw 	$fp, ($fp)		# restore $fp (remove stack frame)

	jr 	$ra			# return
decideCell:
	sw 	$fp, -4($sp)		# push $fp onto stack
	la 	$fp, -4($sp)		# set up $fp for this function
	sw 	$ra, -4($fp)		# save return address
	sw 	$s0, -8($fp)		# save $s0 to use as ... char ret
	addi 	$sp, $sp, -12		# move $sp to top of stack


	beq 	$a0, 1, decideCell_old_eq_1		#if (old == 1)
	beq 	$a1, 3, decideCell_n_eq_3
	j 	decideCell_else0
decideCell_old_eq_1:
	blt 	$a1, 2, decideCell_nn_lt_2		#if (nn < 2)
	beq 	$a1, 2, decideCell_nn_lt_3		#else if (nn == 2 
	beq 	$a1, 3, decideCell_nn_lt_3		#	|| nn == 3)
	j 	decideCell_else1					#else
decideCell_nn_lt_2:
	li 	$s0, 0	#ret = 0
	j 	decideCell_epi
decideCell_nn_lt_3:
	li 	$s0, 1	#ret = 1
	j 	decideCell_epi
decideCell_else1:
	li 	$s0, 0	#ret = 0
	j 	decideCell_epi
decideCell_n_eq_3:
	li 	$s0, 1	#ret = 1
	j 	decideCell_epi
decideCell_else0:
	li 	$s0, 0	#ret = 0
decideCell_epi:
	move $v1, $s0 #return ret in $v1

	lw 	$s0, -8($fp)		# restore $s0 value
	lw 	$ra, -4($fp)		# restore $ra for return
	la 	$sp, 4($fp)		# restore $sp (remove stack frame)
	lw 	$fp, ($fp)		# restore $fp (remove stack frame)

	jr 	$ra		# return 0	
copyBackAndShow:
	#load array address into $a0
	la 	$a1, board	#a1 is used as address of board
	la 	$a2, newBoard	#a2 is used as address of newboord
	lw 	$t0, N	# $t0 is used as N
	li 	$t1, 0	# i = 0 
copyBackAndShow_i_cond:
	bge 	$t1, $t0, copyBackAndShow_i_epi 	# for (int i = 0; i < N; i++) 

	li 	$t2, 0	#j = 0
copyBackAndShow_j_cond:
	bge 	$t2, $t0, copyBackAndShow_i_step	#for (int j = 0; j < N; j++)

	mul	 $t3, $t0, $t1		#t3 is row
	add 	$t4, $t3, $t2		#t4 is the array index

	add 	$t5, $a2, $t4		#t5 = newboard[i][j]
	lb 	$t5, ($t5)
	sb 	$t5, board($t4)		#board[i][j] = newboard[i][j];

	bnez 	$t5, copyBackAndShow_neq_0		# if (board[i][j] == 0)
copyBackAndShow_eq_0:
	li 	$v0, 11
	li 	$a0, '.'		# putchar ('.')
	syscall
	j 	copyBackAndShow_exit_if
			
copyBackAndShow_neq_0:		#else
	li 	$v0, 11
	li 	$a0, '#'		# putchar ('#')
	syscall	
copyBackAndShow_exit_if:
	addi 	$t2, $t2, 1	#j++
	j copyBackAndShow_j_cond
copyBackAndShow_i_step:
	li 	$v0, 11
	li 	$a0, '\n'	# putchar ('\n')
	addi 	$t1, $t1, 1
	syscall
	j 	copyBackAndShow_i_cond
copyBackAndShow_i_epi:
	jr 	$ra

print_string:
	li 	$v0, 4
	syscall
	jr 	$ra

print_int:
	li 	$v0, 1
	syscall
	jr 	$ra