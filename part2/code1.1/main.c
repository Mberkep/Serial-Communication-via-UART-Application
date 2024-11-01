#include <16F877A.h> 
#FUSES XT, NOWDT, NOPROTECT, NOBROWNOUT, NOLVP, NOPUT, NODEBUG, NOCPD 
#use delay(crystal=4000000) 
#use rs232 (baud=9600,xmit=PIN_C6, rcv=PIN_C7, parity=N, stop=1) // configuretion for serial communication 

 

void main() 
{ 
   while(1) 
   { 
      printf("h"); 
      delay_ms(500); 
      printf("e"); 
      delay_ms(500); 
      printf("l"); 
      delay_ms(500); 
      printf("l"); 
      delay_ms(500);
      printf("o"); 
      delay_ms(500); 
      printf(" "); 
      delay_ms(500); 
      printf("W"); 
      delay_ms(500); 
      printf("o"); 
      delay_ms(500);
      printf("r"); 
      delay_ms(500); 
      printf("l"); 
      delay_ms(500); 
      printf("d"); 
      delay_ms(500);
      printf("*"); 
      delay_ms(5000); 
   } 
}
