   .data
john:                     # Person john;
   .word 5000035          # id @ offset 0
   .asciiz "Shepherd"     # family @ offset 4
   .space 6               #  make up to 15 bytes
   .asciiz "John"         # given @ offset 19
   .space 10              #  make up to 15 bytes
   .align 2               # then align to addr%4

   .text
   .globl main
main:
   # prologue
   sw    $fp, -4($sp)      # push $fp
   la    $fp, -4($sp)      # reset $fp
   sw    $ra, -4($fp)      # push $ra
   add   $sp, $sp, -8
   # function body
   la    $a0, john
   jal   showPerson        # showPerson(&john)
   nop
   # epilogue
   lw    $ra, -4($fp)      # $ra = pop
   lw    $fp, ($fp)        # $fp = pop
   add   $sp, $sp, 8
   j     $ra

# void showPerson(Person *p)
# {
#    printf("%d ", p->id_no);
#    printf("%s, %s\n", p->family, p->given);
# }
showPerson:
   # prologue
   sw    $fp, -4($sp)      # push $fp
   la    $fp, -4($sp)      # reset $fp
   sw    $ra, -4($fp)      # push $ra
   sw    $s0, -8($fp)      # push $ra
   addi  $sp, $sp, -12

   # function body
   move  $s0, $a0

   lw    $a0, 0($s0)      # s->id_no
   li    $v0, 1           # printf "%d"
   syscall               
   li    $a0, ' '
   li    $v0, 11          # printf " "
   syscall
   la    $a0, 4($s0)      # s->family
   li    $v0, 4           # printf "%s"
   syscall
   li    $a0, ','
   li    $v0, 11          # printf ","
   syscall
   li    $a0, ' '
   li    $v0, 11          # printf " "
   syscall
   la    $a0, 19($s0)     # s->given
   li    $v0, 4           # printf "%s"
   syscall
   li    $a0, '\n'
   li    $v0, 11          # printf "\n"
   syscall

   # epilogue
   lw    $s0, -8($fp)     # $s0 = pop
   lw    $ra, -4($fp)     # $ra = pop
   lw    $fp, ($fp)       # $fp = pop
   addi  $sp, $sp, 12
   jr    $ra
