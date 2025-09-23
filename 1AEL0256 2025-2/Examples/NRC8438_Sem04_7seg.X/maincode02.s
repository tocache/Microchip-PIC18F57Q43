    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcinos, class=CODE, reloc=2, abs
upcinos:
    ORG 000000H	    ;vector de RESET
    bra configuro
    
    ORG 000100H	    ;zona de constantes de la decodificacion
		    ;0    1    2    3    4    5    6    7    8    9
deco_siete_s:	DB  3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 67H    
    
    ORG 000200H	    ;zona de programa de la app
configuro:
    ;configuro el modulo de oscilador
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    ;configuro las E/S
    movlb 4H
    movlw 0FFH
    movwf TRISA, 1	;RA3 al RA0 como entradas
    movlw 0F0H
    movwf ANSELA, 1	;RA3 al RA0 como digitales
    movlw 0FH
    movwf WPUA, 1	;RA3 al RA0 con pullup activadas
    movlw 80H
    movwf TRISD, 1	;RD6 al RD0 como salidas
    movwf ANSELD, 1	;RD6 al RD0 como digitales
    movlw 0F8H
    movwf TRISF, 1	;RF2 al RF0 como salidas
    movwf ANSELF, 1	;RF2 al RF0 como digitales
    ;establecer la direccion de apunte de TBLPTR a 000100H
    clrf TBLPTRU, 1
    movlw 01H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1	;TBLPTR apunta a 000100H de la mem de prog
    
inicio:
    comf PORTA, 0, 1	;lectura del contenido del puerto RA en complemento y lo aloja en Wreg
    andlw 0FH		;operacion de enmascaramiento para que pase solo RA3 a RA0
    movwf TBLPTRL, 1	;asignando al TBLPTR el valor de entrada para la decodificacion
    TBLRD*		;accion de lectura, el resultado lo aloja en TABLAT
    movf TABLAT, 0, 1	;el dato de TABLAT lo mando a Wreg
    movwf LATD, 1	; escribimos el dato decodificado en el puerto D
    movlw 5		;cargando valor 5 en wreg
    cpfsgt TBLPTRL, 1	;pregunto si TBLPTRL es mayor que 5
    bra preguntasiguiente1
    movlw 01H
    movwf LATF, 1	;encendiendo solo RF0
    bra inicio
preguntasiguiente1:
    cpfseq TBLPTRL, 1	;pregunto si TBLPTRL es igual a 5
    bra esmenor
    movlw 02H
    movwf LATF, 1	;enciendiendo solo RF1
    bra inicio
esmenor:
    movlw 04H
    movwf LATF, 1	;enciendo solo RF2
    bra inicio
    end upcinos
    
    




