    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs

cuenta EQU 500H		;etiqueta "cuenta" para GPR 500H de memoria de datos
x_var EQU 501H
y_var EQU 502H
z_var EQU 503H		;variables de retardazo

upcino:
    ORG 000000H
    bra configuro
    
    ORG 000700H			    ;dirección de la memoria de programa
		;0    1    2    3    4    5    6    7    8    9
decod_7s:    DB 3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 67H 
    
    ORG 000100H
configuro:
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    movlb 5H		;al bank5 para los GPR
    clrf cuenta, 1		;valor inicial de cero en cuenta
    movlb 4H
    movlw 80H
    movwf TRISD, 1	;RD6:RD0 como salidas
    movwf ANSELD, 1	;RD6:RD0 como digitales
    movlw 0F0H		;11110000B
    movwf TRISB, 1	;RB3:RB0 como salidas
    movwf ANSELB, 1	;RB3:RB0 como digitales
    bsf TRISB, 4, 1	;RB4 como entrada
    bcf ANSELB, 4, 1	;RB4 como digital
    bsf WPUB, 4, 1	;RB4 con pullup
    bsf LATB, 0, 1	;habilito el primer digito del display para mostrar la cuenta
    clrf TBLPTRU, 1
    movlw 07H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1	;el puntero de tabla esta en 700H de mem prog.
    
inicio:
    movlb 5H
    movf cuenta, 0, 1	;mueve cuenta a Wreg
    movlb 4H
    movwf TBLPTRL, 1	;mueve Wreg a TBLPTRL (tabla de busqueda)
    TBLRD*
    movff TABLAT, LATD
    movlb 5H
    movlw 9
    cpfseq cuenta, 1	;pregunto si cuenta=9
    bra noesnueve
    bra siesnueve
noesnueve:
    incf cuenta, 1, 1
    bra otro
siesnueve:
    clrf cuenta, 1
otro:    
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











