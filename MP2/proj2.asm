;
;
;partners: xrouth2, pjj3
;Introductory Paragraph:
;This program uses stack to create a calculator
;that evaluates postfix expressions. The calculator
;can handle addition, subtraciton, multiplication, division,
;and exponent. The code evaluates each of the inputs by the user,
;because postfix notation only allows numbers from 0-9, and
;operators (i.e. *, +, -). Also postfix notation requires
;that the input be in the format where every operator comes
;after its pair of operands. For example, 2 + 3 would be
;represented as 2 3 + in postfix. If the input format is
;not valid then it prints out invalid expression. It is also
;important to note that the expression may be invalid at any point
;in the input. The way that the input is taken is that the code is
;printed to the screen and checks if the character is equals
;and if it is not then it will check if it is a space, if
;it is a space then it will read the next input, but if it is not
;a space then it will make sure that it is valid.
;If it is valid and an operand, then it will push it to the stack
;and if it is a operator then it will pop two values on the stack
;and execute the calculation. After the calculation is executed, the
;result is then pushed back on to the stack. The code continues
;until an equal sign is inputted by the user. Then it makes sure
;that there are no more values in the stack, or else it would be 
;a invalid expression. Then the code halts. This code also implements
;subroutines for each of the operators.

.ORIG x3000

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;your code goes here

;-------------------------------------------
; Read input; Use R5 to check values
;-------------------------------------------
EVALUATE	
	GETC ; Get character, store in R0
	OUT  ; Echo character out to R0
	
	LD R5, ASCII_NEQ
	ADD R5, R0, R5  ; Is input equals?
	BRz DONE_EVAL   ; If yes, finish evaluating
	
	LD R5, ASCII_NSPC
	ADD R5, R0, R5  ; Is input space?
	BRz EVALUATE     ; If yes, go to next input

;-------------------------------------------
; Read operation ;
;-------------------------------------------
; Runs through each of the possibilities of an input
CHECK_ADD ;checks for add operator
	LD R5, ASCII_NADD
	ADD R5, R0, R5  ; Input is 'plus'
	BRnp CHECK_MIN
	JSR POP
	AND R4, R0, R0
	JSR POP
	AND R3, R0, R0
	AND R5, R5, R5 ; Check for underflow
	BRp INV_INPUT
	JSR PLUS
	JSR PUSH
	BRnzp EVALUATE   ;

CHECK_MIN ;checks for subtraction operator
	LD R5, ASCII_NMIN
	ADD R5, R0, R5  ; Input is 'minus'
	BRnp CHECK_MULT
	JSR POP
	AND R4, R0, R0
	JSR POP	
	AND R3, R0, R0
	AND R5, R5, R5 ; Check for underflow
	BRp INV_INPUT
	JSR MIN
	JSR PUSH
	BRnzp EVALUATE   ;

CHECK_MULT ;checks for multiplication operator
	LD R5, ASCII_NMUL	
	ADD R5, R0, R5  ; Input is 'multiply'
	BRnp CHECK_DIV
	JSR POP
	AND R4, R0, R0
	JSR POP
	AND R3, R0, R0
	AND R5, R5, R5 ; Check for underflow
	BRp INV_INPUT
	JSR MULT
	JSR PUSH
	BRnzp EVALUATE   ;

CHECK_DIV ;checks for division operator
	LD R5, ASCII_NDIV
	ADD R5, R0, R5  ; Input is 'divide'
	BRnp CHECK_EXP
	JSR POP
	AND R4, R0, R0
	JSR POP
	AND R3, R0, R0
	AND R5, R5, R5 ; Check for underflow
	BRp INV_INPUT
	JSR DIV
	JSR PUSH
	BRnzp EVALUATE   ;

CHECK_EXP ;checks for exponent operator
	LD R5, ASCII_NEXP
	ADD R5, R0, R5  ; Input is 'exponent'
	BRnp CHECK_NUM
	JSR POP
	AND R4, R0, R0
	JSR POP
	AND R3, R0, R0
	AND R5, R5, R5 ; Check for underflow
	BRp INV_INPUT
	JSR EXP
	JSR PUSH
	BRnzp EVALUATE   ;

;-------------------------------------------
; Read number ;
;-------------------------------------------

CHECK_NUM ;makes sure that the number is valid
	LD R5, ASCII_ZERO ; Normalize ascii value
	NOT R5, R5
	ADD R5, R5, #1
	ADD R0, R0, R5

	BRn INV_INPUT  ; If negative, input is invalid
	ADD R5, R0, #-9; Subtract 9, if positive, input invalid
	BRp INV_INPUT   

	JSR PUSH
	
	BRnzp EVALUATE
;-------------------------------------------
; Invalid Input ;
;-------------------------------------------

INV_INPUT ; prints out invalid expression if the expression is invalid
	LEA R0, INV_EXP
	PUTS
	HALT

;-------------------------------------------
; Done with evaluating ;
;-------------------------------------------

DONE_EVAL
	JSR POP
	AND R4, R0, R0
	AND R5, R5, R5
	BRp INV_INPUT

	JSR POP
	AND R5, R5, R5 ; Stack has more than one value, invalid expression
	BRz INV_INPUT

	AND R0, R4, R4
	JSR PRINT_HEX
	AND R5, R4, R4

	HALT
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - value to print in hexadecimal
PRINT_HEX
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - Stores characters to be printed
;R1 - Counter for 4bit character in the 16bit word (1-4)
;R2 - Counter for bit in the character (1-4) 

;-----------------------------------
; Callee-Savee
;-----------------------------------

	ST R1, PRINT_SaveR1
	ST R2, PRINT_SaveR2
	ST R3, PRINT_SaveR3
	ST R4, PRINT_SaveR4
	ST R7, PRINT_SaveR7

;-----------------------------------
; Loop 4 times with R1 (Outer Loop)
;-----------------------------------

; Initialize R1 to 4
	AND R1, R1, #0
	ADD R1, R1, #4
	AND R3, R0, #-1

;----------------------------------
; Load first 4 bits of R3 into R0
;----------------------------------
LOAD_CHAR
;Initialize R0 and R2
	AND R0, R0, #0
	ADD R2, R0, #4

LOAD_BIT
	ADD R0, R0, R0  ; Shift R0 Left
	AND R3, R3, R3  ; Check sign bit
	BRzp LOAD_NONE
	ADD R0, R0, #1  ; Load 1 into R0
LOAD_NONE
	ADD R3, R3, R3  ; Shift R3 Left
	ADD R2, R2, #-1
	BRp LOAD_BIT

; Done loading char (first 4 bits)

;----------------------------------
; Print Char
;----------------------------------
	
	ADD R4, R0, #-9
	BRp ADD_A 	    ; Greater than 9 
	BRnz ADD_ZERO   ; Less than or equal to 9

ADD_ZERO
	LD R4, ASCII_ZERO
	ADD R0, R0, R4
	BRnzp CHAR_DONE
ADD_A
	LD R4, ASCII_A
	ADD R0, R0, R4
	ADD R0, R0, #-10

CHAR_DONE
	OUT
	ADD R1, R1, #-1
	BRp LOAD_CHAR

;-----------------------------------
; Restore Callee-Savee / Done
;-----------------------------------
PRINT_DONE

	LD R1, PRINT_SaveR1
	LD R2, PRINT_SaveR2
	LD R3, PRINT_SaveR3
	LD R4, PRINT_SaveR4
	LD R7, PRINT_SaveR7

	RET


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4 ; out R0
PLUS	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	ADD R0, R3, R4
	RET


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4 ; out R0 (R3 - R4)
MIN	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	NOT R0, R4 ; flip the bits and add one then add the two registers
	ADD R0, R0, #1
	ADD R0, R3, R0 ; (R3 - R4)
	RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4 ; out R0 (R3 * R4)
;R5, register to store sign (1 negative, 0 positive)
MULT	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	ST R4, MULT_SaveR4 ;save registers
	ST R5, MULT_SaveR5
	AND R0, R0, #0  ; clear register 0
	AND R5, R5, #0  ; Fill R5 with 0s  

ABS_R3				; Take absolute value of both registers (R3, R4)
	ADD R3, R3, #0  ; Check sign of R3
	BRzp ABS_R4		; If postiive, skip to R4
	NOT R5, R5		; Change sign register
	NOT R3, R3		; Change sign of R3
	ADD R3, R3, #1	; Finish changing sign
ABS_R4
	ADD R4, R4, #0  ; Check sign of R4
	BRzp MULT_START	; If positive, skip to end
	NOT R5, R5
	NOT R4, R4
	ADD R4, R4, #1
	
MULT_START
	AND R4, R4, R4  ; Check if R4 is 0
	BRp MULT_LOOP   ;
	AND R0, R0, #0  ;
	BRnzp MULT_OUT  ;

MULT_LOOP			; Begin multiplication
	ADD R0, R3, R0
	ADD R4, R4, #-1 ;decrement counter
	BRp MULT_LOOP


	ADD R5, R5, #0 ; Check sign of R5
	BRzp MULT_OUT  ; If negative, switch sign of R0
	NOT R0, R0
	ADD R0, R0, #1 
	
MULT_OUT
	LD R4, MULT_SaveR4 ; restore registers
	LD R5, MULT_SaveR5
	RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4 ; out R0 (R3 / R4)
;R5, temp variable to store QUOT
DIV	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
	ST R3, DIV_SaveR3 ; save registers
	ST R4, DIV_SaveR4
	ST R5, DIV_SaveR5
	ST R7, DIV_SaveR7

	AND R5, R5, #0 ; clear register 5

DIV_LOOP
	JSR MIN			; Jump to the subtraction subroutine
	AND R3, R0, R0 ; Move output (R0) into R3
	BRzp INC_QUOT  
	BRn DIV_DONE

INC_QUOT
	ADD R5, R5, #1
	BRnzp DIV_LOOP

DIV_DONE
	AND R0, R5, #-1
	LD R3, DIV_SaveR3 ; restore registers
	LD R4, DIV_SaveR4
	LD R5, DIV_SaveR5
	LD R7, DIV_SaveR7
	RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4 ; out R0 (R3 ^ R4)
;R5, Counter for EXP_LOOP
EXP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	ST R3, EXP_SaveR3 ; save registers
	ST R4, EXP_SaveR4
	ST R5, EXP_SaveR5
	ST R7, EXP_SaveR7

	LD R5, EXP_SaveR4 ; Load R4 into R5
	LD R4, EXP_SaveR3 ; Load R3 into R4
	ADD R5, R5, #-1    ; Initialize R5
	BRz EXP_ONE		  ; If R5 is now zero, just return R3
	
EXP_LOOP
	JSR MULT         ;jump to multiplication to implement exponent
	AND R3, R0, #-1
	ADD R5, R5, #-1 
	BRp EXP_LOOP
	BRnzp EXP_DONE

EXP_ONE
	LD R0, EXP_SaveR3

EXP_DONE
	LD R3, EXP_SaveR3 ;Restore registers
	LD R4, EXP_SaveR4
	LD R5, EXP_SaveR5
	LD R7, EXP_SaveR7
	RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
PUSH	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	ST R3, PUSH_SaveR3	; save R3
	ST R4, PUSH_SaveR4	; save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACK_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3			;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		; stack is full
	STR R0, R4, #0		; no overflow, store value in the stack
	ADD R4, R4, #-1		; move top of the stack
	ST R4, STACK_TOP	; store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
POP	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	ST R3, POP_SaveR3	; save R3
	ST R4, POP_SaveR4	; save R3
	AND R5, R5, #0		; clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3			;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET

;===========================;
DIV_SaveR3		.BLKW #1	;
DIV_SaveR4		.BLKW #1	;
DIV_SaveR5		.BLKW #1	;
DIV_SaveR7		.BLKW #1	;
EXP_SaveR3		.BLKW #1	;
EXP_SaveR4		.BLKW #1	;
EXP_SaveR5		.BLKW #1	;
EXP_SaveR7		.BLKW #1	;
MULT_SaveR4		.BLKW #1	;
MULT_SaveR5		.BLKW #1	;
POP_SaveR3		.BLKW #1	;
POP_SaveR4		.BLKW #1	;
PRINT_SaveR1	.BLKW #1	;
PRINT_SaveR2	.BLKW #1	;
PRINT_SaveR3	.BLKW #1	;
PRINT_SaveR4 	.BLKW #1	;
PRINT_SaveR7	.BLKW #1	;
;===========================;
STACK_END		.FILL x3FF0	;
STACK_START		.FILL x4000	;
STACK_TOP		.FILL x4000	;
ASCII_A			.FILL x0041 ; stores ASCII 'A'
ASCII_ZERO  	.FILL x0030 ; stores ASCII '0'
ASCII_NINE		.FILL x0039 ; stores ASCII '9'
ASCII_EQ		.FILL x003D ; stores ASCII '=' 
ASCII_NEQ		.FILL xFFC3 ; stores ASCII -'=' (negative =), used to test equality with equals
ASCII_SPC		.FILL x0020 ; stores ASCII ' '
ASCII_NSPC		.FILL xFFE0 ; stores ASCII -' ' (negative space),
ASCII_NADD		.FILL xFFD5 ; stores ASCII -'+' 
ASCII_NMIN		.FILL xFFD3 ; stores ASCII -'-'
ASCII_NMUL 		.FILL xFFD6 ; stores ASCII -'*'
ASCII_NDIV		.FILL xFFD1 ; stores ASCII -'/'
ASCII_NEXP		.FILL xFFA2 ; stores ASCII -'^'
;===========================;

INV_EXP			.STRINGZ "Invalid Expression"


.END