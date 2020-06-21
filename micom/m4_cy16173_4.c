/*My Soul,Your Bbats(冒頭部分)、是非聴いてください。*/



#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (Power-up Timer is disabled)
#pragma config CP = OFF         // Code Protection bit (Code protection disabled)

#define _XTAL_FREQ 20000000   /*クロック周波数を200MHzにする*/

void interrupt warikomi (void);

int count=0;  /*特定の音を出すための変数*/

int oto=13;  /*出したい音を指定するための変数、ﾌｧ#(高)を出す*/
int	time=0;  /*音を出すための時間を指定する*/

int main(void)
{
	TRISA=0x00;   /*RA0~RA4を出力として使う*/
	TRISB=0x00;   /*RB0~RB7を出力として使う*/
	PORTA=0x00;   
	PORTB=0x00;
	
	T0CS=0;     /*タイマをクロックで動かす*/
	TMR0=0x00;  /*タイマの現在値を0にする*/
	T0IF=0;     /*タイマオーバーフロー割り込みが発生すると1になる*/
	T0IE=1;     /*タイマオーバーフロー割り込みを許可する*/
	GIE=1;      /*割り込みを許可する*/
	  
	int irekae=0;  /*今をだしている音識別するための変数*/
	
	while(1)
	{
		if(time>=306 && irekae==0)  /*ﾌｧ#(高)の音が0.2秒だされた時*/
		{
			oto=15;    /*ミ(高)の周波数にする*/
			irekae=1;  /*ミ(高)の音であることを知らせる*/
			time=0;    /*timeを0にして数え直す*/
		}
		
		if(time>=546 && irekae==1)  /*ミ(高)の音が0.4秒だされた時*/
		{
			oto=17;    /*レ(高)の周波数にする*/
			irekae=2;  /*レ(高)の音であることを知らせる*/	
			time=0;    /*timeを0にして数え直す*/
		}
		
		if(time>=486 && irekae==2)  /*レ(高)の音が0.4秒だされた時*/
		{
			oto=20;    /*シの周波数にする*/
			irekae=3;  /*シの音であることを知らせる*/	
			time=0;    /*timeを0にして数え直す*/
		}
		
		if(time>=409 && irekae==3)  /*シの音が0.4秒だされた時*/
		{
			oto=22;    /*ラの周波数にする*/
			irekae=4;  /*ラの音であることを知らせる*/	
			time=0;    /*timeを0にして数え直す*/
		}
		
		
		
		
		if(time>=1639 && irekae==4)  /*ラの音が1.9秒だされた時*/
		{
			oto=13;    /*ﾌｧ#(高)の周波数にする*/
			irekae=5;  /*ﾌｧ#(高)の音であることを知らせる*/	
			time=0;    /*timeを0にして数え直す*/
		}
		
		
		if(time>=306 && irekae==5)  /*ﾌｧ#(高)の音が0.2秒だされた時*/
		{
			oto=15;    /*ミ(高)の周波数にする*/
			irekae=6;  /*ミ(高)の音であることを知らせる*/
			time=0;    /*timeを0にして数え直す*/
		}
		
		if(time>=546 && irekae==6)  /*ミ(高)の音が0.4秒だされた時*/
		{
			oto=17;    /*レ(高)の周波数にする*/
			irekae=7;  /*レ(高)の音であることを知らせる*/	
			time=0;    /*timeを0にして数え直す*/
		}
		
		if(time>=486 && irekae==7)  /*レ(高)の音が0.4秒だされた時*/
		{
			oto=20;    /*シの周波数にする*/
			irekae=8;  /*シの音であることを知らせる*/	
			time=0;    /*timeを0にして数え直す*/
		}
		
		if(time>=409 && irekae==8)  /*シの音が0.4秒だされた時*/
		{
			oto=22;    /*ラの周波数にする*/
			irekae=9;  /*ラの音であることを知らせる*/	
			time=0;    /*timeを0にして数え直す*/
		}
		
		
		
		
		if(time>=1639 && irekae==9)  /*ラの音が1.9秒だされた時*/
		{
			oto=13;    /*ﾌｧ#(高)の周波数にする*/
			irekae=10;  /*ﾌｧ#(高)の音であることを知らせる*/	
			time=0;    /*timeを0にして数え直す*/
		}
		
		
		if(time>=306 && irekae==10)  /*ﾌｧ#(高)の音が0.2秒だされた時*/
		{
			oto=15;    /*ミ(高)の周波数にする*/
			irekae=11;  /*ミ(高)の音であることを知らせる*/	
			time=0;    /*timeを0にして数え直す*/
		}
		
		
		
		if(time>=546 && irekae==11)  /*ミ(高)の音が0.4秒だされた時*/
		{
			oto=17;    /*レ(高)の周波数にする*/
			irekae=12;  /*レ(高)の音であることを知らせる*/	
			time=0;    /*timeを0にして数え直す*/
		}
		
		
		if(time>=486 && irekae==12)  /*レ(高)の音が0.4秒だされた時*/
		{
			oto=13;    /*ﾌｧ#(高)の周波数にする*/
			irekae=13;  /*ﾌｧ#(高)の音であることを知らせる*/	
			time=0;    /*timeを0にして数え直す*/
		}
		
		if(time>=612 && irekae==13)  /*ﾌｧ#(高)の音が0.4秒だされた時*/
		{
			oto=11;    /*ラ(高)の周波数にする*/
			irekae=14;  /*ラ(高)の音であることを知らせる*/	
			time=0;    /*timeを0にして数え直す*/
		}
		
		if(time>=728 && irekae==14)  /*ラ(高)の音が0.4秒だされた時*/
		{
			oto=5;    /*シ(更に高)の周波数にする*/
			irekae=15;  /*シ(更に高)の音であることを知らせる*/	
			time=0;    /*timeを0にして数え直す*/
		}
		
		
		
		
		if(time>=4087 && irekae==15)  /*シ(更に高)の音が1.0秒だされた時*/
		{
			TRISA=0x1F;  /*強制的に出力をきる*/
			__delay_ms(414);  /*無音を0.414秒作る*/
			
			TRISA=0x00;  /*出力に戻す*/
			irekae=16;  
			time=0;
			oto=13;  /*ﾌｧ#(高)の音にする*/
			count=0;
		}
		
		
		if(time>=306 && irekae==16)  /*ﾌｧ#(高)の音が0.2秒だされた時*/
		{
			oto=15;    /*ミ(高)の周波数にする*/
			irekae=17;  /*ミ(高)の音であることを知らせる*/	
			time=0;    /*timeを0にして数え直す*/
		}
		
		
		if(time>=546 && irekae==17)  /*ミ(高)の音が0.4秒だされた時*/
		{
			oto=17;    /*レ(高)の周波数にする*/
			irekae=18;  /*レ(高)の音であることを知らせる*/	
			time=0;    /*timeを0にして数え直す*/
		}
		
		
		if(time>=486 && irekae==18)  /*レ(高)の音が0.4秒だされた時*/
		{
			oto=22;    /*ラの周波数にする*/
			irekae=19;  /*ラの音であることを知らせる*/	
			time=0;    /*timeを0にして数え直す*/
		}
		
		
		if(time>=364 && irekae==19)  /*ラの音が0.4秒だされた時*/
		{
			oto=20;    /*シの周波数にする*/
			irekae=20;  /*シの音であることを知らせる*/	
			time=0;    /*timeを0にして数え直す*/
		}
		
		
		if(time>=2044 && irekae==20)  /*シの音2.1秒だされた時*/
		{
			TRISA=0x1F;  /*強制的に出力をきる*/
			__delay_ms(3000);  /*無音を3秒作る*/
			
			TRISA=0x00;  /*出力に戻す*/
			irekae=0;  
			time=0;
			oto=13;  /*ﾌｧ#(高)の音にする*/
			count=0;
		
			
		}
		
	}
	
	return 0;
	
}

void interrupt warikomi(void)
{
	if(T0IF!=0 && T0IE!=0)  /*タイマオーバーフロー割り込みが許可されていて、発生したら*/
	{
		count++;  /*音をだすために割り込みをカウントする*/
		
		if(count>=oto)  /*特定の周波数をつくるタイミングで*/
		{
			RA2=1-RA2;  /*Highとlowを入れ替える*/
			
			count=0;    /*カウントし直す*/
			
			time++;     /*時間をはかるためにtimeの値を増やしていく*/
		}
		
		T0IF=0;  /*0に戻す*/
	}
	
	return;
}

