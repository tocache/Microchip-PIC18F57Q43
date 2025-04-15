;Programa del ejemplo de la semana 2 - 2025-1
    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
;declarar etiquetas para los GPR
x_var EQU 500H
y_var EQU 501H
z_var EQU 502H

upcino:
    ORG 000000H
    bra configuro
    
    ORG 000100H
configuro:
    ;Configuracion del modulo de oscilador
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1	    ;NOSC=HFINTOSC, NDIV 1:1
    movlw 02H
    movwf OSCFRQ, 1	    ;HFINTOSC a 4MHz
    bsf OSCEN, 6, 1	    ;HFINTOSC enabled
    
    ;Configuracion de los puertos de E/S
    movlb 4H
    ;RF4 como entrada digital con pullup activado
    bsf TRISF, 4, 1	    ;RF4 entrada
    bcf ANSELF, 4, 1	    ;RF4 digital
    bsf WPUF, 4, 1	    ;RF4 pullup enabled
    ;RD3 como salida digital
    bcf TRISD, 3, 1	    ;RD3 salida
    bcf ANSELD, 3, 1	    ;RD3 digital
    
inicio:
    btfsc PORTF, 4, 1	    ;pregunto si presione el boton
    bra nopresione	    ;falso, salta a nopresione
    bra sipresione	    ;verdad, salta a sipresione
    
nopresione:
    bcf LATD, 3, 1	    ;apago el LED
    bra inicio		    ;salto de retorno a inicio
    
sipresione:
    bsf LATD, 3, 1	    ;enciendo el LED
    call dly200ms	    ;salto a subrutina dly200ms
    bcf LATD, 3, 1	    ;apago el LED
    call dly200ms	    ;salto a subrutina dly200ms
    bra inicio		    ;salto de retorno a inicio

;subrutina de retardo
dly200ms:
    movlb 5H
    movlw 50
    movwf x_var, 1
llegada_uno:
    movlw 50
    movwf y_var, 1
llegada_dos:
    movlw 20
    movwf z_var, 1
llegada_tres:
    nop
    ;pregunta si z_var llegó a cero
    movf z_var, 1, 1
    movlb 4H
    btfss STATUS, 2, 1	;pregunta si se levanto bandera Z
    bra noselevanto1
    movlb 5H
    ;pregunta si y_var llego a cero
    movf y_var, 1, 1
    movlb 4H
    btfss STATUS, 2, 1	;pregunta si se levanto bandera Z
    bra noselevanto2
    movlb 5H
    ;pregunta si x_var llego a cero
    movf x_var, 1, 1
    movlb 4H
    btfss STATUS, 2, 1	;pregunta si se levanto bandera Z
    bra noselevanto3
    return
noselevanto1:
    movlb 5H
    decf z_var, 1, 1	;decremento de z_var
    bra llegada_tres
noselevanto2:
    movlb 5H
    decf y_var, 1, 1	;decremento de y_var
    bra llegada_dos
noselevanto3:
    movlb 5H
    decf x_var, 1, 1	;decremento de x_var
    bra llegada_uno

    end upcino
