.data
.text

	main:
		sw $fp, -4($sp)		# push $fp onto stack
		la $fp, -4($sp)		# set up $fp for this function
		sw $ra, -4($fp)		# save return address
		sw $s0, -8($fp)		# save $s0 to use as ... char ret
		addi $sp, $sp, -12	# move $sp to top of stack
		
		#load arguments
		li $a0, 1	#a0 to use as int old
		li $a1, 4	#a1 to use as int nn
		

		beq $a0, 1, IF_OLD1	#if (old == 1)
		beq $a1, 3, IF_N3
		j ELSE
		IF_OLD1:
			blt $a1, 2, IF_NN_LESS2		#if (nn < 2)
			beq $a1, 2, ELSE_IF_NN23	#else if (nn == 2 
			beq $a1, 3, ELSE_IF_NN23	#	|| nn == 3)
			j ELSE1				#else
			IF_NN_LESS2:
				li $s0, 0	#ret = 0
				j EXIT_IF0
			ELSE_IF_NN23:
				li $s0, 1	#ret = 1
				j EXIT_IF0
			ELSE1:
				li $s0, 0	#ret = 0
				j EXIT_IF0


		IF_N3:
			li $s0, 1	#ret = 1
			j EXIT_IF0
		ELSE:
			li $s0, 0	#ret = 0
		EXIT_IF0:
		
		
		move $v1, $s0 #return ret in $v1
		

		lw $s0, -8($fp)		# restore $s0 value
		lw $ra, -4($fp)		# restore $ra for return
		la $sp, 4($fp)		# restore $sp (remove stack frame)
		lw $fp, ($fp)		# restore $fp (remove stack frame)

		#jr $ra		# return 0