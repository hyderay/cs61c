.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
#   a0 (int*) is the pointer to the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   None
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# ==============================================================================
relu:
    # Prologue
    addi t4, x0, 1
    blt a1, t4, error
    add t0, x0, x0
    
loop_start:
    bge t0, a1, loop_end
    slli t1, t0, 2
    add t2, a0, t1
    lw t3, 0(t2)
    blt x0, t3, loop_continue
    add t3, x0, x0
    sw t3, 0(t2)
    addi t0, t0, 1
    j loop_start
    
loop_continue:
    addi t0, t0, 1
    j loop_start

loop_end:
    

    # Epilogue


    jr ra
    
error:
    li a0, 36
    j exit
