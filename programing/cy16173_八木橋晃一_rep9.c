#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
CY16173	���؋��W��	�쐬���F2017�N6��15��			�ۑ�7


�e�X�g
case	1
�t�@�C���F��̃t�@�C��							�폜�������P��F		am																								���ʁF�����o�͂���Ȃ�

case2
�t�@�C���F���݂��Ȃ��t�@�C��							�폜�������P��F		����Ȃ�																								���ʁFcan	not	open

case3
�t�@�C���FThis shit hist tHis sit						�폜�������P��F	this																				���ʁF=><sit,1>
																																																																																													=><hist,1>=><shit,1>
case4
�t�@�C���FThis shit hist tHis sit						�폜�������P��F	THIS																					���ʁF=><sit,1>
																																																																																													=><hist,1>=><shit,1>
case5
�t�@�C���FThis shit hist tHis sit					�폜�������P��F		shit																												���ʁF=><sit,1>
																																																																																														=><hist,1>=><this,2>																								
case6
�t�@�C���FThis shit hist tHis sit							�폜�������P��Fhist																										���ʁF=><sit,1>
																																																																																																		=><shit,1>=><this,2>
case7
�t�@�C���FThis shit hist tHis sit								�폜�������P��F	sit																									���ʁF=><hist,1>=><shit,1>=><this,2>


case8
�t�@�C���FThis shit hist tHis sit								�폜�������P��Fam																										���ʁF=><sit,1>
																																																																																																=><hist,1>=><shit,1>=><this,2>
case9
�t�@�C���Fa							�폜�������P��Fa																										���ʁF�����o�͂���Ȃ�

case10
�t�@�C���Fam	am	am	am	am	am	am								�폜�������P��Fam																										���ʁF�����o�͂���Ȃ�


�֐��̐���
azur�ɂ�������̃t�@�C�����Ăяo���ĊJ���A���̂Ȃ��ɏ�����Ă���P���啶���A�������̋�ʖ����o���񐔂𐔂�
�Փ˂����ꍇ�͐V�����Z�������ɍ��B���̌�폜�������P�����͂���Ƃ��̒P�ꂪ�폜���ꂽ��ԂŒP�ꂪ�����Ă���
���X�g���o�͂���֐��B
*/
struct	item	*create_item(char	*key,struct	item	*p);				
void	print_list(struct	item	*p);
char	*create_string(char	*key);
struct	item	*search_item(char	*key,struct	item	*p);
int	hash	(char	*key);
void	dump_ht(void);
void	chainhash	(char	*key);
struct	item	*delete_item(char	*key,struct	item	*p);


struct	item{																																						//�\���̂̐錾�F�v�f�͏ォ��o���񐔁A�P��A�\���̂ւ̃|�C���^
	int	count;
	char	*word;
	struct	item	*next;
};
char	men[100000];																																				//�P���ۑ����Ƃ��z��
char	buff[100];																																				//�P����ꎞ�I�ɕۑ����Ƃ��z��
struct	item	*hashtable[256];																						//�\���̂ւ̃|�C���^�̔z��


int	main(void)
{
	char	delete[100];																																	//delete[100]:�폜����������������[���邽�߂̔z��
	int	s,hashti;																																			//s:�J�E���^�[�ϐ�,hashti:�n�b�V���l�i�����256�̏�]�j
	FILE	*istream;	
																														
	istream=fopen("text.txt","r");												//�t�@�C�����J���Ar:�ǂݍ���

	if(istream==0)																						//�Y������t�@�C�����Ȃ��ꍇ
	{
		printf("can	not	open\n");
		return	0;
	}

	printf("�폜�������P�����͂��Ă��������B");
	scanf("%s",delete);
	hashti=hash(delete);

	for(s=0;s<2000;s++)
	{
		if(fscanf(istream,"%s",buff)==EOF)	break;				//�I���(EOF)��������break																		
		chainhash	(buff);
	}

	hashtable[hashti]=delete_item(delete,hashtable[hashti]);
	fclose(istream);													//�t�@�C�������
	dump_ht();																//�\���̗̂v�f���o��

	return	0;
}


/*
�֐��̐���
�\����item���琬�郊�X�g��\������
�����F�\�����������X�g�̐擪�̍\����item�ւ̃|�C���^�i0�ł��悢�j
�߂�l�F�Ȃ�
���ӁF������0�̏ꍇ�͉��s��������
*/
void	print_list(struct	item	*p)
{
	while(p!=0)
	{
		printf("=><%s,%d>",p->word,p->count);				//�\���`���̏C���͂���
		p=p->next;
	}

	printf("\n");
}


/*
�e�X�g						�R�����g�ɂ���悤��print_list(p)�Aprintf("%s\n",moziretu)��p��
case	1
�t�@�C���F	This shit hist this sit									�폜�������P��F	this				���ʁF=><this,1>
																																																																																		=><this,1>
																																																																																		=><shit,1>=><this,1>
																																																																																		=><shit,1>=><this,1>
																																																																																		=><hist,1>=><shit,1>=><this,1>

																																																																																		=><sit,1>

�֐��̐���
�Z���ɓ��ꂽ���P��ƐV����������Z����next���w�������A�h���X�������Ƃ��A
�V�����Z������肻�̃Z���ɒP�������V����������Z���̃A�h���X��Ԃ��֐��B

����1�Fword�ɂ��ꂽ���P��
����2�F�V����������Z����next���w�������A�h���X
�߂�l�F�V����������Z���̃A�h���X
*/
struct	item	*	create_item(char	*key,struct	item	*p)
{
	struct	item		*new_item,*old_item;																																		//*new_item:�m�ۂ����������̃A�h���X�������邽�߂̕ϐ�
																																																																					//*old_item:new_item�̃A�h���X�������Ĉꎞ�I�ɒl��ۑ����邽�߂̕ϐ�

																																																																					//print_list(p);							//	create_item��case1�ɂ����Ďg�p
	new_item=(struct	item*)malloc(sizeof(struct	item));						//�m�ۂ����������̃A�h���X��new_item�ɑ��
	new_item->count=1;																																																												//���߂Č����P��Ȃ̂�count��1�ɂ���
	new_item->word=create_string(key);											
	new_item->next=p;																
	old_item=new_item;																																																													//new_item�̃A�h���X�������Ĉꎞ�I�ɒl��ۑ�����
	new_item++;
																																																																//	print_list(old_item);						//	create_item��case1�ɂ����Ďg�p
	return	old_item;		
}


/*
�e�X�g		�R�����g�ɂ���悤��printf("%s   ",buff)�Aprintf("%s\n",moziretu)��p��
case	1
�t�@�C���FThis shit hist this sit									�폜�������P��F	this													���ʁFthis   this
																																																																																								shit   shit
																																																																																								hist   hist
																																																																																								sit   sit


�֐��̐���
�R�s�[������������̃A�h���X�������Ƃ��āA�V���ȃ�������\0�����m�ۂ������Ɏw�肵���������
�R�s�[���Ă��̃A�h���X��Ԃ��֐�

�����F�R�s�[������������̃A�h���X
�߂�l�F�R�s�[����������̃A�h���X

*/
char	*create_string(char	*key)
{
	char	*p,*moziretu;																													//p:�R�s�[�����̃A�h���X�������ϐ�
																																					//	moziretu:buff�̕������p�ɃR�s�[�����������̃A�h���X�������ϐ�
	int	length;																															//�R�s�[������������i\0���܂ށj�̒�����������ϐ�
															
																																					//			printf("%s   ",buff);		//create_string��case1�ɂ����Ďg�p

	length=strlen(key)+1;																									//strlen(buff)�ŃR�s�[������������̒��������߂�i\0���܂܂Ȃ�)�A+1��\0
	p=malloc(length);
	moziretu=strcpy(p,key);																					//buff�̕������p�̏ꏊ�ɃR�s�[
																																			//printf("%s\n",moziretu);						//create_string��case1�ɂ����Ďg�p
	return	moziretu;
}



/*
�e�X�g									�R�����g�ɂ���悤��printf�𗘗p
case	1
�t�@�C���F	This shit hist this sit									�폜�������P��F	this										���ʁFthis   7103000
																																																																																								this   4350752


�֐��̐���
�T�������P��̃A�h���X�ƒT�������P��̃n�b�V���l�ɑΉ�����hashtable�̃A�h���X�������Ƃ�
���X�g�̂Ȃ�����T�������P���T���A�Y������P�ꂪ����Z���̃A�h���X��Ԃ��֐��B

����1�F�T�������P��̃A�h���X
����2�F�T�������P��̃n�b�V���l�ɑΉ�����hashtable�̃A�h���X
�߂�l�F�Y������P�ꂪ����Z���̃A�h���X
*/
struct	item	*search_item(char	*key,struct	item	*p)
{
	int	hantei;	

	while(p!=0)
	{
		hantei=strcmp(p->word,key);																				//p���w�����X�g��word��key�Ɠ���������
																																													/*
																																														if(hantei==0)								//search_item��case1�ɂ����Ďg�p
																																														{
																																																	printf("%s   ",p->word);	
																																																	printf("%d\n",p);		
																																																	printf("%s   ",key);	
																																																	printf("%d\n",key);		
																																														}				
																																												*/

		if(hantei==0)		return	p;																							//�������̂ł��̃��X�g�̃A�h���X��Ԃ�
		p=p->next;
	}

	return	0;											//�����炸�ɍŌ�̃��X�g�ɂ����̂�0��Ԃ�
}


/*
�e�X�g		�R�����g�ɂ���悤��printf("%d",key)�A	printf("���v%d  ",hashval)��p��
case1	
�t�@�C��:adk			����:97  100  107  ���v304

case2
�t�@�C��:ADK			����:97  100  107		���v304

case3
�t�@�C��:this			����:116  104  105  115  ���v440

case4
�t�@�C��:htsi			����:104  116  115  105  ���v440

�֐��̐���
��������󂯎��啶�����������ɒ������̃n�b�V���l��Ԃ��֐��i�����256�̗]��j

�����F�n�b�V���l�𒲂ׂ���������
�߂�l�F�����ł��镶����̃n�b�V���l
*/
int	hash	(char	*key)
{
	int	hashval,hashti;				
													
	
	hashval=0;

	while(*key!='\0')
	{
		if((65<=*key)&&(*key<=90))						//65<=�啶��<=90
			*key=*key+32;																					//�������ɂȂ���
																													//printf("%d  ",*key);
		hashval=hashval+*key;														
		key++;
	}

	hashti=hashval%256;																			
	return	hashti;
}


/*
�֐��̐���
�\���̂̒P��ɂ�����v�f��\0�̎��͂��̃Z���͏o�͂��Ȃ����A����ȊO�̂Ƃ��̓Z���̂Ȃ��ɂ���P���
count���o�͂���֐��B

����:�Ȃ�
�߂�l�F�Ȃ�
*/
void	dump_ht(void)
{
	int	t;												//�J�E���^�[�ϐ�

	for(t=0;t<256;t++)
	{
		if(hashtable[t]!=0)														//�\���̂̒P��ɂ�����v�f��\0�̎��͂��̃Z���͏o�͂��Ȃ�
			print_list(hashtable[t]);
	}
}


/*
�e�X�g						�R�����g�ɂ���悤��printf�𗘗p
case	1
�t�@�C���FThis shit hist this sit																						���ʁF1,2

case	2
�t�@�C���FThis shit hist this sit							�폜�������P��Fthis														���ʁFthis
																																																																																						this
																																																																																						shit
																																																																																						shit
																																																																																						hist
																																																																																						hist
																																																																																						sit
																																																																																						sit
		

�֐��̐���
�o�^������������������Ƃ��A�n�b�V���l���Փ˂����Ƃ��ɂ��̒P������邽�߂̃Z����create_item���g���ĐV�������ɍ��A
�Փ˂��Ȃ��Ƃ��́A���̃Z����count���P���₷�֐��B

�����F�o�^������������
�߂�l�F�Ȃ�
*/
void	chainhash	(char	*key)
{
	int	hashti;
	struct	item	*list,*p;																																	//list:���X�g�̐擪�̃A�h���X�������邽�߂̕ϐ�
																																														//p:�Y������P�ꂪ����Z���̃A�h���X�isearch_item�̖߂�l�j
	hashti=hash(buff);
	list=hashtable[hashti];																																//���X�g�̐擪�̃A�h���X���w��
	p=search_item(key,list);

	if(p!=0)																																															//�����̒P��Ȃ̂�count�𑝂₷
		p->count++;																																												//	chainhash��case1�ɂ�����this�̃J�E���^���o��
	
	else
		hashtable[hashti]=create_item(key,list);					//list���w����͍ŏ�0���w���Ă���̂ŏꍇ�����̕K�v�͖���
		
																																																		/*																																																		
																																																			else																											//chainhash��case2�ɂ����Ďg�p
																																																			{	hashtable[hashti]=create_item(key,list);					
																																																						printf("%s\n",hashtable[hashti]->word);
																																																						printf("%s\n",key);
																																																			}	
																																																		*/	
}


/*
�e�X�g			�R�����g�ɂ���悤��printf("%s\n",p->word)�Aprintf("%d\n",p)��p��
case	1
�t�@�C���FThis shit hist this sit			�폜�������P��F	hist																	���ʁFhist
																																																																																							shit
case	2
�t�@�C���FThis shit hist this sit					�폜�������P��F	this																	���ʁFthis

�֐��̐���
�폜�������P��̃A�h���X�ƃ��X�g�̐擪�̃A�h���X�������Ƃ��A�ړI�̒P�ꂪ����Z���̃A�h���X��p�Ƃ���ƁA
p�̑O�̃Z����next�̎w�����p�̎��̃Z���ɂ��Ap���w���Z������ɂ��ĒP����폜�������Ƃ̃��X�g�̐擪��
�Z���̃A�h���X��Ԃ��֐��B


����1�F�폜�������P��̃A�h���X
����2�F���X�g�̐擪�̃Z���̃A�h���X�ihashtable[hashti]�͎w���A�h���X�j
�߂�l�F�ړI�̒P����폜�������Ƃ̃��X�g�̐擪�̃Z���̃A�h���X
*/
struct	item	*delete_item(char	*key,struct	item	*p)
{
	struct	item	*p_back,*p_head;																		//p_back:p->back���w���P�O�̃Z���̃A�h���X��ۑ����邽�߂̕ϐ�
																																									//p_head:�ړI�̒P����폜�������Ƃ̃��X�g�̐擪�̃Z���̃A�h���X
																																								
	p_head=p;

	if(p==0)		return	p_head;
	
	if(strcmp(p->word,key)==0)																//�폜�������P��ƃZ���̒��̒P�ꂪ��v�����Ƃ�
	{
																																							//	printf("%s\n",p->word);				//delete_item��case1�ɗ��p
		p_head=p->next;																														//���X�g�̐擪�̃Z�����폜����̂ŁA2�Ԗڂ̃Z�����擪�ƂȂ�
		free(p);																																	//�폜�����P�ꂪ����Z���̃f�[�^����ɂ���
																																							//	printf("%s\n",p_head->word);																//delete_item��case1�ɗ��p

		return	p_head;																													//���X�g�̐擪��Ԃ�
	}
		
		
	p_head=p;																																							//���X�g�̐擪�̃Z�����폜����̂ŁA1�Ԗڂ̃Z�����擪�ƂȂ�
		
	while(p->next!=0)																																			//���ڂ��Ă���Z�������X�g�̍Ōザ��Ȃ��Ƃ�
	{				
		p_back=p;																																						//p���w���Z���̂P�O�̃Z�����g�������̂ł̃A�h���X��ۑ�
																																							
		p=p->next;																																					//���̃Z������ɍl����
		
		if(strcmp(p->word,key)==0)																			//�폜�������P��ƃZ���̒��̒P�ꂪ��v�����ꍇ
		{
																																										//printf("%s\n",p->word);								//delete_item��case2�ɗ��p			
																																											
			p_back->next=p->next;																							//�폜�������P�ꂪ����Z�����Ƃ΂��ăZ�����q��
			free(p);																																			//�폜�����P�ꂪ����Z���̃f�[�^����ɂ���
			break;
		}
	}
			
	return	p_head;																									//���X�g�̐擪��Ԃ�
}
	



	




