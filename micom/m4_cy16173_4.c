/*My Soul,Your Bbats(�`������)�A���񒮂��Ă��������B*/



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

int oto=13;  /*�o�����������w�肷�邽�߂̕ϐ��A̧#(��)���o��*/
int	time=0;  /*�����o�����߂̎��Ԃ��w�肷��*/

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
	  
	int irekae=0;  /*���������Ă��鉹���ʂ��邽�߂̕ϐ�*/
	
	while(1)
	{
		if(time>=306 && irekae==0)  /*̧#(��)�̉���0.2�b�����ꂽ��*/
		{
			oto=15;    /*�~(��)�̎��g���ɂ���*/
			irekae=1;  /*�~(��)�̉��ł��邱�Ƃ�m�点��*/
			time=0;    /*time��0�ɂ��Đ�������*/
		}
		
		if(time>=546 && irekae==1)  /*�~(��)�̉���0.4�b�����ꂽ��*/
		{
			oto=17;    /*��(��)�̎��g���ɂ���*/
			irekae=2;  /*��(��)�̉��ł��邱�Ƃ�m�点��*/	
			time=0;    /*time��0�ɂ��Đ�������*/
		}
		
		if(time>=486 && irekae==2)  /*��(��)�̉���0.4�b�����ꂽ��*/
		{
			oto=20;    /*�V�̎��g���ɂ���*/
			irekae=3;  /*�V�̉��ł��邱�Ƃ�m�点��*/	
			time=0;    /*time��0�ɂ��Đ�������*/
		}
		
		if(time>=409 && irekae==3)  /*�V�̉���0.4�b�����ꂽ��*/
		{
			oto=22;    /*���̎��g���ɂ���*/
			irekae=4;  /*���̉��ł��邱�Ƃ�m�点��*/	
			time=0;    /*time��0�ɂ��Đ�������*/
		}
		
		
		
		
		if(time>=1639 && irekae==4)  /*���̉���1.9�b�����ꂽ��*/
		{
			oto=13;    /*̧#(��)�̎��g���ɂ���*/
			irekae=5;  /*̧#(��)�̉��ł��邱�Ƃ�m�点��*/	
			time=0;    /*time��0�ɂ��Đ�������*/
		}
		
		
		if(time>=306 && irekae==5)  /*̧#(��)�̉���0.2�b�����ꂽ��*/
		{
			oto=15;    /*�~(��)�̎��g���ɂ���*/
			irekae=6;  /*�~(��)�̉��ł��邱�Ƃ�m�点��*/
			time=0;    /*time��0�ɂ��Đ�������*/
		}
		
		if(time>=546 && irekae==6)  /*�~(��)�̉���0.4�b�����ꂽ��*/
		{
			oto=17;    /*��(��)�̎��g���ɂ���*/
			irekae=7;  /*��(��)�̉��ł��邱�Ƃ�m�点��*/	
			time=0;    /*time��0�ɂ��Đ�������*/
		}
		
		if(time>=486 && irekae==7)  /*��(��)�̉���0.4�b�����ꂽ��*/
		{
			oto=20;    /*�V�̎��g���ɂ���*/
			irekae=8;  /*�V�̉��ł��邱�Ƃ�m�点��*/	
			time=0;    /*time��0�ɂ��Đ�������*/
		}
		
		if(time>=409 && irekae==8)  /*�V�̉���0.4�b�����ꂽ��*/
		{
			oto=22;    /*���̎��g���ɂ���*/
			irekae=9;  /*���̉��ł��邱�Ƃ�m�点��*/	
			time=0;    /*time��0�ɂ��Đ�������*/
		}
		
		
		
		
		if(time>=1639 && irekae==9)  /*���̉���1.9�b�����ꂽ��*/
		{
			oto=13;    /*̧#(��)�̎��g���ɂ���*/
			irekae=10;  /*̧#(��)�̉��ł��邱�Ƃ�m�点��*/	
			time=0;    /*time��0�ɂ��Đ�������*/
		}
		
		
		if(time>=306 && irekae==10)  /*̧#(��)�̉���0.2�b�����ꂽ��*/
		{
			oto=15;    /*�~(��)�̎��g���ɂ���*/
			irekae=11;  /*�~(��)�̉��ł��邱�Ƃ�m�点��*/	
			time=0;    /*time��0�ɂ��Đ�������*/
		}
		
		
		
		if(time>=546 && irekae==11)  /*�~(��)�̉���0.4�b�����ꂽ��*/
		{
			oto=17;    /*��(��)�̎��g���ɂ���*/
			irekae=12;  /*��(��)�̉��ł��邱�Ƃ�m�点��*/	
			time=0;    /*time��0�ɂ��Đ�������*/
		}
		
		
		if(time>=486 && irekae==12)  /*��(��)�̉���0.4�b�����ꂽ��*/
		{
			oto=13;    /*̧#(��)�̎��g���ɂ���*/
			irekae=13;  /*̧#(��)�̉��ł��邱�Ƃ�m�点��*/	
			time=0;    /*time��0�ɂ��Đ�������*/
		}
		
		if(time>=612 && irekae==13)  /*̧#(��)�̉���0.4�b�����ꂽ��*/
		{
			oto=11;    /*��(��)�̎��g���ɂ���*/
			irekae=14;  /*��(��)�̉��ł��邱�Ƃ�m�点��*/	
			time=0;    /*time��0�ɂ��Đ�������*/
		}
		
		if(time>=728 && irekae==14)  /*��(��)�̉���0.4�b�����ꂽ��*/
		{
			oto=5;    /*�V(�X�ɍ�)�̎��g���ɂ���*/
			irekae=15;  /*�V(�X�ɍ�)�̉��ł��邱�Ƃ�m�点��*/	
			time=0;    /*time��0�ɂ��Đ�������*/
		}
		
		
		
		
		if(time>=4087 && irekae==15)  /*�V(�X�ɍ�)�̉���1.0�b�����ꂽ��*/
		{
			TRISA=0x1F;  /*�����I�ɏo�͂�����*/
			__delay_ms(414);  /*������0.414�b���*/
			
			TRISA=0x00;  /*�o�͂ɖ߂�*/
			irekae=16;  
			time=0;
			oto=13;  /*̧#(��)�̉��ɂ���*/
			count=0;
		}
		
		
		if(time>=306 && irekae==16)  /*̧#(��)�̉���0.2�b�����ꂽ��*/
		{
			oto=15;    /*�~(��)�̎��g���ɂ���*/
			irekae=17;  /*�~(��)�̉��ł��邱�Ƃ�m�点��*/	
			time=0;    /*time��0�ɂ��Đ�������*/
		}
		
		
		if(time>=546 && irekae==17)  /*�~(��)�̉���0.4�b�����ꂽ��*/
		{
			oto=17;    /*��(��)�̎��g���ɂ���*/
			irekae=18;  /*��(��)�̉��ł��邱�Ƃ�m�点��*/	
			time=0;    /*time��0�ɂ��Đ�������*/
		}
		
		
		if(time>=486 && irekae==18)  /*��(��)�̉���0.4�b�����ꂽ��*/
		{
			oto=22;    /*���̎��g���ɂ���*/
			irekae=19;  /*���̉��ł��邱�Ƃ�m�点��*/	
			time=0;    /*time��0�ɂ��Đ�������*/
		}
		
		
		if(time>=364 && irekae==19)  /*���̉���0.4�b�����ꂽ��*/
		{
			oto=20;    /*�V�̎��g���ɂ���*/
			irekae=20;  /*�V�̉��ł��邱�Ƃ�m�点��*/	
			time=0;    /*time��0�ɂ��Đ�������*/
		}
		
		
		if(time>=2044 && irekae==20)  /*�V�̉�2.1�b�����ꂽ��*/
		{
			TRISA=0x1F;  /*�����I�ɏo�͂�����*/
			__delay_ms(3000);  /*������3�b���*/
			
			TRISA=0x00;  /*�o�͂ɖ߂�*/
			irekae=0;  
			time=0;
			oto=13;  /*̧#(��)�̉��ɂ���*/
			count=0;
		
			
		}
		
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
			
			time++;     /*���Ԃ��͂��邽�߂�time�̒l�𑝂₵�Ă���*/
		}
		
		T0IF=0;  /*0�ɖ߂�*/
	}
	
	return;
}

