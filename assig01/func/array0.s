#THIS PROGRAM SAVE AND LOAD VALUES FROM ARRAY

.data

	array:	.space 12
.text
	main:
		addi $s0, $zero, 4
		addi $s1, $zero, 10
		addi $s2, $zero, 12
		
		#store the values in RAM
		#index = $t0
		
		#method 1:
		##addi $t0, $zero, 0
		
		sw $s0, array($t0)
		sw $s1, array+4($t0)
		sw $s2, array+8($t0)
		
		#method 2:
		addi $t0, $zero, 0
		
		sw $s0, array($t0)
			addi $t0, $t0, 4
		sw $s1, array($t0)
			addi $t0, $t0, 4
		sw $s2, array($t0)

		#retriving value
		lw $t6, array($zero)	#retriving first index
		lw $t7, array+4  	#retriving second index