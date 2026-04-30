    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT amaaa, class=CODE, reloc=2, abs
amaaa:
    ORG 000000H
    bra configuro
    
    ORG 000100H
configuro:
    ;conf mod osc
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    ;conf E/S
    movlb 4H
    movlw 80H
    movwf TRISD, 1
    movwf ANSELD, 1
    movlw 0F0H
    movwf TRISB, 1
    movwf ANSELB, 1
    movlw 0FCH
    movwf ANSELF, 1
    movlw 03H
    movwf WPUF, 1
    ;condiciones iniciales
    clrf LATB, 1	;todos los habs del display en cero
    
inicio:  
    movlw 73H
    movwf LATD, 1	;mando P a RD
    bsf LATB, 0, 1	;enciendo primer digito
    call micro_dly	;un pequeño retardo
    bcf LATB, 0, 1	;apago el primer digito
    movlw 7BH
    movwf LATD, 1	;mando e a RD
    bsf LATB, 1, 1	;enciendo segundo digito
    call micro_dly	;un pequeño retardo
    bcf LATB, 1, 1	;apago el segundo digito
    movlw 50H
    movwf LATD, 1	;mando r a RD
    bsf LATB, 2, 1	;enciendo tercer digito
    call micro_dly	;un pequeño retardo
    bcf LATB, 2, 1	;apago el tercer digito
    movlw 1CH
    movwf LATD, 1	;mando u a RD
    bsf LATB, 3, 1	;enciendo cuarto digito
    call micro_dly	;un pequeño retardo
    bcf LATB, 3, 1	;apago el cuarto digito
    bra inicio
    
micro_dly:
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

;,73H?,7BH?,50H?,1CH
    end amaaa
