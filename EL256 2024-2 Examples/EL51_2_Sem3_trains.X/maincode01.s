    PROCESSOR 18F57Q43
    #include "cabecera.inc"

;Asignacion de labels a GPR    
x_var EQU 500H
y_var EQU 501H
z_var EQU 502H
 
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H	    ;vector de RESET
    bra configuro   ;salto a label configuro
    
    ORG 000100H	    ;zona de programa de usuario
configuro:
    ;configuracion la fuente de reloj
    movlb 0H		;nos vamos al Bank0
    movlw 60H
    movwf OSCCON1, 1	;NOSC=HFINTOSC, NDIV 1:1
    movlw 02H
    movwf OSCFRQ, 1	;HFINTOSC a 4MHz
    movlw 40H
    movwf OSCEN, 1	;HFINTOSC habilitado
    ;configuracion las E/S
    movlb 4H		;saltamos al Bank4
    bsf TRISE, 0, 1	;RE0 es entrada
    bcf ANSELE, 0, 1	;RE0 es digital
    bcf TRISB, 0, 1	;RB0 es salida
    bcf TRISB, 1, 1	;RB1 es salida
    ;Recordando bcf [registro], #bit, access bank o BSR (1 o 0)
    bcf ANSELB, 0, 1	;RB0 es digital
    bcf ANSELB, 1, 1	;RB1 es digital
    
inicio_tren:
    btfss PORTE, 0, 1	;pregunto si RE0 es 1
    bra es_falsazo	;viene aqui cuando es Falso
    bra es_verdad	;viene aqui cuando es Verdadero
es_verdad:
    bsf LATB, 0, 1	;enciendo RB0
    bcf LATB, 1, 1	;apago RB1
    call retardo	;llamada a subrutina retardo
    bcf LATB, 0, 1	;apago RB0
    bsf LATB, 1, 1	;enciendo RB1
    call retardo	;llamada a subrutina retardo
    bra inicio_tren	;retorno al inicio_tren
es_falsazo:
    bcf LATB, 0, 1	;apago RB0
    bcf LATB, 1, 1	;apago RB1
    bra inicio_tren	;retorno al inicio_tren
;Subrutina de retardo    
retardo:
    movlw 50
    movwf x_var, 1	;x_var valor de 50
punto_tres:    
    movlw 50
    movwf y_var, 1	;y_var valor de 50
punto_dos:    
    movlw 50
    movwf z_var, 1	;z_var valor de 50
punto_uno:    
    nop			;instruccion no operacion
    movf z_var, 1, 1	;evaluar z_var
    btfss STATUS, 2, 1	;pregunto si Z=1
    bra z_var_noescero	;Falso salta a label z_var_noescero
    movf y_var, 1, 1	;Verdad, evaluar y_var
    btfss STATUS, 2, 1	;preguntar Z=1
    bra y_var_noescero	;Falso salta a label y_var_noescero
    movf x_var, 1, 1	;evaluo x_var
    btfss STATUS, 2, 1	;preguntar si Z=1
    bra x_var_noescero	;Falso salta label x_var_noescero
    return
z_var_noescero:
    decf z_var, 1, 1	;decrementamos z_var
    bra punto_uno	;salto a label punto_uno
y_var_noescero:
    decf y_var, 1, 1	;decrementamos y_var
    bra punto_dos		;salto a label punto_dos
x_var_noescero:
    decf x_var, 1, 1	;decremento x_var
    bra punto_tres
    end upcino
    
    
    


