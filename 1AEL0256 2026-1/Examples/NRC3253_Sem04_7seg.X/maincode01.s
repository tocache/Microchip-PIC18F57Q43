    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H		;vector de reset
    bra configuro
    
    ORG 000200H
	        ;0   1    2    3    4    5    6    7    8    9
tabls_7s:   DB 3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 67H    
    
    ORG 000100H		;zona de user program
configuro:
    ;conf el modulo de oscilador
    movlb 0H		    ;Al Bank0
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    ;conf las E/S
    movlb 4H		    ;Al Bank4
    movlw 80H
    movwf TRISD, 1	    ;RD6 al RD0 como salidas
    movwf ANSELD, 1	    ;RD6 al RD0 como digitales
    movlw 0F0H
    ;Por defecto RB es entrada en un Power on Reset
    movwf ANSELB, 1	    ;RB3 al RB0 como digitales
    ;conf el puntero de tabla para que apunte a 200H
    clrf TBLPTRU, 1
    movlw 02H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1	    ;TBLPTR esta apuntando a 000200H
    
inicio:  
    movf PORTB, 0, 1	    ;Leo RB y lo almaceno en Wreg
    andlw 0FH		    ;operacion de enmascaramiento AND con Wreg
    movwf TBLPTRL, 1	    ;muevo Wreg a TBLPTRL
    TBLRD*		    ;accion de lectura de lo que apunta TBLPTR
    movff TABLAT, LATD	    ;muevo contenido de TABLAT hacia RD
    bra inicio
    
    end upcino


