#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (Power-up Timer is disabled)
#pragma config CP = OFF         // Code Protection bit (Code protection disabled)

#define	_XTAL_FREQ	20000000	/*�}�C�R���̒�`*/
int	main(void)
{
TRISA=0x10;
TRISB=0x00;
PORTA=0x00;
PORTB=0x00;			/*���͂Ƃ��Ďg���Ƃ��͂P�A�o�͂Ƃ��Ďg���Ƃ��͂O*/

		
			while(1)
			{
				
				
				
				
				if(RA4==1)				/*�X�C�b�`�͂Ȃ�*/
				{	
					
					
						PORTB=0xff;
						__delay_ms(2000);
						
				
						PORTB=0x00;
						__delay_ms(2000);
						
				}
				
				
				
				
				if(RA4==0)						/*�X�C�b�`������*/	
				{
						
						PORTB=0xCA;					/*16�i��*/
						__delay_ms(2000);
						
						
						PORTB=0x35;					/*16�i��*/
						__delay_ms(2000);
						
						
						
				}	
			}	
	
	
			
		

	return	0;
}

