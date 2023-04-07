    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 000020H
configuro:
    ;configuraciones iniciales
    movlb 0H
    movlw 60H
    movwf OSCCON1
    movlw 02H
    movwf OSCFRQ
    bsf OSCEN,6
    movlb 4H
    ;configuracion de los puertos
    movlw 80H		;1000 0000 en binario
    movwf TRISD		;RD6 al RD0 como salidas, en TRISx 0 es salida, 1 es entrada
    movwf ANSELD	;RD6 al RD0 como digitales
    movlw 0FFH		;1111 1111 en binario
    movwf TRISB		;forzamos RB3 al RB0 como entradas
    movlw 0F0H
    movwf ANSELB	;RB3 al RB0 como digitales
        
inicio:
    btfss PORTB, 0	;pregunto si RB0 es uno
    bra noesasi		;Falso, salta a etiqueta noesasi
    setf LATD		;Verdadero, enciende todos los segmentos en el display
    bra inicio		;retorna a inicio
noesasi:
    clrf LATD		;apaga todos los segmentos en el display
    bra inicio		;retorna a inicio
    end upcino





