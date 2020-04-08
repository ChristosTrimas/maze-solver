.data
.globl printLabyrinth
.globl makeMove
.globl map
.globl tmp

map:	.asciiz "I.IIIIIIIIIIIIIIIIIIII....I....I.......I.IIII.IIIII.I.I.III.I.II.I.....I..I..I.....II.I.III.II...II.I.IIII...I...III.I...I...IIIIII.IIIII.III.III.II.............I.I...IIIIIIIIIIIIIIII.I.III@...............I..IIIIIIIIIIIIIIIIIIIIIII"
		
tmp:		.space 100
		.align 2

labmessage:	.asciiz "Labyrinth:"
newline:	.asciiz "\n"
#////////////////////////////////////////////////////////////////////

.text

.globl main

main:

	li $s1, 231	#totalElements
	li $s3, 21	# W
	li $s4, 11	# H

	li $a0, 1	#startIndex
	jal makeMove
	
	jal printLabyrinth

	li $v0, 10	#end
	syscall
#///////////////////////////////////////////////////////////////////


printLabyrinth:
	addi $sp,$sp,-8			#δημιουργια δυο "word" στο stack
	sw $a0,0($sp)			#αποθηκευση του ορισματος της συναρτησης στα πρωτα 4 bytes
	sw $ra,4($sp)			#αποθηκευση του καταχωρητη ra στα επομενα 4
	
	li $t0, 0	#i
	li $t1, 0	#j
	li $t2, 0	#k

	li $v0, 4
	la $a0, labmessage
	syscall
	
	li $v0,4
	la $a0, newline
	syscall

	for_label_1:
	bge $t0,$s4,exit_label
	li $t1,0
	for_label_2:
	bge $t1,$s3,continue_label
	lb $t3, map($t2)	
	sb $t3, tmp($t1)		#προσθηκη μιας σειρας στοιχειων του λαβυρινθου


	addi $t1,$t1,1
	addi $t2,$t2,1
	j for_label_2

	continue_label:
	li $v0,4
	la $a0,tmp			#εκτύπωση κάθε φορά του temp
	syscall

	li $v0,4
	la $a0,newline
	syscall

	addi $t0,$t0,1
	j for_label_1

	exit_label:
	lw $a0,0($sp)			#φορτωση αρχικων τιμων
	lw $ra,4($sp)
	addi $sp,$sp,8			#απελευθερωση του stack
	jr $ra
	
	
	

#/////////////////////////////////////////////////////////////////////////
makeMove:
	addi $sp,$sp,-8			#δημιουργια δυο "word" στο stack
	sw $a0,0($sp)			#αποθηκευση του ορισματος της συναρτησης στα πρωτα 4 bytes
	sw $ra,4($sp)			#αποθηκευση του καταχωρητη ra στα επομενα 4
	
	if_1_label:
	bgez $a0,scnd		
	j end_if
	scnd:
	blt $a0,$s1,if_label
	j end_if
	

	if_label:
	la $t0,map
	add $t1,$t0,$a0
	lb $t0,0($t1)

	bne $t0,46,el_if		#ελεγχος για το σωστο path
	li $t0,42
	sb $t0,0($t1)			#αντικατασταση του με *
	jal printLabyrinth		#κληση της συναρτησης για εκτυπωση
	lw $a0,0($sp)

	if_1:
	addi $a0,$a0,1			#index=index+1
	jal makeMove
	lw $a0,0($sp)

	bne $v0,1,if_2			#if(makeMove(index+1)==1),ελεγχος του δεξιου στοιχειου
	la $t3,map
	add $t3,$t3,$a0
	li $t0,35
	sb $t0,0($t3)			#map[index]='#'
	li $v0,1
	j ret_label

	if_2:
	addi $a0,$a0,21
	jal makeMove
	lw $a0,0($sp)

	bne $v0,1,if_3			#if(makeMove(index+W)==1),ελεγχος του κάτω στοιχειου
	la $t3,map
	add $t3,$t3,$a0
	li $t0,35
	sb $t0,0($t3)			#map[index]='#'
	li $v0,1
	j ret_label

	if_3:
	addi $a0,$a0,-1
	jal makeMove
	lw $a0,0($sp)

	bne $v0,1,if_4			#if(makeMove(index-1)==1),ελεγχος του αριστερου στοιχειου
	la $t3,map
	add $t3,$t3,$a0
	li $t0,35
	sb $t0,0($t3)			#map[index]='#'
	li $v0,1
	j ret_label

	if_4:
	addi $a0,$a0,-21
	jal makeMove
	lw $a0,0($sp)

	bne $v0,1,end_if		#if(makeMove(index-W)==1),ελεγχος του πανω στοιχειου
	la $t3,map
	add $t3,$t3,$a0
	li $t0,35
	sb $t0,0($t3)			#map[index]='#'
	li $v0,1
	j ret_label

	el_if:
	la $t0,map
	add $t1,$t0,$a0
	lb $t0,0($t1)

	bne $t0,64,end_if		#ευρεση του τελους
	li $t0,37			
	sb $t0,0($t1)			#αντικατασταση με το % συμβολο
	jal printLabyrinth
	li $v0,1
	j ret_label

	end_if:
	li $v0,0
	
	ret_label:
	lw $a0,0($sp)			#φορτωση αρχικων τιμων
	lw $ra,4($sp)			
	addi $sp,$sp,8			#απελευθερωση του stack
	jr $ra













