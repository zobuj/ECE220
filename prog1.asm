;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP			; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA			; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments

; partners: ag72, ananyag8

; Introductory Paragraph:
; This program prints the frequencies (as a hexadecimal number) of the histogram that is stored in memory,
; starting at x3F00. To accomplish this, we initialize R2 as a counter and set it to 27. This value will be
; decremented every time we print the frequency (as a hexadecimal number) of each ASCII character. This is because
; we want to print the contents of memory location x3F00 to x3F1B which contain the frequencies of the histogram.
; R6 is used as a temporary register to load the starting address of the histogram, which is stored in memory at the
; label HISTADDR. This is later incremented in the code to the next histogram address. Then we check the CC value of
; R2, once it reaches 0, we know that we have printed all 27 values of the histogram and their frequencies, so we
; branch to HALT. In the next instruction, we load into R3 the content of the histograms. Because we want to print the
; labels of the histogram bins (which are the ASCII characters from '@' to 'Z') along with their respective
; frequencies, R0 is used to print the ASCII value of the bin labels. The initial ASCII value stored in memory is that
; for '@'. This is later incremented in the code to next ASCII value ('A'). Then we implement the code developed in
; lab1. R1 is used to store the digit counter which is set to 0. R6 is used as a temporary register to hold the sum or
; differences throughout the code. R6 is cleared and the difference between R1 (digit counter) and 4 is taken to
; indicate whether 4 digits have been printed or not. If 4 digits have not been printed, then we branch to the label
; "init". Once there, we initialize R4 to act as a storage for each digit shifted from R3. We also use initialize R5
; to act as the bit counter. We then use R5's value to check if we have 4 bits by subtracting 4 from it. By putting 
; the result into R6, we judge whether it is negative (less than 4 bits) or positive (more than 4 bits). If we have
; less than 4 bits, we jump to the label LS where we left shift R4 so we can accept another bit into its LSB. We then
; check the sign of R3. If it is negative (we have an MSB of 1) and so we add 1 to R4. If it is positive
; (we have an MSB of 0), we add 0 to R4. After that, we left shift R3 to look at the next bit value and increment the
; bit counter in R5. We then loop back to label "BitCheck" and see if we have 4 bits in the bit counter. If we do, then
; we don't branch to label "LS", but use R6 to store the difference between R4 and #9. If that difference is negative
; or zero (if the digit we have is less than 9), then we load the character for '0' (its corresponding decimal value)
; and add that to the digit value (what is already in R4). If that difference is positive
; (the digit we have is greater than 9), we then load then decimal equivalent of character 'A', subtract #10, and add
; that to the digit value. These options transform the "number" of the digit into the "character" version. We then
; print out this string to the console. We then increment the digit counter and loop back to label "DigCheck". If we
; have 4 digits then we go to a new line; else, we repeat the aforementioned code again.
; After printing out the hexadecimal number, we print out a new line by clearing R0 and storing the ASCII value for
; [LINE FEED]. Then we, increment the histogram address in memory by loading the current histogram address into R6
; and incrementing the value in R6 by 1, and storing the new histogram address back in the memory. We do the same thing
; for incrementing the ASCII value so that we can print out the bin labels. We load into R6 the current ASCII value,
; then we increment the value in R6 by 1, and store the new ASCII value in memory. After this, we decrement the
; counter by 1. Finally, we use a BR instruction to loop back to the instruction that loads into R6 the address of the
; histogram. Once the counter value stored in R2 reaches 0, we branch to the HALT statement, since we have printed out
; all the bin labels and their respective frequencies.

; Register Table:
; R0: Stores the characters to be printed to the console
; R1: Stores the value of the digit counter 
; R2: Stores the counter value which is initialized to 27, which is the number of times we want to print the hexadecimal
; numbers.
; R3: Stores the hexadecimal number that is to be printed to the monitor
; R4: Stores the set of 4 bits (a digit) that are to be converted to a hexadecimal number in ASCII format
; R5: Stores the bit counter, which checks the number of times we have left shifted the digits stored in R4 
; R6: Temporary register which initially stores the histogram addresses. Then stores the ASCII values from '@' to 'Z'
; R7: Not used.

		AND R2, R2, #0 ; clear R2
		LD R2, ADD27   ; set counter to 27

LOOP		LD R6, HISTADDR ; R6 gets addresses of histogram
			
		ADD R2, R2, #0 ; checks CC of R2
		BRz DONE 

		LDR R3, R6, #0 ; R3 gets content of histogram address 

		LD R0, ASCII ; R0 gets ASCII value of '@'
		OUT 
			
		LD R0, SPACE ; R0 gets ASCII value of [SPACE]  
		OUT

; -----------------------------------------------------------------------------------			
	AND R1,R1,#0 ; initialize digit counter
			
DigCheck    AND R6,R6,#0 ; 
            ADD R6,R1,#-4 ; difference between digit counter and #4 to check if 4 digits printed 

            BRn init ; printed<4 digits?
            BR NewLine

init        AND R4,R4,#0 ; initialize digit
            AND R5,R5,#0 ; initialize bit counter 

BitCheck    AND R6,R6,#0
            ADD R6,R5,#-4 ; difference between bit counter and #4 to check if bit counter has 4 bits
            BRn LS ; got <4 bits from R3?

            AND R6,R6,#0
            ADD R6,R4,#-9 ; difference between digit and #9 to check if digit is less than or equal to #9
            BRnz AddZ ; digit<=9?

            AND R6,R6,#0
            LD R6,CharA
            ADD R0,R6,#-10 ; difference between #65 ('A') and #10
            ADD R0,R0,R4 ; adding above difference to digit to convert number to ASCII version
            OUT
            ADD R1,R1,#1 ; increment digit counter
            BR DigCheck

AddZ        LD R0,CharZ ; 
            ADD R0,R0,R4 ; Adding #48 ('0') to digit to convert number to ASCII version 
            OUT
            ADD R1,R1,#1 ; increment digit counter 
            BR DigCheck

LS          ADD R4,R4,R4 ; left shift R4 to accept another bit into its LSB
            ADD R3,R3,#0 ; 
            BRn AddI ; R3<0 (MSB=1?)

            ADD R4,R4,#0 ; if R3>0 then add #0 to R4
            ADD R3,R3,R3 ; Left shift R3 to allow next bit to be compared

            ADD R5,R5,#1 ; increment bit counter 
            BR BitCheck 

AddI        ADD R4,R4,#1 ; if R3<0 add #0 to R4
            ADD R3,R3,R3 ; Left shift R3 to allow next bit to be compared
            ADD R5,R5,#1 ; increment bit counter 
            BR BitCheck

CharA       .FILL #65 ; x41
CharZ       .FILL #48 ; x30

; ----------------------------------------------------------------------------

NewLine		AND R0, R0, #0 ; Clear R0
		ADD R0, R0, #10 ; R0 gets ASCII value of [LINE FEED]
		OUT 	

		LD R6, HISTADDR			
		ADD R6, R6, #1 ; increment histogram address
		ST R6, HISTADDR ; store incremented address in HISTADDR
			
		LD R6, ASCII			
		ADD R6, R6, #1 ; increment ASCII value
		ST R6, ASCII ; store incremented ASCII value in ASCII
	
		ADD R2, R2, #-1 ; decrement counter
	
		BR LOOP

DONE	HALT			; done

HISTADDR .FILL x3F00
ADD27	 .FILL #27
ASCII 	 .FILL #64    ; ASCII value of '@'
SPACE  	 .FILL #32	  ; ASCII value of [SPACE]


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END