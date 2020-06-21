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

		
	RB0=1;
	__delay_ms(500);	/*�O�����点��*/
	
	while(1)
	{	
		PORTB=PORTB<<1;				/*�����͍��A�����͉E�Ɍ�̐������������炷*/
		__delay_ms(500);
	
		
			while(RA4==0)
			{
				PORTB=PORTB>>1;		/*�����͍��A�����͉E�Ɍ�̐������������炷*/
				__delay_ms(500);
			
					if(RA4==1)
					{
						break;
					}				/*���[�v���甲���o��*/
					
					if(RB0==1)
					{
						PORTB=0x80;
						__delay_ms(500);
					}						/*���Ȃ��Ȃ�Ȃ��悤�ɂV�ֈړ�*/
			
					if(RA4==1)
					{
						break;
					}				/*PORTB=PORTB<<1�ɖ߂�Ȃ��悤��*/
			
			}

			if(RB7==1)
			{
				PORTB=0x01;
				__delay_ms(500);
			}						/*RB0���������Ƃ��̂��߂����Ɏ����Ă���*/
		
			while(RA4==0)
			{
				if(RB0==1)
				{
					PORTB=0x80;
					__delay_ms(500);
				}						/*���Ȃ��Ȃ�Ȃ��悤�ɂV�ֈړ�*/
			
				if(RA4==1)
				{
					break;
				}					/*���[�v���甲���o��*/
				
				PORTB=PORTB>>1;
				__delay_ms(500);
			
					if(RA4==1)
					{
						break;
					}				/*���[�v���甲���o��*/
					
					
			
			}		
			
	}	
	
	return	0;
}

