    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcinos, class=CODE, reloc=2, abs
upcinos:
    
num_nopes EQU 500H
 
    ORG 001200H
mensaje: DB 73H, 06H, 38H, 77H
 
    ORG 000000H
    bra configuro
    
    ORG 000020H
configuro:
    movlb 0H
    movlw 60H
    movwf OSCCON1
    movlw 02H
    movwf OSCFRQ
    movlw 40H
    movwf OSCEN

    movlb 4H
    movlw 80H
    movwf TRISB
    movwf ANSELB
    movlw 0F0H
    movwf TRISA
    movwf ANSELA
    
    clrf TBLPTRU
    movlw HIGH mensaje
    movwf TBLPTRH
    movlw LOW mensaje
    movwf TBLPTRL
    
inicio:
    clrf TBLPTRL
    call multiplex
    bra inicio

multiplex:
    TBLRD*+
    movff TABLAT, LATB
    bsf LATA, 0
    call nopes
    bcf LATA, 0
    TBLRD*+
    movff TABLAT, LATB
    bsf LATA, 1
    call nopes
    bcf LATA, 1
    TBLRD*+
    movff TABLAT, LATB
    bsf LATA, 2
    call nopes
    bcf LATA, 2
    TBLRD*
    movff TABLAT, LATB
    bsf LATA, 3
    call nopes
    bcf LATA, 3
    return
    
nopes:
    movlw 10
    movwf num_nopes
bucle:
    nop
    decfsz num_nopes, f
    bra bucle
    return
    
    end upcinos


