        .text
        .globl  main

main:   #input the string
        li      $v0,8          # service code
        la      $a0,str        # address of buffer
        li      $a1,128        # buffer length 
        syscall  


        .data
str:    .space  128            # character buffer            