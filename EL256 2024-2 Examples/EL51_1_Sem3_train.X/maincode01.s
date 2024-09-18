    PROCESSOR 18F57Q43
    #include "cabecera.inc"

;asignación de nombres a los registros GPR para la rutina de retardo    
x_var EQU 500H
y_var EQU 501H
z_var EQU 502H
    
    PSECT upcino, class=CODE, reloc=2, abs
upcino:
    ORG 000000H		;vector de reset
    bra configuro	;salto a label configuro
    
    ORG 000100H		;zona de programa de usuario
configuro:
    ;configuracion de la fuente de reloj
    movlb 0H		;nos vamos al Bank0
    movlw 60H
    movwf OSCCON1, 1	;NOSC=HFINTOSC, NDIV 1:1
    movlw 02H
    movwf OSCFRQ, 1	;HFINTOSC a 4MHz
    movlw 40H
    movwf OSCEN, 1	;HFINTOSC habilitado
    ;configuracion las E/S
    movlb 4H
    bsf TRISE, 0, 1	;RE0 como entrada
    bcf ANSELE, 0, 1	;RE0 como digital
    ;opcion 1 manipulacion individual de bits
    ;bcf TRISB, 0, 1	;RB0 como salida
    ;bcf TRISB, 1, 1	;RB1 como salida
    ;bcf ANSELB, 0, 1	;RB0 como digital
    ;bcf ANSELB, 1, 1	;RB1 como digital
    ;opcion 2 manipulacion numerica al registro
    movlw 0FCH
    movwf TRISB, 1	;RB0 y RB1 como salidas
    movwf ANSELB, 1	;RB0 y RB1 como digitales

inicio_train:
    btfss PORTE, 0, 1	;Pregunto si RE0 es uno
    bra es_falso	;Falso, salta a label es_falso
    movlw 01H		;Verdad (efecto de luces del cruce de tren)
    movwf LATB, 1	;RB1 apagado, RB0 encendido
    call retardo	;llamo rutina de retardo
    movlw 02H
    movwf LATB, 1	;RB1 encendido, RB0 apagado
    call retardo	;llamo rutina de retardo
    bra inicio_train	;salta a label inicio_train
es_falso:
    clrf LATB, 1	;todo el RB en cero (apagado RB1 y RB0)
    bra inicio_train	;salta a label inicio_train
    
retardo:
    movlb 5H		;nos vamos al Bank5
    movlw 50
    movwf x_var, 1
punto_2:    
    movlw 50
    movwf y_var, 1
punto_1:    
    movlw 50
    movwf z_var, 1
punto_0:
    nop			;se va a repatir 125000 veces
    movlw 0
    cpfseq z_var, 1
    bra falso_z
    movlw 0
    cpfseq y_var, 1
    bra falso_y
    movlw 0
    cpfseq x_var, 1
    bra falso_x
    movlb 4H		;regresamos al Bank4
    return
falso_z:
    decf z_var, 1, 1
    bra punto_0
falso_y:
    decf y_var, 1, 1
    bra punto_1
falso_x:
    decf x_var, 1, 1
    bra punto_2

    end upcino