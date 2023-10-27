    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H		;Vector de reset
    bra configuro
    
    ORG 000008H		;Vector de interrupcion
    bra TMR0_ISR

    ORG 000100H
configuro:
    movlb 0H		;bank0
    movlw 60H
    movwf OSCCON1, 1	;hfintosc, 1:1
    movlw 02H
    movwf OSCFRQ, 1	;hfintosc 4MHz
    movlw 40H
    movwf OSCEN, 1	;hfintosc enabled
    movlb 3H		;bank3
    movlw 90H	
    movwf T0CON0, 1 	;tmr0 enabled, 16 bit, posts 1:1
    movlw 40H
    movwf T0CON1, 1	;fosc/4 presc 1:1024
    movlb 4H		;bank4
    bcf TRISC, 0, 1
    bcf ANSELC, 0, 1
    bcf TRISD, 0, 1
    bcf ANSELD, 0, 1
    bsf TRISB, 0, 1
    bcf ANSELB, 0, 1
    movlw 80H
    movwf PIE3, 1	;TMR0IE=1 (TMR0 interrupt enabled)
    movwf INTCON0, 1	;GIE=1 (Global interrupt enabled)
    
inicio:			;rutina principal
    btfss PORTB, 0, 1	;pregunto si pulse boton
    bra $-2		;no pulse
    btg LATC, 0, 1	;si pulse y basculo LED
    btfsc PORTB, 0, 1	;pregunto si solte boton
    bra $-2		;no solte
    bra inicio		;si solte, retorno a inicio
    
TMR0_ISR:		;rutina de interrupcion para TMR0
    btg LATD, 0, 1	;basculo LED
    movlb 3H		;bank3
    movlw 0FEH
    movwf TMR0H, 1
    movlw 17H
    movwf TMR0L, 1	;carga de cuenta inicial a TMR0
    movlb 4H		;bank4
    bcf PIR3, 7, 1
    retfie
    
    end upcino
    
    
    
    

