# int main(int argc, char *argv[])
# {
#    for (int i = 1; i < argc; i++)
#       printf("%s ", argv[i]);
#    printf("\n");
#    return 0;
# }
   .text
   .globl main
main:
   # build stack frame for main()
   # reg usage: $s0=argc, $s1=argv, $s2=i
   sw    $fp, -4($sp)
   la    $fp, -4($sp)
   sw    $ra, -4($fp)
   sw    $s0, -8($fp)
   sw    $s1, -12($fp)
   sw    $s2, -16($fp)
   addi  $sp, $sp, -20

   # body of main()

   ...

   li    $a0, '\n'
   li    $v0, 11
   syscall

   # pop main()'s stack frame
   lw    $s2, -16($fp)
   lw    $s1, -12($fp)
   lw    $s0, -8($fp)
   lw    $ra, -4($fp)
   addi  $sp, $sp, 20
   lw    $fp, ($fp)
   j     $ra 

