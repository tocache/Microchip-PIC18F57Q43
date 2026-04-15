    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H		;vector de reset
    bra configuro
    
    ORG 000100H		;zona user program
configuro:
    movlb 0H		;al Bank0
    movlw 60H
    movwf OSCCON1, 1	;NOSC=HFINTOSC NDIV 1:!
    movlw 02H
    movwf OSCFRQ, 1	;HFINTOSC a 4MHz
    movlw 40H
    movwf OSCEN, 1	;HFINTOSC enabled
    movlb 4H		;Al Bank4
    clrf TRISD, 1	;Todo RD como salida
    clrf ANSELD, 1	;Todo RD como digital
    bsf TRISE, 0, 1	;RE0 como entrada
    bcf ANSELE, 0, 1	;RE0 como digital
    bsf WPUE, 0, 1	;RE0 con pullup enabled

inicio:    
    movlw 63H		;cargo dato 63H en wreg
    movwf LATD, 1	;muevo contenido dew wreg hacia LATD
cuenta:
    btfsc PORTE, 0, 1	;pregunto si presione BTN
    bra cuenta		;rpta falsa y salto a label cuenta
    incf LATD, 1, 1	;rpta verdad incremento registro LATD
aunno:
    btfss PORTE, 0, 1	;pregunto si debe de presionar BTN
    bra aunno		;rpta falsa y salto a label aunno
    bra cuenta		;rpta verdad y salto a label cuenta 
    
    end upcino
