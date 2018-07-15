#include <msp430.h>
#define MCU_CLOCK 1000000
#define PWM_FREQUENCY 52 // 锟斤拷为44时锟斤拷频锟绞刚猴拷50hz.
#define SERVO_STEPS 180   // 锟斤拷锟矫诧拷锟斤拷
#define SERVO_MIN 650     // 锟斤拷小值0锟斤拷
#define SERVO_MAX 2700    // 锟斤拷锟阶拷锟�180锟斤拷
#define MCLK_C      (1)
#define Delay_ms(n)  __delay_cycles(n*(1000L)*MCLK_C)
unsigned int PWM_P =(MCU_CLOCK / PWM_FREQUENCY);
unsigned char UartGetchar1();
void UartPutchar(unsigned char c);


void reset_SteerEngine(){

    unsigned int servo_stepval, servo_stepnow;
    unsigned int servo_lut[180];
    unsigned int i;

        servo_stepval =((SERVO_MAX - SERVO_MIN)/ SERVO_STEPS );
        servo_stepnow = SERVO_MIN;

    // 锟斤拷值LUT
        for(i =0;i<180; i++)
        {
            servo_stepnow += servo_stepval;
            servo_lut[i]= servo_stepnow;
        }

        TA1CCTL1=OUTMOD_7;
        TA1CTL |= TASSEL_2 + MC_1;
        TA1CCR0 = PWM_P;
        P2SEL |= BIT2;
        P2DIR |= BIT2;
        TA1CCR1 = servo_lut[90];

}
void display_SteerEngine ()
{
    UartPutchar('6');
    unsigned int servo_stepval, servo_stepnow;
    unsigned int servo_lut[180];
    unsigned int i;

    servo_stepval =((SERVO_MAX - SERVO_MIN)/ SERVO_STEPS );
    servo_stepnow = SERVO_MIN;

// 锟斤拷值LUT
    for(i =0;i<180; i++)
    {
        servo_stepnow += servo_stepval;
        servo_lut[i]= servo_stepnow;
    }

    TA1CCTL1=OUTMOD_7;
    TA1CTL |= TASSEL_2 + MC_1;
    TA1CCR0 = PWM_P;
    TA1CCR1 = servo_lut[0];
    P2SEL |= BIT2;
    P2DIR |= BIT2;

//转锟斤拷锟角讹拷锟斤拷锟斤拷
    while(UartGetchar1()=='6'){//!(IFG2&UCA0RXIFG)

// Go to 0锟姐；+duty 3.0%锟斤拷
        TA1CCR1 = servo_lut[5];
        Delay_ms(500);

// Go to 45锟姐；+duty 4.8%锟斤拷
        TA1CCR1 = servo_lut[40];
        Delay_ms(500);

// Go to 90锟斤拷; +duty 7.4%.
        TA1CCR1 = servo_lut[80];
        Delay_ms(500);

// Go to 135锟斤拷; +duty 9.8%.
        TA1CCR1 = servo_lut[120];
        Delay_ms(500);

// Go to 180锟斤拷; +duty 12.3%.
        TA1CCR1 = servo_lut[160];
        Delay_ms(500);

// Go to 0锟姐；+duty 3.0%锟斤拷
        TA1CCR1 = servo_lut[120];
        Delay_ms(500);

        TA1CCR1 = servo_lut[80];
        Delay_ms(500);

        TA1CCR1 = servo_lut[40];
        Delay_ms(500);

        TA1CCR1 = servo_lut[0];
        Delay_ms(500);

    }
    UartPutchar('r');

}



