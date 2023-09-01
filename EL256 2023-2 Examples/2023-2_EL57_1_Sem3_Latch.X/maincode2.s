    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 000020H
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
    movlw 0FCH
    movwf TRISD, 1		;RD0 y RD1 como salidas
    movwf ANSELD, 1	;RD0 y RD1 como digitales
    movlw 01H
    movwf LATD, 1		;RD0 encendido y RD1 apagado
        
inicio:
    btfsc PORTB, 4, 1	;Pregunta si RB4 es cero (si presione el boton)
    bra inicio		;falso, regresa a preguntar
    comf LATD, 1, 1	;complemento a registro
    call retardon
otro:    
    btfss PORTB, 4, 1	;Pregunta si RB4 es uno (si solte el boton)
    bra otro		;falso, vuelvo a preguntar
    bra inicio

retardon:
    nop
    nop    
    nop
    nop    
    nop
    nop    
    nop
    nop    
    nop
    nop    
    nop
    nop    
    nop
    nop    
    nop
    nop    
    nop
    nop    
    nop
    nop    
    nop
    nop    
    nop
    nop    
    nop
    nop    
    nop
    nop    
    nop
    nop    
    nop
    nop    
    nop
    nop    
    nop
    nop    
    nop
    nop    
    nop
    nop    
    return
    
    end upcino


