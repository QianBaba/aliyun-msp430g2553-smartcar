#include <msp430.h>
#define MCLK_C      (1)
#define Delay_ms(n)  __delay_cycles(n*(1000L)*MCLK_C)



void Init_HC05() {

   	P1SEL = BIT1+BIT2;      //P1.1涓篟XD,P1.2涓篢XD
	P1SEL2 = BIT1+BIT2;     //P1.1涓篟XD,P1.2涓篢XD
	UCA0CTL1 |= UCSSEL_2;   //閫夋嫨鏃堕挓BRCLK
	UCA0BR0 = 104;          //1Mhz 9600
	UCA0BR1 = 0;            //1Mhz 9600
	UCA0MCTL = UCBRS2 + UCBRS0;     //娉㈢壒鐜�=BRCLK/(UBR+(M7+...0)/8)
	UCA0CTL1 &=~ UCSWRST;           //鍒濆鍖栭『搴忥細SWRST=1璁剧疆涓插彛 鐒跺悗璁剧疆SWRST=0 鏈�鍚庤缃浉搴斾腑鏂�
	IE2|=UCA0RXIE;                   //浣胯兘鎺ユ敹涓柇,浣胯兘鍙戦�佷腑鏂�
}

void UartPutchar(unsigned char c)
{
    UCA0TXBUF=c;
    while(!(IFG2&UCA0TXIFG)); //(寰呭彂閫佷负绌�)
    IFG2&=~UCA0RXIFG;
}
void UartPutchar1(unsigned char c)
{
    UCA0TXBUF=c;
   //while(!(IFG2&UCA0TXIFG)); //(寰呭彂閫佷负绌�)
    IFG2&=~UCA0RXIFG;
}

void Send_String(unsigned char *String)    //鍙戦�佷竴缁勫瓧绗︿覆
{
    unsigned char *str;
    str=String;
  while(*str!='\0')
   {
      UCA0TXBUF=*str++;
      while(!(IFG2&UCA0TXIFG));//绛夊緟鏁版嵁鍙戦�佸畬姣�
   }
  IFG2&=~UCA0RXIFG;
}

unsigned char UartGetchar()
{
	unsigned char c;
	while(!(IFG2&UCA0RXIFG));       //(绛夊緟鎺ユ敹瀹屾垚)
	c=UCA0RXBUF;
	IFG2 &=~UCA0TXIFG;
	UCA0RXBUF=0;
	P1OUT=0;
	return c;
}
unsigned char UartGetchar1()
{
	unsigned char c;
	//while(!(IFG2&UCA0RXIFG));       //(绛夊緟鎺ユ敹瀹屾垚)
	c=UCA0RXBUF;
	IFG2 &=~UCA0TXIFG;
	UCA0RXBUF=0;
	P1OUT=0;
	return c;
}


//void HC05(){
//    Init_HC05();
//    P1DIR |= BIT0;
//    P1OUT|=1;
//    while(1)
//        {
//            temp_value=UartGetchar();
//
//            if(temp_value=='4')
//            {
//                P1OUT|=0;
//               unsigned char* a="hello";
//               Send_String(a);
//
//            }
//            else{
//                Delay_ms(3000);
//                P1OUT|=1;
//            }
//
//        }
//
//}


