#include <plib.h>
// (or use xc.h)

//	Declare your count variable (Declaring it up here will make it global and accessible by the ISRs.)


//	ISR for first interrupt
//	{
//		Check the values on both inputs and modify count accordingly
//		(consider the table on slide 8 whether this interrupt was triggered by a rising or falling edge)

//		Adjust interrupt edge polarity
//		Clear interrupt flag
//	}


//	ISR for second interrupt
//	{
//		Check the values on both inputs and modify count accordingly
//		(consider the table on slide 8 whether this interrupt was triggered by a rising or falling edge)

//		Adjust interrupt edge polarity
//		Clear interrupt flag
//	}

main(){    
//	Map a second external interrupt to your chosen input pin (PPS)

//	Inputs and outputs (TRISx, etc.)

//	Set up both external interrupts (similar to Lab 5)    
    
    
    while(1)
	{
//		Restrict count to [0,15] (remember that it can be increasing or decreasing this time)
        
//      Write count to outputs (remember that count only changes in the ISRs)
    }
}