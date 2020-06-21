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

		
			while(1)
			{
				
				
				
				
				if(RA4==1)				/*スイッチはなす*/
				{	
					
					
						PORTB=0xff;
						__delay_ms(2000);
						
				
						PORTB=0x00;
						__delay_ms(2000);
						
				}
				
				
				
				
				if(RA4==0)						/*スイッチを押す*/	
				{
						
						PORTB=0xCA;					/*16進数*/
						__delay_ms(2000);
						
						
						PORTB=0x35;					/*16進数*/
						__delay_ms(2000);
						
						
						
				}	
			}	
	
	
			
		

	return	0;
}

