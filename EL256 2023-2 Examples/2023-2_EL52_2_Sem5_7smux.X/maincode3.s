    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 000300H
	    ;	H    O    L    A
palabra1:    DB 76H, 3FH, 38H, 77H  
    ORG 000320H
	    ;	S    E    C    O
palabra2:    DB 6DH, 79H, 39H, 3FH   
    
    ORG 000100H
configuro:
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1	
    movlw 02H
    movwf OSCFRQ, 1	;HFINTOSC = 4MHz
    movlw 40H
    movwf OSCEN, 1
    movlb 4H
    movlw 80H
    movwf TRISD, 1	;RD6 al RD0 como salidas
    movwf ANSELD, 1	;RD6 al RD0 como digitales
    movlw 0F0H
    movwf TRISB, 1	;RB3 al RB0 como salidas
    movwf ANSELB, 1	;RB3 al RB0 como digitales
    clrf LATB, 1	;RB3 al RB0 son ceros al inicio
    bsf TRISB, 4, 1	;RB4 es entrada
    bcf ANSELB, 4, 1	;RB4 es digital
    bsf WPUB, 4, 1	;RB4 su pullup interno activado

inicio:
    btfsc PORTB, 4, 1	;pregunto si presione el boton
    bra nopresione	;falso
    bra sipresione	;verdadero
    
nopresione:		;asignar TBLPTR a posicion 300H
    clrf TBLPTRU, 1
    movlw 03H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1	;TBLPTR esta apuntando a la 300H en la mem de prog
    bra siguiente
    
sipresione:		;asignar TBLPTR a posicion 320H    
    clrf TBLPTRU, 1
    movlw 03H
    movwf TBLPTRH, 1
    movlw 20H
    movwf TBLPTRL, 1	;TBLPTR esta apuntando a la 320H en la mem de prog
    bra siguiente
    
siguiente:    
    TBLRD*+		;Lectura de lo que esta apuntando el TBLPTR y luego hace incremento a la direcciond e apunte		
    movff TABLAT, LATD	;muevo el contenido leido hacia RD (puerto de los segmentos)
    bsf LATB, 0, 1	;enciendo primer digito del display
    call nopes
    bcf LATB, 0, 1	;apago el primer digito del display
    TBLRD*+		;Lectura de lo que esta apuntando el TBLPTR y luego hace incremento a la direcciond e apunte		
    movff TABLAT, LATD	;muevo el contenido leido hacia RD (puerto de los segmentos)
    bsf LATB, 1, 1	;enciendo segundo digito del display
    call nopes
    bcf LATB, 1, 1	;apago el segundo digito del display
    TBLRD*+		;Lectura de lo que esta apuntando el TBLPTR y luego hace incremento a la direcciond e apunte		
    movff TABLAT, LATD	;muevo el contenido leido hacia RD (puerto de los segmentos)
    bsf LATB, 2, 1	;enciendo tercer digito del display
    call nopes
    bcf LATB, 2, 1	;apago el tercer digito del display
    TBLRD*+		;Lectura de lo que esta apuntando el TBLPTR y luego hace incremento a la direcciond e apunte		
    movff TABLAT, LATD	;muevo el contenido leido hacia RD (puerto de los segmentos)
    bsf LATB, 3, 1	;enciendo cuarto digito del display
    call nopes
    bcf LATB, 3, 1	;apago el cuarto digito del display
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
    return

    end upcino





