;Visualizador de mensajes ASCII en display de cuatro dígitos
;de siete segmentos multiplexados cátodo común
;Hecho por Kalun Lau
;21/09/2023
;Changelog:
;21/09/2023:	Codificación inicial
    
    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT dafart, class=CODE, reloc=2, abs

TEMPORAL1   EQU 500H	;GPR 1    
DESPLAZO    EQU 501H	;GPR 2
;Voy a usar GPR 510H-513H para almacenar el dato que va a ir a cada display
	
dafart:
    ORG 000000H
    bra configuro
    
    ORG 000300H
mensaje:    db "    NO SE COPIEN    "    
    
    ORG 000400H
		   ;A   B   C   D   E   F   G   H   I   J   K   L   M   N   O   P   Q   R   S   T   U   V   W   X   Y   Z  
ascii_decod:	db 77H,7CH,39H,5EH,79H,71H,6FH,74H,30H,1EH,76H,38H,15H,54H,3FH,73H,67H,50H,6DH,78H,3EH,1CH,2AH,76H,6EH,5BH
	
    ORG 000080H
configuro:
    movlb 0H			;Bank 0
    movlw 60H
    movwf OSCCON1		;HFINTOSC, POSTSC 1:1
    movlw 02H
    movwf OSCFRQ		;HFINTOSC 4MHz
    movlw 40H
    movwf OSCEN			;HFINTOSC enabled
    movlb 4H			;Bank 4
    movlw 80H
    movwf TRISD, 1		;RD6 al RD0 como salidas
    movwf ANSELD, 1		;RD6 al RD0 como digitales
    movlw 0F0H
    movwf TRISB, 1		;RB3 al RB0 como salidas
    movwf ANSELB, 1		;RB3 al RB0 como digitales
    clrf LATB, 1		;RB3 al RB0 son ceros al inicio
    movlb 5H
    clrf DESPLAZO		;inicio del mensaje
    clrf TEMPORAL1		;variable temporal1 en cero
    lfsr 0, 510H		;FSR0 apuntando a GPR 510H
    
inicio:
    movlb 4H
    movlw 03H
    movwf TBLPTRH, 1
    movlb 5H
    movf DESPLAZO, 0, 1
    movlb 4H
    movwf TBLPTRL
    TBLRD*
    movlw 20H
    cpfseq TABLAT	    ;pregunto si ASCII leido es un espacio
    bra noes_espacio
    bra sies_espacio
    call vis_mux
    bra inicio

noes_espacio:
    movlw 41H
    subwf TABLAT, 0
    movwf TBLPTRL
    movlw 04H
    movwf TBLPTRH
    TBLRD*
    movff TABLAT, INDF0
    bra siguiente

sies_espacio:
    movlw 00H
    movwf INDF0
    bra siguiente
    
siguiente:
;Jod.. no me sale, tengo que ver la manera de colocar un indice para que se
;obtenga los cuatro valores que van a los cuatro digitos del display    
    
tabla_mensaje:
    movlb 4H
    clrf TBLPTRU
    movlw 03H
    movwf TBLPTRH
    return
    
tabla_ascii:
    movlb 4H
    clrf TBLPTRU
    movlw 04H
    movwf TBLPTRH
    return
    
vis_mux:
    movff DESPLAZO, TBLPTRL
    TBLRD*+
    movff TABLAT, LATB
    bsf LATA, 0
    call un_ratito
    bcf LATA, 0
    TBLRD*+
    movff TABLAT, LATB
    bsf LATA, 1
    call un_ratito
    bcf LATA, 1
    TBLRD*+
    movff TABLAT, LATB
    bsf LATA, 2
    call un_ratito
    bcf LATA, 2
    TBLRD*
    movff TABLAT, LATB
    bsf LATA, 3
    call un_ratito
    bcf LATA, 3
    bra inicio    


