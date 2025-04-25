;Programa para un decodificador BCD a 7 segmentos
    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 001500H
datos_7s:   DB	3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 67H    
    
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
    ;configuracion de las E/S
    movlb 4H
    movlw 80H
    movwf TRISD, 1
    movwf ANSELD, 1
    setf TRISB, 1
    movlw 0F0H
    movwf ANSELB, 1
    movlw 0FH
    movwf WPUB, 1
    ;establecer la direccion de apunte del TBLPTR
    clrf TBLPTRU, 1
    movlw 15H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1	;Direccion de apunte a 001500H en TBLPTR
    
inicio:
    comf PORTB, 0, 1	;lectura de RB en complemento y lo almaceno en Wreg
    andlw 0FH		;operacion de enmascaramiento para que pase los 4 primeros bits
    movwf TBLPTRL, 1	;muevo contenido de wreg hacia TBLPTRL
    TBLRD*		;accion de lectura de lo que apunta TBLPTR
    movf TABLAT, 0, 1	;muevo el contenido de TABLAT y lo mando a wreg
    movwf LATD, 1	;muevo contenido de wreg y lo mando a RD
    bra inicio		;regreso a inicio
    end upcino


