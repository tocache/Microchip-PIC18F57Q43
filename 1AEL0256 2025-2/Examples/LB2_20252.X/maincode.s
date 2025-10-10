    PROCESSOR 18F57Q43
    #include "cabecera.inc"

veloc EQU 500H
desp  EQU 501H
indic EQU 502H  
var_nopes EQU 503H
    
    PSECT elebe2, class=CODE, reloc=2
elebe2:
    ORG 000000H
    bra configuro
    
    ORG 000010H	    ;vector de la INT0 (2*08H)
    DW INT0_ISR shr 2
    
    ORG 00003EH	    ;vector de la TMR0 (2*1FH)
    DW TMR0_ISR shr 2
    
    ORG 000060H	    ;vector de la INT1 (2*30H)
    DW INT1_ISR shr 2

    ORG 0000A0H	    ;vector de la INT2 (2*50H)
    DW INT2_ISR shr 2
    
    ORG 000200H
mensaje_p1: DB	00H, 00H, 00H, 00H, 3EH, 73H, 39H, 00H
mensaje_p2: DB	30H, 54H, 6FH, 7BH, 54H, 10H, 7BH, 50H
mensaje_p3: DB	10H, 5FH, 00H, 6FH, 5FH, 54H, 5FH, 5EH
mensaje_p4: DB	5CH, 50H, 5FH, 00H, 5EH, 7BH, 00H, 38H
mensaje_p5: DB	5FH, 00H, 6DH, 7BH, 15H, 5FH, 54H, 5FH
mensaje_p6: DB	00H, 1CH, 54H, 10H, 1CH, 7BH, 50H, 6DH
mensaje_p7: DB	10H, 78H, 5FH, 50H, 10H, 5FH, 00H, 5BH
mensaje_p8: DB	3FH, 5BH, 6DH, 00H, 00H, 00H, 00H
   
;Cada rutina de interrupción debe de tener su propio PSECT
    PSECT INT0_ISR, class=CODE, reloc=4
INT0_ISR:
    bcf PIR1, 0, 1	;bajamos bandera INT0IF
    movlb 5H
    bcf indic, 0, 1
    movlb 4H
    retfie

    PSECT TMR0_ISR, class=CODE, reloc=4
TMR0_ISR:
    bcf PIR3, 7, 1	;bajamos bandera TMR0IF
    movlb 5H
    movlw 59
    cpfseq desp, 1
    bra suma_desp
    clrf desp, 1
    bra next_desp
suma_desp:
    incf desp, 1, 1
next_desp:
    movlb 4H    
    retfie    
    
    PSECT INT1_ISR, class=CODE, reloc=4
INT1_ISR:
    bcf PIR6, 0, 1	;bajamos bandera INT0IF
    movlb 5H
    bsf indic, 0, 1
    movlb 4H    
    retfie     

    PSECT INT2_ISR, class=CODE, reloc=4
INT2_ISR:
    bcf PIR10, 0, 1	;bajamos bandera INT0IF
    btg T0CON0, 7, 1
    movlb 4H
    retfie     

    ;Inicio de codigo de usuario    
    PSECT code
    ORG 000300H
configuro:
    ;conf mod osc a 4MHz
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    ;conf PPS
    movlb 2H
    movlw 01H
    movwf INT0PPS, 1
    movlw 0DH
    movwf INT1PPS, 1
    movlw 2AH
    movwf INT2PPS, 1
    ;conf TMR0
    movlb 3H
    movlw 80H
    movwf T0CON0, 1
    movlw 86H
    movwf T0CON1, 1
    movlw 242
    movwf TMR0H, 1
    ;conf E/S
    movlb 4H
    movlw 80H
    movwf TRISD, 1
    movwf ANSELD, 1
    movlw 0F0H
    movwf TRISB, 1
    movlw 0D0H
    movwf ANSELB, 1
    bsf WPUB, 5, 1
    bcf ANSELA, 1, 1
    bsf WPUA, 1, 1
    bcf ANSELF, 2, 1
    bsf WPUF, 2, 1
    bcf ANSELC, 5, 1
    bsf WPUC, 5, 1
    ;conf TBLPTR
    clrf TBLPTRU, 1
    movlw 02H
    movwf TBLPTRH, 1
    movlw 00H
    movwf TBLPTRL, 1
    ;conf interrupts
    bsf PIE1, 0, 1
    bcf PIR1, 0, 1
    bsf PIR3, 7, 1
    bcf PIR3, 7, 1
    bsf PIE6, 0, 1
    bcf PIR6, 0, 1
    bsf PIE10, 0, 1
    bcf PIR10, 0, 1
    movlw 80H
    movwf INTCON0, 1
    ;cond iniciales
    clrf LATB, 1
    clrf LATD, 1
    movlb 5H
    clrf veloc, 1
    clrf desp, 1
    clrf indic, 1
    movlb 4H
    
inicio:
    btfsc PORTC, 5, 1
    bra next_veloc
    movlb 5H
    movlw 3
    cpfseq veloc, 1
    bra mas_veloc
    clrf veloc, 1
    bra suelta_rc5
mas_veloc:
    incf veloc, 1, 1
suelta_rc5:
    movlb 4H
    btfss PORTC, 5, 1
    bra $-2
next_veloc:
    movlb 5H
    movlw 0
    cpfseq veloc, 1
    bra mas_rapido1
    movlb 3H
    movlw 242
    movwf TMR0H, 1
    bra hacia_mux
mas_rapido1:
    movlb 5H
    movlw 1
    cpfseq veloc, 1
    bra mas_rapido2
    movlb 3H
    movlw 121
    movwf TMR0H, 1
    bra hacia_mux
mas_rapido2:
    movlb 5H
    movlw 1
    cpfseq veloc, 1
    bra mas_rapido3
    movlb 3H
    movlw 60
    movwf TMR0H, 1
    bra hacia_mux
mas_rapido3:
    movlb 3H
    movlw 30
    movwf TMR0H, 1
    bra hacia_mux
hacia_mux:
    movlb 4H
    call multiplexacion
    bra inicio
    
multiplexacion:
    movlb 5H
    btfsc indic, 0, 1
    bra der_izq
    movf desp, 0, 1
    sublw 60
    bra init_mux
der_izq:
    movf desp, 0, 1
init_mux:    
    movlb 4H
    movwf TBLPTRL, 1
    TBLRD*+
    movff TABLAT, LATD
    bsf LATB, 0, 1
    call miniretardo
    bcf LATB, 0, 1
    TBLRD*+
    movff TABLAT, LATD
    bsf LATB, 1, 1
    call miniretardo
    bcf LATB, 1, 1
    TBLRD*+
    movff TABLAT, LATD
    bsf LATB, 2, 1
    call miniretardo
    bcf LATB, 2, 1
    incf TBLPTRL, 1, 1
    TBLRD*
    movff TABLAT, LATD
    bsf LATB, 3, 1
    call miniretardo
    bcf LATB, 3, 1
    return
   
miniretardo:
    movlb 5H
    movlw 20
    movwf var_nopes, 1
    nop
    decfsz var_nopes, 1, 1
    bra $-4
    movlb 4H
    return
    
    end elebe2
