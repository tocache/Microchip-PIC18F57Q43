;Decodificador BCD a siete segmentos catodo comun con entrada negada
    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 001000H
tablex_dec: DB 3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 67H    
    
    ORG 000100H
configuro:
    ;configuracion de la fuente de reloj al CPU
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
    ;direccion de apunte de TBLPTR
    clrf TBLPTRU, 1
    movlw 10H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1	;Direccion a la que apunta TBLPTR: 001000H
    
inicio:
    comf PORTB, 0, 1	;leo el RB en complemento y lo almaceno en Wreg
    andlw 0FH		;enmascaramiento para que solo sea valido RB3 al RB0
    movwf TBLPTRL, 1	;mandamos la direccion de apunte al TBLPTR
    TBLRD*		;accion de lectura de lo que apunta TBLPTR
    movf TABLAT, 0, 1	;muevo contenido de TABLAT hacia Wreg
    movwf LATD, 1	;muevo contenido de Wreg a RD
    end upcino


