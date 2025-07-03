;Programa para genera una señal de 1KHz y 50% de DC
    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
    
upcino:
    ORG 000000H
    bra configuro
    
    ORG 005000H
data_dc_10:	DB 225, 25
    ORG 005100H
data_dc_50:	DB 25, 225

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
    clrf TBLPTRU, 1
    
inicio:
    btfsc PORTD, 0, 1	;pregunto si presione boto
    bra nopresione
    bra sipresione
    
nopresione:
    movlb 4H
    movlw 50H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1
    TBLRD*+
    movlb 3H
    movff TABLAT, TMR0H
    movlb 4H
    bsf LATF, 0, 1	;prendo LED
ab1: btfss PIR3, 7, 1	;pregunto si TMR0IF=1    
    bra ab1		;aun no se levanta bandera TMR0IF
    bcf PIR3, 7, 1	;ya se levanto y se vuelve a bajar TMR0IF
    movlb 4H
    TBLRD*
    movlb 3H
    movff TABLAT, TMR0H
    movlb 4H
    bcf LATF, 0, 1	;apago LED
ba1: btfss PIR3, 7, 1	;pregunto si TMR0IF=1    
    bra ba1		;aun no se levanta bandera TMR0IF
    bcf PIR3, 7, 1	;ya se levanto y se vuelve a bajar TMR0IF    
    bra inicio
    
sipresione:
    movlb 4H
    movlw 51H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1
    TBLRD*+
    movlb 3H
    movff TABLAT, TMR0H
    movlb 4H
    bsf LATF, 0, 1	;prendo LED
ab2: btfss PIR3, 7, 1	;pregunto si TMR0IF=1    
    bra ab2		;aun no se levanta bandera TMR0IF
    bcf PIR3, 7, 1	;ya se levanto y se vuelve a bajar TMR0IF
    movlb 4H
    TBLRD*
    movlb 3H
    movff TABLAT, TMR0H
    movlb 4H
    bcf LATF, 0, 1	;apago LED
ba2: btfss PIR3, 7, 1	;pregunto si TMR0IF=1    
    bra ba2		;aun no se levanta bandera TMR0IF
    bcf PIR3, 7, 1	;ya se levanto y se vuelve a bajar TMR0IF    
    bra inicio
    
    end upcino








