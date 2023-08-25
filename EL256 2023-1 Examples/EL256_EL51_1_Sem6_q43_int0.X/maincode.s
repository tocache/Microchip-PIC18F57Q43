    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    
var_i EQU 500H    
var_j EQU 501H
var_k EQU 502H   
 
    ORG 000000H		;vector de reset
    bra configuro

    ORG 000008H		;vector de interurpcion de alta prioridad
    bra INT0_ISR
    
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
    bcf TRISA, 0	;RA0 salida
    bcf ANSELA, 0	;RA0 digital
    movlw 0FCH
    movwf TRISD		;RD1 a RD0 como salidas
    movwf ANSELD	;RD1 a RD0 como digitales
    bsf TRISB, 0	;RB0 como entrada
    bcf ANSELB, 0	;RB0 como digital
    bsf WPUB, 0		;RB0 con pullup
    bsf INTCON0, 7	;GIE=1
    bcf INTCON0, 0	;INT0EDG=0
    bsf PIE1, 0		;INT0IE=1

inicio:
    bsf LATA, 0		;RA0 en uno
    call repeticua	;subrutina de retardo
    bcf LATA, 0		;RA0 en cero
    call repeticua	;subrutina de retardo
    bra inicio
    
INT0_ISR:
    bcf PIR1, 0		;Bajamos la bandera INT0IF
    incf LATD, f
    retfie
    
repeticua:   
    movlw 80
    movwf var_i
otro1:
    call bucle1		;Salto a subrutina
    decfsz var_i, 1
    goto otro1
    return
bucle1:
    movlw 50
    movwf var_j
otro2:
    call bucle2		;Salto a subrutina
    decfsz var_j, 1
    goto otro2
    return
bucle2:
    movlw 18
    movwf var_k
otro3:
    nop			
    decfsz var_k, 1
    goto otro3
    return    
    
    end upcino    
    
    





