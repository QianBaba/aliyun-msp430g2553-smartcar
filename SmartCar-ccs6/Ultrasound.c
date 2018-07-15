
    #include<msp430.h>
    #include <stdlib.h>
    #include <stdio.h>
    #define uint unsigned int
    #define uchar unsigned char

    //定义主时钟频率，供延时使用
    #define MCLK_C      (1)
    #define Delay_us(n)  __delay_cycles(n*MCLK_C)
    #define Delay_ms(n)  __delay_cycles(n*(1000L)*MCLK_C)


    unsigned int  result1_start,result1_end;
    unsigned char index=0;
    unsigned int  temp,flag;
    double   distance;
    void Send_String(unsigned char *String);
    void UartPutchar(unsigned char c);

//    char* toString(int iVal)
//       {
//            /* 优化点:
//            *  1,不通过堆栈的方式,无需进出栈,或者是对字符串进行逆序,直接通过指针运算,内存拷贝方式或者最终结果
//            */
//           char str[1024] = {'\0',};
//           char *pos = NULL;
//           int sign = 0;   //正数 或者是 0
//           int abs = iVal;
//
//           pos = str + 1023; //移动指针,指向堆栈底部
//
//           *pos-- = '\0';  //end
//
//          if(iVal < 0)
//          {
//              sign = 1;
//              abs = -abs;
//          }
//          int dit = 0;
//          while(abs > 0)
//          {
//              dit = abs % 10;
//              abs = abs / 10;
//              *pos-- = (char)('0' + dit);
//          }
//
//          if(sign)
//
//              *pos-- = '-';
//
//          char *ret = (char*)malloc(1024 - (pos - str));
//
//          if(iVal == 0)               //0的一个处理
//              strcpy(ret, "0");
//          else                        //iVal非0的拷贝
//              strcpy(ret, pos+1);
//          return(ret);
//}

    //超声波发送15us的高电平
    void send_15us()
    {

             P2OUT&=~BIT0;
             Delay_us(20);
             P2OUT|=BIT0;
             Delay_us(15);
             P2OUT&=~BIT0;
    }
    void Ultrasound(void)
    {
            WDTCTL=WDTPW+WDTHOLD;
    //设置时钟为1MHZ
            BCSCTL1=CALBC1_1MHZ;
            DCOCTL=CALDCO_1MHZ;
    //设置IO
            P1DIR|=BIT0;
            P1OUT=1;         //LED0灯
            P2DIR &=~BIT3;   //P1.2,为输入引脚  接ECHO
            P2SEL |= BIT3;   // P1.2 = (TA0.CCI1A) = CCIxA.1 --> CCR1，P1.2作为输入，CCI1A，指定输入//数据手册page43
            P2DIR|=BIT0;            //接TRIG,设置为输出方向
            P2OUT= 0;
    //设置定时器
            TA1CTL |=TASSEL_1 + MC_2;
            TA1CCTL0 = CAP + CCIS_1 + CM_3 + CCIE+SCS;   // 捕获模式,捕捉/比较输入选择CCIxA,上升沿和下降沿二者的捕捉,使能捕捉/比较中断,CCI1A->p1.2(使用定时器时钟同步捕捉输入信号)
            TA1CCR0=0;//当一个捕捉被执行时，定时器_A 寄存器，TAR，被复制进 TACCRx 寄存器。
//            TA1CTL&=~CCIFG;
    //开总中断
            _EINT();
        flag=0;
        while(1)
        {

                send_15us();  //发送15us的高电平
                Delay_ms(200);//测量周期应在60ms以上，以避免发射信号对回响信号的影响

        }
        if (flag==0){
            UartPutchar('l');//>=25
        }
        else{
            UartPutchar('s');//<25
        }

    }
//    ==================================TA的中断服务程序=========================================
 //   函数名称： Timer_A ISR (INTERRUPT SERVICE REGISTER)
 //   函数功能： 定时器A中断服务子函数,捕获待测信号上升沿,下降沿
 //   函数参数：CCR0单独的占用了个中断，是TIMER0_A0_VECTOR,其他的合着用TIMER0_A1_VECTOR，所以进入中断后要判断是CCR1，还是CCR2产生的中断，也就是TAOIV或者
 //   TA1IV对应case  :2 和4,另外如果你不访问TAIV这个寄存器，那你产生的一些标志位就要你手动的软件复位了，反之是硬件自己复位。由于捕获是硬件捕获的，测距比较准。
  //  =========================================================================================
#pragma vector=TIMER1_A0_VECTOR
    __interrupt void TAIV_ISR(void)
    {
             TA1CTL |=TASSEL_2 + ID_0 + MC_2+ TAIE+TACLR ;//选择1M－SMCLK时钟，不分频，连续模式，使能定时器_A中断；复位 TAR，时钟分频器，和计数方向

             result1_start=0;
             result1_end=TA1CCR0;
             if(result1_end>result1_start){
                    temp=result1_end-result1_start;
             }
             else{
                    temp=result1_end+(65535-result1_start);
             }
             distance=temp*0.0172;
             Delay_ms(3000);

             if(distance<10){
                 P1OUT=~BIT0;
                 flag=1;
             }else{
                 flag=0;
             }

//             P1OUT=1;
//             Delay_ms(10000);
//             switch(TA0IV)
//                    {
//                     case 2:{                   //ccr1中断向量
//                       P1OUT=0;
//                         if (TA1CCTL0&CCI)    //上升沿触发  选择的输入信号可以通过CCI位读取。
//                                    {
//                                         result1_start=CCR0;//记录初始值
//                                         index=0;  //从0开始计数
//                                         break;
//                                    }
//                             else
//                               {
//                                        result1_end=CCR0;          //记录结束值
//                                        if(result1_end>result1_start)//结果比开始数值小，表示溢出了一次或者几次，但是一般从0开始计数的话是不溢出的，这超声波实际测不了那么远，最多有个4米，5米的样子已经很好了
//
//                                           temp=result1_end-result1_start;
//                                        else
//                                           temp=result1_end+index*65535-result1_start;
//    //距离=（时间*速度）/2
//    //距离=（（计数次数/频率）*340/2） m/s=(temp/1000000)*170 00  cm/s=temp*0.0172 cm/s
//                                        distance=temp*0.0172;
//                                        if(distance<10)
//                                        {
//
////                                            P1OUT|=~BIT0;
//                                            Delay_ms(3000);
//                                        }
//                                        if(distance>=10)
//                                        {
//                                         //P1OUT&=~BIT0;
//                                            //P1OUT=0;
//
//
//                                        }
//                                        index=0;         //溢出次数清零
//                                        break;
//                               }}
//                     case 4: break;
//                     case 10:P1OUT=0;index++;break;  //定时器溢出中断向量，其实就2,4,10号向量有用.
//                     default :break;
//                    }



       }






