    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
DESPLAZO EQU 500H    
    
    ORG 000000H
    bra configuro
    
    ORG 000900H
mensaje: DB 00H,00H,00H,00H,0EH,3EH,7DH,3FH,00H,00H,00H
    
    ORG 000020H
configuro:
    movlb 0H		;bank 0
    movlw 60H
    movwf OSCCON1	;HFINTOSC y 1:1
    movlw 02H
    movwf OSCFRQ	;HFINTOSC a 4MHz
    movlw 40H
    movwf OSCEN		;HFINTOSC enabled
    movlb 3H		;bank 3
    movlw 90H
    movwf T0CON0	;TMR0 enabled, postscaler 1:1, 
    movlw 52H
    movwf T0CON1	;fosc/4, async, prescaler 1:4
    movlb 4H		;bank 4
    movlw 80H
    movwf TRISB
    movwf ANSELB	;RB6 al RB0 como salidas digitales
    movlw 0F0H
    movwf TRISA
    movwf ANSELA	;RA3 al RA0 como salidas digitales
    clrf TBLPTRU
    movlw HIGH mensaje
    movwf TBLPTRH
    movlw LOW mensaje
    movwf TBLPTRL	;apunto a 900H con el TBLPTR
    clrf LATA		;condicion inicial de la multiplexacion
    clrf DESPLAZO
    
inicio:
    btfss PIR3, 7
    bra vis_mux
    bcf PIR3, 7
    movlw 3CH
    movwf TMR0H
    movlw 0B0H
    movwf TMR0L		;carga de cuenta inicial 15536 a TMR0
    movlw 7
    cpfseq DESPLAZO
    bra nollega7
    clrf DESPLAZO
    bra vis_mux
nollega7:
    incf DESPLAZO, f
    
vis_mux:
    movff DESPLAZO, TBLPTRL
    TBLRD*+
    movff TABLAT, LATB
    bsf LATA, 0
    call un_ratito
    bcf LATA, 0
    TBLRD*+
    movff TABLAT, LATB
    bsf LATA, 1
    call un_ratito
    bcf LATA, 1
    TBLRD*+
    movff TABLAT, LATB
    bsf LATA, 2
    call un_ratito
    bcf LATA, 2
    TBLRD*
    movff TABLAT, LATB
    bsf LATA, 3
    call un_ratito
    bcf LATA, 3
    bra inicio

un_ratito:
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    return
    end upcino


