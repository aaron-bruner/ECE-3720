#include <xc.h>

int main(void){

 TRISBbits.TRISB14 = 1;
 TRISBbits.TRISB15 = 1;
 TRISBbits.TRISB10 = 1;
 TRISAbits.TRISA1 = 0;
 TRISBbits.TRISB0 = 0;
 TRISBbits.TRISB1 = 0;
 CNPUBbits.CNPUB10 = 1;

 ANSELB = 0;
 ANSELAbits.ANSA1 = 0;
 
 while(1){
 LATBbits.LATB0 = PORTBbits.RB15;
 LATBbits.LATB1 = PORTBbits.RB14;

 if (PORTBbits.RB10 == 0){
 LATAbits.LATA1 = 1;
 }
 else {
 LATAbits.LATA1 = 0;
 }
 }
}