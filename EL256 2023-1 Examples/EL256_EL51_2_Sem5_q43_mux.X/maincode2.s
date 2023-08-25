    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    
corredera EQU 500H    

    ORG 000000H
    bra configuro
    
    ORG 000500H
	                        ;C    A    F    E
mensaje: DB 00H, 00H, 00H, 00H, 39H, 77H, 71H, 79H, 00H, 00H, 00H
    
    ORG 000020H
configuro:
    movlb 0		;bank 0
    movlw 60H
    movwf OSCCON1	;HFINTOSC con 1:1
    movlw 02H
    movwf OSCFRQ	;HTINTOSC a 4MHz
    movlw 40H
    movwf OSCEN		;HFINTOSC enabled
    movlw 80H
    movlb 3		;bank 3
    movlw 90H
    movwf T0CON0	;TMR0 enabled, modo 16 bit, postsacer 1:1
    movlw 73H
    movwf T0CON1	;TMR0 src HFINTOSC, prescaler 1:32
    movlb 4	        ;bank 4
    movlw 80H
    movwf TRISD		;RD6 al RD0 son salidas
    movwf ANSELD	;RD6 al RD0 son digitales
    movlw 0F0H
    movwf TRISB		;RB3 al RB0 son salidas
    movwf ANSELB	;RB3 al RB0 son digitales
    clrf TBLPTRU
    movlw HIGH mensaje
    movwf TBLPTRH
    movlw LOW mensaje
    movwf TBLPTRL	;TBLPTR apuntando a mensaje (500H)
    clrf LATB		;todos los habilitadores del disp a cero
    clrf corredera	;corredera valor inicial cero
inicio:
    btfss PIR3, 7	;pregunto si se desbordo TMR0
    bra visualiz	;no se desbordo, se va a visualizar
    movlw 7		;si se desbordo
    cpfseq corredera	;pregunto si corredera = 7
    bra no_llego	;corredera no es siete
    clrf corredera	;corredera si es siete, limpia la corredera
    bra siguiente
no_llego:
    incf corredera, 1	;incrementa corredera
siguiente:
    bcf PIR3, 7	    	;baja bandera TMR0IF
visualiz:
    movff corredera, TBLPTRL
    TBLRD*+		;accion de lectura en el TBLPTR y posterior incremento 
    movff TABLAT, LATD	;mueve lo leido hacia RD donde estan los segmentos del disp
    bsf LATB, 0
    call nopes
    bcf LATB, 0
    TBLRD*+		;accion de lectura en el TBLPTR y posterior incremento 
    movff TABLAT, LATD	;mueve lo leido hacia RD donde estan los segmentos del disp
    bsf LATB, 1
    call nopes
    bcf LATB, 1
    TBLRD*+		;accion de lectura en el TBLPTR y posterior incremento 
    movff TABLAT, LATD	;mueve lo leido hacia RD donde estan los segmentos del disp
    bsf LATB, 2
    call nopes
    bcf LATB, 2
    TBLRD*		;accion de lectura en el TBLPTR y posterior incremento 
    movff TABLAT, LATD	;mueve lo leido hacia RD donde estan los segmentos del disp
    bsf LATB, 3
    call nopes
    bcf LATB, 3
    bra inicio
    
nopes:
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    return
    
    end upcino


