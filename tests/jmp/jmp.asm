.ORIG x3000
JMP R0              ; jump to value from R0 (the value is address where HALT is)
ADD R1, R1, 0       ; dummy instruction to skip
HALT

