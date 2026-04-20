;Este es mi primer programa hecho en XC8 PIC Assembler
    
    ;Modelo del procesador
    PROCESSOR 18F57Q43
    ;Llamada a la cabecera.inc
    #include "cabecera.inc"
    
    ;Declaracion de un PSECT
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H		;Vector de reset
    bra configuro	;Salto a zona de configuracion
    
    ORG 000100H		;Zona de programa de usuario
configuro:
    ;Config del modulo de oscilador
    movlb 0H		;Al Bank0
    movlw 60H
    movwf OSCCON1, 1	;NOSC=HFINTOSC NDIV 1:1
    movlw 02H
    movwf OSCFRQ, 1	;HFINTOSC 4MHz
    movlw 40H
    movwf OSCEN, 1	;HFINTOSC enabled
    ;Conf las E/S de la aplicacion
    movlb 4H		;Al Bank4
    movlw 0FFH
    movwf TRISB, 1	;Todo el RB como entradas
    movlw 0FCH
    movwf ANSELB, 1	;RB1 y RB0 como digital
    bcf TRISD, 0, 1	;RD0 como salida
    bcf ANSELD, 0, 1	;RD0 como digital
    
inicio:
    btfss PORTB, 0, 1	;Pregunto si RB0 es uno
    bra falso		;Falso, salta a label falso
    btfss PORTB, 1, 1	;Verdad y Preguntando si RB1 es uno
    bra falso		;Falso, salta a label falso
    bsf LATD, 0, 1	;Verdad y enciende LED en RD0
    bra inicio		;Salto a label inicio
falso:
    bcf LATD, 0, 1	;apago LED en RD0
    bra inicio		;Salto a label inicio
    
    end upcino

