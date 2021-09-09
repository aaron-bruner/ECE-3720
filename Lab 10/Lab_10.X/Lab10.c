#include <xc.h>
#include <sys/attribs.h>

#pragma config FSOSCEN = OFF    //Disable secondary Oscillator (enable RA4 and RB4)
#pragma config JTAGEN = OFF     //Disable JTAG (Enable RB7-RB9 & RB11)


void __ISR(23)FSRinterrupt(void){ // Interrupt for FSR
    int FSR = 0;
    // 4 buffers to make it more exact
    FSR = (ADC1BUF0 + ADC1BUF1 + ADC1BUF2 + ADC1BUF3) / 4;
    LATB = FSR >> 2; //shifts bits to only get upper bits
    
    IFS0bits.INT0IF = 0;   
}

int main(void) {
	INTCONbits.MVEC = 1;
	__builtin_enable_interrupts();

	ANSELBbits.ANSB12 = 1; // Analog for FSR
	TRISB = 0x1000; // LED Outputs & FSR Input

	TRISA = 1; // Analog for Vref+ and Vref-
	ANSELA = 1; // Vref+ & Vref-

    AD1CHSbits.CH0SA = 0; // Make Vref+ the input for the ADC
    AD1CHSbits.CH0NA = 0; // Set Vref- to be the V_R-
    AD1CON1bits.FORM = 0; // 16-bit integer
    AD1CON1bits.SSRC = 7; // internal counter ends sampling and starts conversion (auto convert) 
    AD1CON2bits.VCFG = 0; // Use internal reference voltages (V_DD and V_SS)
    AD1CON2bits.CSCNA = 0; // Module does not scan inputs
    AD1CON2bits.SMPI = 4; // Number of conversions per interrupt
    AD1CON2bits.BUFM = 0; // Buffer configured as one 16-word buffer
    AD1CON2bits.ALTS = 0; // Always use MUX A input multiplexer setting
    AD1CON3bits.ADRC = 0; // Clock is derived from peripheral bus clock
    AD1CON3bits.SAMC = 12; // Set auto-sample time
    AD1CON3bits.ADCS = 0xFF; // Set the conversion clock
    AD1CON1bits.ON = 1; // Turn on the ADC module
    
    IEC0bits.AD1IE = 1; // Enable A/D interrupt
    IFS0bits.AD1IF = 0; // Clear A/D Interrupt Flag
    IPC5bits.AD1IP = 1; // A/D Priority
    IPC5bits.AD1IS = 1; // A/D Sub prioritya

    AD1CON1bits.ASAM = 1; // Auto sample mode
 
while(1){ // Run forever
}

}