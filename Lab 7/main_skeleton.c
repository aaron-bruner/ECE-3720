#include<plib.h>

//This is here to make timing calculations easier!
#pragma config FPBDIV = DIV_2

//r is a Rest.  If r, do not toggle! (don't want noise to play) 
#define r 3000 
#define a 4545 
#define b 4050 
#define C 3817 
#define C_ 3610 
#define D 3402 
#define D_ 3216 
#define E 3031 
#define F 2866 
#define F_ 2703 
#define G 2551 
#define G_ 2410 
#define A 2273 
#define A_ 2146 
#define B 2025 
#define CC 1911 
#define q 400 
#define qdot q * 1.5 
#define e q/2
#define s e/2 
#define t32 s/2 
#define sdot s+t32 
#define h q*2
#define hdot q+e
#define edot e+s
#define num_notes 52 

int i,j;
    
short delay[num_notes] = {t32,t32,t32,t32,t32,t32,t32,t32,t32,t32,s,sdot,t32,t32, 
							  t32,t32,t32,t32,t32,t32,t32,t32,t32,s,sdot,t32,t32,t32, 
							  t32,t32,t32,t32,t32,t32,t32,t32,s,sdot,t32,t32,t32,t32, 
							  t32,t32,t32,t32,t32,t32,t32,t32,s,e}; 

short music_notes[num_notes] = {b,r,B,r,F_,r,D_,r,B,F,r,D,r,C,r,CC,r,G,r,E,r,CC,G,r, 
									E,r,b,r,B,r,F_,r,D_,r,B,F,r,D,r,D,E,D_,r,F,F_,G,r,G,G_,A,r,B}; 

//Interrupt Function

main()
{
    //Setup Timers/Interrupts

    while(1)                     //Run Continuously
    {
        
        for(i=0; i < num_notes; i++) 
		{ 
            j = 0;
			while(j < delay[i]) // for length of time to play note 
			{
            } 
		} 
         
	
    }

}