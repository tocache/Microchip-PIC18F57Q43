    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 001000H
deco7s:	DB 3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 67H
	;   0    1    2    3    4    5    6    7    8    9
    
    ORG 000100H
configuro:
    ;conf fuente de reloj
    movlb 0H	    ;voy al Bank0
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    ;conf puertos E/S
    movlb 4H		;voy al Bank4
    setf TRISB, 1	;RB[3:0] como entradas
    movlw 0F0H
    movwf ANSELB, 1	;RB[3:0] como digitales
    bsf TRISE, 0, 1	;RE0 como entrada
    bcf ANSELE, 0, 1	;RE0 como digital
    movlw 80H
    movwf TRISD, 1	;RD[6:0] como salida
    movwf ANSELD, 1	;RD[6:0] como digital
    ;conf adicional
    clrf TBLPTRU, 1
    movlw 10H
    movwf TBLPTRH, 1	;                    U H L
    clrf TBLPTRL, 1	;TBLPTR apuntando a 001000H

inicio_deco:
    movf PORTB, 0, 1	;Leo el puerto RB[3:0] y lo almaceno en Wreg
    andlw 0FH		;Enmascaramiento de los cuatro LSB de WReg
    movwf TBLPTRL, 1	;asignamos el valor de Wreg hacia TBLPTRL
    TBLRD*		;accion de lectura de lo apuntado por TBLPTR
    movff TABLAT, LATD	;mueve contenido leido y alojado en TABLAT hacia RD
    bra inicio_deco
    
    end upcino


