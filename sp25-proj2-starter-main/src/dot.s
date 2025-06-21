.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int arrays
# Arguments:
#   a0 (int*) is the pointer to the start of arr0
#   a1 (int*) is the pointer to the start of arr1
#   a2 (int)  is the number of elements to use
#   a3 (int)  is the stride of arr0
#   a4 (int)  is the stride of arr1
# Returns:
#   a0 (int)  is the dot product of arr0 and arr1
# Exceptions:
#   - If the number of elements to use is less than 1,
#     this function terminates the program with error code 36
#   - If the stride of either array is less than 1,
#     this function terminates the program with error code 37
# =======================================================
dot:
    li t0, 1  
    blt a2, t0, error1
    blt a3, t0, error2
    blt a4, t0, error2
    li t0, 0  # t0 -- the index of the first array
    li t1, 0  # t1 -- the index of the second array
 
    li a5, 0  # a5 -- the sum
    
loop_start:
    beq a2, x0, loop_end
    
    
    slli t2, t0, 2
    add t2, a0, t2
    lw t3, 0(t2)  # t3 stores the current value of arr1
    
    slli t2, t1, 2
    add t2, a1, t2
    lw t4, 0(t2)  # t4 stores the current value of arr2
    
    mul t2, t3, t4
    add a5, a5, t2
    
    add t0, t0, a3
    add t1, t1, a4
    addi a2, a2, -1
    j loop_start
    
loop_end:
    add a0, x0, a5
    jr ra
    
error1:
    li a0, 36
    j exit

error2:
    li a0, 37
    j exit