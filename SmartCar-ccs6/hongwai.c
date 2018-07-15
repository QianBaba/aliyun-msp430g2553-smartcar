#include <msp430.h>
#define   uchar     unsigned char

#define MCLK_C      (1)
#define Delay_us(n)  __delay_cycles(n*MCLK_C)
#define Delay_ms(n)  __delay_cycles(n*(1000L)*MCLK_C)

//#define X6 (P1IN&BIT0)
#define X7 (P1IN&BIT5)    //璁剧疆P2涓鸿緭鍏ユā寮忥紝璇诲彇鏉ヨ嚜绾㈠閬块殰妯″潡鐨勪俊鎭�
void Advance();
void UartPutchar(unsigned char c);
unsigned char UartGetchar1();
void hongwai( void )
{
          P1SEL|=BIT0;
          P1DIR &=~BIT0;
          P1REN|=BIT0;
          UartPutchar('9');
    while(!(IFG2&UCA0RXIFG))
    {
        if(X7==0){
            Advance(4);
            Delay_ms(1000);
            Advance(2);
            Delay_ms(1500);
            Advance(3);
            Delay_ms(1500);
            Advance(1);
        }else{
            Advance(1);
        }
    }
    UartPutchar('r');
}
