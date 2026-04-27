    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H		    ;vector de RESET
    bra configuro	    ;salto a label configuro

    ORG 000300H
tablita_7s: DB 3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 67H    
    
    ORG 000100H
configuro:
    ;conf el modulo de oscilador
    movlb 0H		    ;Bank0
    movlw 60H
    movwf OSCCON1, 1	    ;HFINTOSC 1:1
    movlw 02H
    movwf OSCFRQ, 1	    ;HFINTOSC 4MHz
    movlw 40H
    movwf OSCEN, 1	    ;HFINTOSC enabled
    ;conf las E/S
    movlb 4H		    ;Bank4
    movlw 80H
    movwf TRISD, 1	    ;RD6 al RD0 salidas
    movwf ANSELD, 1	    ;RD6 al RD0 digitales
    movlw 0F0H
    movwf ANSELB, 1	    ;RB3 al RB0 como digitales
    ;conf el TBLPTR para que apunte a 300H de la mem de prog
    clrf TBLPTRU, 1
    movlw 03H
    movwf TBLPTRH, 1
    clrf TBLPTRL	    ;TBLPTR esta apuntando a 000300H
    
inicio:
    movf PORTB, 0, 1	    ;Leo contenido de RB y lo mando a Wreg
    andlw 0FH		    ;aplico enmascaramiento AND a wreg con valor 0FH
    movwf TBLPTRL, 1	    ;muevo Wreg hacia TBLPTRL para que funcione la lookup
    TBLRD*		    ;accion de lectura del TBLPTR
    movff TABLAT, LATD	    ;muevo contenido de TABLAT hacia RD
    bra inicio
    
    end upcino
    

