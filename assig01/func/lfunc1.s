.data

.text
	main:
	
		addi $a1, $zero, 50
		addi $a2, $zero, 100
		
       	 	jal addNumbers

		li $v0, 1
		addi $a0, $v1, 0
		syscall


    	# Tell the system that the program is done. 
    	li $v0, 10
    	syscall
    
	addNumbers:
		add $v1, $a1, $a2	#store the number in v1 if it's the return value
        	jr $ra