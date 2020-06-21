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

int oto; /*出したい音を指定するための変数*/


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
	  
	
	
	while(1)
	{
			oto=26;    /*ﾌｧ♯の周波数にする*/
			__delay_ms(900); /*ﾌｧ♯の音を0.9秒だす*/
	
			
			
			oto=31;    /*レ♯の周波数にする*/
			__delay_ms(900); /*レ♯の音を0.9秒だす*/
		
		
		
			oto=26;    /*ﾌｧ♯の周波数にする*/
			__delay_ms(900); /*ﾌｧ♯の音を0.9秒だす*/
		
		
		
			oto=20;    /*シの周波数にする*/
			__delay_ms(2000); /*シの音を2.0秒だす*/
		
		
			TRISA=0x1F;  /*強制的に出力をきる*/
			__delay_ms(3000);  /*無音を3秒作る*/
			
			TRISA=0x00;  /*出力に戻す*/
			
			
		
		
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
			
			
		}
		
		T0IF=0;  /*0に戻す*/
	}
	
	return;
}
