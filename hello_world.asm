.ORIG x3000												; this is the address in memory where the program will be loaded
LEA R0, HELLO_STR									; load the address of the HELLO_STR string into R0
PUTs															; output the string pointed to by R0 to the console
HALt														  ; halt the program
HELLO_STR .STRINGZ "Hello World"  ; store the string in the program
.END														  ; mark the end of the file
