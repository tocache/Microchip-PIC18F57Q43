    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upeceno, class=CODE, reloc=2, abs
upeceno:
    ORG 000000H
    bra configuro

    ORG 000700H
str_dale: DB 5EH,5FH,38H,7BH
 
    ORG 000800H
str_upc: DB 00H, 3EH, 73H, 39H    
    
    ORG 000100H
configuro:
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1	    ;NOSC=HFINTOSC NDIV=1:1
    movlw 02H
    movwf OSCFRQ, 1	    ;HFINTOSC a 4MHz
    movlw 50H
    movwf OSCEN, 1	    ;Se active LFINTOSC también
    movlb 4H
    movlw 80H
    movwf TRISD, 1
    movwf ANSELD, 1
    movlw 0F0H
    movwf TRISB, 1
    movwf ANSELB, 1
    bcf ANSELB, 4, 1	    ;RB4 como digital
    bsf WPUB, 4, 1	    ;RB4 con pullup activo
    ;conf TBLPTR
    clrf TBLPTRU, 1
    movlw 08H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1		;TBLPTR apunta a 000700H de la mem de prog
    ;condiciones iniciales
    clrf LATD, 1
    clrf LATB, 1

inicio:
    btfsc PORTB, 4, 1		;pregunto el valor de RB4
    bra es_cero
    bra es_uno

es_cero:
    movlw 07H
    movwf TBLPTRH, 1
    call multiplex
    bra inicio
  
es_uno:
    movlw 08H
    movwf TBLPTRH, 1
    call multiplex
    bra inicio    
        
multiplex:
    clrf TBLPTRL, 1
    TBLRD*+
    movf TABLAT, 0, 1
    movwf LATD, 1	;mando primer dato a RD ("d")
    bsf LATB, 0, 1	;habilito primer digito del display
    call nopes
    bcf LATB, 0, 1	;deshabilito primero digito del display
    TBLRD*+
    movf TABLAT, 0, 1
    movwf LATD, 1	;mando primer dato a RD ("a")
    bsf LATB, 1, 1	;habilito segundo digito del display
    call nopes
    bcf LATB, 1, 1	;deshabilito segundo digito del display
    TBLRD*+
    movf TABLAT, 0, 1
    movwf LATD, 1	;mando primer dato a RD ("d")
    bsf LATB, 2, 1	;habilito primer digito del display
    call nopes
    bcf LATB, 2, 1	;deshabilito primero digito del display
    TBLRD*
    movf TABLAT, 0, 1
    movwf LATD, 1	;mando primer dato a RD ("d")
    bsf LATB, 3, 1	;habilito primer digito del display
    call nopes
    bcf LATB, 3, 1	;deshabilito primero digito del display
    return
    
nopes:			;Ejecución de 100 nops (generación de retardo)
    movlb 5H
    movlw 100
    movwf 500H, 1	;GPR de 500H
    nop
    decfsz 500H, 1, 1	;decremento y pregunto si ya llego a cero
    bra $-4
    movlb 4H
    return

retardazo:
    movlb 5H
    movlw 100
    movwf 501H, 1	;GPR 501H con 100 en decimal
carga502:    
    movlw 100
    movwf 502H, 1	;GPR 502H con 100 en decimal
carga503:
    movlw 50
    movwf 503H, 1	;GPR 503H con 50 en decimal
    nop
    decfsz 503H, 1, 1	;decremento 503H y pregunto si llego a cero
    bra $-4
    decfsz 502H, 1, 1	;decremento 502H y pregunto si llego a cero
    bra carga503
    decfsz 501H, 1, 1	;decremento 501H y pregunto si llego a cero
    bra carga502
    movlb 4H
    return
 
    end upeceno
    



