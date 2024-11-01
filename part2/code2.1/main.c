#include <16F877A.h>
#include <stdlib.h>
#FUSES XT, NOWDT, NOPROTECT, NOBROWNOUT, NOLVP, NOPUT, NODEBUG, NOCPD
#use delay(crystal=4000000)
#include <lcd.c>
#use rs232 (baud=9600,xmit=PIN_C6, rcv=PIN_C7, parity=N, stop=1) // configuration for serial communication

#define DEBOUNCE_DELAY 20 // Debounce delay in milliseconds

int counter = 0; // Counter to be used
char strInput[11]; // String array for input characters
int inputString; // inputString value to be used

// Function to perform debounce
int debounce(int pin) {
   int state = input(pin); // Get initial pin state
   delay_ms(DEBOUNCE_DELAY); // Delay for debounce
   if (state == input(pin)) // Check if pin state is stable
      return state; // Return stable state
   else
      return -1; // Return -1 for unstable state
}

void main()
{
   lcd_init();
   delay_ms(10);

   while (1)
   {
      if (kbhit()) // If data has been received
      {
         char i = getc(); // UART read
         int debounceState = debounce(PIN_C7); // Perform debounce on input pin

         if (debounceState == 1) // Check if debounce state is HIGH (stable)
         {
            if (i == '*') // Special character for serial input. If the received character is '*', then this condition is called
            {
               counter = 0; // Counter to be zero again
               printf("Incoming Data: %s", strInput); // Print string array to the screen
               printf(" Number: %s ", strInput); // Print inputString value to the screen
               lcd_putc('\n'); // Print a newline character on the LCD
               printf(LCD_PUTC, "%s", strInput); // Print inputString value to the LCD
               memset(strInput, 0, sizeof(strInput)); // Clear the string array
            }
            else
            {
               strInput[counter] = i; // Attend input character to the string array
               counter++; // Increase the counter by 1
            }
         }
      }
   }
}

