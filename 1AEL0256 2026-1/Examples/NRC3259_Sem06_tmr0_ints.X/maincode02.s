    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT viernes, class=CODE, reloc=2
viernes:
    ORG 000000H
    bra configuro
    
    ORG 00003EH	    ;vector de la TMR0 (2*1FH)
    DW TMR0_ISR shr 2
    
    PSECT TMR0_ISR, class=CODE, reloc=4
TMR0_ISR:
    movlb 4H
    bcf PIR3, 7, 1
    btg LATC, 0, 1
    movlb 3H
    movlw 6DH
    movwf TMR0H, 1
    movlw 84H
    movwf TMR0L, 1
    movlb 4H
    retfie     
    
    PSECT code    
    ORG 000100H
configuro:
    ;conf mod osc
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    ;conf tmr0
    movlb 3H
    movlw 90H
    movwf T0CON0, 1
    movlw 65H
    movwf T0CON1, 1
    ;conf E/S
    movlb 4H
    bcf TRISC, 0, 1
    bcf ANSELC, 0, 1
    ;conf las ints
    bsf PIE3, 7, 1	;Activando la int de tmr0
    bsf INTCON0, 7, 1	;Activando GIE
    
inicio:
    nop
    bra inicio
    
    end viernes




