START 200
MOVER AREG, ='5'
MOVEM AREG, A
MOVER AREG, A
MOVER CREG, B
ADD CREG, ='1'
LTORG
SUB AREG, ='1'
ORIGIN 204
MULT CREG,B
ORIGIN 211
DS 2
DS 1
END