.ORIG x3000
AND R0, R0, x0   ; clear R0
ADD R0, R0, 7    ; set R0 to 7   (0111)
AND R1, R0, 9    ; AND R0 with 9 (1001) and store (result: 1) in R1
HALT

