    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
x_var EQU 500H    
upcino:
    ORG 000000H
    bra configuro
    
    ORG 000080H
configuro:
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    
    movlb 4H
    bsf TRISB, 4, 1
    bcf ANSELB, 4, 1
    bsf WPUB, 4, 1
    bcf TRISF, 3, 1
    bcf ANSELF, 3, 1
    bsf LATF, 3, 1

inicio:
    btfsc PORTB, 4, 1
    bra inicio
    btg LATF, 3, 1
    call retardado
otro:
    btfss PORTB, 4, 1
    bra otro
    bra inicio
    
retardado:
    movlb 5H
    movlw 255
    movwf x_var, 1
otro2:    
    nop			;se va a ejecutar 100 veces
    movf x_var, 1, 1
    movlb 4H
    btfss STATUS, 2, 1
    bra noescero
    movlb 4H
    return
noescero:
    movlb 5H
    decf x_var, 1, 1
    bra otro2
    
    end upcino
