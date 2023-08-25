    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
var_i EQU 500H    
var_j EQU 501H
var_k EQU 502H      
    
    ORG 001000H
mensaje:    DB 76H, 3FH, 38H, 77H    
;mensaje1: DB "HOLA"    
    
    ORG 000000H
    bra configuro
    
    ORG 000020H
configuro:
    BANKSEL 0
    movlw 60H
    movwf OSCCON1
    movlw 02H
    movwf OSCFRQ
    movlw 40H
    movwf OSCEN
    BANKSEL 4
    clrf TBLPTRU
    movlw HIGH mensaje
    movwf TBLPTRH
    movlw LOW mensaje
    movwf TBLPTRL
    movlw 80H
    movwf TRISD
    movwf ANSELD
    movlw 0F0H
    movwf TRISB
    movwf ANSELB
    clrf LATB

inicio:    
    TBLRD*+
    movff TABLAT, LATD
    bsf LATB, 0
    call repeticua
    bcf LATB, 0
    TBLRD*+
    movff TABLAT, LATD
    bsf LATB, 1
    call repeticua
    bcf LATB, 1
    TBLRD*+
    movff TABLAT, LATD
    bsf LATB, 2
    call repeticua
    bcf LATB, 2
    TBLRD*
    movff TABLAT, LATD
    bsf LATB, 3
    call repeticua
    bcf LATB, 3
    clrf TBLPTRL
    bra inicio
    
repeticua:   
    movlw 20
    movwf var_i
otro1:
    call bucle1		;Salto a subrutina
    decfsz var_i, 1
    goto otro1
    return

bucle1:
    movlw 20
    movwf var_j
otro2:
    call bucle2		;Salto a subrutina
    decfsz var_j, 1
    goto otro2
    return
    
bucle2:
    movlw 20
    movwf var_k
otro3:
    nop			
    decfsz var_k, 1
    goto otro3
    return      
    
    end upcino





