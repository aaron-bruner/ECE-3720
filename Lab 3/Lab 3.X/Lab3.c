#include <xc.h>

main(void){

    ANSELAbits.ANSA0 = 1;
    ANSELAbits.ANSA1 = 1;
    ANSELBbits.ANSB0 = 1;
    ANSELBbits.ANSB2 = 1;
    ANSELBbits.ANSB3 = 1;
    ANSELBbits.ANSB15 = 1;
    
    // Inputs for the potentiometer
    TRISBbits.TRISB15 = 1;
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    
    // Set C1INA, C2IND, C3IND to input
    TRISBbits.TRISB3 = 1;
    TRISBbits.TRISB2 = 1;
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB15 = 1;
    
    // Digital Outputs for LEDs
    ANSELBbits.ANSB12 = 0;
    ANSELBbits.ANSB13 = 0;
    ANSELBbits.ANSB14 = 0;
    
    // Set output LED pins to output
    TRISBbits.TRISB12 = 0;
    TRISBbits.TRISB13 = 0;
    TRISBbits.TRISB14 = 0;

    // Enable compare register 1, 2 and 3
    CM1CONbits.ON = 1;
    CM2CONbits.ON = 1;
    CM3CONbits.ON = 1;

    // Compare output enable
    //CM1CONbits.COE = 0;
    //CM2CONbits.COE = 0;
    //CM3CONbits.COE = 0;

    // Compare output inversion bit
    CM1CONbits.CPOL = 0;
    CM2CONbits.CPOL = 1;
    CM3CONbits.CPOL = 1;

    // Comparator Positive Input Configure bit
    CM1CONbits.CREF = 0;
    CM2CONbits.CREF = 1;
    CM3CONbits.CREF = 0;

    // Comparator Negative Input Select bits for Comparator
    CM1CONbits.CCH = 0x3;
    CM2CONbits.CCH = 0x2;
    CM3CONbits.CCH = 0x2;

    // Set the comparator reference voltage (CV_REF)
    CVRCONbits.ON = 1;
    CVRCONbits.CVRSS = 1;
    CVRCONbits.CVRR = 0;
    CVRCONbits.CVR = 0xF;

    while(1) {
        LATBbits.LATB12 = CMSTATbits.C1OUT;
        LATBbits.LATB13 = CMSTATbits.C2OUT;
        LATBbits.LATB14 = CMSTATbits.C3OUT;
    }
}
