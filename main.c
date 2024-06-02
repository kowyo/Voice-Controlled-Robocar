#include <msp430.h>

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978


int melody[] = {
    NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5,
    NOTE_C5, NOTE_C5, NOTE_C5, NOTE_C5,
    NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
    NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5,
    NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5,
    NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5,
    NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_F4,
    NOTE_G4, 0, NOTE_G4, NOTE_D5,
    NOTE_C5, 0, NOTE_AS4, 0,
    NOTE_A4, 0, NOTE_A4, NOTE_A4,
    NOTE_C5, 0, NOTE_AS4, NOTE_A4,
    NOTE_G4,0, NOTE_G4, NOTE_AS5,
    NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
    NOTE_G4,0, NOTE_G4, NOTE_AS5,
    NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
    NOTE_G4, 0, NOTE_G4, NOTE_D5,
    NOTE_C5, 0, NOTE_AS4, 0,
    NOTE_A4, 0, NOTE_A4, NOTE_A4,
    NOTE_C5, 0, NOTE_AS4, NOTE_A4,
    NOTE_G4,0, NOTE_G4, NOTE_AS5,
    NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
    NOTE_G4,0, NOTE_G4, NOTE_AS5,
    NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5
};

int noteDurations[] = {
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
    4,4,4,4,
};

unsigned int thisnote = 0;
double time = 0;
int flag = 1;
int first_flag = 1;
//void Play_songs();

/**
 * main.c
 */
int i = 0;
int flag_receive = 0;
void ioinit(void)
{
    P8DIR |= BIT1;
    P8OUT &= ~BIT1;

    P3DIR |= BIT7;
    P3OUT &= ~BIT7;

    P7DIR |= BIT4;
    P7OUT &= ~BIT4;

    P6DIR |= BIT3;
    P6OUT &= ~BIT3;

    P6DIR |= BIT4;
    P6OUT &= ~BIT4;

    P3DIR |= BIT5;
    P3OUT &= ~BIT5;

    P6DIR &= ~BIT2;
    P6SEL |= BIT2;

    P6DIR &= ~BIT1;
    P6SEL |= BIT1;

    P8DIR |= BIT1;
    P3DIR |= BIT6;

    P2DIR |= BIT7;
    P2OUT &= ~BIT7;
    P1DIR |= BIT6;
    P1OUT &= ~BIT6;

    P1REN |= BIT2;
    P1OUT |= BIT2;

    P1REN |= BIT3;
    P1OUT |= BIT3;
}

void AD_init(void)
{
    ADC12CTL0 |= ADC12MSC;
    ADC12CTL0 |= ADC12ON;
    ADC12CTL1 |= ADC12CONSEQ_3;
    ADC12CTL1 |= ADC12SHP;
    ADC12CTL1 |= ADC12CSTARTADD_0;
    ADC12MCTL0 |= ADC12INCH_1;
    ADC12MCTL1 |= ADC12INCH_2 + ADC12EOS;
    ADC12CTL0 |= ADC12ENC;
}


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    TA0CTL=MC_1 + TASSEL_2 + TACLR;//TIMA:100Mhz

    ioinit();
    AD_init();

    ADC12CTL0 |= ADC12SC;
    ADC12CTL1 |= ADC12SC;
    volatile unsigned int value1 = 0;
    volatile unsigned int value2 = 0;
    while(1)
    {
        value1 = ADC12MEM0;
        value2 = ADC12MEM1;

        if(value2 > 3000 && flag && !first_flag)
        {
            flag = 0;
            flag_receive = 1 ;
            P2OUT |= BIT7;
            P1OUT |= BIT6;
            while(1)
            {
                TA0CTL |= MC_1 + TASSEL_2 + TACLR;
                TA0CCTL0 = CCIE;
                if(melody[thisnote]==0){}
                else
                {
                    TA0CCR0  = 1000000/melody[thisnote];
                    __enable_interrupt();
                }
                thisnote++;

                if(noteDurations[thisnote]==4)
                {
                    time = time + 0.25;
                    __delay_cycles(250000);

                }
                else if(noteDurations[thisnote]==8)
                {
                    time = time + 0.125;
                    __delay_cycles(125000);
                }

                if( time > 5)
                {
                    thisnote = 0;
                    time = 0;
                    flag = 1;
                    P2OUT &= ~BIT7;
                    P1OUT &= ~BIT6;
                    __disable_interrupt();
                    __delay_cycles(2000000);
                    break;
                }
            }
        }
        else{
            first_flag = 0;
        }


    }
    return 0;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    P3OUT ^= BIT6;
}
