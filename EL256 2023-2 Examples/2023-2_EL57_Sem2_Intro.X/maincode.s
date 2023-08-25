    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT principal, class=CODE, reloc=2, abs
principal:
    ORG 000000H		;Vector de RESET
    bra configuro	;Salto hacia etiqueta configuro
    
    ORG 000020H		;Zona de programa de usuario
configuro:
    ;Configuraciones de la aplicación (puertos, periféricos, etc)
    ;Configuración de la fuente de reloj para 4MHz con el HFINTOSC
    movlb 0H		;Bank 0 donde estan los registros de conf del OSC
    ;OSCFRQ = 02H
    movlw 02H		;muevo literal 02H a wreg
    movwf OSCFRQ, 1	;muevo contenido de wreg hacia OSCFRQ
    ;OSCCON1 = 60H
    movlw 60H		;muevo literal 60H a wreg
    movwf OSCCON1, 1	;muevo contenido de wreg hacia OSCCON1
    ;OSCEN = 40H
    movlw 40H		;muevo literal 40H a wreg (0100 0000)
    movwf OSCEN, 1	;muevo contenido de wreg hacia OSCEN
    
    ;Configuración de las E/S para el negador lógico integrado
    movlb 4H		;Bank4 donde estan los registros de los puertos
    bsf TRISB, 4, 1	;RB4 como entrada
    bcf ANSELB, 4, 1	;RB4 como digital
    bsf WPUB, 4, 1	;RB4 con pullup
    bcf TRISF, 3, 1	;RF3 como salida
    bcf ANSELF, 3, 1	;RF3 como digital
    
inicio:
    ;Detalle de lo que va a hacer el microcontrolador
    btfsc PORTB, 4, 1	;Pregunto si RB4 es cero
    bra nopresione	;Falso, RB4 es uno
    bsf LATF, 3, 1	;Verdadero, apagar el LED
    bra inicio		;Salto hacia etiqueta inicio
nopresione:
    bcf LATF, 3, 1	;enciendo el LED
    bra inicio		;Salto hacia etiqueta inicio
    
    end principal


