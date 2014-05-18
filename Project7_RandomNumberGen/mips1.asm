# Description: Generates pseudo random numbers using linear congruence.
# Inputs: Seed, Min, Max, Number of Random Values
# Output: Random Numbers based on Inputs

.data	#Data declaration section
#Input Variables
inputSeed:	.asciiz		"Please enter an initial seed greater than 3000: "
inputMin:	.asciiz		"Please enter a minimum value of greater than 1: "
inputMax:	.asciiz		"Please enter a maximum value less than 1000: "
inputNumber: 	.asciiz		"How many random numbers should I generate? The request should be between 1 and 30: "
#Output Formating
outputSep:	.asciiz		"; " 
#Variables for Calculations and Outputs
prime:		.word		2385367 #very large arbitrary prime number
seed:		.word		0 
numOf:		.word		0
min:		.word		0
max:		.word		0
mod:		.word		0
		.text
		.globl main #main function is global
		.ent main #Begin procedure

#Code starts here with main function
main: 
#Handles seed
handleSeed:
	la	$a0, inputSeed #output message for seed
	li	$v0, 4 
	syscall 	
	li	$v0, 5 #input seed 
	syscall	
	sw	$v0, seed #save register to memory
	li	$t0, 3001 #must be greater than
	blt	$v0, $t0, handleSeed #error handling	 
#Handles the number of random numbers to be generated 
handleNum:
	la	$a0, inputNumber #output message for no. of numbers
	li	$v0, 4
	syscall 
	li	$v0, 5 #input number
	syscall 
	sw	$v0, numOf #save register to memory
	li	$t0, 1 #must be greater than
	ble	$v0, $t0, handleNum
	li	$t0, 30 #must be less than
	bgt	$v0, $t0, handleNum #error handling
#Handles the Min value
handleMin:
	la	$a0, inputMin  #output message for Min
	li	$v0, 4
	syscall
	li	$v0, 5 #input Min
	syscall			
	sw	$v0, min #save register to memory
	li	$t0, 2 #must be greater than
	blt	$v0, $t0, handleMin #error handling
#Handles the Min value
handleMax:
	la	$a0, inputMax #output message for Min
	li	$v0, 4
	syscall
	li	$v0, 5 #input Min
	syscall	
	sw	$v0, max #save register to memory
	li	$t0, 999  #must be less than
	bgt	$v0, $t0, handleMax #error handling
LinCong:
	#load
	lw	$t0, max
	lw	$t1, min
	#find range
	sub	$t2, $t0, $t1
	#add immediate for adding a constant 
	addi	$t2, $t2, 1
	sw	$t2, mod
	#counter
	li	$t7, 1
generateNum:
	#load prime and seed
	lw	$t0, prime
	lw	$t1, seed
	#prime * seed
	mult 	$t1, $t0
	#move result of multiplication for use
	mflo	$t2
	mfhi	$t3	
	#load mod
	lw	$t4, mod
	#remainder/modulus
	rem	$t3, $t3, $t4
	addi	$t3, $t3, 1
	abs	$t5, $t2
	sw	$t5, seed	
	#return random number
	move	$a0, $t3
	li	$v0, 1
	syscall
	#print output formatting
	la	$a0, outputSep
	li	$v0, 4
	syscall
	#increment counter and end when the numbers are printed
	addi	$t7, $t7, 1
	lw	$t5, numOf 
	ble	$t7, $t5, generateNum
	#end program
	li $v0, 10
	syscall
.end main
