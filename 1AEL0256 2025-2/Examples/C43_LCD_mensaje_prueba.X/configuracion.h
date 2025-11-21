// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef CONFIGURACION_H
#define	CONFIGURACION_H

#include <xc.h> // include processor files - each processor file is guarded.  
#define _XTAL_FREQ 64000000UL// unsigned Long 32 bits

void Clock_Init(void);

#endif	/* CONFIGURACION_H */
