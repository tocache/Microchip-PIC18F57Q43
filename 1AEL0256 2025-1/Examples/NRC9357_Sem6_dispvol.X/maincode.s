;Programa especial del 09 de mayo 2025
   PROCESSOR 18F57Q43
   #include "cabecera.inc"
    
NUMERO EQU 500H	;asignacion de label numero a GPR 500H

   PSECT upcino, class=CODE, reloc=2, abs
upcino:
   ORG 000000H
   bra configuro
    
   ORG 001000H
datos_7s:   DB 3FH, 06H, 5BH, 4FH, 66H, 6DH, 7DH, 07H, 7FH, 67H
   
   ORG 000100H
configuro:
    ;configuracion del modulo de oscilador
    movlb 0H
    movlw 60H
    movwf OSCCON1, 1
    movlw 02H
    movwf OSCFRQ, 1
    movlw 40H
    movwf OSCEN, 1
    ;configuracion de las E/S
    movlb 4H
    movlw 80H
    movwf TRISD, 1
    movwf ANSELD, 1
    movlw 0F8H
    movwf TRISF, 1
    movwf ANSELF, 1
    movlw 0FCH
    movwf ANSELB, 1
    movlw 03H
    movwf WPUB, 1
    ;asignacion de direccion 1000H al TBLPTR
    clrf TBLPTRU, 1
    movlw 10H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1
    ;configuraciones iniciales de la aplicación
    bsf LATF, 0, 1
    movlb 5H
    clrf NUMERO, 1  ;numero = 0
    movlb 4H

inicio:
btn1:	btfsc PORTB, 1, 1   ;pregunto si presione BTN1
	bra btn2	    ;no presion y va a preguntar a BTN2
	movlb 5H
	movlw 00H
	cpfseq NUMERO, 1    ;pregunto si NUMERO = 0
	bra noescero
	clrf NUMERO, 1	    ;NUMERO permanece en 0
	bra siguiente1
noescero:
	decf NUMERO, 1, 1   ;decremento NUMERO
siguiente1:
	movlb 4H
	btfss PORTB, 1, 1   ;pregunto si deje de pulsar BTN1
	bra $-2		    ;BTN1 sigue pulsado
	bra btn2	    ;se va a preguntar a BTN2

btn2:	btfsc PORTB, 0, 1   ;pregunto si presione BTN2
	bra disp7s	    ;no presione y va a rutina de disp7s
	movlb 5H
	movlw 09H
	cpfseq NUMERO, 1    ;pregunto si NUMERO = 9
	bra noesnueve
	movlw 09H
	movwf NUMERO, 1	    ;NUMERO permanece en 9
	bra siguiente2
noesnueve:
	incf NUMERO, 1, 1   ;incremento NUMERO
siguiente2:
	movlb 4H
	btfss PORTB, 0, 1   ;pregunto si deje de pulsar BTN1
	bra $-2		    ;BTN1 sigue pulsado
	bra disp7s	    ;se va a rutina de disp7s
	
disp7s:	movlb 5H
	movf NUMERO, 0, 1   ;leo NUMERO y lo mando a Wreg
	movlb 4H
	movwf TBLPTRL, 1    ;asignamos direccion de TBLPTR segun NUMERO
	TBLRD*
	movff TABLAT, LATD
	bra inicio
	
	end upcino
	
    
    

