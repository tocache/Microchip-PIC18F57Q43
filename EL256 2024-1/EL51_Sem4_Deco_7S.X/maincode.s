    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
	ORG 000000H
	bra configuro
	
	ORG 001000H
tabla_7s:   DB 	3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 67H
   
	ORG 000100H
configuro:
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 03H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    movlb 4H
    movlw 80H
    movwf TRISD, 1
    movwf ANSELD, 1
    ;Por defecto todos los puertos son entradas
    movlw 0F0H
    movwf ANSELB, 1	;RB0 a RB3 como digitales
    movlw 0FH
    movwf WPUB, 1	;weak pullup para RB0-RB3
    clrf TBLPTRU, 1
    movlw 10H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1	;TBLPTR esta apuntando a 1000H
    clrf TBLPTRL, 1	;TBLPTR esta apuntando a 1000H    
inicio:
    comf PORTB, 0, 1	;complemento contenido de PORTB hacia Wreg
    andlw 0FH		;enmascaramiento a Wreg con 0FH
    ;modo violento
    ;movlw 0FH
    ;andwf PORTB, 0, 1
    movwf TBLPTRL, 1
    TBLRD*		;accion de lectura de TBLPTR
    movff TABLAT, LATD	;mando dato decodificado al display
    bra inicio
    
    end upcino