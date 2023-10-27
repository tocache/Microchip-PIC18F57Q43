    PROCESSOR 18F57Q43
    #include "cabecera.inc"
    
    PSECT upcino, class=CODE, reloc=2, abs
temporal EQU 500H	;GPR

upcino:
    ORG 000000H		;Vector de reset
    bra configuro
    
    ORG 000300H		;tabla de decodificacion
ceroaltres: DB	77H, 7CH, 58H,  5EH
    
    ORG 000100H
configuro:
    movlb 0H		;bank0
    movlw 60H
    movwf OSCCON1, 1	;hfintosc, 1:1
    movlw 02H
    movwf OSCFRQ, 1	;hfintosc 4MHz
    movlw 40H
    movwf OSCEN, 1	;hfintosc enabled
    movlb 3H		;bank3
    movlw 90H	
    movwf T0CON0, 1 	;tmr0 on, 16 bit, posts 1:1
    movlw 40H
    movwf T0CON1, 1	;fosc/4 presc 1:1
    movlb 4H		;bank4
    bcf TRISB, 0, 1	;RB0 salida
    bcf ANSELB, 0, 1	;RB0 digital
    clrf TRISD, 1	;RD salida
    clrf ANSELD, 1	;RD digital
    setf TRISC, 1	;RC1 y RC0 entradas
    movlw 0FCH
    movwf ANSELC, 1	;RC1 y RC0 digitales
    clrf TBLPTRU, 1
    movlw 03H
    movwf TBLPTRH, 1
    clrf TBLPTRL, 1	;TBLPTR apuntando a 300H
    movlb 5H
    clrf temporal, 1
    
inicio:			;rutina principal
    movlb 4H
    movf PORTC, 0, 1	;leo RC1 y RC0
    andlw 03H	    	;enmascaramiento
    movlb 5H
    movwf temporal, 1	;almacenar en GPR temporal
    call deco7s		;visualizacion en el display
    movlb 5H
    movlw 0
    cpfseq temporal, 1	;combinacional 0?
    bra siguiente1	;no, sigue preguntando
    bra estado_0	;salta a combinacional 0
siguiente1:
    movlw 1		
    cpfseq temporal, 1	;combinacional 1?
    bra siguiente2	;no, sigue preguntando
    bra estado_1	;salta a combinacional 1
siguiente2:
    movlw 2
    cpfseq temporal, 1	;combinacional 2?
    bra estado_3	;salta a combinacional 3
    bra estado_2	;salta a combinacional 2
    
estado_0:		;duty cycle 10%
    movlb 4H
    bsf LATB, 0, 1	;RB0 a uno
    movlb 3H
    movlw 0FFH
    movwf TMR0H, 1
    movlw 0DFH
    movwf TMR0L, 1
    movlb 4H
    btfss PIR3, 7, 1
    bra $-2
    bcf PIR3, 7, 1	;termino de TON (33us)
    bcf LATB, 0, 1	;RB0 a cero
    movlb 3H
    movlw 0FEH
    movwf TMR0H, 1
    movlw 0D4H
    movwf TMR0L, 1
    movlb 4H
    btfss PIR3, 7, 1
    bra $-2
    bcf PIR3, 7, 1	;termino de TOF (300us)
    bra inicio
 
estado_1:		;duty cycle 30%
    movlb 4H
    bsf LATB, 0, 1	;RB0 a uno
    movlb 3H
    movlw 0FFH
    movwf TMR0H, 1
    movlw 0ADH
    movwf TMR0L, 1
    movlb 4H
    btfss PIR3, 7, 1
    bra $-2
    bcf PIR3, 7, 1	;termino de TON (83us)
    bcf LATB, 0, 1	;RB0 a cero
    movlb 3H
    movlw 0FFH
    movwf TMR0H, 1
    movlw 06H
    movwf TMR0L, 1
    movlb 4H
    btfss PIR3, 7, 1
    bra $-2
    bcf PIR3, 7, 1	;termino de TOF (250us)
    bra inicio

estado_2:		;duty cycle 80%
    movlb 4H
    bsf LATB, 0, 1	;RB0 a uno
    movlb 3H
    movlw 0FFH
    movwf TMR0H, 1
    movlw 22H
    movwf TMR0L, 1
    movlb 4H
    btfss PIR3, 7, 1
    bra $-2
    bcf PIR3, 7, 1	;termino de TON (222us)
    bcf LATB, 0, 1	;RB0 a cero
    movlb 3H
    movlw 0FFH
    movwf TMR0H, 1
    movlw 91H
    movwf TMR0L, 1
    movlb 4H
    btfss PIR3, 7, 1
    bra $-2
    bcf PIR3, 7, 1	;termino de TOF (111us)
    bra inicio 
    
estado_3:		;duty cycle 100%
    movlb 4H
    bsf LATB, 0, 1	;RB0 a uno
    movlb 3H
    movlw 0FEH
    movwf TMR0H, 1
    movlw 0D4H
    movwf TMR0L, 1
    movlb 4H
    btfss PIR3, 7, 1
    bra $-2
    bcf PIR3, 7, 1	;termino de TON (300us)
    bcf LATB, 0, 1	;RB0 a cero
    movlb 3H
    movlw 0FFH
    movwf TMR0H, 1
    movlw 0DFH
    movwf TMR0L, 1
    movlb 4H
    btfss PIR3, 7, 1
    bra $-2
    bcf PIR3, 7, 1	;termino de TOF (33us)
    bra inicio  
    
deco7s:			;decodificacion 7seg
    movlb 4H
    movff temporal, TBLPTRL
    TBLRD*
    movff TABLAT, LATD
    return
    
    end upcino
    
    
    
    




