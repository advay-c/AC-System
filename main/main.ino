#include<avr/io.h>  
#include<util/delay.h>  
#include<LCD.h> 
#define checkbit(x,y) ((x) & (y))
#define bitn(p) (0x01 << (p))
#define power 0x01FE48B7
#define volumeinc 0x01FE609F
#define volumedec 0x01FEA05F
LCD lcd;  
long keycode = 0;   
int timervalue;
int bitposition = 0;
int var = 0;
int num, num2, temperature, count;
float c1 = 0.001125308852122;  
float c2 =  0.000234711863267;   
float c3 =  0.000000085663516;   
double logR2, R2, T, Tc; 
int pulse, roomtemp, roomtemp2, press; 
int dummyvar, ACtemperature;  
int main (void)
{
  lcd.init();   
  lcd.cmd(0x0C); 
  lcd.cmd(0x01);  
  lcd.string("Press Power key");
  lcd.line2(0);   
  lcd.string("to turn on AC");    
  temperature = 25;   
  ACtemperature = 25;   
  DDRD = 0xFF;    
  DDRB = 0x00;    
  TIMSK0 = 0x01;                      
  EICRA = 0x20;                       
  EIMSK = 0x04;     
  SREG = 0x80;  
  TCCR0A = 0x00;
  TCCR0B = 0x03;              
  while (1)
  {
    if (press == 1) 
    {
      ADMUX = 0x40 ;                
      ADCSRA = 0xC7    ;                  
      while (checkbit(ADCSRA, bitn(ADSC))); 
      R2 = (10000 / (1023 - ADCW)) * ADCW;    
      logR2 = log(R2);  
      T = (1.0 / (c1 + c2 * logR2 + c3 * logR2 * logR2 * logR2));   
      Tc = T - 273.15;    
      pulse++;  
      if (pulse == 1) 
      {
        roomtemp = Tc;  
      }
      if (pulse == 2)   
      {
        roomtemp2 = Tc;   
        pulse = 0;  
      }
      if (!(roomtemp == roomtemp2) || dummyvar == 0)  
      {
        LCDdisplay();   
        dummyvar = 1;   
      }
      if (Tc < temperature)   
      {
        PORTD = 0x04;   
      }
      else
      {
        PORTD = 0x88;   
      }
    }
    if (press == 2) 
    {
      press = 0;  
      dummyvar = 0;   
      lcd.cmd(0x01);  
      lcd.string("Turning off AC");   
      _delay_ms(1000);    
      lcd.cmd(0x01);    
      lcd.string("Press Power key");    
      lcd.line2(0); 
      lcd.string("to turn on AC");  
    }
  }
}
void compare()
{
  if (keycode == power)   
  {
    press++;    
  }
  if (keycode == volumeinc)   
  {
    ACtemperature ++;   
    if (ACtemperature >= 16 && ACtemperature <= 30) 
    {
      temperature++; 
      LCDdisplay(); 
    }
    if (ACtemperature < 16) 
    {
      ACtemperature = 16;
    }
    if (ACtemperature > 30) 
    {
      ACtemperature = 30; 
    }
  }
  if (keycode == (volumedec)) 
  {
    ACtemperature --; 
    if (ACtemperature >= 16 && ACtemperature <= 30) 
    {
      temperature--;  
      LCDdisplay(); 
    }
    if (ACtemperature < 16) 
    {
      ACtemperature = 16; 
    }
    if (ACtemperature > 30) 
    {
      ACtemperature = 30; 
    }
  }
}
void LCDdisplay()
{
  lcd.cmd(0x01); 
  lcd.string("Set temp:   "); 
  lcd.showvalue(temperature);
  lcd.line2(0); 
  lcd.string("Room temp:  "); 
  lcd.showvalue(Tc);  
}
