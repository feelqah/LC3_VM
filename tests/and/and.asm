.ORIG x3000
AND R0, R0, x0   ; clear R0
ADD R0, R0, 7    ; set R0 to 7 (0111)
AND R1, R0, 9    ; AND R1 and R2; R1 is now: 1 (0001)
HALT

