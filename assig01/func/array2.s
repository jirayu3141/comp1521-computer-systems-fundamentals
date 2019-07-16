#2D array

.data
	myArray:	.word 2, 5
			.word 3, 7
	size:		.word 2
	.eqv DATA_SIZE 4
	
.text
	main:
		la $a0, myArray
		lw $a1, size
		
		jal sumDiagonal
		
		move $a0, $v0
		li $v0, 1
		syscall
		
		#EOF
		li $v0, 10
		syscall
		
	sumDiagonal:
		li $v0, 0	# sum = 0
		li $t0, 0	# $t0 is the index
		
		sumLoop:
			mul $t1, $t0, $a1	#t1 = rowIndex * colSize
			add $t1, $t1, $t0		#		+ colIndex
			mul $t1, $t1, DATA_SIZE		#		* dataSize
			add $t1, $t1, $a0		#	+ baseAddr
			
			lw $t2, ($t1)
			add $v0, $v0, $t2	#sum = sum + myArray [i][i]
			
			addi $t0, $t0, 1	#i++
			
			blt $t0, $a1, sumLoop	#if (i < size) loop, 
			
	jr $ra