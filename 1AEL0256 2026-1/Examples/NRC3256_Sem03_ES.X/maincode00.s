    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H		    ;Vector de RESET
    bra configuro
    
    ORG 000100H		    ;Zona de prg de usuario
configuro:
    ;conf del modulo de oscilador
    movlb 0H		    ;al Bank0
    movlw 60H
    movwf OSCCON1, 1	    ;NOSC=HFINTOSC NDIV 1:1
    movlw 02H
    movwf OSCFRQ, 1	    ;FRQ=4MHz
    movlw 40H
    movwf OSCEN, 1	    ;HFINTOSC enabled
    ;conf de las E/S
    movlb 4H
    clrf TRISD, 1	    ;todo RD como salida
    clrf ANSELD, 1	    ;todo RD como digital
    bsf TRISE, 2, 1	    ;RE2 como entrada
    bcf ANSELE, 2, 1	    ;RE2 como digital
    bsf WPUE, 2, 1	    ;RE2 con pullup activo
    
inicio:			    ;inicio de la aplicacion
    movlw 9DH
    movwf LATD, 1	    ;escribo 9DH en RD
    bra inicio		    ;salto a inicio
    
    end upcino
    
    


