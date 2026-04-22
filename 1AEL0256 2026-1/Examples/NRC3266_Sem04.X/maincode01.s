    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H		    ;vector RST
    bra configuro	    ;salto a label configuro
    
    ORG 000200H		    ;datos del decodificador
datos_7s:   DB	3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 67H    
    
    ORG 000100H		    ;user program
configuro:
    ;conf modulo de osc
    movlb 0H		    ;al Bank0
    movlw 60H
    movwf OSCCON1, 1	    ;HFINTOSC 1:1
    movlw 02H
    movwf OSCFRQ, 1	    ;HFINTOSC a 4MHz
    movlw 40H
    movwf OSCEN, 1	    ;HFINTOSC enabled
    ;conf E/S
    movlb 4H		    ;al Bank4
    movlw 80H		    ;cargo 80H a wreg
    movwf TRISD, 1	    ;RD6 al RD0 como salidas
    movwf ANSELD, 1	    ;RD6 al RD0 como digitales
    movlw 0F0H
    movwf ANSELB, 1	    ;RB3 al RB0 como digitales
    ;conf el TBLPTR
    clrf TBLPTRU, 1
    movlw 02H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1	    ;TBLPTR apuntando a 000200H

inicio:    
    movf PORTB,0, 1	    ;muevo PORTB a wreg
    andlw 0FH		    ;enmascaramiento AND a PORTB con 0FH
    movwf TBLPTRL	    ;muevo wreg a TBLPTRL
    TBLRD*		    ;accion de lectura de TBLPTR
    movff TABLAT, LATD	    ;muevo contenido de TABLAT a LATD
    bra inicio		    ;salto a label inicio
    
    end upcino