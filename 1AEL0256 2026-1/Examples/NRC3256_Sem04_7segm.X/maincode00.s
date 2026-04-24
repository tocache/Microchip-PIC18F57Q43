    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H		    ;Vector de RESET
    bra configuro	    ;salto a label configuro
    
    ORG 000100H
configuro:
    ;conf modulo oscilador
    movlb 0H		    ;En el Bank0
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    ;conf E/S
    movlb 4H
    movlw 80H
    movwf TRISD, 1	    ;RD6 al RD0 como salidas
    movwf ANSELD, 1	    ;RD6 al RD0 como digitales
    movlw 0F0H
    movwf ANSELB, 1	    ;RB3 al RB0 como digitales
    ;conf TBLPTR
    clrf TBLPTRU, 1
    movlw 02H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1	    ;TBLPTR esta apuntando a 000200H
    
inicio:
    movf PORTB, 0, 1	    ;Leo PORTB y lo mando a Wreg
    andlw 0FH		    ;enmascaramiento AND a wreg
    movwf TBLPTRL, 1	    ;actualizo direccion de apunte de TBLPTR
    TBLRD*		    ;accion de lectura de lo que apunta TBLPTR
    movff TABLAT, LATD	    ;muevo TABLAT hacia LATD
    bra inicio
    
    ORG 000200H		    ;zona donde alojas los datos del decoder
datos_7s: DB 3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 67H
 
    end upcino

