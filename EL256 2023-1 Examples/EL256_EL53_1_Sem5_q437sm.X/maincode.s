    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    
nop_veces EQU 500H
 
    ORG 001100H
mensaje: DB 71H,73H,7DH,77H    
 
    ORG 000000H
    bra configuro
    
    ORG 000020H
configuro:
    movlb 0H		    ;bank 0
    movlw 60H
    movwf OSCCON1	    ;HFINTOSC postscaler 1:1
    movlw 02H
    movwf OSCFRQ	    ;HFINTOSC 4MHz
    movlw 40H
    movwf OSCEN		    ;HFINTOSC enabled
    movlb 4H
    movlw 80H
    movwf TRISB
    movwf ANSELB	    ;RB6 al RB0 como salidas digitales
    movlw 0F0H
    movwf TRISA
    movwf ANSELA	    ;RA3 al RA0 como salidas digitales
    clrf TBLPTRU
    movlw HIGH mensaje
    movwf TBLPTRH
    movlw LOW mensaje
    movwf TBLPTRL	    ;TBLPTR apuntando a 001100H
    clrf LATA		    ;displays deshabilitados
    
inicio:
    clrf TBLPTRL
    TBLRD*+
    movff TABLAT, LATB
    bsf LATA, 0
    call nopes
    bcf LATA,0
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
    bra inicio

nopes:
    movlw 10
    movwf nop_veces
bucle:
    nop
    decfsz nop_veces, f
    bra bucle
    return
    end upcino
    
    


