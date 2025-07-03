;Programa para genera una señal de 1KHz y 50% de DC
    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
    
upcino:
    ORG 000000H
    bra configuro

    ORG 000100H
configuro:
    ;configuracion del modulo de oscilador
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    ;configuracion del Timer0
    movlb 3H
    movlw 80H
    movwf T0CON0, 1	;TMR0 enabled, 8bit, posts 1:1
    movlw 52H
    movwf T0CON1, 1	;FOSC/4, nosync, presc 1:4
    ;configuracion de las E/S
    movlb 4H
    movlw 0FCH
    movwf TRISF, 1
    movwf ANSELF, 1
    bcf ANSELD, 0, 1
    bsf WPUD, 0, 1
    ;condiciones iniciales de la aplicacion
    bsf LATF, 1, 1	;LED en RF1 ON constante
    
inicio:
    movlb 3H
    movlw 225
    movwf TMR0H, 1	;valor de ref de comparacion
    movlb 4H
    bsf LATF, 0, 1	;prendo LED
ab: btfss PIR3, 7, 1	;pregunto si TMR0IF=1    
    bra ab		;aun no se levanta bandera TMR0IF
    bcf PIR3, 7, 1	;ya se levanto y se vuelve a bajar TMR0IF
    movlb 3H
    movlw 25
    movwf TMR0H, 1	;valor de ref de comparacion
    movlb 4H
    bcf LATF, 0, 1	;apago LED
ba: btfss PIR3, 7, 1	;pregunto si TMR0IF=1    
    bra ba		;aun no se levanta bandera TMR0IF
    bcf PIR3, 7, 1	;ya se levanto y se vuelve a bajar TMR0IF    
    bra inicio
    end upcino





