;Programa de decodificador BCD a siete segmentos
    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro

    ORG 001000H
tablita:    DB 3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 67H
    
    ORG 000100H
configuro:
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    movlb 4H
    movlw 80H
    movwf TRISD, 1
    movwf ANSELD, 1
    setf TRISB, 1
    movlw 0F0H
    movwf ANSELB, 1
    movlw 0FH
    movwf WPUB, 1
    clrf TBLPTRU, 1
    movlw 10H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1	;direccion de TBLPTR 001000H
        
inicio:
    comf PORTB, 0, 1	;leemos dato en complemento de PORTB y lo mandamos a Wreg
    andlw 0FH		;operacion de enmascaramiento para que solo pase RB0 al RB3
    movwf TBLPTRL, 1
    TBLRD*
    movff TABLAT, LATD
    bra inicio
    end upcino


