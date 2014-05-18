# Description: Sorts 10 random digits or letters using Bubble Sort.
# Inputs: Up to 10 digits or letters
# Output: Sorted digits

.data	#Data declaration section
#Variables
inputNums: 	.asciiz 	"\n\nPlease enter up to 10 digits: "
newLine: 	.asciiz 	"\n"     
numsString: 	.asciiz 	"           "				# for holding the numbers

.text 

#Code starts here with main function
main:
    la 	$a0, inputNums   # prompt message for numbers
    li 	$v0, 4        
    syscall         
    la $a0,numsString  # load string to hold numbers
    li $a1,11         # load input+1 into a1
    li $v0,8          # read input
    syscall

    li $s7,10           # s7 upper index

#functions 
    jal caps  
    jal BSort
    jal PrintNums
    j exit

#Uses ASCII codes to sort letters (makes lowercase uppercase)
caps:
    la $s0, numsString    # load the input
    add $t6,$zero,$zero  # index = 0

    #conditional branch to decide if loop ends
    upper:
        beq $t6,$s7,done 
        add $s2,$s0,$t6 #load input
        lb  $t1,0($s2) #load into mem

        sgt  $t2,$t1,96 #see if input is lowercase
        slti $t3,$t1,123 
        and $t3,$t2,$t3 

        beq $t3,$zero,isUpper #uppercase, don't bother
        addi $t1,$t1,-32
        sb   $t1, 0($s2)

        isUpper:
        addi $t6,$t6,1 #increment and jump
        j lupper

#Bubble Sort
BSort:   
    add $t0,$zero,$zero #counter for 2nd loop
    loop:
        beq $t0,$s7,done #conditional branch to decide if loop ends

        sub $t7,$s7,$t0 #upperbound of first loop
        addi $t7,$t7,-1

        add $t1,$zero,$zero #counter for 1st loop

        inLoop: #1st loop
            beq $t1,$t7,continue #conditional branch to decide if loop ends
            add $t6,$s0,$t1 #input array
            lb  $s1,0($t6) #load
            lb  $s2,1($t6)

            sgt $t2, $s1,$s2 #if curr element is greater than next, swap
            beq $t2, $zero, good #else, don't swap
            sb  $s2,0($t6) #store
            sb  $s1,1($t6)

            good:
            addi $t1,$t1,1 #increment 1st loop
            j inLoop #jump

        continue:
        addi $t0,$t0,1 #increment 2nd loop
        j loop #jump

PrintNums:
    la $a0,newLine #print
    li $v0,4
    syscall 

    add $t6,$zero,$zero #cursor at beginning of loop

    printArray:
        beq $t6,$s7,done #conditional branch to decide if loop ends
        add $t1,$s0,$t6 #load and print array
        lb $a0, 0($t1)  
        li $v0, 11      
        syscall         

        addi $t6,$t6,1  #increment and jump
        j printArray
done:
    jr $ra
exit:
