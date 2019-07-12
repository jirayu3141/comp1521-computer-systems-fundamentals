.data
    prompt:     .asciiz "Enter your age: "
    message:    .asciiz "Your Age is: "



.text
main:
    #promp user
    li $v0, 4 #print string
    la $a0, prompt
    syscall

    #ask for user input
    li $v0, 5   #input integer
    syscall

    #store result in t0
    move $t0, $v0

    #disply :Your age is"
    li $v0, 4
    la $a0, message
    syscall

    #print age
    li $v0, 1
    move $a0, $t0
    syscall

    li $v0, 10
    syscall