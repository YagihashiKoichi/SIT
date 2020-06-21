#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (Power-up Timer is disabled)
#pragma config CP = OFF         // Code Protection bit (Code protection disabled)

#define	_XTAL_FREQ	20000000	/*クロック周波数200MHzにする*/
int	main(void)
{
	TRISA=0x00;					/*RA0~RA4を出力にする*/
	TRISB=0x00;					/*RB0~RB7を出力にする*/
	PORTA=0x00;
	PORTB=0x00;
	while(1)
	{
		RB0=1;
		RB1=1;
		RB2=1;
		RB3=1;
		RB4=1;
		RB5=1;
		RB6=1;
		RB7=1;					/*左辺が場所を表し、右辺が１は点灯、２は消灯、_は2つ*/
		__delay_ms(2000);		/*2000ms待つ*/
	
		
		RB0=0;
		RB1=0;
		RB2=0;
		RB3=0;
		RB4=0;
		RB5=0;
		RB6=0;
		RB7=0;
		__delay_ms(1000);
	}	
	return	0;
}
