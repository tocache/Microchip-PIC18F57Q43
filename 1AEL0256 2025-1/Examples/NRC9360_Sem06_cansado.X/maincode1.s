;Programa para visualizar 0 al 9 en un display
    PROCESSOR 18F57Q43
    #include "cabecera.inc"

numero EQU 500H	    ;etiqueta al GPR 500H    
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 000600H
tabla_7s:   DB 3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 67H    
   
    ORG 000100H
configuro:
    ;configuracion del modulo de oscilador
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    ;configuracion de las E/S
    movlb 4H
    movlw 80H
    movwf TRISD, 1
    movwf ANSELD, 1
    movlw 0F8H
    movwf TRISF, 1
    movwf ANSELF, 1
    movlw 0FCH
    movwf ANSELB, 1
    movlw 03H
    movwf WPUB, 1
    ;condiciones iniciales
    movlb 5H
    clrf numero, 1	;inicializamos "numero" en cero
    movlb 4H
    bsf LATF, 0, 1	;encendemos el display
    clrf TBLPTRU, 1
    movlw 06H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1	;El TBLPTR esta apuntando a 000600H
    
inicio:
btn1:	btfsc PORTB, 1, 1	;pregunto si presione BTN1
	bra btn2		;no se presiono y se va a rutina btn2
	movlb 5H
	movlw 0
	cpfseq numero, 1	;pregunto si numero=0
	bra decremento		;numero no es cero y se va a etiqueta decremento
	clrf numero, 1		;numero es cero y se mantiene en cero
	bra siguiente1
decremento:
	decf numero, 1, 1	;accion de decremento a numero
siguiente1:
	movlb 4H
	btfss PORTB, 1, 1	;pregunto si solte el boton
	bra $-2			;regreso a preguntar si solte el boton
	bra btn2		;ya solte el boton y me voy a etiqueta btn2
	
btn2:	btfsc PORTB, 0, 1	;pregunto si presione BTN2
	bra disp7s		;no se presiono y se va a rutina disp7s
	movlb 5H
	movlw 9
	cpfseq numero, 1	;pregunto si numero=9
	bra incremento		;numero no es nueve y se va a etiqueta incremento
	movlw 9
	movwf numero, 1		;numero es nueve y se mantiene en nueve
	bra siguiente2
incremento:
	incf numero, 1, 1	;accion de incremento a numero
siguiente2:
	movlb 4H
	btfss PORTB, 0, 1	;pregunto si solte el boton
	bra $-2			;regreso a preguntar si solte el boton
	bra disp7s		;ya solte el boton y me voy a etiqueta disp7s
    
disp7s:	movlb 5H
	movf numero, 0, 1	;leyendo el contenido de numero y lo mandamos a Wreg
	movlb 4H
	movwf TBLPTRL, 1	;movemos contenido de Wreg hacia TBLPTRL
	TBLRD*			;accion de lectura de lo apuntado por TBLPTR
	movff TABLAT, LATD	;muevo contenido de TABLAT hacia LATD
	bra inicio
	end upcino


