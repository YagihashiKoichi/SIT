/*
 作成日時：2018年5月23日
 プロジェクト演習２　第5回
 CY16173  八木橋晃一
  */
// PIC16F1827 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>
#include<stdlib.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1
//#pragma config FOSC = INTOSC  // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config FOSC = HS        // Oscillator Selection (HS Oscillator, High-speed crystal/resonator connected between OSC1 and OSC2 pins)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

#define _XTAL_FREQ   20000000

void interrupt warikomi (void); //割り込み関数
void bad_apple (void);          // bad_appleの繰り返し部分
void undertale (void);          //undertaleの繰り返し部分

int count=0;  //特定の音を出すための変数
int oto; //出したい音を指定するための変数

int main (void){
    
    int new_value;  //測定結果
    int minimam;    //最短距離
    int limit;      //限界距離
    int ransu;      //乱数の結果
    int i;          //カウンタ変数
    int music=0;    //音楽のナンバー
    srand(10);      //乱数の種
    
    TRISA =  0x00; //使わないので全部出力
    TRISB =  0x28; //RB5は入力.RB3の出力は切っておく
    ANSELA = 0x00;
    ANSELB = 0x20; //RB5はアナログ
    PORTA =  0x00;
    PORTB =  0x00;
    ADCON0 = 0x1D; //ADCするのはAN7(RB5), ADONにする -> 00011101
    ADCON1 = 0xC0; //結果右詰め, ADCS = FOSC/4, REF = VDD/VSS -> 11000000
        //  ADRESH    ADRESL
        // 000000ab  cdefghij (ADFM=1)
        //  int new_value = ADRESH*256 + ADRESL;
    
    TMR0CS=0;         //タイマをクロックで動かす*/
	TMR0=0x00;        //タイマの現在値を0にする*/
	TMR0IF=0;         //タイマオーバーフロー割り込みが発生すると1になる*/
	TMR0IE=1;         //タイマオーバーフロー割り込みを許可する*/
	GIE=1;            //割り込みを許可する*/
    
    while(1){         //ゲームが続く
        
        minimam=91;   //ものが何もない時をあとで測定
        while(1){
            ransu=rand()%455;
            if((117<=ransu)&&(ransu<=440)){ //13センチ-60センチ
                                            // 1.934/4.5*1023
                                            // 0.5135/4.5*1023
                limit=ransu;                //乱数で限界の距離を生成
                break;
            }
        }
       
        while(1){   //一回のゲーム

            //--- AD変換
            GO = 1;
            while(GO==1){   //計算が終わると0になる
                ;
            }
            new_value = ADRESH*256 + ADRESL;
            //--- AD変換
            
             if(minimam<new_value){  //最小距離が更新される
                minimam=new_value;
                RB1=1;               //緑LED点灯
            }
          
            else    if(new_value<37){      //人がいなくなったら
                                           // 0.1632/4.5*1023
                RB1=0;                    //緑LED消灯
            }
            
            if(limit<=new_value){         //設定より近づいたら
                  
               if(RB1==1)                 //もしアウトでも人がいたとき
                    RB1=0;                //緑LED消灯
                RB2=1;                    //赤LED点灯
               
               TRISB =  0x20;             //スピーカーの出力を戻す
               
               if(music%3==0){            //My soul your beats 
                    for(i=0;i<2;i++){
                        
                        oto=13;           //ファ＃（高）の周波数にする
                        __delay_ms(207);  //ファ＃（高）の音を207m秒だす
                
                        oto=15;           //ミ（高）の周波数にする
                         __delay_ms(414); //ミ（高）の音を414m秒だす
                 
                        oto=17;           //レ（高）の周波数にする
                        __delay_ms(414);  //レ（高）の音を414m秒だす
                 
                        oto=20;           //シの周波数にする
                        __delay_ms(414);  //シの音を414m秒だす
                   
                        oto=22;           //ラの周波数にする
                        __delay_ms(1812); //ラの音を1812m秒だす
                    }
                
                    oto=13;               //ファ＃（高）の周波数にする
                    __delay_ms(207);      //ファ＃（高）の音を207m秒だす
                
                    oto=15;               //ミ（高）の周波数にする
                    __delay_ms(400);      //ミ（高）の音を400m秒だす
                 
                    oto=17;               //レ（高）の周波数にする
                    __delay_ms(414);      //レ（高）の音を414m秒だす
                  
                    oto=13;               //ファ＃（高）の周波数にする
                    __delay_ms(414);      //ファ＃（高）の音を414m秒だす
                   
                    oto=11;               //ラ（高）の周波数にする
                    __delay_ms(414);      //ラ（高）の音を414秒だす
                
                    oto=5;                //シ（更に高）の周波数にする
                    __delay_ms(828);      //シ（更に高）の音を828m秒だす
                
                    TRISB =  0x28;        //出力を切る
                    __delay_ms(207);      //休符(207m秒)
                    TRISB =  0x20;        //出力を戻す    
                
                    oto=13;               //ファ＃（高）の周波数にする
                    __delay_ms(207);      //ファ＃（高）の音を207m秒だす
                
                    oto=15;               //ミ（高）の周波数にする
                     __delay_ms(414);     //ミ（高）の音を414m秒だす
                 
                    oto=17;               //レ（高）の周波数にする
                     __delay_ms(414);     //レ（高）の音を414m秒だす
                
                    oto=22;               //ラの周波数にする
                   __delay_ms(414);       //ラの音を414m秒だす
                  
                    oto=20;               //シの周波数にする
                    __delay_ms(2069);     //シの音を2069m秒だす
               }
               
               else if(music%3==1){       //BadApple
                 bad_apple();
                
                    oto=28;               //ファの周波数にする
                      __delay_ms(217);    //ファの音を217m秒だす
                
                    oto=31;               //ｂミの周波数にする
                     __delay_ms(217);     //ｂミの音を217m秒だす
                
                    oto=28;               //ファの周波数にする
                    __delay_ms(217);      //ファの音を217m秒だす
                
                    oto=26;               //bソの周波数にする
                    __delay_ms(217);      //bソの音を217m秒だす
                
                    oto=28;               //ファの周波数にする
                    __delay_ms(217);      //ファの音を217m秒だす
                
                    oto=31;               //ｂミの周波数にする
                    __delay_ms(217);      //ｂミの音を217m秒だす
                
                    oto=33;               //レの周波数にする
                    __delay_ms(217);      //レの音を217m秒だす
                
                    oto=28;               //ファの周波数にする
                    __delay_ms(217);      //ファの音を217m秒だす
                
                    bad_apple();
                 
                    oto=28;               //ファの周波数にする
                    __delay_ms(435);      //ファの音を435m秒だす
                
                    oto=26;               //bソの周波数にする
                    __delay_ms(435);      //bソの音を435m秒だす
                
                    oto=24;               //bラの周波数にする
                    __delay_ms(435);      //bラの音を435m秒だす
    
                    oto=21;               //bシの周波数にする
                    __delay_ms(435);      //bシの音を435m秒だす
               }
               
               else{                      //Undertale
                    oto=33;               //レの周波数にする
                    __delay_ms(103);      //レの音を103m秒だす
                   
                    TRISB =  0x28;        //出力を切る
                    __delay_ms(10);       //連続した同じ音なので10m秒の無音
                    TRISB =  0x20;        //スピーカーの出力を戻す
                    
                    oto=33;               //レの周波数にする
                    __delay_ms(103);      //レの音を103m秒だす
                   
                    undertale ();
                   
                    oto=37;               //ドの周波数にする
                    __delay_ms(103);      //ドの音を103m秒だす
                   
                    TRISB =  0x28;        //出力を切る
                    __delay_ms(10);       //連続した同じ音なので10m秒の無音
                    TRISB =  0x20;        //スピーカーの出力を戻す
                    
                    oto=37;               //ドの周波数にする
                    __delay_ms(103);      //ドの音を103m秒だす
                   
                   undertale ();
                   
                   oto=40;                //(低)シの周波数にする
                   __delay_ms(103);       //(低)シの音を103m秒だす
                   
                   TRISB =  0x28;         //出力を切る
                   __delay_ms(10);        //10m秒待つ
                   TRISB =  0x20;         //スピーカーの出力を戻す
                    
                    oto=40;               //(低)シの周波数にする
                   __delay_ms(103);       //(低)シの音を103秒だす
                   
                   undertale ();
                   
                   oto=42;                //(低)bシの周波数にする
                   __delay_ms(103);       //(低)bシの音を103秒だす
                   
                   TRISB =  0x28;         //出力を切る
                   __delay_ms(10);        //連続した同じ音なので10m秒の無音
                   TRISB =  0x20;         //スピーカーの出力を戻す
                    
                    oto=42;               //(低)bシの周波数にする
                   __delay_ms(103);       //(低)bシの音を103m秒だす
                   
                    undertale ();
               }
               
                TRISB =  0x28;            //スピーカーの出力を切る 
                RB2=0;                    //赤LED消灯
                music++; 
                
                break;
            }  
        }
    }
    return  0;
}


void interrupt warikomi(void){
	if(TMR0IF!=0 && TMR0IE!=0){  //タイマオーバーフロー割り込みが許可されていて、発生したら
		count++;                //音をだすために割り込みをカウントする
		
		if(count>=oto){          //特定の周波数をつくるタイミングで
			RB3=1-RB3;          //Highとlowを入れ替える	
			count=0;            //カウントし直す
		}
		TMR0IF=0;               //0に戻す
	}
	return;
}



void bad_apple (void){
    oto=31;              //ｂミの周波数にする
    __delay_ms(217);     //ｂミの音を217m秒だす
   
    oto=28;              //ファの周波数にする
    __delay_ms(217);     //ファの音を217m秒だす
    
    oto=26;              //bソの周波数にする
    __delay_ms(217);     //bソの音を217m秒だす
    
    oto=24;              //bラの周波数にする
    __delay_ms(217);     //bラの音を217m秒だす
    
    oto=21;              //bシの周波数にする
    __delay_ms(435);     //bシの音を435秒だす
    
    oto=16;              //(高)bミの周波数にする
    __delay_ms(217);     //(高)bミの音を217m秒だす
    
    oto=18;              //(高)bレの周波数にする
    __delay_ms(217);     //(高)bレの音を217m秒だす
    
     oto=21;             //bシの周波数にする
    __delay_ms(435);     //bシの音を435m秒だす
    
    oto=31;              //ｂミの周波数にする
    __delay_ms(435);     //ｂミの音を435m秒だす
    
    oto=21;             //bシの周波数にする
    __delay_ms(217);     //bシの音を217m秒だす
    
    oto=24;              //bラの周波数にする
    __delay_ms(217);     //bラの音を217m秒だす
    
    oto=26;              //bソの周波数にする
    __delay_ms(217);     //bソの音を217m秒だす
    
    oto=28;              //ファの周波数にする
    __delay_ms(217);     //ファの音を217m秒だす
    
    oto=31;              //ｂミの周波数にする
    __delay_ms(217);     //ｂミの音を217m秒だす
    
    oto=28;              //ファの周波数にする
    __delay_ms(217);     //ファの音を217m秒だす
    
    oto=26;              //bソの周波数にする
    __delay_ms(217);     //bソの音を217m秒だす
    
    oto=24;              //bラの周波数にする
    __delay_ms(217);     //bラの音を217m秒だす
    
    oto=21;              //bシの周波数にする
    __delay_ms(435);     //bシの音を435秒mだす
    
    oto=24;              //bラの周波数にする
    __delay_ms(217);     //bラの音を217m秒だす
    
    oto=26;              //bソの周波数にする
    __delay_ms(217);     //bソの音を217m秒だす
    
    return;
}


void undertale (void){
    oto=17;              //(高)レの周波数にする
    __delay_ms(103);     //(高)レの音を103m秒だす
    
    TRISB =  0x28;       //出力を切る
    __delay_ms(103);     //休符(103m秒)
    TRISB =  0x20;       //出力を戻す    

    oto=22;              //ラの周波数にする
    __delay_ms(207);     //ラの音を207m秒だす
    
    TRISB =  0x28;       //出力を切る
    __delay_ms(103);     //休符(103m秒)
    TRISB =  0x20;       //出力を戻す    
    
    oto=24;              //bラの周波数にする
    __delay_ms(103);     //bラの音を103m秒だす
    
    TRISB =  0x28;       //出力を切る
    __delay_ms(103);     //休符(103m秒)
    TRISB =  0x20;       //出力を戻す    
     
    oto=25;              //ソの周波数にする
    __delay_ms(207);     //ソの音を207m秒だす
    
    oto=28;              //ファの周波数にする
    __delay_ms(207);     //ファの音を207m秒だす
    
    oto=33;              //レの周波数にする
    __delay_ms(103);     //レの音を103m秒だす
    
    oto=28;              //ファの周波数にする
    __delay_ms(103);     //ファの音を103m秒だす
    
    oto=25;              //ソの周波数にする
    __delay_ms(103);     //ソの音を103m秒だす
    
    return; 
}