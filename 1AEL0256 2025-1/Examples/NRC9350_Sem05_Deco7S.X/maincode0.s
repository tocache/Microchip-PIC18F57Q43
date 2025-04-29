;Programa para visualizar la palabra HOLA en un display de
;cuatro dígitos de siete segmentos de cátodo común
    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H
    bra configuro
    
    ORG 004000H	    ;zona de datos del mensaje
hola_msg:   DB	76H, 3FH, 38H, 77H    
    
    ORG 000100H
configuro:
    ;configuracion del modulo de oscilador
    movlb 0H		;va al Bank0
    movlw 60H
    movwf OSCCON1, 1	    ;NDIV 1:1
    movlw 02H
    movwf OSCFRQ, 1	    ;HFINTOSC a 4MHz
    movlw 40H
    movwf OSCEN, 1
    ;configuración de PPS
    movlb 2H		;al Bank2
    movlw 39H
    movwf RF1PPS, 1	;asignando salida de TMR0 a puerto RF1
    ;configuración del Timer0
    movlb 3H
    movlw 80H
    movwf T0CON0, 1	;TMR0 enabled, 8bit mode, posts 1:1
    movlw 6BH
    movwf T0CON1, 1	;source: HFINTOSC (4MHz), sync, presc 1:2048
    movlw 195
    movwf TMR0H, 1	;valor de referencia de cpomparación del Tmr0 en 8bit mode
    ;configuración de las E/S
    movlb 4H		;va al Bank4
    movlw 80H
    movwf TRISD, 1	;RD6 al RD0 como salidas
    movwf ANSELD, 1	;RD6 al RD0 como digital
    movlw 0F0H
    movwf TRISB, 1	;RB3 al RB0 como salidas
    movwf ANSELB, 1	;RB3 al RB0 como digitales
    bcf TRISF, 1, 1	;RF1 como salida
    bcf ANSELF, 1, 1	;RF1 como digital
    ;ubicar el TBLPTR en la dirección 4000H de mem prog
    clrf TBLPTRU, 1
    movlw 40H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1	;TBLPTR apunta a 4000H
    ;condiciones iniciales de la aplicación
    clrf LATB, 1	;habilitadores del disp apagados

inicio:
    clrf TBLPTRL, 1	;ubico a TBLPTR en 4000H
    TBLRD*
    movff TABLAT, LATD	;muevo contenido de TABLAT a puerto RD
    bsf LATB, 0, 1	;habilitando el primer digito
    nop
    bcf LATB, 0, 1	;apagando el primer digito
    incf TBLPTRL, 1, 1	;incremento el TBLPTR a 4001H
    TBLRD*
    movff TABLAT, LATD	;muevo contenido de TABLAT a puerto RD
    bsf LATB, 1, 1	;habilitando el segundo digito
    nop
    bcf LATB, 1, 1	;apago el segundo digito
    incf TBLPTRL, 1, 1	;incremento el TBLPTR a 4002H
    TBLRD*
    movff TABLAT, LATD	;muevo contenido de TABLAT a puerto RD
    bsf LATB, 2, 1	;habilitando el tercer digito
    nop
    bcf LATB, 2, 1	;apago el tercer digito
    incf TBLPTRL, 1, 1	;incremento el TBLPTR a 4003H
    TBLRD*
    movff TABLAT, LATD	;muevo contenido de TABLAT a puerto RD
    bsf LATB, 3, 1	;habilitando el cuarto digito
    nop
    bcf LATB, 3, 1	;apago el cuarto digito
    bra inicio
    end upcino


