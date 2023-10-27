    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H		;vector de reset
    bra configuro
    
    ORG 000008H		;vector de int hp
    bra INT0_ISR
    
    ORG 000018H		;vector de int lp
    bra TMR0_ISR
    
    ORG 000100H
configuro:
    movlb 0H		;bank0
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    movlb 3H		;bank3
    movlw 81H
    movwf T0CON0, 1
    movlw 4AH
    movwf T0CON1, 1
    movlw 250
    movwf TMR0H, 1
    bcf IPR3, 7, 1	;TMR0IP=0 (low priority)
    movlb 4H		;bank4
    bsf PIE3, 7, 1	;TMR0IE=1
    bsf PIE1, 0, 1	;INT0IE=1
    movlw 0E7H
    movwf INTCON0, 1	;GIEH=1, GIEL=1, IPEN=1
    bcf TRISC, 0, 1	;RC0 como salida
    bcf ANSELC, 0, 1	;RC0 como digital
    bcf TRISD, 0, 1	;RD0 como salida
    bcf ANSELD, 0, 1	;RD0 como digital
    bsf TRISB, 0, 1	;RB0 como entrada
    bcf ANSELB, 0, 1	;RB0 como digital

inicio:
    bra inicio
    
TMR0_ISR:
    btg LATC, 0, 1	;complementamos RC0
    bcf PIR3, 7, 1	;bajamos TMR0IF
    retfie
    
INT0_ISR:
    btg LATD, 0, 1	;complementamos RD0
    bcf PIR1, 0, 1	;bajamos INT0IF
    retfie
    
    end upcino


