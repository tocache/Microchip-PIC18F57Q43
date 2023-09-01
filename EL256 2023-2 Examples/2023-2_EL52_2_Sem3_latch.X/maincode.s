    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs

x_var EQU 500H		;etiqueta x_var para el GPR 500H
y_var EQU 501H		;etiqueta y_var para el GPR 501H 

upcino:
    ORG 000000H
    bra configuro
    
    ORG 000080H
configuro:
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    
    movlb 4H
    bsf TRISB, 4, 1
    bcf ANSELB, 4, 1
    bsf WPUB, 4, 1
    bcf TRISF, 3, 1
    bcf ANSELF, 3, 1
    bsf LATF, 3, 1	    ;RF3 a uno (LED apagado como condicion inicial)

inicio:    
    btfsc PORTB, 4, 1
    bra inicio
    btg LATF, 3, 1
    call retardo
bucle:    
    btfss PORTB, 4, 1
    bra bucle
    bra inicio
    
retardo:
    movlb 5H
    movlw 100
    movwf x_var, 1
bucle2:    
    movlw 40
    movwf y_var, 1
bucle1:    
    nop			    ;Este nop se va a ejecutar 40000 veces
    movf y_var, 1, 1
    movlb 4H
    btfss STATUS, 2, 1	    ;Pregunto si Z=1 (y_var es cero)
    bra y_var_noescero
    movlb 5H
    movf x_var, 1, 1
    movlb 4H
    btfss STATUS, 2, 1	    ;Pregunto si Z=1 (x_var es cero)
    bra x_var_noescero
    return
y_var_noescero:
    movlb 5H
    decf y_var, 1, 1
    bra bucle1
x_var_noescero:
    movlb 5H
    decf x_var, 1, 1
    bra bucle2

    end upcino
    
