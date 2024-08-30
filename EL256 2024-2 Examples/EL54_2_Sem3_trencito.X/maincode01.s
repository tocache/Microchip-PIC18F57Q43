    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H		;vector de reset
    bra configuro
    
    ORG 000100H		;inicio de zona de programa de usuario
configuro:
    ;configuracion de la fuente de reloj
    movlb 0H	    ;al Bank0
    movlw 60H
    movwf OSCCON1, 1	;NOSC=HFINTOSC, NDIV 1:1
    movlw 02H
    movwf OSCFRQ, 1	;HFINTOSC 4MHz
    movlw 40H
    movwf OSCEN, 1	;HFINTOSC enabled
    ;configuracion de las E/S
    movlb 4H		;al Bank4
    movlw 0FCH		;binario 11111100
    movwf TRISB, 1	;RB0 y RB1 como salidas
    movwf ANSELB, 1	;RB0 y RB1 como digitales
    bsf TRISE, 0, 1	;RE0 como entrada
    bcf ANSELE, 0, 1	;RE0 como digital
inicio_tren:
    btfss PORTE, 0, 1	;Pregunto si RE0 es uno
    bra nohaytren	;viene aqui cuando es falso
    bra sihaytren	;viene aqui cuando es verdad
nohaytren:
    clrf LATB, 1	;Apagamos los LEDs
    bra inicio_tren	;Regreso a inicio_tren
sihaytren:
    movlw 01H
    movwf LATB, 1	;RB0=1 RB1=0
    nop			;retardo
    movlw 02H
    movwf LATB, 1	;RB0=0 RB1=1
    nop			;retardo
    bra inicio_tren
    
    end upcino
    
    


