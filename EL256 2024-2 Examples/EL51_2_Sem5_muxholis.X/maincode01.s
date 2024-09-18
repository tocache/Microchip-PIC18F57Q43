    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 001000H
p_holis: DB 76H, 3FH, 38H, 77H
    
    ORG 000100H
configuro:
    ;configuro la fuente de reloj
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1	;NOSC=HFINTOSC, NDIV=1:1
    movlw 02H
    movwf OSCFRQ, 1	;HFINTOSC 4MHz, CPU 4MHz
    movlw 40H
    movwf OSCEN, 1	;HFINTOSC enabled
    ;configuro las E/S
    movlb 4H
    movlw 80H
    movwf TRISD, 1	;RD[6:0] sean salidas
    movwf ANSELD, 1	;RD[6:0] sean digitales
    movlw 0F0H
    movwf TRISB, 1	;RB[3:0] sean salidas
    movwf ANSELB, 1	;RB[3:0] sean digitales
    ;condiciones iniciales
    clrf LATB, 1	;RB[3:0] estan en cero
    clrf TBLPTRU, 1
    movlw 10H
    movwf TBLPTRH, 1
    
inicio_mux:
    movlw LOW p_holis
    movwf TBLPTRL, 1	;TBLPTR apunta a 001000H
    TBLRD*+		;Leo la dir apuntada por TBLPTR y lo incrementa
    movff TABLAT, LATD	;muevo el contenido leido a LATD
    bsf LATB, 0, 1	;habilito primer digito
    call nopesx32
    bcf LATB, 0, 1	;deshabilito primer digito
    TBLRD*+		;Leo la dir apuntada por TBLPTR y lo incrementa
    movff TABLAT, LATD	;muevo el contenido leido a LATD
    bsf LATB, 1, 1	;habilito primer digito
    call nopesx32
    bcf LATB, 1, 1	;deshabilito primer digito
    TBLRD*+		;Leo la dir apuntada por TBLPTR y lo incrementa
    movff TABLAT, LATD	;muevo el contenido leido a LATD
    bsf LATB, 2, 1	;habilito primer digito
    call nopesx32
    bcf LATB, 2, 1	;deshabilito primer digito
    TBLRD*+		;Leo la dir apuntada por TBLPTR y lo incrementa
    movff TABLAT, LATD	;muevo el contenido leido a LATD
    bsf LATB, 3, 1	;habilito primer digito
    call nopesx32
    bcf LATB, 3, 1	;deshabilito primer digito
    bra inicio_mux
    
nopesx32:
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
