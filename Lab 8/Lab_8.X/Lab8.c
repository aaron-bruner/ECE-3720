#include <xc.h>
#include <sys/attribs.h>

int pwm;

void __ISR(3)pushbutton(void){ // Interrupt for button press
    pwm+=25;
    if (pwm > 100) { // If PWM gets above 100 then go back to 0
        pwm = 0;
    }
    
 OC2RS=pwm;			  // Set OC2R to be our pwm
 IFS0bits.INT0IF = 0; // Clear the INT0 interrupt flag
}

int main(void) {

INTCONbits.MVEC = 1;
__builtin_enable_interrupts();
CFGCONbits.JTAGEN = 0;

TRISBbits.TRISB8 = 0; // Output for L293DNE
TRISBbits.TRISB7 = 1; // Input from button
CNPUBbits.CNPUB7 = 1;

RPB8R = 0b0101; // Assign B8 to OC2

IPC0bits.INT0IP=1; // Interrupt polarity
IEC0bits.INT0IE=1; // Enable INT0 interrupt
IFS0bits.INT0IF = 0; // Clear INT0 interrupt
INTCONbits.INT0EP=1; // Edge Polarity (1 Rising, 0 Falling Edge)

T2CONbits.TCS=0; // Use internal clock
T2CONbits.TCKPS=0; // 1:1 Prescale
T2CONbits.TGATE=0; // Gated time accumulation disabled
T2CONbits.T32=0; // 16-bit timer (TMRx and TMRy separate)

TMR2=0; // Clear timer register
PR2=100; // Load period value

T2CONbits.ON=1; // Enable timer 2

OC2CONbits.OCM=0x6; // PWM mode on OC, fault disabled
OC2CONbits.OC32=0; // 16-bit Mode
OC2CONbits.OCTSEL=0; // Timer 2 is clock source

OC2RS=0; // Initialize compare register with 0% duty cycle

OC2CONbits.ON=1; // Enable module

while(1){
}

}