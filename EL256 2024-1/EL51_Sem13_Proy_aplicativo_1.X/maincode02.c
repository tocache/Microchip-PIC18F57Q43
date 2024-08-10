/*
 * File:   maincode01.c
 * Author: klnla
 *
 * Created on 12 de junio de 2024, 02:04 PM
 */
#include <xc.h>
#include <string.h>
#include "cabcezota.h"
#define _XTAL_FREQ 32000000UL

void configuro(void){
    OSCCON1 = 0x60;
    OSCFRQ = 0x06;
    OSCEN = 0x40;
    //configuracion del UART
    U1BRGH = 0;
    U1BRGL = 207;           //UART1 a 9600 baudios
    U1CON0 = 0x30;          //TX enabled, RX enabled
    U1CON1 = 0x80;          //UART1 habilitado (enabled)
    U1CON2 = 0x00;          //Dejarlo valores por defecto
    RF0PPS = 0x20;          //RF0 esta conectado a UART1TX
    U1RXPPS = 0x29;         //RF1 esta conectado a UART1RX    
}

void U1_BYTE_SEND(unsigned char dato){
    U1TXB = dato;
    while(U1ERRIRbits.TXMTIF == 0);
}

void U1_STRING_SEND(const char *cadena)
{
    unsigned char tam;
    tam = strlen(cadena);
	unsigned char i = 0;
	for(i = 0; i<tam; i++)
	{
		U1_BYTE_SEND(cadena[i]);
	}
}

void U1_NEWLINE(void){
    U1_BYTE_SEND(0x0A);
    U1_BYTE_SEND(0x0D);
}

void apuren(void){
    U1_STRING_SEND("  /$$$$$$  /$$$$$$$  /$$   /$$ /$$$$$$$  /$$$$$$$$ /$$   /$$ /$$");
    U1_NEWLINE();
    U1_STRING_SEND(" /$$__  $$| $$__  $$| $$  | $$| $$__  $$| $$_____/| $$$ | $$| $$");
    U1_NEWLINE();
    U1_STRING_SEND("| $$  \ $$|  $$  \ $$|  $$  | $$| $$  \ $$|  $$      | $$$$| $$| $$");
    U1_NEWLINE();
    U1_STRING_SEND("| $$$$$$$$| $$$$$$$/| $$  | $$| $$$$$$$/| $$$$$   | $$ $$ $$| $$");
    U1_NEWLINE();
    U1_STRING_SEND("| $$__  $$| $$____/ | $$  | $$| $$__  $$| $$__/   | $$  $$$$|__/");
    U1_NEWLINE();
    U1_STRING_SEND("| $$  | $$| $$      | $$  | $$| $$  \ $$ | $$      | $$\   $$$    ");
    U1_NEWLINE();
    U1_STRING_SEND("| $$  | $$| $$      |  $$$$$$/| $$  | $$| $$$$$$$$| $$ \   $$ /$$");
    U1_NEWLINE();
    U1_STRING_SEND("|__/  |__/|__/       \______/ |__/  |__/|________/|__/  \__/|__/");
    U1_NEWLINE();
}

void apuren2(void){
    U1_STRING_SEND("               AAA               PPPPPPPPPPPPPPPPP   UUUUUUUU     UUUUUUUURRRRRRRRRRRRRRRRR   EEEEEEEEEEEEEEEEEEEEEENNNNNNNN        NNNNNNNN !!! ");
    U1_NEWLINE();
    U1_STRING_SEND("              A:::A              P::::::::::::::::P  U::::::U     U::::::UR::::::::::::::::R  E::::::::::::::::::::EN:::::::N       N::::::N!!:!!");
    U1_NEWLINE();
    U1_STRING_SEND("             A:::::A             P::::::PPPPPP:::::P U::::::U     U::::::UR::::::RRRRRR:::::R E::::::::::::::::::::EN::::::::N      N::::::N!:::!");
    U1_NEWLINE();
    U1_STRING_SEND("            A:::::::A            PP:::::P     P:::::PUU:::::U     U:::::UURR:::::R     R:::::REE::::::EEEEEEEEE::::EN:::::::::N     N::::::N!:::!");
    U1_NEWLINE();
    U1_STRING_SEND("           A:::::::::A             P::::P     P:::::P U:::::U     U:::::U   R::::R     R:::::R  E:::::E       EEEEEEN::::::::::N    N::::::N!:::!");
    U1_NEWLINE();
    U1_STRING_SEND("          A:::::A:::::A            P::::P     P:::::P U:::::D     D:::::U   R::::R     R:::::R  E:::::E             N:::::::::::N   N::::::N!:::!");
    U1_NEWLINE();
    U1_STRING_SEND("         A:::::A A:::::A           P::::PPPPPP:::::P  U:::::D     D:::::U   R::::RRRRRR:::::R   E::::::EEEEEEEEEE   N:::::::N::::N  N::::::N!:::!");
    U1_NEWLINE();
    U1_STRING_SEND("        A:::::A   A:::::A          P:::::::::::::PP   U:::::D     D:::::U   R:::::::::::::RR    E:::::::::::::::E   N::::::N N::::N N::::::N!:::!");
    U1_NEWLINE();
    U1_STRING_SEND("       A:::::A     A:::::A         P::::PPPPPPPPP     U:::::D     D:::::U   R::::RRRRRR:::::R   E:::::::::::::::E   N::::::N  N::::N:::::::N!:::!");
    U1_NEWLINE();
    U1_STRING_SEND("      A:::::AAAAAAAAA:::::A        P::::P             U:::::D     D:::::U   R::::R     R:::::R  E::::::EEEEEEEEEE   N::::::N   N:::::::::::N!:::!");
    U1_NEWLINE();
    U1_STRING_SEND("     A:::::::::::::::::::::A       P::::P             U:::::D     D:::::U   R::::R     R:::::R  E:::::E             N::::::N    N::::::::::N!!:!!");
    U1_NEWLINE();
    U1_STRING_SEND("    A:::::AAAAAAAAAAAAA:::::A      P::::P             U::::::U   U::::::U   R::::R     R:::::R  E:::::E       EEEEEEN::::::N     N:::::::::N !!! ");
    U1_NEWLINE();
    U1_STRING_SEND("   A:::::A             A:::::A   PP::::::PP           U:::::::UUU:::::::U RR:::::R     R:::::REE::::::EEEEEEEE:::::EN::::::N      N::::::::N     ");
    U1_NEWLINE();
    U1_STRING_SEND("  A:::::A               A:::::A  P::::::::P            UU:::::::::::::UU  R::::::R     R:::::RE::::::::::::::::::::EN::::::N       N:::::::N !!! ");
    U1_NEWLINE();
    U1_STRING_SEND(" A:::::A                 A:::::A P::::::::P              UU:::::::::UU    R::::::R     R:::::RE::::::::::::::::::::EN::::::N        N::::::N!!:!!");
    U1_NEWLINE();
    U1_STRING_SEND("AAAAAAA                   AAAAAAAPPPPPPPPPP                UUUUUUUUU      RRRRRRRR     RRRRRRREEEEEEEEEEEEEEEEEEEEEENNNNNNNN         NNNNNNN !!! ");
    U1_NEWLINE();
}

void main(void) {
    configuro();
    while(1){
        U1_STRING_SEND("|----------------------|");
        U1_NEWLINE();
        U1_STRING_SEND("|                      |");
        U1_NEWLINE();
        U1_STRING_SEND("|     Hola mundo!      |");
        U1_NEWLINE();
        U1_STRING_SEND("|  Microcontroladores  |");
        U1_NEWLINE();
        U1_STRING_SEND("|                      |");
        U1_NEWLINE();
        U1_STRING_SEND("|----------------------|");
        U1_NEWLINE();
        U1_NEWLINE();
        apuren();
        apuren2();
        __delay_ms(1000);
    }
}
