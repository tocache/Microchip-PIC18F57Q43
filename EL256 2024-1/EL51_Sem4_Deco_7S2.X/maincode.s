    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 001000H
tabla_7s:   DB 3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 67H
       
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
    movlw 0FFH
    movwf TRISB, 1
    movlw 0F0H
    movwf ANSELB, 1
    movlw 0FH
    movwf WPUB, 1
    movlw 80H
    movwf TRISD, 1
    movwf ANSELD, 1
    movlw 00H
    movwf TBLPTRU, 1
    movlw 10H
    movwf TBLPTRH, 1
    movlw 00H
    movwf TBLPTRL, 1
    
inicio:
    comf PORTB, 0, 1	    ;complemento PORTB y lo mando a Wreg
    andlw 0FH		    ;enmascaramiento para que pase solo los 4 menos significativos
    movwf TBLPTRL, 1	    ;cambio de direccion de apunte de TBLPTR segun entrada de botones
    TBLRD*		    ;accion de lectura del TBLPTR
    movff TABLAT, LATD	    ;mando el contenido leido al puerto del display
    bra inicio
    
    end upcino
    

