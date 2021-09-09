#include <xc.h>

void main(){
    
    // Declare integers to be used in program
    int output;
    int i;
    
    // Masking to connect our bianry inputs with the binary output
    unsigned int mask[16] = { 0x8008, 0x8004, 0x8002, 0x8001,
                              0x4008, 0x4004, 0x4002, 0x4001,
                              0x2008, 0x2004, 0x2002, 0x2001,
                              0x1008, 0x1004, 0x1002, 0x1001};
    
    unsigned char key_mask[16] = {1,  2, 3,  10,
                                  4,  5, 6,  11,
                                  7,  8, 9,  12,
                                  14, 0, 15, 13};
    
    // Set all A & B pins to digital
    ANSELA = 0;
    ANSELB = 0;
    
    // Pull down resistor for keypad input pins
    CNPDB = 0xF; // 0xF = 1111
	
	// Keypad Input Pins ( B0-B3 )
    TRISBbits.TRISB0 = 1;
	TRISBbits.TRISB1 = 1;
	TRISBbits.TRISB2 = 1;
	TRISBbits.TRISB3 = 1;
    
    // Keypad Output Pins ( B12-B15 )
    TRISBbits.TRISB12 = 0;
	TRISBbits.TRISB13 = 0;
    TRISBbits.TRISB14 = 0;
    TRISBbits.TRISB15 = 0;
    
	// LED Output Pins
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISAbits.TRISA3 = 0;
    
	while(1) {
			for(i = 0; i < 16; i++) { // Checking every input on the keypad
                
				// Set Keypad Output To High
				LATB = mask[i] & 0xF000;
                
                if((PORTB & 0xF) == (mask[i] & 0xF)) { // If our input equals the 
                                                       // mask then set the
                                                       // output to the key_mask
                                                       // index value
                    output = key_mask[i]; 
                }
				LATA = output; // If we're not pressing a button just keep
                               // representing our old output value on the LEDs
			}
    }
}