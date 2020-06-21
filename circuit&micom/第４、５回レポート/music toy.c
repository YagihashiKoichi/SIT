/*
 �쐬�����F2018�N5��23��
 �v���W�F�N�g���K�Q�@��5��
 CY16173  ���؋��W��
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

void interrupt warikomi (void); //���荞�݊֐�
void bad_apple (void);          // bad_apple�̌J��Ԃ�����
void undertale (void);          //undertale�̌J��Ԃ�����

int count=0;  //����̉����o�����߂̕ϐ�
int oto; //�o�����������w�肷�邽�߂̕ϐ�

int main (void){
    
    int new_value;  //���茋��
    int minimam;    //�ŒZ����
    int limit;      //���E����
    int ransu;      //�����̌���
    int i;          //�J�E���^�ϐ�
    int music=0;    //���y�̃i���o�[
    srand(10);      //�����̎�
    
    TRISA =  0x00; //�g��Ȃ��̂őS���o��
    TRISB =  0x28; //RB5�͓���.RB3�̏o�͂͐؂��Ă���
    ANSELA = 0x00;
    ANSELB = 0x20; //RB5�̓A�i���O
    PORTA =  0x00;
    PORTB =  0x00;
    ADCON0 = 0x1D; //ADC����̂�AN7(RB5), ADON�ɂ��� -> 00011101
    ADCON1 = 0xC0; //���ʉE�l��, ADCS = FOSC/4, REF = VDD/VSS -> 11000000
        //  ADRESH    ADRESL
        // 000000ab  cdefghij (ADFM=1)
        //  int new_value = ADRESH*256 + ADRESL;
    
    TMR0CS=0;         //�^�C�}���N���b�N�œ�����*/
	TMR0=0x00;        //�^�C�}�̌��ݒl��0�ɂ���*/
	TMR0IF=0;         //�^�C�}�I�[�o�[�t���[���荞�݂����������1�ɂȂ�*/
	TMR0IE=1;         //�^�C�}�I�[�o�[�t���[���荞�݂�������*/
	GIE=1;            //���荞�݂�������*/
    
    while(1){         //�Q�[��������
        
        minimam=91;   //���̂������Ȃ��������Ƃő���
        while(1){
            ransu=rand()%455;
            if((117<=ransu)&&(ransu<=440)){ //13�Z���`-60�Z���`
                                            // 1.934/4.5*1023
                                            // 0.5135/4.5*1023
                limit=ransu;                //�����Ō��E�̋����𐶐�
                break;
            }
        }
       
        while(1){   //���̃Q�[��

            //--- AD�ϊ�
            GO = 1;
            while(GO==1){   //�v�Z���I����0�ɂȂ�
                ;
            }
            new_value = ADRESH*256 + ADRESL;
            //--- AD�ϊ�
            
             if(minimam<new_value){  //�ŏ��������X�V�����
                minimam=new_value;
                RB1=1;               //��LED�_��
            }
          
            else    if(new_value<37){      //�l�����Ȃ��Ȃ�����
                                           // 0.1632/4.5*1023
                RB1=0;                    //��LED����
            }
            
            if(limit<=new_value){         //�ݒ���߂Â�����
                  
               if(RB1==1)                 //�����A�E�g�ł��l�������Ƃ�
                    RB1=0;                //��LED����
                RB2=1;                    //��LED�_��
               
               TRISB =  0x20;             //�X�s�[�J�[�̏o�͂�߂�
               
               if(music%3==0){            //My soul your beats 
                    for(i=0;i<2;i++){
                        
                        oto=13;           //�t�@���i���j�̎��g���ɂ���
                        __delay_ms(207);  //�t�@���i���j�̉���207m�b����
                
                        oto=15;           //�~�i���j�̎��g���ɂ���
                         __delay_ms(414); //�~�i���j�̉���414m�b����
                 
                        oto=17;           //���i���j�̎��g���ɂ���
                        __delay_ms(414);  //���i���j�̉���414m�b����
                 
                        oto=20;           //�V�̎��g���ɂ���
                        __delay_ms(414);  //�V�̉���414m�b����
                   
                        oto=22;           //���̎��g���ɂ���
                        __delay_ms(1812); //���̉���1812m�b����
                    }
                
                    oto=13;               //�t�@���i���j�̎��g���ɂ���
                    __delay_ms(207);      //�t�@���i���j�̉���207m�b����
                
                    oto=15;               //�~�i���j�̎��g���ɂ���
                    __delay_ms(400);      //�~�i���j�̉���400m�b����
                 
                    oto=17;               //���i���j�̎��g���ɂ���
                    __delay_ms(414);      //���i���j�̉���414m�b����
                  
                    oto=13;               //�t�@���i���j�̎��g���ɂ���
                    __delay_ms(414);      //�t�@���i���j�̉���414m�b����
                   
                    oto=11;               //���i���j�̎��g���ɂ���
                    __delay_ms(414);      //���i���j�̉���414�b����
                
                    oto=5;                //�V�i�X�ɍ��j�̎��g���ɂ���
                    __delay_ms(828);      //�V�i�X�ɍ��j�̉���828m�b����
                
                    TRISB =  0x28;        //�o�͂�؂�
                    __delay_ms(207);      //�x��(207m�b)
                    TRISB =  0x20;        //�o�͂�߂�    
                
                    oto=13;               //�t�@���i���j�̎��g���ɂ���
                    __delay_ms(207);      //�t�@���i���j�̉���207m�b����
                
                    oto=15;               //�~�i���j�̎��g���ɂ���
                     __delay_ms(414);     //�~�i���j�̉���414m�b����
                 
                    oto=17;               //���i���j�̎��g���ɂ���
                     __delay_ms(414);     //���i���j�̉���414m�b����
                
                    oto=22;               //���̎��g���ɂ���
                   __delay_ms(414);       //���̉���414m�b����
                  
                    oto=20;               //�V�̎��g���ɂ���
                    __delay_ms(2069);     //�V�̉���2069m�b����
               }
               
               else if(music%3==1){       //BadApple
                 bad_apple();
                
                    oto=28;               //�t�@�̎��g���ɂ���
                      __delay_ms(217);    //�t�@�̉���217m�b����
                
                    oto=31;               //���~�̎��g���ɂ���
                     __delay_ms(217);     //���~�̉���217m�b����
                
                    oto=28;               //�t�@�̎��g���ɂ���
                    __delay_ms(217);      //�t�@�̉���217m�b����
                
                    oto=26;               //b�\�̎��g���ɂ���
                    __delay_ms(217);      //b�\�̉���217m�b����
                
                    oto=28;               //�t�@�̎��g���ɂ���
                    __delay_ms(217);      //�t�@�̉���217m�b����
                
                    oto=31;               //���~�̎��g���ɂ���
                    __delay_ms(217);      //���~�̉���217m�b����
                
                    oto=33;               //���̎��g���ɂ���
                    __delay_ms(217);      //���̉���217m�b����
                
                    oto=28;               //�t�@�̎��g���ɂ���
                    __delay_ms(217);      //�t�@�̉���217m�b����
                
                    bad_apple();
                 
                    oto=28;               //�t�@�̎��g���ɂ���
                    __delay_ms(435);      //�t�@�̉���435m�b����
                
                    oto=26;               //b�\�̎��g���ɂ���
                    __delay_ms(435);      //b�\�̉���435m�b����
                
                    oto=24;               //b���̎��g���ɂ���
                    __delay_ms(435);      //b���̉���435m�b����
    
                    oto=21;               //b�V�̎��g���ɂ���
                    __delay_ms(435);      //b�V�̉���435m�b����
               }
               
               else{                      //Undertale
                    oto=33;               //���̎��g���ɂ���
                    __delay_ms(103);      //���̉���103m�b����
                   
                    TRISB =  0x28;        //�o�͂�؂�
                    __delay_ms(10);       //�A�������������Ȃ̂�10m�b�̖���
                    TRISB =  0x20;        //�X�s�[�J�[�̏o�͂�߂�
                    
                    oto=33;               //���̎��g���ɂ���
                    __delay_ms(103);      //���̉���103m�b����
                   
                    undertale ();
                   
                    oto=37;               //�h�̎��g���ɂ���
                    __delay_ms(103);      //�h�̉���103m�b����
                   
                    TRISB =  0x28;        //�o�͂�؂�
                    __delay_ms(10);       //�A�������������Ȃ̂�10m�b�̖���
                    TRISB =  0x20;        //�X�s�[�J�[�̏o�͂�߂�
                    
                    oto=37;               //�h�̎��g���ɂ���
                    __delay_ms(103);      //�h�̉���103m�b����
                   
                   undertale ();
                   
                   oto=40;                //(��)�V�̎��g���ɂ���
                   __delay_ms(103);       //(��)�V�̉���103m�b����
                   
                   TRISB =  0x28;         //�o�͂�؂�
                   __delay_ms(10);        //10m�b�҂�
                   TRISB =  0x20;         //�X�s�[�J�[�̏o�͂�߂�
                    
                    oto=40;               //(��)�V�̎��g���ɂ���
                   __delay_ms(103);       //(��)�V�̉���103�b����
                   
                   undertale ();
                   
                   oto=42;                //(��)b�V�̎��g���ɂ���
                   __delay_ms(103);       //(��)b�V�̉���103�b����
                   
                   TRISB =  0x28;         //�o�͂�؂�
                   __delay_ms(10);        //�A�������������Ȃ̂�10m�b�̖���
                   TRISB =  0x20;         //�X�s�[�J�[�̏o�͂�߂�
                    
                    oto=42;               //(��)b�V�̎��g���ɂ���
                   __delay_ms(103);       //(��)b�V�̉���103m�b����
                   
                    undertale ();
               }
               
                TRISB =  0x28;            //�X�s�[�J�[�̏o�͂�؂� 
                RB2=0;                    //��LED����
                music++; 
                
                break;
            }  
        }
    }
    return  0;
}


void interrupt warikomi(void){
	if(TMR0IF!=0 && TMR0IE!=0){  //�^�C�}�I�[�o�[�t���[���荞�݂�������Ă��āA����������
		count++;                //�����������߂Ɋ��荞�݂��J�E���g����
		
		if(count>=oto){          //����̎��g��������^�C�~���O��
			RB3=1-RB3;          //High��low�����ւ���	
			count=0;            //�J�E���g������
		}
		TMR0IF=0;               //0�ɖ߂�
	}
	return;
}



void bad_apple (void){
    oto=31;              //���~�̎��g���ɂ���
    __delay_ms(217);     //���~�̉���217m�b����
   
    oto=28;              //�t�@�̎��g���ɂ���
    __delay_ms(217);     //�t�@�̉���217m�b����
    
    oto=26;              //b�\�̎��g���ɂ���
    __delay_ms(217);     //b�\�̉���217m�b����
    
    oto=24;              //b���̎��g���ɂ���
    __delay_ms(217);     //b���̉���217m�b����
    
    oto=21;              //b�V�̎��g���ɂ���
    __delay_ms(435);     //b�V�̉���435�b����
    
    oto=16;              //(��)b�~�̎��g���ɂ���
    __delay_ms(217);     //(��)b�~�̉���217m�b����
    
    oto=18;              //(��)b���̎��g���ɂ���
    __delay_ms(217);     //(��)b���̉���217m�b����
    
     oto=21;             //b�V�̎��g���ɂ���
    __delay_ms(435);     //b�V�̉���435m�b����
    
    oto=31;              //���~�̎��g���ɂ���
    __delay_ms(435);     //���~�̉���435m�b����
    
    oto=21;             //b�V�̎��g���ɂ���
    __delay_ms(217);     //b�V�̉���217m�b����
    
    oto=24;              //b���̎��g���ɂ���
    __delay_ms(217);     //b���̉���217m�b����
    
    oto=26;              //b�\�̎��g���ɂ���
    __delay_ms(217);     //b�\�̉���217m�b����
    
    oto=28;              //�t�@�̎��g���ɂ���
    __delay_ms(217);     //�t�@�̉���217m�b����
    
    oto=31;              //���~�̎��g���ɂ���
    __delay_ms(217);     //���~�̉���217m�b����
    
    oto=28;              //�t�@�̎��g���ɂ���
    __delay_ms(217);     //�t�@�̉���217m�b����
    
    oto=26;              //b�\�̎��g���ɂ���
    __delay_ms(217);     //b�\�̉���217m�b����
    
    oto=24;              //b���̎��g���ɂ���
    __delay_ms(217);     //b���̉���217m�b����
    
    oto=21;              //b�V�̎��g���ɂ���
    __delay_ms(435);     //b�V�̉���435�bm����
    
    oto=24;              //b���̎��g���ɂ���
    __delay_ms(217);     //b���̉���217m�b����
    
    oto=26;              //b�\�̎��g���ɂ���
    __delay_ms(217);     //b�\�̉���217m�b����
    
    return;
}


void undertale (void){
    oto=17;              //(��)���̎��g���ɂ���
    __delay_ms(103);     //(��)���̉���103m�b����
    
    TRISB =  0x28;       //�o�͂�؂�
    __delay_ms(103);     //�x��(103m�b)
    TRISB =  0x20;       //�o�͂�߂�    

    oto=22;              //���̎��g���ɂ���
    __delay_ms(207);     //���̉���207m�b����
    
    TRISB =  0x28;       //�o�͂�؂�
    __delay_ms(103);     //�x��(103m�b)
    TRISB =  0x20;       //�o�͂�߂�    
    
    oto=24;              //b���̎��g���ɂ���
    __delay_ms(103);     //b���̉���103m�b����
    
    TRISB =  0x28;       //�o�͂�؂�
    __delay_ms(103);     //�x��(103m�b)
    TRISB =  0x20;       //�o�͂�߂�    
     
    oto=25;              //�\�̎��g���ɂ���
    __delay_ms(207);     //�\�̉���207m�b����
    
    oto=28;              //�t�@�̎��g���ɂ���
    __delay_ms(207);     //�t�@�̉���207m�b����
    
    oto=33;              //���̎��g���ɂ���
    __delay_ms(103);     //���̉���103m�b����
    
    oto=28;              //�t�@�̎��g���ɂ���
    __delay_ms(103);     //�t�@�̉���103m�b����
    
    oto=25;              //�\�̎��g���ɂ���
    __delay_ms(103);     //�\�̉���103m�b����
    
    return; 
}