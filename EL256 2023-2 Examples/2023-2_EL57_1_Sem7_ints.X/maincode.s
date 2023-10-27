    PROCESSOR 18F57Q43
    #include "cabecera.inc"

    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H		;vector de reset
    bra configuro
    
    ORG 000008H		;vector de interrupcion
    bra INT0_ISR
    
    ORG 000100H
configuro:
    movlb 0H		    ;bank0
    movlw 60H
    movwf OSCCON1, 1	    ;hfintosc, 1:1
    movlw 02H
    movwf OSCFRQ, 1	    ;hfintosc 4MHz
    movlw 40H
    movwf OSCEN, 1	    ;hfintosc enabled
    movlb 2H		    ;bank2
    movlw 08H
    movwf INT0PPS, 1	    ;rb0 asignado a INT0
    movlb 3H		    ;bank3
    movlw 81H
    movwf T0CON0, 1	    ;tmr0 on, 8bit, posts 1:2
    movlw 4AH
    movwf T0CON1, 1	    ;fosc4, presc 1:1024
    movlw 250
    movwf TMR0H, 1	    ;valor de referencia
    movlb 4H		    ;bank4
    bcf TRISD, 0, 1	    ;rd0 salida
    bcf ANSELD, 0, 1	    ;rd0 digital
    bcf TRISC, 0, 1	    ;rc0 salida
    bcf ANSELC, 0, 1	    ;rc0 digital
    bsf TRISB, 0, 1	    ;rb0 entrada
    bcf ANSELB, 0, 1	    ;rb0 digital
    movlw 01H
    movwf PIE1, 1	    ;INT0 enabled
    movlw 87H
    movwf INTCON0, 1	    ;GIE enabled, INT0EDG=1
    bcf LATD, 0, 1	    ;rd0=0

inicio:
    btfss PIR3, 7, 1	    ;pregunto si hubo evento en TMR0 (TMR0IF=1)
    bra $-2		    ;no hubo evento en TMR0 (TMR0IF=0)
    btg LATC, 0, 1	    ;si hubo evento, basculo rc0
    bcf PIR3, 7, 1	    ;bajo bandera TMR0IF
    bra inicio		    ;repito
    
INT0_ISR:
    btg LATD, 0, 1	    ;basculo rd0
    bcf PIR1, 0, 1	    ;bajo bandera INT0IF
    retfie		    ;retorno a posicion antes de interrupcion
    
    end upcino
     
    
    


