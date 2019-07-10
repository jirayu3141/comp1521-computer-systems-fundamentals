    .data
msg1:   .asciiz "n = "
msg2:   .asciiz "n! = "
eol:    .asciiz "\n"
##main() function
    .text
    .globl main
main:

  	# code for main()
	li	$s0, 12		# n = 0

	la	$a0, msg1
	li	$v0, 4
	syscall			# printf("n  = ")

	li	$v0, 5
	syscall			# scanf("%d", into $v0)

	### TODO: your code for the body of main() goes here

	la	$a0, msg2
	li	$v0, 4
	syscall			# printf("n! = ")

	move	$a0, $s0	# assume $s2 holds n!
	li	$v0, 1
	syscall			# printf("%d", fac)

	la	$a0, eol
	li	$v0, 4
	syscall			# printf("\n")