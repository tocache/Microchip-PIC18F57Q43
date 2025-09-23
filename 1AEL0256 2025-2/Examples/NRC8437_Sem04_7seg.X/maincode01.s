    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcinos, class=CODE, reloc=2, abs
upcinos:
    ORG 000000H
    bra configuro
    
    ORG 001000H
		;0   1    2    3    4    5    6    7    8    9
decod_7s:   DB 3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 67H     
    
    ORG 000100H
configuro:
    ;configuramos el modulo de oscilador
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    ;configuramos las E/S
    movlb 4H
    movlw 80H
    movwf TRISD, 1	    ;RD0 al RD6 como salidas
    movwf ANSELD, 1	    ;RD0 al RD6 como digitales
    movlw 0FFH
    movwf TRISA, 1	    ;RA3 al RA0 como entradas
    movlw 0F0H
    movwf ANSELA, 1	    ;RA3 al RA0 como digitales
    movlw 0FH
    movwf WPUA, 1	    ;RA3 al Ra0 con pullup activadas
    ;configurar el TBLPTR para que apunte a direccion 001000H
    clrf TBLPTRU, 1
    movlw 10H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1	    ;El puntero TBLPTR esta apuntando a 001000H

inicio:    
    comf PORTA, 0, 1	    ;lectura en completo de RA y lo mete a Wreg
    andlw 0FH		    ;operacion de enmascaramiento, para que solo pase RA3 a RA0
    movwf TBLPTRL, 1	    ;asignando a TBLPTR el valor de la entrada de decodificación (Wreg)
    TBLRD*		    ;accion de lectura de lo que apunta el TBLPTR
    movf TABLAT, 0, 1	    ;obtengo el dato de TABLAT en Wreg
    movwf LATD, 1
    bra inicio
    
    end upcinos
    
    
    


