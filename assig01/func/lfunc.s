.data
    message:    .asciiz "Hi everybody. \nMy name is Peter.\n"

.text
    main:
        jal displayMessage



    # Tell the system that the program is done. 
    li $v0, 10
    syscall


    displayMessage:
        li $v0, 4
        la $a0, message
        syscall

        jr $ra