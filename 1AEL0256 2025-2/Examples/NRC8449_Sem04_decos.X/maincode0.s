 ;Programa para un decodificador BCD a siete segmentos
    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcinos, class=CODE, reloc=2, abs
upcinos:
    ORG 000000H
    bra configuro
    
    ORG 000100H
datos_tabla:	DB 3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 67H
    
    ORG 000200H
configuro:
    ;conf modulo oscilador
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    ;conf las E/S
    movlb 4H
    ;por defecto los puertos estan como entradas analogicas
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
    ;asignarle la direccion 100H al TBLPTR
    clrf TBLPTRU, 1
    movlw 01H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1	;TBLPTR asignado a direccion 100H
    
inicio:
    comf PORTA, 0, 1	;Leo contenido en complemento de RA y lo mando a Wreg
    andlw 0FH		;enmascaramiento para que pase solo los cuatro LSB
    movwf TBLPTRL, 1	;actualizamos direccion de TBLPTR
    TBLRD*		;accion de lectura en el TBLPTR
    movff TABLAT, LATD	;muevo contenido de TABLAT a LATD (puerto del display)
    ;funcion de comparacion con valor 5
    movlw 5
    cpfsgt TBLPTRL, 1	;pregunto si es mayor que 5
    bra noesmayor
    movlw 01H
    movwf LATF, 1	;prendo primer LED
    bra inicio
noesmayor:
    movlw 5
    cpfseq TBLPTRL, 1	;pregunto si es igual a 5
    bra noesigual
    movlw 02H
    movwf LATF, 1	;prendo el segundo LED
    bra inicio
noesigual:
    movlw 04H
    movwf LATF, 1	;prendo tercer LED
    bra inicio
    
    end upcinos
    





