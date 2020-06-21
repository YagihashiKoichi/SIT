#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (Power-up Timer is disabled)
#pragma config CP = OFF         // Code Protection bit (Code protection disabled)

#define _XTAL_FREQ 20000000   /*�N���b�N���g����200MHz�ɂ���*/

void interrupt warikomi (void);

int count=0;  /*����̉����o�����߂̕ϐ�*/

int oto; /*�o�����������w�肷�邽�߂̕ϐ�*/


int main(void)
{
	TRISA=0x00;   /*RA0~RA4���o�͂Ƃ��Ďg��*/
	TRISB=0x00;   /*RB0~RB7���o�͂Ƃ��Ďg��*/
	PORTA=0x00;   
	PORTB=0x00;
	
	T0CS=0;     /*�^�C�}���N���b�N�œ�����*/
	TMR0=0x00;  /*�^�C�}�̌��ݒl��0�ɂ���*/
	T0IF=0;     /*�^�C�}�I�[�o�[�t���[���荞�݂����������1�ɂȂ�*/
	T0IE=1;     /*�^�C�}�I�[�o�[�t���[���荞�݂�������*/
	GIE=1;      /*���荞�݂�������*/
	  
	
	
	while(1)
	{
			oto=26;    /*̧��̎��g���ɂ���*/
			__delay_ms(900); /*̧��̉���0.9�b����*/
	
			
			
			oto=31;    /*����̎��g���ɂ���*/
			__delay_ms(900); /*����̉���0.9�b����*/
		
		
		
			oto=26;    /*̧��̎��g���ɂ���*/
			__delay_ms(900); /*̧��̉���0.9�b����*/
		
		
		
			oto=20;    /*�V�̎��g���ɂ���*/
			__delay_ms(2000); /*�V�̉���2.0�b����*/
		
		
			TRISA=0x1F;  /*�����I�ɏo�͂�����*/
			__delay_ms(3000);  /*������3�b���*/
			
			TRISA=0x00;  /*�o�͂ɖ߂�*/
			
			
		
		
	}
	
	return 0;
	
}

void interrupt warikomi(void)
{
	if(T0IF!=0 && T0IE!=0)  /*�^�C�}�I�[�o�[�t���[���荞�݂�������Ă��āA����������*/
	{
		count++;  /*�����������߂Ɋ��荞�݂��J�E���g����*/
		
		if(count>=oto)  /*����̎��g��������^�C�~���O��*/
		{
			RA2=1-RA2;  /*High��low�����ւ���*/
			
			count=0;    /*�J�E���g������*/
			
			
		}
		
		T0IF=0;  /*0�ɖ߂�*/
	}
	
	return;
}
