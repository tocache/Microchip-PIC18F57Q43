    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
temporal EQU 500H
 
    ORG 000000H
    bra configuro

    ORG 000020H
configuro:
    movlb 0
    movlw 60H
    movwf OSCCON1
    movlw 02H
    movwf OSCFRQ
    bsf OSCEN, 6
    movlb 4
    clrf TRISD
    clrf ANSELD
    movlw 0FFH
    movwf TRISB
    clrf ANSELB
    movlw 0FH
    movwf WPUB
    
inicio:
    movf PORTB, W
    andlw 0FH
    movwf temporal
eval_btn0:
    movlw 0EH
    cpfseq temporal
    goto eval_btn1
    movlw 01110110B
    movwf LATD
    bra inicio
eval_btn1:
    movlw 0DH
    cpfseq temporal
    goto eval_btn2
    movlw 00111111B
    movwf LATD
    bra inicio
eval_btn2:
    movlw 0BH
    cpfseq temporal
    goto eval_btn3
    movlw 00111000B
    movwf LATD
    bra inicio
eval_btn3:
    movlw 07H
    cpfseq temporal
    goto invalido
    movlw 01110111B
    movwf LATD
    bra inicio    
invalido:    
    clrf LATD
    bra inicio
    end upcino







