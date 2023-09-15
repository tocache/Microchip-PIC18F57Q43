    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 000100H
configuro:
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1	
    movlw 02H
    movwf OSCFRQ, 1	;HFINTOSC = 4MHz
    movlw 40H
    movwf OSCEN, 1
    movlb 4H
    movlw 80H
    movwf TRISD, 1	;RD6 al RD0 como salidas
    movwf ANSELD, 1	;RD6 al RD0 como digitales
    movlw 0F0H
    movwf TRISB, 1	;RB3 al RB0 como salidas
    movwf ANSELB, 1	;RB3 al RB0 como digitales
    clrf LATB, 1	;RB3 al RB0 son ceros al inicio

inicio:
    movlw 76H
    movwf LATD, 1	;Letra H al RD
    bsf LATB, 0, 1	;enciendo primer digito del display
    call nopes
    bcf LATB, 0, 1	;apago el primer digito del display
    movlw 3FH
    movwf LATD, 1	;Letra O al RD
    bsf LATB, 1, 1	;enciendo segundo digito del display
    call nopes
    bcf LATB, 1, 1	;apago el segundo digito del display
    movlw 38H
    movwf LATD, 1	;Letra L al RD
    bsf LATB, 2, 1	;enciendo tercer digito del display
    call nopes
    bcf LATB, 2, 1	;apago el tercer digito del display
    movlw 77H
    movwf LATD, 1	;Letra A al RD
    bsf LATB, 3, 1	;enciendo cuarto digito del display
    call nopes
    bcf LATB, 3, 1	;apago el cuarto digito del display
    bra inicio
    
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
    end upcino