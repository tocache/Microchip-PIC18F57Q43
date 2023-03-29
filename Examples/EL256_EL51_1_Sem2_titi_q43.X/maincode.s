    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
var_i EQU 500H    
var_j EQU 501H
var_k EQU 502H    
    
    ORG 000000H
    bra configuro
    
    ORG 000020H
configuro:
    movlb 0H
    movlw 60H
    movwf OSCCON1
    movlw 02H
    movwf OSCFRQ
    bsf OSCEN, 6
    movlw 4H
    bcf TRISF, 3	    ;RD0 como salida
    bcf ANSELF, 3	    ;RD0 como digital
   
inicio:
    movlb 5
    call repeticua	    ;subrutina de retardo
    btg LATF, 3		    ;basculo RE
    bra inicio		    ;salto a inicio
    
repeticua:   
    movlw 80
    movwf var_i, b
otro1:
    call bucle1		;Salto a subrutina
    decfsz var_i, 1, 0
    goto otro1
    return

bucle1:
    movlw 40
    movwf var_j, b
otro2:
    call bucle2		;Salto a subrutina
    decfsz var_j, 1, 0
    goto otro2
    return
    
bucle2:
    movlw 20
    movwf var_k, b
otro3:
    nop			
    decfsz var_k, 1, 0
    goto otro3
    return    
    end upcino


