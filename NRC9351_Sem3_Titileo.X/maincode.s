;Programa para titular un LED con una entrada de control
    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
    
;declarar nombres de registros GPR (lo que esta mapeado de la RAM)
x_var EQU 500H	    ;asignando etiqueta x_var al registro 500H
y_var EQU 501H
z_var EQU 502H
 
upcino:
    ORG 000000H	    ;vector de reset
    bra configuro   ;salto a label configuro
    
    ORG 000100H	    ;zona de programa de usuario
configuro:
    ;configurar la fuente de reloj
    movlb 0H	    ;nos vamos al Bank0
    movlw 60H
    movwf OSCCON1, 1	;NOSC=HFINTOSC NDIV 1:1
    movlw 02H
    movwf OSCFRQ, 1	;HFINTOSC a 4MHz
    movlw 40H
    movwf OSCEN, 1	;Habilitamos el HFINTOSC
    
    ;configurar los puertos de E/S de la aplicacion
    movlb 4H		;nos vamos al Bank4
    ;RF4 entrada digital con pullup activado
    bsf TRISF, 4, 1	;RF4 es entrada
    bcf ANSELF, 4, 1	;RF4 es digital
    bsf WPUF, 4, 1	;RF4 con pullup activo
    ;RD3 salida digital
    bcf TRISD, 3, 1	;RD3 es salida
    bcf ANSELD, 3, 1	;RD3 es digital

;rutina de la aplicación:
inicio:
    btfsc PORTF, 4, 1	;preguntamos si RF4 es cero (si has pulsado el boton)
    bra no_presionaste	;salto a label no_presionaste
    bra si_presionaste	;salto a label si_presionaste
    
no_presionaste:
    ;mantener el LED apagado
    bcf LATD, 3, 1	;RD3 en bajo (LED apagado)
    bra inicio		;Salta a label inicio
    
si_presionaste:
    ;parpadear el LED
    bsf LATD, 3, 1	;RD3 en alto (LED encendido)
    call retardon	;llamada a la subrutina de retardo
    bcf LATD, 3, 1	;RD3 en bajo (LED apagado)
    call retardon	;llamada a la subrutina de retardo
    bra inicio		;Salta a label inicio


;subrutina de retardo
retardon:
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