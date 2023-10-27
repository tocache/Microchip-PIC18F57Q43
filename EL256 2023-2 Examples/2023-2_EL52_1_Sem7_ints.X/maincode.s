    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H		;vector de reset
    bra configuro
    
    ORG 000008H		;vector de interrupcion
    bra TMR0_ISR

    ORG 000100H		;programa de usuario
configuro:
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    movlb 3H
    movlw 90H
    movwf T0CON0, 1
    movlw 4AH
    movwf T0CON1, 1
    movlb 4H
    bcf TRISD, 0, 1	;RD0 como salida
    bcf ANSELD, 0, 1	;RD0 como digital
    bcf TRISC, 0, 1	;RC0 como salida
    bcf ANSELC, 0, 1	;RC0 como digital
    bsf TRISB, 0, 1	;RB0 como entrada
    bcf ANSELB, 0, 1	;RB0 como digital
    movlw 80H
    movwf PIE3, 1
    movwf INTCON0, 1
    
inicio:    
    btfss PORTB, 0, 1	;pregunto si pulsaste boton
    bra $-2		;falso, vuelve a preguntar
    btg LATC, 0, 1	;verdad, basculo RC0
    btfsc PORTB, 0, 1	;pregunto si solte el boton
    bra $-2		;falso, no solte el boton
    bra inicio

TMR0_ISR:
    btg LATD, 0, 1	;basculo RD0
    movlb 3H
    movlw 0FEH
    movwf TMR0H, 1
    movlw 17H
    movwf TMR0L, 1
    movlb 4H
    bcf PIR3, 7, 1
    retfie

    end upcino