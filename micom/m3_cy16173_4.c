#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (Power-up Timer is disabled)
#pragma config CP = OFF         // Code Protection bit (Code protection disabled)

#define	_XTAL_FREQ	20000000	/*マイコンの定義*/
int	main(void)
{
TRISA=0x10;
TRISB=0x00;
PORTA=0x00;
PORTB=0x00;			/*入力として使うときは１、出力として使うときは０*/

		
	RB0=1;
	__delay_ms(500);	/*０を光らせる*/
	
	while(1)
	{	
		PORTB=PORTB<<1;				/*＜＜は左、＞＞は右に後の数字分だけずらす*/
		__delay_ms(500);
	
		
			while(RA4==0)
			{
				PORTB=PORTB>>1;		/*＜＜は左、＞＞は右に後の数字分だけずらす*/
				__delay_ms(500);
			
					if(RA4==1)
					{
						break;
					}				/*ループから抜け出す*/
					
					if(RB0==1)
					{
						PORTB=0x80;
						__delay_ms(500);
					}						/*いなくならないように７へ移動*/
			
					if(RA4==1)
					{
						break;
					}				/*PORTB=PORTB<<1に戻らないように*/
			
			}

			if(RB7==1)
			{
				PORTB=0x01;
				__delay_ms(500);
			}						/*RB0が光ったときのためここに持ってきた*/
		
			while(RA4==0)
			{
				if(RB0==1)
				{
					PORTB=0x80;
					__delay_ms(500);
				}						/*いなくならないように７へ移動*/
			
				if(RA4==1)
				{
					break;
				}					/*ループから抜け出す*/
				
				PORTB=PORTB>>1;
				__delay_ms(500);
			
					if(RA4==1)
					{
						break;
					}				/*ループから抜け出す*/
					
					
			
			}		
			
	}	
	
	return	0;
}

