    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:

x_var EQU 500H
y_var EQU 501H
z_var EQU 502H	    ;Variables de la rutina retardazo
cuenta EQU 503H	    ;Aloja la cuenta del contador
 
    ORG 000000H
    bra configuro
    
    ORG 000700H
		;0   1    2    3    4    5    6    7    8    9
mensaje:    DB	3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 67H     
    
    ORG 000100H
configuro:
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    movlb 5H
    clrf x_var, 1	;x_var a cero
    clrf y_var, 1	;y_var a cero
    clrf z_var, 1	;z_var a cero
    clrf cuenta, 1	;cuenta inicial cero
    movlb 4H
    movlw 80H
    movwf TRISD, 1	;RD6-RD0 como salidas
    movwf ANSELD, 1	;RD6-RD0 como digitales
    movlw 0F0H
    movwf TRISB, 1	;RB3-RB0 como salidas
    movwf ANSELB, 1	;RB3-RB0 como digitales
    movlw 1H
    movwf LATB,1	;Solo el digito 0 del display esta habilitado
    clrf TBLPTRU, 1
    movlw 07H
    movwf TBLPTRH,1
    clrf TBLPTRL, 1	;TBLPTR esta apuntando a la direccion 700H de mem prog
    ;incf TBLPTRL, 1, 1	;701H
    
inicio:
    movlb 5H
    movf cuenta, 0, 1	;obteniendo valor de cuenta a Wreg
    movlb 4H
    movwf TBLPTRL, 1	;asignando posición de TBLPTR segun valor de cuenta
    TBLRD*
    movff TABLAT, LATD
    call retardazo
    movlw 9
    cpfseq cuenta, 1
    bra noesnueve
    clrf cuenta, 1
    bra inicio
noesnueve:
    incf cuenta, 1, 1
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






