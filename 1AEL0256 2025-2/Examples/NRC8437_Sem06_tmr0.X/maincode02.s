    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upecenos, class=CODE, reloc=2, abs
upecenos:
    ORG 000000H
    bra configuro
    
    ORG 000200H
configuro:
    ;conf modulo de oscilador
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 50H
    movwf OSCEN, 1	;HFINTOSC & LFINTOSC enabled
    ;conf del PPS
    movlb 2H
    movlw 39H
    movwf RC5PPS, 1	;RC5 conectado a TMR0
    ;conf del TMR0
    movlb 3H
    movlw 80H
    movwf T0CON0, 1	;TMR0 enabled, 8bit mode, posts 1:1
    movlw 86H
    movwf T0CON1, 1	;clksrc = LFINTOSC, sync, presc 1:64
    movlw 242
    movwf TMR0H, 1	;valor de ref de comp 250
    ;conf E/S
    movlb 4H
    bcf TRISC, 5, 1	;RC5 como salida
    bcf ANSELC, 5, 1	;RC5 como digital
    bcf ANSELB, 1, 1	;RB1 como digital
    bsf WPUB, 1, 1	;RB1 con pullup activado
    bcf TRISD, 6, 1	;RD6 como salida
    bcf ANSELD, 6, 1	;RD6 como digital
    bcf ANSELE, 1, 1	;RE1 como digital
    bsf WPUE, 1, 1	;RE1 con pullup activado

inicio:			;zona de prog de usuario
    btfsc PORTB, 1, 1
    bra alRE1
    btg LATD, 6, 1
    btfss PORTB, 1, 1
    bra $-2
alRE1:
    btfsc PORTE, 1, 1
    bra inicio
    movlb 3H
    movlw 242
    cpfseq TMR0H, 1
    bra noes250
    movlw 60
    movwf TMR0H, 1
    bra final
noes250:
    movlw 242
    movwf TMR0H, 1
final:
    movlb 4H
    btfss PORTE, 1, 1
    bra $-2
    bra inicio
    
    end upecenos







