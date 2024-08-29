    PROCESSOR 18F57Q43
    #include "cabecera.inc"

x_var EQU 500H
y_var EQU 501H
z_var EQU 502H 
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H		;vector de reset
    bra configuro
    
    ORG 000100H		;zona de usuario
configuro:
    ;configuracion de la fuente de reloj
    movlb 0H		;al Bank0
    movlw 60H
    movwf OSCCON1, 1	;NOSC=HFINTOSC NDIV=1:1
    movlw 02H
    movwf OSCFRQ, 1	;HFINTOSC 4MHz
    movlw 40H
    movwf OSCEN, 1	;HFINTOSC enabled
    ;configuracion de las E/S
    movlb 4H		;al Bank4
    movlw 0xFC		;en binario 11111100
    movwf TRISB, 1	;RB0 y RB1 como salidas
    movwf ANSELB, 1	;RB0 y RB1 como digitales
    bsf TRISE, 0, 1	;RE0 como entrada
    bcf ANSELE, 0, 1	;RE0 como digital

inicio_tren:
    btfss PORTE, 0, 1	;pregunto si RE0=1
    bra es_falso	;viene aqui cuando es falso
    bra es_verdad	;viene aqui cuando es verdad
es_falso:
    clrf LATB, 1	;apagamos RB0 y RB1
    bra inicio_tren
es_verdad:
    movlw 01H
    movwf LATB, 1	;RB1=0, RB0=1
    call retardado	;llamada a subrutina de retardo
    movlw 02H
    movwf LATB, 1	;RB1=1, RB0=0
    call retardado	;llamada a subrutina de retardo
    bra inicio_tren
retardado:
    movlb 5H		;al Bank5
    movlw 30
    movwf x_var, 1
punto_tres:    
    movlw 30
    movwf y_var, 1
punto_dos:
    movlw 30
    movwf z_var, 1
punto_uno:    
    nop
    movf z_var, 1, 1
    movlb 4H		;Al Bank4
    btfss STATUS, 2, 1	;pregunto si z_var llego a cero
    bra zvar_noescero	;falso zvar no llego a cero
    movlb 5H		;Al bank5
    movf y_var, 1, 1	;verdad y prosigo a ls siguiente pregunta
    movlb 4H		;Al Bank4
    btfss STATUS, 2, 1	;pregunto si y_var llego a cero
    bra yvar_noescero	;falso yvar no llego a cero
    movlb 5H		;Al bank5
    movf x_var, 1, 1
    movlb 4H		;Al Bank4
    btfss STATUS, 2, 1	;pregunto si x_var llego a cero
    bra xvar_noescero	;falso xvar no llego a cero
    return
zvar_noescero:
    movlb 5H		;Al bank5
    decf z_var, 1, 1	;decremento z_var
    bra punto_uno
yvar_noescero:
    movlb 5H		;Al bank5
    decf y_var, 1, 1	;decremento y_var
    bra punto_dos
xvar_noescero:
    movlb 5H		;Al bank5
    decf x_var, 1, 1	;decremtno x_var
    bra punto_tres
    
    end upcino
    
    

