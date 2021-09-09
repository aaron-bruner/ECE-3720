#include <xc.h>
#include <sys/attribs.h>

#pragma config FSOSCEN = OFF    //Disable secondary Oscillator (enable RA4 and RB4)
#pragma config JTAGEN = OFF     //Disable JTAG (Enable RB7-RB9 & RB11)

void delay(int x);
int count = 0;

void delay(int x){ // Simple delay function so that we can see what is going on
    int i, j;
    for(i = 0; i < x; i++)
        for(j = 0; j < x; j++);
}

void __ISR(12)Timer(void){
    count++;
    if (count >= 0 && count < 20) { // GREEN LIGHT
        LATB = 0b1; // 0 0 1
        delay(200);
    }
    else if (count >= 20 && count <= 40) { // YELLOW LIGHT
        LATB = 0b10; // 0 1 0
        delay(200);
    }
    else if (count > 40 && count < 61) { // RED LIGHT
        LATB = 0b100; // 1 0 0
        if (count == 60) {
            count = 0;
            LATB = 0b1; // 0 0 1
        } else delay(200);
    }
    IFS0bits.T3IF = 0; // Clear interrupt flag
}

void __ISR(11)interupt(void){ // INT2 Interrupt (Emergency Signal)
    int i;
    for (i = 0; i < 11; i++) {
        LATB = 0x5; // 1 0 1
        delay(250);
        LATB = 0x2; // 0 1 0
        delay(250);
    }
    IFS0bits.INT2IF = 0;
}

int main () {
    INTCONbits.MVEC = 1;
    __builtin_enable_interrupts();
    
    // LED Output Pins
    TRISB = 0x8048;  // INT1 & INT2 Input | LED Output
    TRISA = 1;       // A0 (V_ref+) & A1 (V_ref-) Input
    ANSELA = 1;      // Analog A pins Enabled
    ANSELB = 0x8008; // Analog B15 & B3 Enabled
    INT2R = 0b0001;  // INT2 is set to B6
    
    CM1CONbits.ON = 1;
    CM1CONbits.CPOL = 0;
    CM1CONbits.CREF = 0;
    CM1CONbits.CCH = 0x3;

    // Set the comparator reference voltage (CV_REF)
    CVRCONbits.ON = 1;
    CVRCONbits.CVRSS = 1;
    CVRCONbits.CVRR = 0;
    CVRCONbits.CVR = 0xF;
    
    IPC2bits.INT2IP = 0x7;
    INTCONbits.INT2EP = 1;
    IEC0bits.INT2IE = 1;
    
    T2CONbits.ON = 0; // Disable Timer2
    T2CONbits.TCKPS = 0x000; // Utilize a prescale value of 1:1
    T2CONbits.T32 = 1; // 32-Bit Timer
    T2CONbits.TCS = 0; // Internal peripheral clock

    TMR2 = 0x00; //Clear contents of the timer register
    PR2 = 0xFFFF; // Load the Period register with the value 0xFFFF

    IEC0bits.T3IE = 1; // Enable Timer3 interrupts
    IFS0bits.T3IF = 0; // Clear the Timer3 interrupt status flag
    IPC3bits.T3IP = 1; // Polarity level for Timer3

    T2CONbits.ON = 1; // Enable Timer2

    while(1)
    {
        if (CMSTATbits.C1OUT == 1) count = 25; // When FSR is pressed set light to yellow
    }
}