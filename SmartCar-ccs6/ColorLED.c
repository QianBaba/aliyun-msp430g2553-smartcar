#include <msp430.h>
#define MCLK_C      (1)
#define Delay_us(n)  __delay_cycles(n*MCLK_C)
#define Delay_ms(n)  __delay_cycles(n*(1000L)*MCLK_C)
char  play_status[8]={0x20,0x10,0x08,0x30,0x28,0x18,0x38,0x00};
char led_status[7]={'1','2','3','4','5','6','7'};
int n;
void delay(int times);
void UartPutchar(unsigned char c);
unsigned char UartGetchar1();
void Send_String(unsigned char *String);
void UartPutchar1(unsigned char c);

void display_ColorLed()
{
    UartPutchar('7');
	P1DIR |=(BIT3+BIT4+BIT5);

	while(UartGetchar1()=='7')
	{
		 for (n=0;n<7;n++)
		{
		   P1OUT=play_status[n];
		   if(UartGetchar1()!='7')break;
		   UartPutchar(led_status[n]);
		   Delay_ms(1500);
		}
	}
    P1OUT=play_status[7];
    UartPutchar('r');

}

void delay(int times){
	while(times--);
}
