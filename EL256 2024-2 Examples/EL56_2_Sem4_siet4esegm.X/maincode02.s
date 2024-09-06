    PROCESSOR 18F57Q43
    #include "cabecera.inc"

var_cuenta EQU 500H ;asignando etiqueta a GPR 500H    
    
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
    movlb 5H		    ;nos vamos al Bank5
    clrf var_cuenta, 1	    ;valor inicial de var_cuenta=0
    movlb 4H		    ;nos vamos a Bank4
    call imp_7s		    ;llamo a subrutina imp_7s
inicio_conta:
    btfss PORTE, 0, 1	    ;pregunto si presione boton
    bra $-2		    ;falso, retorno a linea anterior
    movlb 5H		    ;nos vamos al Bank5
    movlw 9
    cpfseq var_cuenta, 1    ;pregunto si var_cuenta=9
    bra no_es_nueve	    ;falso, no es nueve
    clrf var_cuenta, 1	    ;verdad, es nueve y lo mandamos a cero
    bra siguiente	    ;salto a label siguiente
no_es_nueve:
    incf var_cuenta, 1, 1    ;incremento var_cuenta
siguiente:
    call imp_7s
    btfsc PORTE, 0, 1	    ;pregunto si deje de pulsar boton
    bra $-2		    ;falso, boton sigue presionado
    bra inicio_conta	    ;retorno al inicio
    
imp_7s:
    movlb 5H		    ;al Bank5
    movf var_cuenta, 0, 1   ;leo var_cuenta y lo mando a Wreg
    movlb 4H		    ;al Bank4
    movwf TBLPTRL, 1	    ;movemos Wreg a TBLPTRL para iniciar decod
    TBLRD*		    ;accion de lectura de lo apuntado por TBLPTR
    movff TABLAT, LATD	    ;muevo contenido de TABLAT a LATD
    return
    
    end upcino



