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
    ;conf del TBLPTR
    clrf TBLPTRU, 1
    movlw 05H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1	;TBLPTR apunta a 000500H
    ;condiciones iniciales
    clrf LATB, 1	;todos los habs del display en cero
    
inicio:
    ;movlw 00H		;muevo 00H a wreg para que luego TBLPTR apunte a 500H
    movlw 04H		;muevo 00H a wreg para que luego TBLPTR apunte a 504H    
    call multiplexacion
    bra inicio

multiplexacion:
    movwf TBLPTRL, 1
    TBLRD*+
    movff TABLAT, LATD
    bsf LATB, 0, 1	;enciendo primer digito
    call micro_dly	;un pequeño retardo
    bcf LATB, 0, 1	;apago el primer digito
    TBLRD*+
    movff TABLAT, LATD
    bsf LATB, 1, 1	;enciendo segundo digito
    call micro_dly	;un pequeño retardo
    bcf LATB, 1, 1	;apago el segundo digito
    TBLRD*+
    movff TABLAT, LATD
    bsf LATB, 2, 1	;enciendo tercer digito
    call micro_dly	;un pequeño retardo
    bcf LATB, 2, 1	;apago el tercer digito
    TBLRD*
    movff TABLAT, LATD
    bsf LATB, 3, 1	;enciendo cuarto digito
    call micro_dly	;un pequeño retardo
    bcf LATB, 3, 1	;apago el cuarto digito
    return
    
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
    
    ORG 000500H
str_peru:   DB 73H, 7BH, 50H, 1CH
str_lego:   DB 38H, 7BH, 6FH, 5CH
   
    end amaaa



