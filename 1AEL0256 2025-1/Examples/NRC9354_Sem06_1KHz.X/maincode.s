;Programa para genera una seal de 1khz y dc 50%
    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 000100H
configuro:
    ;configuracion del modulo de oscilador
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    ;configuracion del Timer0
    movlb 3H
    movlw 80H
    movwf T0CON0, 1
    movlw 41H
    movwf T0CON1, 1
    movlw 250
    movwf TMR0H, 1	;valor d ereferencia de comparacion
    ;configuracion de las entradas y salidas
    movlb 4H
    bsf TRISD, 0, 1
    bcf ANSELD, 0, 1
    bsf WPUD, 0, 1
    movlw 0FCH
    movwf TRISF, 1
    movwf ANSELF, 1
    ;condiciones iniciales de la aplicacion
    bsf LATF, 1, 1	;enciendo el LED en RF1
        
inicio:
    btfss PIR3, 7, 1	;pregunto si se levanto TMR0IF
    bra $-2		;aun no se levanto la bandera salta para atras
    bcf PIR3, 7, 1	;bajo la bandera
    btg LATF, 0, 1	;basculo LED en RF0
    bra inicio
    
    end upcino


