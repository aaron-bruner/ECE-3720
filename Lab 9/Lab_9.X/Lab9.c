#include <xc.h>
#include <sys/attribs.h>

int i = 0;
char spiChars[18] = {0, 1, 2, 4, 8, 16, 32, 64, 128, 255, 254, 
                        253, 251, 247, 239, 223, 191, 127};

void __ISR(3)pushbutton(void){ // Interrupt for button press
 if(i == 18) {
    i = 0;
 }
 SPI1BUF = spiChars[i];
 i++;
 IFS0bits.INT0IF = 0;
}

int main(void) {

INTCONbits.MVEC = 1;
__builtin_enable_interrupts();
CFGCONbits.JTAGEN = 0;

ANSELB = 0; // Digital IO

RPB15R = 0b0011; // PPS : B15 is SS1
RPB5R = 0b0011;  // PPS : B5  is SDO1

TRISBbits.TRISB15 = 0; // Output for SS1
TRISBbits.TRISB14 = 0; // Output for SCK1
TRISBbits.TRISB5 = 0;  // Output for SDO1
TRISBbits.TRISB7 = 1;  // Button input

INTCONbits.INT0EP = 0; // Edge polarity (falling)
IPC0bits.INT0IP = 1;   // Priority Level
IFS0bits.INT0IF = 0;   // Interrupt Flag
IEC0bits.INT0IE = 1;   // Enable

IEC1bits.SPI1EIE = 0;  // Disable SPI interrupt
IEC1bits.SPI1RXIE = 0;
IEC1bits.SPI1TXIE = 0;

SPI1CONbits.ON = 0;		 // Disable SPI
SPI1BUF = 0;			 // Clear recieve buffer
SPI1CONbits.ENHBUF = 0;  // Disable enhanced buffer mode
SPI1BRG = 1000;			 // SPI clock frequency
SPI1STATbits.SPIROV = 0; // Clear overflow detection
SPI1CONbits.MSTEN = 1;   // SPI peripheral is the master
SPI1CONbits.MSSEN = 1;   // Select to be in master mode

SPI1CONbits.CKP = 0;     // Clock is idle when low, active when high
SPI1CONbits.CKE = 1;     // The output data changes when clock transitions from active to idle
SPI1CONbits.ON = 1;		 // Enable SPI
SPI1BUF = 0;

while(1){
}
}