    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 000100H
configuro:
    ;configurar la fuente de reloj
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    ;configuro el PPS
    movlb 2H
    movlw 39H
    movwf RF0PPS, 1	;el RF0 conectado a TMR0
    ;configuro el Timer0
    movlb 3H
    movlw 244
    movwf TMR0H, 1	;valor de ref de comparador 244
    movlw 81H
    movwf T0CON0, 1	;TMR0 enabled, 8bit, POSTS 1:2
    movlw 0A9H
    movwf T0CON1, 1	;MFINTOSC, SYNC, PRESC 1:512
    ;configurar las E/S
    movlb 4H
    bcf TRISF, 0, 1	;RF0 es salida
    bcf ANSELF, 0, 1	;RF0 es digital

inicio:
    bra inicio
    ;el CPU no hace nada despues de la configuración!
    end upcino
    
    

