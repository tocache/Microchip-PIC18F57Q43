    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upeceno, class=CODE, reloc=2, abs
upeceno:
    ORG 000000H
    bra configuro
    
    ORG 000100H
configuro:
    movlb 0H
    movlw 59H
    movwf OSCCON1, 1	    ;NOSC=LFINTOSC NDIV=1:512
    movlw 02H
    movwf OSCFRQ, 1
    movlw 50H
    movwf OSCEN, 1	    ;Se active LFINTOSC también
    movlb 4H
    movlw 80H
    movwf TRISD, 1
    movwf ANSELD, 1
    movlw 0F0H
    movwf TRISB, 1
    movwf ANSELB, 1
    ;condiciones iniciales
    clrf LATD, 1
    clrf LATB, 1

inicio:
    movlw 5EH
    movwf LATD, 1	;mando primer dato a RD ("d")
    bsf LATB, 0, 1	;habilito primer digito del display
    nop
    bcf LATB, 0, 1	;deshabilito primero digito del display
    nop
    movlw 5FH
    movwf LATD, 1	;mando primer dato a RD ("a")
    bsf LATB, 1, 1	;habilito segundo digito del display
    nop
    bcf LATB, 1, 1	;deshabilito segundo digito del display
    nop
    movlw 38H
    movwf LATD, 1	;mando primer dato a RD ("d")
    bsf LATB, 2, 1	;habilito primer digito del display
    nop
    bcf LATB, 2, 1	;deshabilito primero digito del display
    nop
    movlw 7BH
    movwf LATD, 1	;mando primer dato a RD ("d")
    bsf LATB, 3, 1	;habilito primer digito del display
    nop
    bcf LATB, 3, 1	;deshabilito primero digito del display
    nop
    bra inicio
    end upeceno
    
    


