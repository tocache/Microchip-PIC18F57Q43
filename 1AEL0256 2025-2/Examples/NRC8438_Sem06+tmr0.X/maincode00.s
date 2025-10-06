    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upecenios, class=CODE, reloc=2, abs
upecenios:
    ORG 000000H
    bra configuro
    
    ORG 000200H
configuro:
    ;conf mod oscilador
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 50H
    movwf OSCEN, 1	;LFINTOSC y HFINTOSC habilitados
    ;conf del RC5 para el TMR0
    movlb 2H
    movlw 39H
    movwf RC5PPS, 1	;TMR0 conectado a RC5
    ;conf del Timer0
    movlb 3H
    movlw 80H
    movwf T0CON0, 1	;TMR0 enabled, 8bit, posts 1:1
    movlw 86H
    movwf T0CON1, 1	;clk src LFINTOSC, sync, presc 1:64
    movlw 242
    movwf TMR0H, 1	;valor de referencia para la comparación
    ;conf E/S
    movlb 4H
    bcf TRISC, 5, 1	;RC5 como salida
    bcf ANSELC, 5, 1	;RC5 como digital
    bcf ANSELB, 1, 1	;RB1 como digital
    bsf WPUB, 1, 1	;RB1 con pull activada
    bcf TRISD, 6, 1	;RD6 como salida
    bcf ANSELD, 6, 1	;RD6 como digital
    
inicio:			;zona de prog de usuario
    btfsc PORTB, 1, 1
    bra $-2
    btg LATD, 6, 1
    btfss PORTB, 1, 1
    bra $-2
    bra inicio
    
    end upecenios
    


