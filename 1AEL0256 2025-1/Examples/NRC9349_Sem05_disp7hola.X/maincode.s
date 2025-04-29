;Programa para visualizar HOLA en un display de cuatro dígitos de siete segmentos
    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
;declarar etiquetas para los GPR
x_var EQU 500H
y_var EQU 501H
z_var EQU 502H    
    
upcino:
    ORG 000000H	    ;vector de RESET
    bra configuro
    
    ORG 005000H	    ;posicion de la palaba hola
	    ;	H    O	  L    A
msg_hola:   DB 76H, 3FH, 38H, 77H
    
    ORG 000100H	    ;zona de programa de usuario
configuro:
    ;configurar el modulo de oscilador
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    ;configurar las E/S
    movlb 4H
    movlw 80H
    movwf TRISD, 1
    movwf ANSELD, 1 ;RD6 al RD0 como salidas digitales
    movlw 0F0H
    movwf TRISB, 1
    movwf ANSELB, 1 ;RB3 al RB0 como salidas digitales
    ;establecer la direccion de apunte al puntero de tabla TBLPTR
    clrf TBLPTRU, 1
    movlw 50H
    movwf TBLPTRH, 1
    clrf TBLPTRL,1    ;El TBLPTR esta apuntando a la dirección 005000H de la memoria de datos
    
    ;condiciones iniciales de la aplicación
    clrf LATD, 1    ;Apagamos todos los segmentos del display
    clrf LATB, 1    ;Apagamos todos los habilitadores del display
    
inicio:
    clrf TBLPTRL, 1 ;TBLPTR apuntando a 005000H
    TBLRD*	    ;Acción de lectura
    movf TABLAT, 0, 1	;mover contenido de TABLAT a Wreg
    movwf LATD, 1	;mover contenido de Wreg a puerto RD
    bsf LATB, 0, 1	;Encienda el primer digito del display
    call retardon
    bcf LATB, 0, 1	;Apago el primger digito del display
    incf TBLPTRL, 1, 1	;incremento posición de apunte de TBLPTR
    TBLRD*
    movf TABLAT, 0, 1	;mover contenido de TABLAT a Wreg
    movwf LATD, 1	;mover contenido de Wreg a puerto RD
    bsf LATB, 1, 1	;Enciendo el segundo digito del display
    call retardon
    bcf LATB, 1, 1	;Apago el segundo digito del display
    incf TBLPTRL, 1, 1	;incremento posición de apunte de TBLPTR
    TBLRD*
    movf TABLAT, 0, 1	;mover contenido de TABLAT a Wreg
    movwf LATD, 1	;mover contenido de Wreg a puerto RD
    bsf LATB, 2, 1	;Enciendo el tercer digito del display
    call retardon
    bcf LATB, 2, 1	;Apago el tercer digito del display
    incf TBLPTRL, 1, 1	;incremento posición de apunte de TBLPTR
    TBLRD*
    movf TABLAT, 0, 1	;mover contenido de TABLAT a Wreg
    movwf LATD, 1	;mover contenido de Wreg a puerto RD
    bsf LATB, 3, 1	;Enciendo el cuarto digito del display
    call retardon
    bcf LATB, 3, 1	;Apago del cuarto digito del display
    bra inicio
    
;subrutina de retardo
retardon:
    movlb 5H
    movlw 5
    movwf x_var, 1
llegada_uno:
    movlw 5
    movwf y_var, 1
llegada_dos:
    movlw 5
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
    
    


