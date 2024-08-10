    PROCESSOR 18F57Q43
    #include "cabecera.inc"
        
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
TACUEN EQU 0500H
    
    org 000000H
    bra configuro
    org 000500H
tabla_7s_a: DB 3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H
tabla_7s_b: DB 7FH, 67H, 77H, 7CH, 39H, 5EH, 79H, 71H    
    org 000100H
configuro:
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 03H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    movlb 4H
    clrf TRISB, 1
    clrf ANSELB, 1
    bsf TRISD, 0, 1
    bsf TRISD, 2, 1
    bcf ANSELD, 0, 1
    bcf ANSELD, 2, 1
    bsf WPUD, 0, 1
    bsf WPUD, 2, 1
    clrf TBLPTRU, 1
    movlw 05H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1
    movlb 5H
    clrf TACUEN, 1
    movlb 4H
    call visual
inicio:    
    btfsc PORTD, 2, 1
    bra siguiente1
    bra limpia
siguiente1:
    btfsc PORTD, 0, 1
    bra inicio
    movlw 15
    movlb 5H
    cpfseq TACUEN, 1
    bra aunno
    clrf TACUEN, 1
    bra siguiente2
aunno:    
    incf TACUEN, 1, 1
siguiente2:    
    movlb 4H
    call visual
    bsf LATB, 7, 1
otro:
    btfss PORTD, 0, 1
    bra otro
    bcf LATB, 7, 1
    bra inicio
limpia:
    movlb 5H
    clrf TACUEN, 1
    movlb 4H
    call visual
    bra inicio
visual:
    movlb 5H
    movf TACUEN, 0, 1
    movlb 4H
    movwf TBLPTRL, 1
    TBLRD*
    movff TABLAT, LATB
    return
    
    end upcino


