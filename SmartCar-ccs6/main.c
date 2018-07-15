#include <msp430.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

volatile unsigned char temp_value='0';
volatile unsigned char temp_num='0';
void Advance();
void display_ColorLed();
void reset_SteerEngine();
void display_SteerEngine();
void Ultrasound();
void hongwai();
void xunji();
void Init_HC05();
void UartPutchar(unsigned char c);
void Send_String(unsigned char *String);
unsigned char UartGetchar();
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watch dog
	Init_HC05();
	while(1)
	{
	    temp_value=UartGetchar();
	    switch(temp_value){
	        case '1': //姝ｅ父鍓嶈繘
	            Advance(1);
	            UartPutchar(temp_value);
	            break;
	        case '0'://灏忚溅鍋滄
	            Advance(0);
	            UartPutchar(temp_value);
	            break;
	        case '2'://灏忚溅宸﹁浆
	            Advance(2);
	            UartPutchar(temp_value);
	            break;
	        case '3'://灏忚溅鍙宠浆
	            Advance(3);
	            UartPutchar(temp_value);
	            break;
	        case '4'://灏忚溅鍚庨��
	            Advance(4);
	            UartPutchar(temp_value);
	            break;
	        case '5'://鑸垫満澶嶄綅
	            reset_SteerEngine();
	            UartPutchar(temp_value);
	            break;
	        case '6'://鑸垫満鑷姩鏃嬭浆
	            display_SteerEngine();
	             break;
	        case '7'://涓冨僵鎺㈢収杞︾伅
	            display_ColorLed();
	            break;
	        case '8'://瀵昏抗
	            xunji();
	            UartPutchar(temp_value);
	            break;
	        case '9'://閬块殰
	            hongwai();
                UartPutchar(temp_value);
                break;
	        case 'f':
	        	Advance(6);
	        	UartPutchar(temp_value);
	        	break;
//	        case 'a'://瓒呭０娉㈡祴璺�
//	            Ultrasound();
//	        default:
//	        break;
	    }

	}
	return 0;
}
