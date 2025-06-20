.globl argmax

.text
# =================================================================
# FUNCTION: Given a int array, return the index of the largest
#   element. If there are multiple, return the one
#   with the smallest index.
# Arguments:
#   a0 (int*) is the pointer to the start of the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   a0 (int)  is the first index of the largest element
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# =================================================================
argmax:
    # Prologue
    li t0, 1
    blt a1, t0, error
    li t0, 0
    li t1, -9999999
    li t4, -1

loop_start:
    beq t0, a1, loop_end
    slli t3, t0, 2
    add t2, t3, a0
    lw t2, 0(t2)
    blt t2, t1, loop_continue
    add t1, t2, x0
    add t4, t0, x0
    addi t0, t0, 1
    j loop_start

loop_continue:
    addi t0, t0, 1
    j loop_start

loop_end:
    # Epilogue
    mv a0, t4
    jr ra
    
error:
    li a0 36
    j exit
