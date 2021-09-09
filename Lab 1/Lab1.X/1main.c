#include <xc.h>

//Simple delay w/o timers because of lab order
void delay(){
    int i, j;
    for(i = 0; i < 300; i++)
        for(j = 0; j < 300; j++);
}

main(){
    int count = 15;
    TRISB = 0;          // Set all B pins to output
      
    while(1){
        LATB = count;	// Write count to output pins 
        count--;
        if(count < 0)
            count = 15;
        delay();
    }
}
