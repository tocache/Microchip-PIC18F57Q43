    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upzote, class=CODE, reloc=2, abs
upzote:
    ORG 000000H
    bra configuro
    
    ORG 000100H
configuro:
    ;conf mod osc
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    ;conf E/S
    movlb 4H
    movlw 80H
    movwf TRISD, 1
    movwf ANSELD, 1
    movlw 0F0H
    movwf ANSELB, 1
    ;conf TBLPTR
    clrf TBLPTRU, 1
    movlw 02H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1		;TBLPTR esta apuntando a 000200H
    
inicio:
    movf PORTB, 0, 1		;leo RB y lo mando a Wreg
    andlw 0FH			;enmascaramiento AND 0FH a Wreg
    movwf TBLPTRL, 1		;muevo contenido de Wreg a TBLPTRL
    TBLRD*			;accion de lectura de TBLPTR
    movff TABLAT, LATD		;muevo lo leido hacia RD
    bra inicio

    ORG 000200H
datos_7s:   DB 3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 67H    
   
    end upzote
    


