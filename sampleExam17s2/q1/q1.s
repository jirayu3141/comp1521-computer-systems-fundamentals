# COMP1521 17s2 Final Exam
# void colSum(m, N, a)

   .text
   .globl colSum

# params: m=$a0, N=$a1, a=$a2
colSum:
# prologue
   addi $sp, $sp, -4
   sw   $fp, ($sp)
   la   $fp, ($sp)
   addi $sp, $sp, -4
   sw   $ra, ($sp)
   addi $sp, $sp, -4
   sw   $s0, ($sp)
   addi $sp, $sp, -4
   sw   $s1, ($sp)
   addi $sp, $sp, -4
   sw   $s2, ($sp)
   addi $sp, $sp, -4
   sw   $s3, ($sp)
   addi $sp, $sp, -4
   sw   $s4, ($sp)
   addi $sp, $sp, -4
   sw   $s5, ($sp)
   # if you need to save more than six $s? registers
   # add extra code here to save them on the stack

# suggestion for local variables (based on C code):
# m=#s0, N=$s1, a=$s2, row=$s3, col=$s4, sum=$s5

   # add code for your colSum function here
	addi	$s0, $a0, 0
	addi    $s1, $a1, 0
	addi    $s2, $a2, 0
	addi	$s3, $a3, 0
	addi    $s4, $a4, 0
	addi    $s5, $a5, 0

	addi	$t0, $t0, 0					# $t0 is index row
	addi 	$t1, $t1, 0					# $t1 is index col
	addi	$t2, $t2, 0					# $t2 is array index
	
col_sum_loop:            
    bgt     $s4, $s1, exit_col_sum_for  # for (col = 0; col < N; col++) {
    
    addi    $s5, $zero, 0               # sum = 0
    
    addi    $s3, $zero, 0               # row = 0
col_sum_loop2:
    bgt     $s3, $s1, col_sum_end_loop2 # for (row = 0; row < N; row++)
    
    muli	$t2, $s3, 4
    add		$t2, $t2, $s4
    
    
    
    
    
    mul		$

    
    addi    $s3, $s3, 1                 # row++
    addi	$t0, $t0, 4					# row_index++
    j	col_sum_loop2
col_sum_end_loop2:                                   
    
    addi	$s4, $s4, 0                 # col++
    addi	$t1, $t1, 4					# col_index++
    j	col_sum_loop
col_sum_end_loop:   
   
   

# epilogue
   # if you saved more than six $s? registers
   # add extra code here to restore them
   lw   $s5, ($sp)
   addi $sp, $sp, 4
   lw   $s4, ($sp)
   addi $sp, $sp, 4
   lw   $s3, ($sp)
   addi $sp, $sp, 4
   lw   $s2, ($sp)
   addi $sp, $sp, 4
   lw   $s1, ($sp)
   addi $sp, $sp, 4
   lw   $s0, ($sp)
   addi $sp, $sp, 4
   lw   $ra, ($sp)
   addi $sp, $sp, 4
   lw   $fp, ($sp)
   addi $sp, $sp, 4
   j    $ra

