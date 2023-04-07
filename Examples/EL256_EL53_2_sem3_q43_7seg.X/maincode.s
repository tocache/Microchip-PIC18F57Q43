    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000500H
	   ;0    1    2    3    4    5    6    7    8    9
deco7s:	DB 3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 67H    
    
    ORG 000000H
    bra configuro
    
    ORG 000020H
configuro:
    movlb 0H
    movlw 60H
    movwf OSCCON1
    movlw 02H
    movwf OSCFRQ
    bsf OSCEN, 6
    movlb 4H
    ;configuracion de los puertos
    movlw 80H
    movwf TRISD
    movwf ANSELD	;RD6 al RD0 como salidas digitales
    movlw 0FFH
    movwf TRISB
    clrf ANSELB		;RB3 al RB0 como entradas digitales
    clrf TBLPTRU
    movlw HIGH deco7s
    movwf TBLPTRH
    movlw LOW deco7s
    movwf TBLPTRL	;TBLPTR esta apuntando a la direccion 100H de la mem prog
    
inicio:
    movlw 0FH
    andwf PORTB, W	;lectura de PORTB y enmascarmiento para que pase solo RB0 al RB3
    movwf TBLPTRL	;asigne la direccion en el TLBPTR para sacar el dato
    TBLRD*		;accion de lectura de lo apuntado por TBLPTR
    movff TABLAT, LATD	;muevo lo leido hacia RD
    bra inicio
    end upcino
    





