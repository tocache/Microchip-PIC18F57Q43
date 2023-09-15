    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE,reloc=2, abs
R_CUENTA EQU 500H	;asignacion de etiqueta a GPR 500H
x_var EQU 501H
y_var EQU 502H
z_var EQU 503H
 
upcino:
    ORG 000000H		;Vector de RESET
    bra configuro
    
    ORG 000200H		;Direccion de memoria de programa
		;0    1    2    3    4    5    6    7    8    9
tabla_7s:    DB	3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 67H 

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
    clrf R_CUENTA, 1	;cuenta inicial cero del contador
    movlb 4H
    movlw 80H
    movwf TRISD, 1	;RD6-RD0 como salidas
    movwf ANSELD, 1	;RD6-RD0 como digitales
    movlw 0F0H
    movwf TRISB, 1	;RB3-RB0 como salidas
    movwf ANSELB, 1	;RB3-RB0 como digitales
    movlw 01H
    movwf LATB, 1	;Activo el primer digito para visualizar la cuenta
    clrf TBLPTRU, 1
    movlw 02H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1	;TBLPTR esta apuntando a 200H en la mem prog
    
inicio:
    call visualiza
    movlb 5H
    movlw 9
    cpfseq R_CUENTA, 1	;Pregunto si cuenta llego a nueve
    bra nollego		;falso
    clrf R_CUENTA, 1	;verdadero
    bra siguiente
nollego:
    incf R_CUENTA, 1, 1
siguiente:
    call retardazo
    bra inicio
    
visualiza:
    movlb 5H
    movf R_CUENTA, 0, 1
    movlb 4H
    movwf TBLPTRL, 1
    TBLRD*
    movff TABLAT, LATD
    return
    
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









