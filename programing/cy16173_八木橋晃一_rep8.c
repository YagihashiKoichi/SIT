#include<stdio.h>
#include<string.h>
/*
CY16173	���؋��W��	�쐬���F2017�N6��8��	�ۑ�6
�e�X�g
case1	
������:	(��̃t�@�C��)					����:�����\������Ȃ�

case	2
������:	��										����:�o��:1��  �Փ�:0��  k

case	3
������:	there	are	pens				����:�o��:1��  �Փ�:0��  there
																					�o��:1��  �Փ�:0��  are
																					�o��:1��  �Փ�:0��  pens

case	4
������:	I am student * / - +		����:�o��:1��  �Փ�:0��  student
																										�o��:1��  �Փ�:0��  *
																										�o��:1��  �Փ�:0��  +
																										�o��:1��  �Փ�:0��  -
																										�o��:1��  �Փ�:0��  /
																										�o��:1��  �Փ�:0��  i
																										�o��:1��  �Փ�:0��  am



case	5
������:I aM Pen i Am pEN 			����:�o��:2��  �Փ�:0��  pen
																								�o��:2��  �Փ�:0��  i
																								�o��:2��  �Փ�:0��  am
case	6
������:������ 			����:�����o�Ȃ�

case	7
������: this hist desk isth this			����:�o��:1��  �Փ�:0��  desk
																																			�o��:2��  �Փ�:2��  this


case	8
������:Are you a man?	 				����:�o��:1��  �Փ�:0��  are
																							�o��:1��  �Փ�:0��  you
																							�o��:1��  �Փ�:0��  a
																						�o��:1��  �Փ�:0��  man?


case	9
������:Are you a man ?	 			����:�o��:1��  �Փ�:0��  are
																						�o��:1��  �Փ�:0��  man
																						�o��:1��  �Փ�:0��  ?
																						�o��:1��  �Փ�:0��  you
																					�o��:1��  �Փ�:0��  a


case	10
������:tom�̃t�@�C�� 			����:�o��:1��  �Փ�:2��  jimpson
																		�o��:4��  �Փ�:3��  through
																�o��:1��  �Փ�:0��  thought
															�o��:2��  �Փ�:0��  child
															��:1��  �Փ�:3��  heads
															�o��:1��  �Փ�:0��  alike
															�o��:2��  �Փ�:0��  angle
															�o��:1��  �Փ�:2��  board							(�ꕔ�݂̂�\��)


case	11
text(���݂��Ȃ��t�@�C���j			����:can	not	open


�֐��̐���
azur�ɂ�������̃t�@�C�����Ăяo���ĊJ���A���̂Ȃ��ɏ�����Ă���P���啶���A�������̋�ʖ����o���񐔂ƏՓˉ񐔂𐔂�
���̕����ƈꏏ�ɏo�͂���֐�
*/
char	men[100000];																						//�P���ۑ����Ƃ��z��
char	buff[100];																							//�P����ꎞ�I�ɕۑ����Ƃ��z��
char	*p_newmen=men;																					//men�̃|�C���^
struct	point{																								//�\���̂̐錾�F�v�f�͏ォ��o���񐔁A�P��A�Փˉ�
	int	syutugen;
	char	*word;
	int	syoutotu;
};
struct	point	hashtable[256];							//�\���̂̔z��



char	*create_string(char	buff[100]);								
char	*mem_alloc(int	length);																				
int	hash	(char	*key);																																	
void	dump_ht(void);


int	main	(void)
{
	int	s,amari;											//s:�J�E���^�[�ϐ�
																				//	amari:�n�b�V���l
																	
	char	*moziretu;
	FILE	*istream;
	istream=fopen("tom.txt","r");												//�t�@�C�����J���Ar:�ǂݍ���

	if(istream==0)																						//�Y������t�@�C�����Ȃ��ꍇ
	{
		printf("can	not	open\n");
		return	1;
	}

	for(s=0;s<2000;s++)
	{
		if(fscanf(istream,"%s",buff)==EOF)	break;				//�I���(EOF)��������break
																							
		
		amari=hash(buff);											//�n�b�V���l����
		
		if(hashtable[amari].syutugen==0)							//�܂��������Ă��Ȃ��Ƃ�
		{		
			moziretu=create_string(buff);								//�V�������������m��
			hashtable[amari].word=moziretu;					//��������
			hashtable[amari].syutugen++;										//�o���񐔂��J�E���g
		}								

		else	if(strcmp(hashtable[amari].word,buff)==0)																			//��������r										
			hashtable[amari].syutugen++;							

		else
			hashtable[amari].syoutotu++;							//�Փˉ񐔂��J�E���g
			

	}

	fclose(istream);													//�t�@�C�������
	dump_ht();																//�\���̗̂v�f���o��
	return	0;
}



/*
�e�X�g		�R�����g�ɂ���悤��printf("%s   ",buff)�Aprintf("%s\n",moziretu)��p��

case1
�z��F	there are	pens							���ʁFthere   there
																			are   are
																			pens   pens


�֐��̐���
�R�s�[������������̃A�h���X�������Ƃ��āA�V���ȃ�������\0�����m�ۂ������Ɏw�肵���������
�R�s�[���Ă��̃A�h���X��Ԃ��֐�

�����F�R�s�[������������̃A�h���X
�߂�l�F�R�s�[����������̃A�h���X
*/
char	*create_string(char	buff[100])
{
	char	*p,*moziretu;										//p:�R�s�[�����̃A�h���X�������ϐ�
																			//	moziretu:buff�̕������p�ɃR�s�[�����������̃A�h���X�������ϐ�
	int	length;													//�R�s�[������������i\0���܂ށj�̒�����������ϐ�

																			//	printf("%s   ",buff);
	length=strlen(buff)+1;						//strlen(buff)�ŃR�s�[������������̒��������߂�i\0���܂܂Ȃ�)�A+1��\0
	p=mem_alloc(length);
	moziretu=strcpy(p,buff);			//buff�̕������p�̏ꏊ�ɃR�s�[
																		//		printf("%s\n",moziretu);

	return	moziretu;
}




/*
�e�X�g		�R�����g�ɂ���悤��printf("%d�@�@",p)�A		printf("%d\n",p_newmen)��p��
case1	
������:	there are	pens						����:4250624�@�@4250630
																							4250630�@�@4250634
																							4250634�@�@4250639

�֐��̐���
���������m�ۂ��ăR�s�[��̃A�h���X��Ԃ��֐�

�����F�R�s�[�����������񂨃A�h���X
�߂�l�F�R�s�[��̃A�h���X
*/
char	*mem_alloc(int	length)
{
	char	*p;																			//�R�s�[�����̃A�h���X�������ϐ�																							
	p=p_newmen;																		//�R�s�[�����̃A�h���X������
																							//		printf("%d�@�@",p);
	p_newmen=p_newmen+length;					//���ɃR�s�[�����̃A�h���X������
																							//			printf("%d\n",p_newmen);
	return	p;
}



/*
�e�X�g		�R�����g�ɂ���悤��printf("%d",key)�A	printf("���v%d  ",hashval)��p��
case1	
������:adk			����:97  100  107  ���v304

case2
������:ADK			����:97  100  107		���v304

case3
������:this			����:116  104  105  115  ���v440

case4
������:htsi			����:104  116  115  105  ���v440

�֐��̐���
��������󂯎��啶�����������ɒ������̃n�b�V���l��Ԃ��֐��i�����256�̗]��j

�����F�n�b�V���l�𒲂ׂ���������
�߂�l�F�����ł��镶����̃n�b�V���l
*/
int	hash	(char	*key)
{
	int	hashval,amari;				//hashval:�����R�[�h��S�đ������킹���l��������ϐ�
													//amari:�n�b�V���l
	
	hashval=0;

	while(*key!='\0')
	{
		if((65<=*key)&&(*key<=90))						//65<=�啶��<=90
			*key=*key+32;																					//�������ɂȂ���
	
																														//printf("%d  ",*key);
		
		hashval=hashval+*key;														//�����R�[�h�𑫂����킹��
		key++;
	}
	
																														//printf("���v%d  ",hashval);

	amari=hashval%256;																				//�n�b�V���l�����߂�A�����R�[�h�̘a��256�̗]��

	return	amari;
}



/*
�֐��̐���
�\���̗̂v�f�ɑ�����ꂽ���̂�printf�ŏo�͂���֐�
�������A�\���̂̒P��ɂ�����v�f��\0�̎��͂��̃Z���͏o�͂��Ȃ�

�����F�Ȃ�
�߂�l�F�Ȃ�
*/
void	dump_ht(void)
{
	int	t;												//�J�E���^�[�ϐ�

	for(t=0;t<265;t++)
	{
		if(hashtable[t].word!=0)																																						//�\���̂̒P��ɂ�����v�f��\0�̎��͂��̃Z���͏o�͂��Ȃ�
		{	
			printf("�o��:%d��  ",hashtable[t].syutugen);				//���̒P�ꂪ�o��������
			printf("�Փ�:%d��  ",hashtable[t].syoutotu);				//���̒P�ꂪ�Փ˂�����
			printf("%s\n",hashtable[t].word);																					//�Ȃ�̒P��ɂ��Ă�
		}
	}
}

