#include <xc.h>
#include <sys/attribs.h>

void __ISR(3)interupt(void){
    LATA = 0xF;
    delay(700);    
    IFS0bits.INT0IF = 0;
}

void delay(int x){
    int i, j;
    for(i = 0; i < x; i++)
        for(j = 0; j < x; j++);
}

int main () {
    INTCONbits.MVEC = 1;
    __builtin_enable_interrupts();
    CFGCONbits.JTAGEN = 0;
    
    int count = 0;
    
    // LED Output Pins
    TRISA = 0x0;
    // NAND Chip input (Q)
    TRISBbits.TRISB7 = 1;
    CNPDBbits.CNPDB7 = 1;

    IPC0bits.INT0IP = 0x1;
    INTCONbits.INT0EP = 1;
    IEC0bits.INT0IE = 1;

    while(1){
    LATA = count; //Output count to B
    count++;

    if(count > 15)//Restrict count to 0-15, needing only 4 bits
        count = 0;
    delay(300);
    }
}