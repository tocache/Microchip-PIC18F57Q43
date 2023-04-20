    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 000500H
	    ;C	  A    F    E
mensaje: DB 39H, 77H, 71H, 79H
    
    ORG 000020H
configuro:
    movlb 0FH
    movlw 60H
    movwf OSCCON1	;HFINTOSC con 1:1
    movlw 02H
    movwf OSCFRQ	;HTINTOSC a 4MHz
    movlw 40H
    movwf OSCEN		;HFINTOSC enabled
    movlw 80H
    movlb 4
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
    
inicio:
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
    clrf TBLPTRL
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


