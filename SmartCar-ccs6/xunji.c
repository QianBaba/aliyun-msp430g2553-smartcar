#include"msp430.h"
#define uchar unsigned char
#define uint unsigned int
#define MCLK_C      (1)
#define Delay_ms(n)  __delay_cycles(n*(1000L)*MCLK_C)
#define X1 (P2IN&BIT0)
#define X2 (P2IN&BIT2)
#define X3 (P2IN&BIT3)
#define X4 (P2IN&BIT4)
void delay(int times);
void Advance();
void UartPutchar(unsigned char c);
void UartPutchar1(unsigned char c);
unsigned char UartGetchar1();
void xunji()
{
	  UartPutchar('8');
      while(!(IFG2&UCA0RXIFG)){//UartGetchar1()=='8'

		  //Delay_ms(50);
    	  if( (X2==0x00) && (X3==0x00))
		  {
			  Advance(5) ;
			  //UartPutchar('l');//out2=1;out3=1
		  }
		  else if((X2!=0x00)&&(X3==0x00)&&(X4==0x00))
		  {
			  Advance(8);
			  //UartPutchar('m');//out2=0;out3=1;out4=1
			  Delay_ms(500);
		  }
		  else if((X1==0x00)&&(X3!=0x00))
		   {
			   Advance(7);
			  // UartPutchar('n');//out1=1;out3=0
			   Delay_ms(500);
		   }
		  else{
			  Advance(6);
			 // UartPutchar('z');//ȫ0
		  }
		  //delay(500);
		}

      UartPutchar('r');

}




