;programa para visualizar CHIP en el display de siete segmentos
    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 003000H
    ;		C    H	  I    P
chip_msg:   DB 39H, 76H, 30H, 73H    
    
    ORG 000100H
configuro:
    ;configuracion del modulo de oscilador
    movlb 0H	    ;al Bank0
    movlw 60H
    movwf OSCCON1, 1	;NOSC=HFINTOSC, NDIV=1:1
    movlw 02H
    movwf OSCFRQ, 1	;HFINTOSC a 4MHz
    movlw 40H
    movwf OSCEN, 1	;HFINTOSC enabled, el CPU a 4MHz
;    movlw 55H
;    movwf OSCCON1, 1	;NOSC=LFINTOSC, NDIV=1:32
;    movlw 10H
;    movwf OSCEN, 1	;LFINTOSC enabled, el CPU a 1KHz aprox
    ;configuracion de las E/S
    movlb 4H	    ;al Bank4
    movlw 80H
    movwf TRISD, 1  ;RD6 al RD0 como salidas
    movwf ANSELD, 1 ;RD6 al RD0 como digitales
    movlw 0F0H
    movwf TRISB, 1  ;RB3 al RB0 como salidas
    movwf ANSELB, 1 ;RB3 al RB0 como digitales
    ;direccion de apunte del TBLPTR
    clrf TBLPTRU, 1
    movlw 30H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1	;direccion de apunte 3000H
    ;condicion inicial de la aplicacion
    clrf LATB, 1	;los habilitadores en cero
    
inicio:
    clrf TBLPTRL, 1	;TBLPTR a 3000H
    TBLRD*		;accion de lectura
    movf TABLAT, 0, 1	;muevo contenido de TABLAT a Wreg
    movwf LATD, 1	;muevo contenido de Wreg a RD
    bsf LATB, 0, 1	;enciendo primer digito del display
    call noups		;microretardo de 20us
    bcf LATB, 0, 1	;apago el primer digito del display
    incf TBLPTRL, 1, 1	;incremento en uno la pos. de apunte de TBLPTR (3001H)
    TBLRD*		;accion de lectura
    movf TABLAT, 0, 1	;muevo contenido de TABLAT a Wreg
    movwf LATD, 1	;muevo contenido de Wreg a RD
    bsf LATB, 1, 1	;enciendo segundo digito del display
    call noups		;microretardo de 20us
    bcf LATB, 1, 1	;apago el segundo digito del display
    incf TBLPTRL, 1, 1	;incremento en uno la pos. de apunte de TBLPTR (3002H)
    TBLRD*		;accion de lectura
    movf TABLAT, 0, 1	;muevo contenido de TABLAT a Wreg
    movwf LATD, 1	;muevo contenido de Wreg a RD
    bsf LATB, 2, 1	;enciendo tercer digito del display
    call noups		;microretardo de 20us
    bcf LATB, 2, 1	;apago el tercer digito del display
    incf TBLPTRL, 1, 1	;incremento en uno la pos. de apunte de TBLPTR (3003H)
    TBLRD*		;accion de lectura
    movf TABLAT, 0, 1	;muevo contenido de TABLAT a Wreg
    movwf LATD, 1	;muevo contenido de Wreg a RD
    bsf LATB, 3, 1	;enciendo cuarto digito del display
    call noups		;microretardo de 20us
    bcf LATB, 3, 1	;apago cuarto digito del display
    bra inicio
    
noups:
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
    nop
    nop
    nop
    nop
    return
    
    end upcino
    


