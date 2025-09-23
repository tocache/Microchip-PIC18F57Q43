;Visualización de HOLA en el display mux 4 digitos CC
    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
posicion EQU 500H	;etiqueta para GPR 500H    
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 000100H
msg_hola:   DB 00H, 00H, 00H, 00H, 76H, 5CH, 38H, 5FH, 00H, 00H, 00H
    
    ORG 000200H
configuro:
    ;configuracion del modulo de oscilador
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1	    ;HFINTOSC PRESC 1:1
    ;movlw 02H
    ;movwf OSCFRQ, 1	    ;HFINTOSC a 4MHz
    movlw 50H
    movwf OSCEN, 1	    ;HFINTOSC y LFINTOSC enabled
    ;configuracion las E/S
    movlb 4H
    movlw 80H
    movwf TRISD, 1	    ;RD6 al RD0 como salidas
    movwf ANSELD, 1	    ;RD6 al RD0 como digitales
    movlw 0F0H
    movwf TRISB, 1	    ;RB3 al RB0 como salidas
    movwf ANSELB, 1	    ;RB3 al RB0 como digitales
    movlw 0FCH		    ;RF1 y RF0 por defecto son entradas
    movwf ANSELF, 1	    ;RF1 y RF0 como digitales
    movlw 03H
    movwf WPUF, 1
    ;direccion de apunte del TBLPTR
    clrf TBLPTRU, 1
    movlw 01H
    movwf TBLPTRH, 1
    movlw 04H
    movwf TBLPTRL, 1	    ;TBLPTR esta apuntando a 104H de la mem prog
    ;condiciones iniciales
    clrf LATD, 1	    ;RD con salidas en cero lógico
    clrf LATB, 1	    ;RB con salidas en cero lógico
    movlb 5H
    clrf posicion, 1	    ;valor de posicion = 0
    movlb 4H
    
;rutina principal de la aplicación    
inicio:
    btfsc PORTF, 0, 1
    bra siguiente
    movlb 5H
    movlw 7
    cpfseq posicion, 1	    ;pregunto si posicion=7
    bra incremento	    ;falso, salta a incremento
    clrf posicion, 1	    ;verdad, posicion=0
    bra fin1
incremento:
    incf posicion, 1, 1	    ;incremento posicion
fin1:
    movlb 4H
    btfss PORTF, 0, 1
    bra fin1
    bra mux_inicio
siguiente:
    btfsc PORTF, 1, 1
    bra mux_inicio
    movlb 5H
    movlw 0
    cpfseq posicion, 1	    ;pregunto si posicio=0
    bra decremento	    ;falso, salta a decremento
    movlw 7
    movwf posicion, 1	    ;verdad, posicion=7
    bra fin2
decremento:    
    decf posicion, 1, 1	    ;decremento posicion
fin2:
    movlb 4H
    btfss PORTF, 1, 1	    ;pregunto si solte RF1
    bra fin2
    
mux_inicio:    
    call multiplex
    bra inicio

;subrutina de multiplexacion    
multiplex:    
    movlb 5H
    movf posicion, 0, 1
    movlb 4H
    movwf TBLPTRL, 1	    ;TBLPTR esta apuntando a 104H de la mem prog
    TBLRD*		    ;lectura de lo que esta apuntando TBLPTR
    movff TABLAT, LATD	    ;muevo contenido de TABLAT a LATD
    bsf LATB, 0, 1	    ;habilito digito uno del display
    call nopes		    ;llama a subrutina nopes
    bcf LATB, 0, 1	    ;deshabilito digito uno del display
    incf TBLPTRL, 1, 1	    ;incremento dirección de apunte del TBLPTR
    TBLRD*		    ;lectura de lo que esta apuntando TBLPTR
    movff TABLAT, LATD	    ;muevo contenido de TABLAT a LATD
    bsf LATB, 1, 1	    ;habilito digito dos del display
    call nopes		    ;llama a subrutina nopes
    bcf LATB, 1, 1	    ;deshabilito digito dos del display
    incf TBLPTRL, 1, 1	    ;incremento dirección de apunte del TBLPTR
    TBLRD*		    ;lectura de lo que esta apuntando TBLPTR
    movff TABLAT, LATD	    ;muevo contenido de TABLAT a LATD
    bsf LATB, 2, 1	    ;habilito digito tres del display
    call nopes		    ;llama a subrutina nopes
    bcf LATB, 2, 1	    ;deshabilito digito tres del display
    incf TBLPTRL, 1, 1	    ;incremento dirección de apunte del TBLPTR
    TBLRD*		    ;lectura de lo que esta apuntando TBLPTR
    movff TABLAT, LATD	    ;muevo contenido de TABLAT a LATD
    bsf LATB, 3, 1	    ;habilito digito cuatro del display
    call nopes		    ;llama a subrutina nopes
    bcf LATB, 3, 1	    ;deshabilito digito cuatro del display
    return
    
nopes:
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    return
    
    end upcino





