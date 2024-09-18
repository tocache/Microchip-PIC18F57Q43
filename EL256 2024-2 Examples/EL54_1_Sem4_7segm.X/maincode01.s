    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 001000H
decod:	DB 3FH, 06H, 5BH, 4FH, 66h, 6DH, 7DH, 07H, 7FH, 67H
;           0    1    2    3    4    5    6    7    8    9
	
    ORG 000100H
configuro:
    ;configuracion de la fuente de reloj
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    ;configuracon de las E/S
    movlb 4H
    movlw 80H
    movwf TRISB, 1	    ;RB[6:0] como salidas
    movwf ANSELB, 1	    ;RB[6:0] como digitales
    setf TRISD, 1	    ;RD como entradas
    movlw 0F0H
    movwf ANSELD, 1	    ;RD[3:0]] como digitales
    ;configuraciones adicionales
    clrf TBLPTRU, 1
    movlw 10H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1	    ;direccion asignada a TBLPTR=001000H
    
inicio_decod:
    ;tengo que leer el puerto de entrada RD[3:0]
    movf PORTD, 0, 1	    ;leo RD y lo mando a Wreg
    andlw 0FH		    ;enmascaramiento a Wreg con el valor 0FH
    ;tengo que decodificar usando el TBLPTR
    movwf TBLPTRL, 1	    ;muevo contenido de Wreg a TBLPTRL
    TBLRD*		    ;lectura de lo que apunta TBLPTR y se graba en TABLAT
    ;tengo que escribir TABLAT a RB[6:0]
    movff TABLAT, LATB	    ;muevo contenido de TABLAT a RB
    bra inicio_decod
    
    end upcino
