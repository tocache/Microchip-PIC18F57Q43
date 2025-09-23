;Visualización de HOLA en el display mux 4 digitos CC
    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
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
    ;direccion de apunte del TBLPTR
    clrf TBLPTRU, 1
    movlw 01H
    movwf TBLPTRH, 1
    movlw 04H
    movwf TBLPTRL, 1	    ;TBLPTR esta apuntando a 104H de la mem prog
    ;condiciones iniciales de las E/S
    clrf LATD, 1	    ;RD con salidas en cero lógico
    clrf LATB, 1	    ;RB con salidas en cero lógico
    
inicio:    
    movlw 04H
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
    bra inicio
    
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


