### COMP1521 19t2 ... week 05 lab
### Compute factorials -- recursive function version

## Global data
	.data
msg1:	.asciiz "n  = "
msg2:	.asciiz "n! = "
eol:	.asciiz "\n"

### main() function
	.text
	.globl	main
main:
	# Set up stack frame
	sw	$fp, -4($sp)	# push $fp onto stack
	la	$fp, -4($sp)	# set up $fp for this function
	sw	$ra, -4($fp)	# save return address
	sw	$s0, -8($fp)	# save $s0 to use as ... int n
	addi	$sp, $sp, -12	# reset $sp to last pushed item

	# code for main()
	li	$s0, 0

	la	$a0, msg1
	li	$v0, 4
	syscall			# printf("n  = ")

	li	$v0, 5
	syscall			# scanf("%d", into $v0)
	move	$s0, $v0
	move	$a0, $s0	#         + from $s0
	li    $t1, 1    # $t1 = 1
	jal	fac		# % = fac(n)
	nop	#[branch delay] # |
	move	$s0, $v0	# + into $s0; don't need n now

	la	$a0, msg2
	li	$v0, 4
	syscall			# printf("n! = ")
    
    move    $s0, $t1
	move	$a0, $s0	# assume $s0 holds n!
	li	$v0, 1
	syscall			# printf ("%d", tmp)

	la	$a0, eol
	li	$v0, 4
	syscall			# printf("\n")

	# clean up stack frame
	lw	$s0, -8($fp)	# restore $s0 value
	lw	$ra, -4($fp)	# restore $ra for return
	la	$sp, 4($fp)	# restore $sp (remove stack frame)
	lw	$fp, ($fp)	# restore $fp (remove stack frame)

	li	$v0, 0
	jr	$ra		# return 0


### fac() function
	.text
	.globl	fac
fac:
	## TODO: set up stack frame
	sw  $fp, -4($sp)
	la  $fp, -4($sp)
	sw  $ra, -4($fp)
	addi $sp, $sp -8

	## TODO: code for recursive fac()
	li  $t0, 1
	li  $t2, 0
	ble $s0, $t2, exit
	beq $t0, $s0, exit
	mul $t1, $s0, $t1
	addi $s0, $s0, -1
	
	jal fac
	
    exit:
	## TODO: clean up stack frame
	lw  $ra, -4($fp)
	la  $sp, 4($sp)
    lw  $fp  ($fp)
	jr	$ra		# ... and return
