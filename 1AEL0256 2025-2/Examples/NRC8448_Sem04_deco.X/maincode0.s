;Programa para hacer un decodificador
    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcinos, class=CODE, reloc=2, abs
upcinos:
    ORG 000000H
    bra configuro
    
    ORG 000100H
tabla_bcd:  DB 3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 67H    
    
    ORG 000200H
configuro:
    ;conf del modulo de oscilador
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    ;conf de las E/S
    movlb 4H
    movlw 0F0H	    ;11110000B
    ;no es necesario conf RA3 a RA0 como entradas pq ya lo son en un PoR
    movwf ANSELA, 1 ;RA3 al RA0 como digitales
    movlw 0FH	    ;00001111B
    movwf WPUA, 1   ;RA3 al RA0 con pullup activadas
    movlw 80H	    ;10000000B
    movwf TRISD, 1  ;RD6 al RD0 como salidas
    movwf ANSELD, 1 ;RD6 al RD0 como digitales
    movlw 0F8H	    ;11111000B
    movwf TRISF, 1  ;RF2 al RF0 como salidas
    movwf ANSELF, 1 ;RF2 al RF0 como digitales
    ;asignar el TBLPTR a la direccion 100H de la mem de prog
    clrf TBLPTRU, 1
    movlw 01H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1 ;TBLPTR apuntando a la direccion 100H
    
inicio:
    comf PORTA, 0, 1	;lectura en complemento de RA
    andlw 0FH		;enmascaramiento para que solo tengamos RA3 a RA0
    movwf TBLPTRL, 1	;actualizamos la direccion de apunte de TBLPTR
    TBLRD*		;accion de lectura del TBLPTR
    movff TABLAT, LATD	;movemos contenido de TABLAT hacia LATD
comparacion:
    movlw 5
    cpfsgt TBLPTRL	;pregunto si es mayor a 5
    bra noesmayor	;falso, salta a la siguiente pregunta
    movlw 01H		;verdad, prendo primer LED
    movwf LATF, 1
    bra inicio
noesmayor:
    movlw 5
    cpfseq TBLPTRL	;pregunto si es igual a 5
    bra esmenor		;falso, salta a ejecutar esmenor
    movlw 02H		;verdad, prendo segundo LED
    movwf LATF, 1
    bra inicio
esmenor:
    movlw 04H		;prendo tercer LED
    movwf LATF, 1
    bra inicio
    
    end upcinos

