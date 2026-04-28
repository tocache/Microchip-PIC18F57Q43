    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upeceno, class=CODE, reloc=2, abs
upeceno:
    ORG 000000H
    bra configuro
    
    ORG 000500H
str_pase: DB 73H,5FH,6DH,7BH
str_nota: DB 54H,5CH,78H,5FH
    
    ORG 000100H
configuro:
    ;conf del modulo de oscilador
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1	    ;NOSC LFINTOSC NDIV 1:8
    movlw 02H
    movwf OSCFRQ, 1	    ;HFINTOSC a 4MHz
    movlw 40H
    movwf OSCEN, 1	    ;HFINTOSC enabled
    ;conf E/S
    movlb 4H
    movlw 80H
    movwf TRISD, 1	    ;RD6 al RD0 como salidas
    movwf ANSELD, 1	    ;RD6 al RD0 como digitales
    movlw 0F0H
    movwf TRISB, 1	    ;RB3 al RB0 como salidas
    movwf ANSELB, 1	    ;RB3 al RB0 como digitales
    bcf ANSELB, 4, 1	    ;RB4 como digital
    bsf WPUB, 4, 1	    ;RB4 con pullup activo
    ;conf TBLPTR
    clrf TBLPTRU, 1
    movlw 05H
    movwf TBLPTRH, 1
    clrf TBLPTRL	    ;TBLPTR apunta a 000500H de la mem prog
    ;cond inicio
    clrf LATB, 1	    ;todos los habilitadores en 0

inicio:
    btfsc PORTB, 4, 1	    ;pregunto si pulse el boton
    bra no_lo_presione
    movlw 04H
    movwf TBLPTRL, 1
    call multiplex
    bra inicio
    
no_lo_presione:
    clrf TBLPTRL, 1
    call multiplex
    bra inicio
    
multiplex:    
    TBLRD*+
    movff TABLAT, LATD
    bsf LATB, 0, 1
    call nopes
    bcf LATB, 0, 1
    TBLRD*+
    movff TABLAT, LATD
    bsf LATB, 1, 1
    call nopes
    bcf LATB, 1, 1
    TBLRD*+
    movff TABLAT, LATD
    bsf LATB, 2, 1
    call nopes
    bcf LATB, 2, 1
    TBLRD*
    movff TABLAT, LATD
    bsf LATB, 3, 1
    call nopes
    bcf LATB, 3, 1 
    return
    
nopes:
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
   
    end upeceno
   
    





