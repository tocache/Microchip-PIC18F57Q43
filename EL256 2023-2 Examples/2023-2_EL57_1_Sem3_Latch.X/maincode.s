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
    bcf TRISF, 3, 1
    bcf ANSELF, 3, 1
    bsf LATF, 3, 1	;LED apagado en un inicio
    
inicio:
    btfsc PORTB, 4, 1	;Pregunta si RB4 es cero (si presione el boton)
    bra inicio		;falso, regresa a preguntar
    btg LATF, 3, 1	;complemento a RF3
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