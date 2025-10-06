;Ejemplo de interrupciones en modo vectorizado individual
;Se han activado INT0, INT1 e INT2 para que con entrada de pulsadores
;activos en bajo puedan bascular LEDs
;Por Kalun Lau @UPC 15/05/2025
    
    PROCESSOR 18F57Q43
    #include "cabecera.inc"

    PSECT upcino, class=CODE, reloc=2
upcino:    
    ORG 000000H	    ;vector de RESET
    goto configuro
    
    ORG 000010H	    ;vector de la INT0 (2*08H)
    DW INT0_ISR shr 2
    
    ORG 000060H	    ;vector de la INT1 (2*30H)
    DW INT1_ISR shr 2

    ORG 0000A0H	    ;vector de la INT2 (2*50H)
    DW INT2_ISR shr 2
    
;Cada rutina de interrupción debe de tener su propio PSECT
    PSECT INT0_ISR, class=CODE, reloc=4
INT0_ISR:
    bcf PIR1, 0, 1	;bajamos bandera INT0IF
    btg LATF, 3, 1	;basculamos LED que esta en RF3
    retfie

    PSECT INT1_ISR, class=CODE, reloc=4
INT1_ISR:
    bcf PIR6, 0, 1	;bajamos bandera INT0IF
    btg LATE, 0, 1	;basculamos LED que esta en RE0
    retfie     

    PSECT INT2_ISR, class=CODE, reloc=4
INT2_ISR:
    bcf PIR10, 0, 1	;bajamos bandera INT0IF
    btg LATC, 0, 1	;basculamos LED que esta en RC0
    retfie    
    
;Inicio de codigo de usuario    
    PSECT code
    ORG 000100H

configuro:
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    movlb 2H		;Faltó el PPS XD
    movlw 0CH
    movwf INT0PPS, 1	;asignación de INT0 a RB4
    movlw 1BH
    movwf INT1PPS, 1	;asignación de INT1 a RD3
    movlw 29H
    movwf INT2PPS, 1	;asignación de INT2 a RF1
    movlb 4H
    bcf TRISF, 3, 1
    bcf ANSELF, 3, 1
    bcf TRISE, 0, 1
    bcf ANSELE, 0, 1
    bcf TRISC, 0, 1
    bcf ANSELC, 0, 1
    bsf TRISB, 4, 1
    bcf ANSELB, 4, 1
    bsf WPUB, 4, 1
    bsf TRISD, 3, 1
    bcf ANSELD, 3, 1
    bsf WPUD, 3, 1
    bsf TRISF, 1, 1
    bcf ANSELF, 1, 1
    bsf WPUF, 1, 1
    bsf LATF, 3, 1
    bcf LATC, 0, 1
    bcf LATE, 0, 1
    clrf IVTBASEU, 1
    ;movlw 10H
    ;movwf IVTBASEH, 1
    clrf IVTBASEH, 1
    clrf IVTBASEL, 1
    bsf PIE1, 0, 1	;activando INT0 con INT0IE=1
    bcf PIR1, 0, 1	;bajo bandera INT0IF
    bsf PIE6, 0, 1	;activando INT1 con INT1IE=1
    bcf PIR6, 0, 1	;bajo bandera INT1IF
    bsf PIE10, 0, 1	;acitvando INT2 con INT2IE=1
    bcf PIR10, 0, 1	;bajo bandera INT2IF
    bcf INTCON0, 0, 1	;INT0EDG=0 para detección de flanco negativo
    bcf INTCON0, 1, 1	;INT1EDG=0 para deteccion de flanco negativo
    bcf INTCON0, 2, 1	;INT2EDG=0 para deteccion de flanco negativo
    bsf INTCON0, 7, 1	;GIE=1 habilitando el interruptor global

;Rutina principal no hace nada
inicio:
    bra inicio
    
   
    end upcino
    


