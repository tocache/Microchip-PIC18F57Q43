    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upezotes, class=CODE, reloc=2, abs
upezotes:
   ORG 000000H
   bra configuro
   
   ORG 000100H
configuro:
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    movlb 4H
    movlw 80H
    movwf TRISD, 1
    movwf ANSELD, 1
    movlw 0F0H
    movwf ANSELB, 1
    clrf TBLPTRU, 1
    movlw 08H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1
    
inicio:
    movf PORTB, 0, 1
    andlw 0FH
    movwf TBLPTRL, 1
    TBLRD*
    movff TABLAT, LATD
    bra inicio
    
    ORG 000800H
datos_7s: DB 3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 67H
 
    end upezotes
   


