# COMP1521 19t2 ... Game of Life on a NxN grid
#
# Written by <<YOU>>, June 2019

## Requires (from `boardX.s'):
# - N (word): board dimensions
# - board (byte[][]): initial board state
# - newBoard (byte[][]): next board state

## Provides:
	.globl	main
	#.globl	decideCell
	#.globl	neighbours
	#.globl	copyBackAndShow


########################################################################

#.DATA
	.data
	iteration: .asciiz "# Iterations: "


# .TEXT <main>
	.text
	main:

# Frame:	...
# Uses:		...
# Clobbers:	...

# Locals:	...

# Structure:
#	main
#	-> [prologue]
#	-> ...
#	-> [epilogue]

# Code:

	# Your main program code goes here.  Good luck!
	#print iterations
	#13: printf("# Iterations: ")
	la $t0, iteration
	jal print_stirng

	#14: scanf("%d", &maxiters);
	#maxiters is saved in $s1
	li $v0, 5
	syscall
	move $s1, $v0
	
	#16: for (int n = 1; n <= maxiters; n++) 
	# n = 1 (saved in t0)
	addi $t0, $zero, 0
	while0:
		bgt $t0, 10, exit0

		add $t0, $t0, 1
		j while

	exit0:
	
	#end program
	li $v0, 10
	syscall
main__post:
	jr	$ra

	# Put your other functions here

print_string:
	li $v0, 4
	move $a0, $t0
	syscall
	jr $ra
print_int:
	li $v0, 1
	