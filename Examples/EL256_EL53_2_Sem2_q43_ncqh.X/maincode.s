    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
var_i EQU 000H    
var_j EQU 001H    
var_k EQU 002H    

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
    bcf TRISF, 3
    bcf ANSELF, 3
    bcf TRISD, 0
    bcf ANSELD, 0
    bcf TRISA, 0
    bcf ANSELA, 0
    bsf TRISB, 4
    bcf ANSELB, 4
    bsf WPUB, 4
    
inicio:
    btfsc PORTB, 4
    bra apagado
    bsf LATF, 3
    bcf LATA, 0
    bsf LATD, 0
    call repeticua
    bsf LATF, 3
    bsf LATA, 0
    bcf LATD, 0
    call repeticua
    bcf LATF, 3
    bcf LATA, 0
    bcf LATD, 0
    call repeticua
    bsf LATF, 3
    bsf LATA, 0
    bcf LATD, 0
    call repeticua
    bra inicio
    
apagado:
    bsf LATF, 3
    bcf LATA, 0
    bcf LATD, 0
    bra inicio
    
repeticua:   
    movlw 80
    movwf var_i
otro1:
    call bucle1		;Salto a subrutina
    decfsz var_i, f
    goto otro1
    return
bucle1:
    movlw 20
    movwf var_j
otro2:
    call bucle2		;Salto a subrutina
    decfsz var_j, f
    goto otro2
    return
bucle2:
    movlw 20
    movwf var_k
otro3:
    nop			
    decfsz var_k, f
    goto otro3
    return      
    end upcino





