    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    
CUENTA EQU 500H
var_i EQU 501H    
var_j EQU 502H
var_k EQU 503H   
 
    ORG 000000H
    bra configuro
    
    ORG 000008H
    bra INT0_ISR
    
    ORG 000018H
    bra INT1_INT2_ISR

    ORG 000100H
	   ;0    1    2    3    4    5    6    7    8    9
deco7s:	DB 3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 67H       

    ORG 000020H
configuro:
    movlb 0H
    ;conf del INTOSC
    movlw 60H
    movwf OSCCON1
    movlw 02H
    movwf OSCFRQ
    movlw 40H
    movwf OSCEN
    movlb 3H
    bcf IPR6, 0	    ;INT1IP=0
    bcf IPR10,0	    ;INT2IP=0
    movlb 4H
    ;conf de E/S
    movlw 80H
    movwf TRISD
    movwf ANSELD
    movlw 0FCH
    movwf TRISA
    movwf ANSELA
    bcf INTCON2, 7  ;RBPU habilitado
    bsf TRISB, 0
    bcf ANSELB, 0
    bsf WPUB, 0
    bsf TRISB, 1
    bcf ANSELB, 1
    bsf WPUB, 1
    bsf TRISB, 2
    bcf ANSELB, 2
    bsf WPUB, 2
    ;conf de interrupts
    bsf INTCON0, 5	    ;IPEN=1
    bsf INTCON0, 7   ;GIEH=1
    bsf INTCON0, 6   ;GIEL=1
    bsf PIE1, 0   ;INT0IE=1
    bsf PIE6, 0  ;INT1IE=1
    bsf PIE10, 0    ;INT2IE=1
    bcf INTCON0, 0  ;INT0EDG=0
    bcf INTCON0, 1  ;INT1EDG=0
    bcf INTCON0, 2  ;INT2EDG=0
    ;conf adicionales
    movlw 01H
    movwf LATA
    clrf TBLPTRU
    movlw HIGH deco7s
    movwf TBLPTRH
    movlw LOW deco7s
    movwf TBLPTRL
    clrf CUENTA
inicio:
    call repeticua
    comf LATA, f
    bra inicio
    
INT0_ISR:
    bcf INTCON, 1   ;INT0IF=0
    movlw 9
    cpfseq CUENTA   ;¿CUENTA=9?
    bra noesnueve   ;F: salto a noesnueve
    clrf CUENTA	    ;V: limpia CUENTA
    bra siguiente1  ;salto a siguiente1
noesnueve:
    incf CUENTA, f  ;incrementa CUENTA
siguiente1:
    call visual7seg ;subrutina visual7seg
    retfie	    ;retorno
    
INT1_INT2_ISR:
    btfss INTCON3, 0	;pregunto si ocurrio INT1IF
    bra fue_INT2	;F: voy hacia INT2
    bcf INTCON3, 0  ;INT1IF=0
    movlw 0
    cpfseq CUENTA   ;¿CUENTA=0?
    bra noescero    ;F: salto a noesceor
    movlw 9
    movwf CUENTA    ;V: CUENTA=9
    bra siguiente2  ;salto a siguiente1
noescero:
    decf CUENTA, f  ;incrementa CUENTA
siguiente2:
    call visual7seg ;subrutina visual7seg
    btfss INTCON3, 1	;Pregunto si ocurrio INT2IF
    retfie
fue_INT2:
    bcf INTCON3, 1  ;INT2IF=0
    clrf CUENTA	    ;V: limpia CUENTA
    call visual7seg ;subrutina visual7seg    
    retfie	    ;retorno    
    
visual7seg:
    movff CUENTA, TBLPTRL
    TBLRD*
    movff TABLAT, LATD
    return
    
repeticua:   
    movlw 80
    movwf var_i
otro1:
    call bucle1		;Salto a subrutina
    decfsz var_i, f
    goto otro1
    return
bucle1:
    movlw 50
    movwf var_j
otro2:
    call bucle2		;Salto a subrutina
    decfsz var_j, f
    goto otro2
    return
bucle2:
    movlw 14
    movwf var_k
otro3:
    nop			
    decfsz var_k, f
    goto otro3
    return    
    
    end upcino





