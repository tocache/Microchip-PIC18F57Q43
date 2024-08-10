    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 000100H
configuro:
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 03H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1	    ;HFINTOSC a 8MHz
    movlb 3H
    movlw 90H
    movwf T0CON0, 1
    movlw 4AH		    ;TMR0 16bit,psc 1:1024, post 1:1
    movwf T0CON1, 1	    ;TMR0 HFINTOSC/4
    movlw 0F8H
    movwf TMR0H, 1
    movlw 5FH
    movwf TMR0L, 1	    ;cuenta inicial de 63583
    movlb 4H
    bcf TRISE, 0, 1	    ;RE0 como salida
    bcf TRISE, 1, 1	    ;RE1 como salida
    bcf TRISC, 0, 1	    ;RC0 cmo salida
    bcf ANSELE, 0, 1	    ;RE0 como digital
    bcf ANSELE, 1, 1	    ;RE1 como digital
    bcf ANSELC, 0, 1	    ;RC0 como digital
    bsf LATE, 0, 1	    ;LD_Rojo encendido
    bcf LATE, 1, 1	    ;LD_Azul apagado
    bcf LATC, 0, 1	    ;LD_Verde apagado
    
inicio:
    btfss PIR3, 7, 1	    ;Pregunto si se levanto bandera de TMR0
    bra $-2		    ;Falso, vuelve a preguntar
    bcf PIR3, 7, 1	    ;Verdad, bajo la bandera TMR0
    bcf LATE, 0, 1
    bsf LATE, 1, 1
    bcf LATC, 0, 1
    movlb 3H
    movlw 0F8H
    movwf TMR0H, 1
    movlw 5FH
    movwf TMR0L, 1	    ;cuenta inicial de 63583
    movlb 4H
    btfss PIR3, 7, 1	    ;Pregunto si se levanto bandera de TMR0
    bra $-2		    ;Falso, vuelve a preguntar
    bcf PIR3, 7, 1	    ;Verdad, bajo la bandera TMR0
    bcf LATE, 0, 1
    bcf LATE, 1, 1
    bsf LATC, 0, 1
    movlb 3H
    movlw 0F8H
    movwf TMR0H, 1
    movlw 5FH
    movwf TMR0L, 1	    ;cuenta inicial de 63583
    movlb 4H
    btfss PIR3, 7, 1	    ;Pregunto si se levanto bandera de TMR0
    bra $-2		    ;Falso, vuelve a preguntar
    bcf PIR3, 7, 1	    ;Verdad, bajo la bandera TMR0
    bcf LATE, 0, 1
    bsf LATE, 1, 1
    bcf LATC, 0, 1
    movlb 3H
    movlw 0F8H
    movwf TMR0H, 1
    movlw 5FH
    movwf TMR0L, 1	    ;cuenta inicial de 63583
    movlb 4H
    btfss PIR3, 7, 1	    ;Pregunto si se levanto bandera de TMR0
    bra $-2		    ;Falso, vuelve a preguntar
    bcf PIR3, 7, 1	    ;Verdad, bajo la bandera TMR0
    bsf LATE, 0, 1
    bcf LATE, 1, 1
    bcf LATC, 0, 1
    movlb 3H
    movlw 0F8H
    movwf TMR0H, 1
    movlw 5FH
    movwf TMR0L, 1	    ;cuenta inicial de 63583
    movlb 4H
    bra inicio
    
    end upcino


