    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 000020H
configuro:
    movlb 0H		    ;yendo al bank0
    movlw 60H
    movwf OSCCON1	    ;HFINTOSC seleccionado
    movlw 02H
    movwf OSCFRQ	    ;HFINTOSC a 4MHz
    bsf OSCEN, 6	    ;HFINTOSC habilitado
    movlb 3H		    ;yendo al bank3 para los regs de Timer0
    movlw 80H
    movwf T0CON0	    ;Tmr0 enabled, postscaler 1:1
    movlw 63H
    movwf T0CON1	    ;Tmr0 8 bit mode, clk_src HFINTOSC, psc 1:8 para 2us x cuenta
    movlw 250
    movwf TMR0H		    ;coloco 250 como referencia de comparación a la cuenta de Tmr0
    movlb 4H		    ;yendo al bank4
    ;configuracion de los puertos
    bcf TRISD, 0	    ;RD0 como salida
    bcf ANSELD, 0	    ;RD0 como digital
    
inicio:
    btfss PIR3, 7	    ;pregunto si TMR0IF
    bra inicio		    ;falso, regreso a preguntar (polling)
    bcf PIR3, 7		    ;verdadero, bajo bandera TMR0IF
    btg LATD, 0		    ;basculo salida RD0
    bra inicio
    
    end upcino

