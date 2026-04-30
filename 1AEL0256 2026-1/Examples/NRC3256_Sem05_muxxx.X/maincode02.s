    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
TEMPORAL EQU 500H	;label temporal a 500H
 
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
    movf PORTF, 0, 1	    ;lectura de RF hacia Wreg
    andlw 03H		    ;enmascaramiento AND con 03H hacia Wreg
    movlb 5H		    ;al BANK5
    movwf TEMPORAL, 1
    movlw 00H
    cpfseq TEMPORAL, 1
    bra siguiente1
    movlb 4H
    movlw 00H
    movwf TBLPTRL, 1
    call multiplexacion
    bra inicio
siguiente1:
    movlw 01H
    cpfseq TEMPORAL, 1
    bra siguiente2
    movlb 4H
    movlw 04H
    movwf TBLPTRL, 1
    call multiplexacion
    bra inicio
siguiente2:
    movlw 02H
    cpfseq TEMPORAL, 1
    bra siguiente3
    movlb 4H
    movlw 08H
    movwf TBLPTRL, 1
    call multiplexacion
    bra inicio
siguiente3:
    movlb 4H
    movlw 0CH
    movwf TBLPTRL, 1
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
str_peru:   DB 73H, 7BH, 50H, 1CH	;000500H
str_lego:   DB 38H, 7BH, 6FH, 5CH	;000504H
str_piso:   DB 73H, 10H, 6DH, 5CH	;000508H
str_azul:   DB 77H, 5BH, 1CH, 38H	;00050CH
   
    end amaaa






