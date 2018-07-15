#include <msp430.h>
char  move_status[3]={0x80,0x0,0x40};
//unsigned int flag=0;
volatile unsigned char value='0';
void setup0()  //TA0.1杈撳嚭PWM
{
    P1DIR|=BIT3+BIT4;
    TACTL|= TASSEL_2+MC_1;//ACLK,澧炶鏁�
    CCTL1=OUTMOD_7;//杈撳嚭妯″紡涓哄浣�/缃綅
    CCR0=32;
}
void setup1(){
    TA1CCTL1 = OUTMOD_7;
    TA1CCR0 = 32;
}
void setup2()
{
    TA1CCTL2=OUTMOD_7;
    TA1CCR0=32;
}
void Set_PWM1_Duty(int duty)//鐠佸墽鐤哖WM閸楃姷鈹栧В鏂呯妳
{
    TA1CCR1 = duty;
}
void Set_PWM2_Duty(int duty)
{
    TA1CCR2 = duty;
}
//閸撳秷绻�
void advance_fast(){
    //瀹革箑褰搁悽鍨簚閸у洤澧犳潻
    P1OUT|= move_status[0];
    Set_PWM1_Duty(15);
    Set_PWM2_Duty(15);
    P1OUT= move_status[0];

}
void advance(){
    //瀹革箑褰搁悽鍨簚閸у洤澧犳潻
    P1OUT|= move_status[0];
    Set_PWM1_Duty(10);
    Set_PWM2_Duty(10);
    P1OUT= move_status[0];

}
void advance_slow(){
    //瀹革箑褰搁悽鍨簚閸у洤澧犳潻
    P1OUT=move_status[0] ;
    Set_PWM1_Duty(8);
    Set_PWM2_Duty(8);

}
//瀹革箒娴�
void turnleft(){
    //瀹革妇鏁搁張楦挎祮闁喐鍙冮敍灞藉礁閻㈠灚婧�鏉烆剟 鐔锋彥
        P1OUT=move_status[0] ;
        Set_PWM1_Duty(5);
        Set_PWM2_Duty(10);
}
//閸欏疇娴�
void turnright(){
    //瀹革妇鏁搁張楦挎祮闁喎鎻╅敍灞藉礁閻㈠灚婧�鏉烆剟 鐔稿弮
        P1OUT=move_status[0] ;
        Set_PWM1_Duty(10);
        Set_PWM2_Duty(5);
}
void xunjileft(){
    //瀹革妇鏁搁張楦挎祮闁喐鍙冮敍灞藉礁閻㈠灚婧�鏉烆剟 鐔锋彥
        P1OUT=move_status[0] ;
        Set_PWM1_Duty(0);
        Set_PWM2_Duty(10);
}
//閸欏疇娴�
void xunjiright(){
    //瀹革妇鏁搁張楦挎祮闁喎鎻╅敍灞藉礁閻㈠灚婧�鏉烆剟 鐔稿弮
        P1OUT=move_status[0] ;
        Set_PWM1_Duty(10);
        Set_PWM2_Duty(0);
}
//閸掔婧�
void stop(){
    //瀹革箑褰搁悽鍨簚閸у洤浠犲
    P1OUT=move_status[1] ;
    Set_PWM1_Duty(0);
    Set_PWM2_Duty(0);
}
void get_back(){
    P1OUT=move_status[2] ;
    Set_PWM1_Duty(8);
    Set_PWM2_Duty(8);
}

void Advance(int state){

    P1DIR|=BIT6+BIT7;
    TA1CTL = MC_1 + TASSEL_2;
    setup1();
    setup2();
    P2SEL|=BIT1+BIT5;
    P2DIR|=BIT1+BIT5;

    switch(state){
        case 0:
            stop();
            break;
        case 1:
            advance_fast();
            break;
        case 2:
            turnleft();
            break;
        case 3:
            turnright();
            break;
        case 4:
            get_back();
            break;
        case 5:
            advance_slow();
            break;
        case 6:
			advance();
			break;
        case 7:
			xunjileft();
			break;
        case 8:
			xunjiright();
			break;
        default:
            advance();
            break;
        }
//    while((IFG2&UCA0RXIFG)){
//        value=UartGetchar();
//        while(flag==1){
//        if(value=='6'){
//            display_SteerEngine();
//            flag=1;
//
//        }else if(value=='7'){
//            display_ColorLed();
//            flag=1;
//        }else{
//            flag=0;
//        }
//       }
//    }

}
