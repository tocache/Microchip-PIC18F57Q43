    PROCESSOR 18F57Q43
    #include "cabecera.inc"

cuenta EQU 500H	    ;asignacion de label a GPR 500H    
    
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
    bsf TRISE, 0, 1	    ;RE0 como entrada
    bcf ANSELE, 0, 1	    ;RE0 como digital
    ;configuraciones adicionales
    clrf TBLPTRU, 1
    movlw 10H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1	    ;direccion asignada a TBLPTR=001000H
    movlb 5H		    ;al bank 5
    clrf cuenta, 1	    ;valor inicial de cuenta=0
    movlb 4H		    ;al bank 4
    call imp_7s
    
inicio_contador:
    btfss PORTE, 0, 1	    ;pregunto si preisone el boton
    bra inicio_contador	    ;falso, no presione el boton
    movlb 5H
    movlw 9
    cpfseq cuenta, 1	    ;pregunto si cuenta=9
    bra no_es_nueve
    bra si_es_nueve
no_es_nueve:
    incf cuenta, 1, 1	    ;incremento cuenta
    bra juntada
si_es_nueve:
    clrf cuenta, 1	    ;cuenta igual a cero
juntada:
    call imp_7s
    movlb 4H
    btfsc PORTE, 0, 1	    ;pregunto si solte el boton
    bra juntada		    ;falso, sigue pulsado
    bra inicio_contador

imp_7s:
    movlb 5H
    movf cuenta, 0, 1	    ;mando cuenta a Wreg
    movlb 4H
    movwf TBLPTRL, 1	    ;muevo Wreg a TBLPTRL
    TBLRD*
    movff TABLAT, LATB
    return
    
    end upcino



