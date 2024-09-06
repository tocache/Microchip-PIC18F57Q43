    PROCESSOR 18F57Q43
    #include "cabecera.inc"

    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 001000H
deco_7s:    DB 3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 67H     
    
    ORG 000100H
configuro:
    ;conf fuente de reloj:
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    ;conf puertos E/S:
    movlb 4H
    movlw 80H
    movwf TRISD, 1	    ;RD[6:0] como salidas
    movwf ANSELD, 1	    ;RD[6:0] como digitales
    setf TRISB, 1	    ;RB[3:0] como entradas
    movlw 0F0H
    movwf ANSELB, 1	    ;RB[3:0] como digitales
    bsf TRISE, 0, 1	    ;RE0 como entrada
    bcf ANSELE, 0, 1	    ;RE0 como digital
    ;conf adicional
    clrf TBLPTRU, 1
    movlw 10H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1	    ;TBLPTR esta apuntando a 001000H

inicio_deco:
    movf PORTB, 0, 1	    ;leo RB y lo mando a Wreg
    andlw 0FH		    ;enmascaramiento para que pase solo RB[3:0]
    movwf TBLPTRL, 1	    ;movemos Wreg a TBLPTRL para iniciar decod
    TBLRD*		    ;accion de lectura de lo apuntado por TBLPTR
    movff TABLAT, LATD	    ;muevo contenido de TABLAT a LATD
    bra inicio_deco
    
    end upcino
