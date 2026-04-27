    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upeceno, class=CODE, reloc=2, abs
upeceno:
    ORG 000000H
    bra configuro
    
    ORG 000100H
configuro:
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1	    ;NOSC=HFINTOSC NDIV=1:1
    movlw 02H
    movwf OSCFRQ, 1	    ;HFINTOSC a 4MHz
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
    call nopes
    bcf LATB, 0, 1	;deshabilito primero digito del display
    movlw 5FH
    movwf LATD, 1	;mando primer dato a RD ("a")
    bsf LATB, 1, 1	;habilito segundo digito del display
    call nopes
    bcf LATB, 1, 1	;deshabilito segundo digito del display
    movlw 38H
    movwf LATD, 1	;mando primer dato a RD ("d")
    bsf LATB, 2, 1	;habilito primer digito del display
    call nopes
    bcf LATB, 2, 1	;deshabilito primero digito del display
    movlw 7BH
    movwf LATD, 1	;mando primer dato a RD ("d")
    bsf LATB, 3, 1	;habilito primer digito del display
    call nopes
    bcf LATB, 3, 1	;deshabilito primero digito del display
    bra inicio
    
nopes:			;Ejecución de 100 nops
    movlb 5H
    movlw 100
    movwf 500H, 1	;GPR de 500H
    nop
    decfsz 500H, 1, 1	;decremento y pregunto si ya llego a cero
    bra $-4
    movlb 4H
    return
    end upeceno
