#include <xc.h>
#include <sys/attribs.h>

int count = 0;

void __ISR(3)Int0Handler(void){

 if (PORTBbits.RB9 == 1){ // B Output From Grayhill61C Optical Encoder
    if (PORTBbits.RB7 == 1) // A Output From Grayhill61C Optical Encoder
        count--;
    else
        count++; 
 }
 else {
    if(PORTBbits.RB7 == 0)
        count--;
    else
        count++;
 }
 INTCONbits.INT0EP = ~INTCONbits.INT0EP; // Invert Current Polarity of INT0
 IFS0bits.INT0IF = 0; // Clear the INT0 interrupt flag
}

void __ISR(7)Int1Handler(void){

 if(PORTBbits.RB7 == 1){
    if(PORTBbits.RB9 == 1)
        count++;
    else
        count--;
 }
 else {
    if(PORTBbits.RB9 == 0)
        count++;
    else
        count--;
 }
 INTCONbits.INT1EP = ~INTCONbits.INT1EP; // Invert Current Polarity of INT1
 IFS0bits.INT1IF = 0; // Clear the INT1 interrupt flag
}

int main(void) {

INTCONbits.MVEC = 1;
__builtin_enable_interrupts();
CFGCONbits.JTAGEN = 0;
    
 TRISA = 0x0; // LED Outputs
 TRISBbits.TRISB7 = 1; // A input
 TRISBbits.TRISB9 = 1; // B input
 IPC0bits.INT0IP = 0x1; // Enable Interrupt 0
 
 if (PORTBbits.RB7 == 0)
    INTCONbits.INT0EP = 1; // Set our edge polarity ( 1 rising, 0 falling edge )
 else
     INTCONbits.INT0EP = 0;
 
 IEC0bits.INT0IE = 1; // Enable INT0 Interrupt

 INT1R = 0b0100; // Assign Interrupt 1 to pin B9

 IPC1bits.INT1IP = 0b0010; // Interrupt Polarity
 if (PORTBbits.RB9 = 0)
    INTCONbits.INT1EP = 1;
 else
     INTCONbits.INT1EP = 0;
 
 IEC0bits.INT1IE = 1; // Enable INT1 Interrupt

 while(1) {
    LATA = count;
    if(count > 15)
        count = 0;
    if(count < 0)
        count = 15;
 }
}
