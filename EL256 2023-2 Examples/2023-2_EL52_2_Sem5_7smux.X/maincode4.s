    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs

 REG_CUENTA EQU 500H	    ;etiqueta para la cuenta del contador
 x_var EQU 501H
 y_var EQU 502H
 z_var EQU 503H

upcino:
    ORG 000000H
    bra configuro
    
    ORG 000300H
	      ;    0    1    2    3    4    5    6    7    8    9
tabla_deco:    DB 3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 67H
    
    ORG 000100H
configuro:
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1	
    movlw 02H
    movwf OSCFRQ, 1	;HFINTOSC = 4MHz
    movlw 40H
    movwf OSCEN, 1
    movlb 5H
    clrf REG_CUENTA, 1
    movlb 4H
    movlw 80H
    movwf TRISD, 1	;RD6 al RD0 como salidas
    movwf ANSELD, 1	;RD6 al RD0 como digitales
    movlw 0F0H
    movwf TRISB, 1	;RB3 al RB0 como salidas
    movwf ANSELB, 1	;RB3 al RB0 como digitales
    movlw 08H
    movwf LATB, 1	;Esta habilitado el cuarto digito del display

inicio:
    movlb 4H
    clrf TBLPTRU, 1
    movlw 03H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1	;puntero de tabla apuntando a 300H de mem prog
    movlb 5H
    movf REG_CUENTA, 0, 1   ;recabo cuenta
    movlb 4H
    movwf TBLPTRL, 1	 ;muevo contenido de Wreg a TBLPTRL para que funcione la tabla de búsqueda
    TBLRD*		;lectura de lo que esta apuntando el TBLPTR
    movff TABLAT, LATD	;mueve lo leído hacia RD
    movlb 5H
    movlw 9
    cpfseq REG_CUENTA, 1	;pregunto si la cuenta = 9
    bra noescierto	;cuenta esta entre 0 y 8
    bra siescierto	;cuenta = 9
noescierto:
    incf REG_CUENTA, 1, 1   ;incremento la cuenta
    bra siguiente
siescierto:
    clrf REG_CUENTA, 1	;limpiando la cuenta
    bra siguiente
siguiente:
    call retardazo
    bra inicio
    
retardazo:
    movlb 5H
    movlw 100
    movwf x_var, 1
bucle3:    
    movlw 100
    movwf y_var, 1
bucle2:
    movlw 10
    movwf z_var, 1
bucle1:    
    nop
    decfsz z_var, 1, 1
    bra bucle1
    decfsz y_var, 1, 1
    bra bucle2
    decfsz x_var, 1, 1
    bra bucle3
    return
    
    end upcino





