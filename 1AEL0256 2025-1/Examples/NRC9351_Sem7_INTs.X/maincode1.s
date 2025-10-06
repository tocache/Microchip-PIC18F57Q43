;Atención de interrupciones en el PIC18F57Q43, modo LEGACY
    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2
upcino:
    ORG 000000H
    goto configuro
    
    ORG 000008H
    goto INT0_ISR
    
    PSECT code
    ORG 000100H
configuro:
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    movlb 2H
    movlw 0CH
    movwf INT0PPS, 1
    movlw 4H
    bcf ANSELF, 3, 1
    bcf TRISF, 3, 1
    bcf ANSELB, 4, 1
    bsf WPUB, 4, 1
    bsf PIE1, 0, 1	;INT0IE=1
    bcf INTCON0, 0, 1	;INT0EDG=0
    bsf INTCON0, 7, 1	;GIE=1
    
inicio:
    nop
    bra inicio
    
INT0_ISR:
    bcf PIR1, 0, 1	;INT0IF=0
    btg LATF, 3, 1	;basculamos LED en RF3
    retfie		;retorno del evento de interrupcion
    


