#include <16F877A.h> 
#device ADC=10 
#FUSES NOWDT                    //No Watch Dog Timer 
#FUSES NOBROWNOUT               //No brownout reset 
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O 

 

#use delay(crystal=20000000) 

 

#include <lcd.c> 

 

#DEFINE IN1 PIN_C3 
#DEFINE IN2 PIN_C4 

 

signed long pwmOut; 
unsigned long int revAngle = 0; 
float velo = 0.0f; 
float t1 = 0; 
float t2 = 0; 
float deltaT = 0; 
unsigned long int i = 0; 

 

#int_ext 
void external_interrupt() 
{ 
   revAngle++; 
 t2 = i*0.512; // Caution here [1] 
   deltaT = t2-t1; 
   velo = 166.667/deltaT;   // Caution here [2] 
   t1 = t2; 
} 

 

#int_timer0 
void tmr_int() 
{ 
   set_timer0(246); 
   i++;      
} 

 

void main() 
{ 
   lcd_init(); 
   lcd_cursor_on(TRUE); 
   port_b_pullups(TRUE); 
   enable_interrupts(GLOBAL); 
   clear_interrupt(int_ext); 
   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_256);  
   set_timer0(246); 
   enable_interrupts(int_timer0); 
   enable_interrupts(int_ext); 
   setup_adc_ports(AN0_AN1_AN3); //A0 A1 A3 are configured for analog input pin 
   setup_adc(ADC_CLOCK_DIV_32); //enable ADC and set clock for ADC 
   unsigned int16 result_1; //variable for A0 value 
   set_tris_c(0x00); //set all portb pins as output 
   setup_ccp1(CCP_PWM); //4kHz PWM signal output at CCP1 pin 17 
    
   setup_timer_2(T2_DIV_BY_16, 255, 1); 
   set_pwm2_duty(0); 
   output_low(IN1); 
   output_high(IN2); 
    
   while(TRUE) 
   { 
 set_adc_channel(0); // next analog reading will be from channel 0 
 delay_us(10); //allow time after channel selection and reading 
 result_1 = read_adc(); //start and read A/D 
 delay_us(10); //allow time after channel selection and reading 
 pwmOut = result_1*0.249; // mapping analog input to pwm output 
 set_pwm1_duty(pwmOut); //set pulse-width during which signal is high 
      printf(lcd_putc, "\fAngle:%lu\n",revAngle); 
      printf(lcd_putc, "dt:%f,w:%f\n",deltaT,velo); 
      delay_ms(50); 
    } 
} 
