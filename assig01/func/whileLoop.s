.data
    space: .asciiz ", "
.text
    main:

    #i = 0
    addi $t0, $zero, 0

    while:
        bgt $t0, 10, exit
        jal printNumber
        add $t0, $t0, 1     #i++
        j while
    exit:


    li $v0, 10
    syscall

    printNumber:
        li $v0, 1
        #add $a0, $t0, $zero
        move $a0, $t0
        syscall

        jr $ra