#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
CY16173 ���؋��W�� �쐬���F2017�N7��13�� �ۑ�5

�e�X�g
case1
�t�@�C���Fa a a a a a a a a a a a a
���ʁFa
case2
�t�@�C���Fa b c A B C
���ʁFa
	  b
      c

case3
�t�@�C���FA B C a b c 
���ʁFA
      B
      C

case4
�t�@�C���Fg f e d c b a 
���ʁFa
      b
      c
      d
      e
      f
      g

case5
�t�@�C���FCHAPTER I TOM No answer TOM 
          No answer  Whats gone with that
          boy I wonder You TOM No answer 
         The old lady pulled her spectacles down 
���ʁFanswer
      boy
      CHAPTER
      down
      gone
      her
      I
      lady
      No
      old
      pulled
      spectacles
      that
      The
      TOM
      Whats
      with
      wonder
      You

case6
�t�@�C���F�i����������Ă��Ȃ��j
���ʁF(null)

case7
�t�@�C���F(���݂��Ȃ��t�@�C��)
���ʁFcan not open

case8
�t�@�C���F���@���@���@���@��
���ʁF���@���@���@���@��

case9
�t�@�C���F�� �� �� �� ��
���ʁF��
      ��
      ��
      ��
      ��

case9
�t�@�C���F9 8 7 6 5 5 4 3 2 2 11 1
���ʁF1   (�����̏����ł͂Ȃ��������̂���)
      11
      2
      3
      4
      5
      6
      7
      8
      9


�֐��̐���
�����P���w���t�@�C���̕������啶���A�������̋�ʂ����A
�d�����������Ɏ������ɕ��בւ��A�����Q�̃t�@�C���ɂ���
���ʂ��������ފ֐��B
�����P�F�������ɕ��בւ������t�@�C���ւ̃|�C���^
�����Q�F�������ɕ��בւ������̂��������݂����t�@�C���ւ̃|�C���^
*/

char	*data[10000];
char	buff[100];

char	*create_string(char	*key);
void	copyfile	(FILE	*is,FILE	*os);
void	string_sort	(int	end);
void	swap	(int	k,int	l);
int uniq(int	wordnum);



int	main		(int	argc	,char	*argv[])
{
	FILE	*is,*os;
	
	is=fopen(argv[1],"r");

	if(is==0)									//�Y������t�@�C�����Ȃ��ꍇ
	{
		printf("can	not	open\n");
		return	0;
	}	
	
	os=fopen(argv[2],"w");
	

	if(os==0)									//�Y������t�@�C�����Ȃ��ꍇ
	{
		printf("can	not	open\n");
		return	0;
	}
	
	copyfile(is,os);
	fclose(is);
	fclose(os);
	
	return	0;
}




/*
�֐��̐���
�R�s�[������������̃A�h���X�������Ƃ��āA�V���ȃ�������\0�����m�ۂ������Ɏw�肵���������
�R�s�[���Ă��̃A�h���X��Ԃ��֐�

�����F�R�s�[������������̃A�h���X
�߂�l�F�R�s�[����������̃A�h���X
*/
char	*create_string(char	*key)
{
	char	*p,*moziretu;						//p:�R�s�[�����̃A�h���X�������ϐ�
	
												//	moziretu:buff�̕������p�ɃR�s�[�����������̃A�h���X�������ϐ�
	int	length;									//�R�s�[������������i\0���܂ށj�̒�����������ϐ�

	length=strlen(key)+1;						//strlen(buff)�ŃR�s�[������������̒��������߂�i\0���܂܂Ȃ�)�A+1��\0				
	p=malloc(length);
	moziretu=strcpy(p,key);						//buff�̕������p�̏ꏊ�ɃR�s�[		

	return	moziretu;
}


/*
�e�X�g
main�Ɠ���

�֐��̐���
�����P���w���t�@�C���̕������啶���A�������̋�ʂ����A
�d�����������Ɏ������ɕ��בւ��A�����Q�̃t�@�C���ɂ���
���ʂ��������ފ֐��B

�����P�F�������ɕ��בւ������t�@�C���ւ̃|�C���^
�����Q�F�������ɕ��בւ������̂��������݂����t�@�C���ւ̃|�C���^
�߂�l�F�Ȃ�
*/
void	copyfile	(FILE	*is,FILE	*os)
{
	int	wordnum,i;								//wordnum:���בւ����s���P�ꐔ��������ϐ�
												//i:�J�E���^�[�ϐ�
	wordnum=0;

	while(1)
	{
		if(fscanf(is,"%s",buff)==EOF)	break;	//�I���(EOF)��������break																		
		data[wordnum]=create_string	(buff);		//�e�ʂ��m��	
		wordnum++;	
	}
	
	string_sort(wordnum);						//�d���������Ď������ɕ��ёւ���
	wordnum=uniq(wordnum);						//�d�����������������ɕ��בւ���

	for(i=0;i<wordnum;i++)
		fprintf(os,"%s\n",data[i]);				//���ёւ������m��V����������t�@�C���ɏ�������

	return;
}


/*
�e�X�g
case1
�t�@�C���Fa b c d e g f
test=2
����:a b c d e f g

case2
�t�@�C���Fa A b B c C
����:a b c

�֐��̐���
�啶���A�������̋�ʂ������d���������āA�ǂݍ��܂ꂽ�P���
�������ɕ��ёւ���i�|�C���^�̎w����������Ă���j

�����F�ǂݍ��܂ꂽ�P�ꐔ
�߂�l�F�Ȃ�
*/
void	string_sort	(int	end)
{
	int	t,s,check;								//t,s:�J�E���^�[�ϐ�
												//check:for����swap���Ă��邩���m�F���邽�߂̕ϐ�
	//int	test=0;								//string_sort�̃e�X�g�Ŏg�p


	for(s=0;s<end-1;s++)
	{
		check=0;
		for(t=0;t<end-1;t++)
		{
			if(stricmp(data[t],data[t+1])>0)	//�������ɂȂ��Ă��Ȃ������ꍇ
			{
				check++;
				swap	(t,t+1);				//���Ԃ����ւ���
			}	
		}

		/*
		test++;								//string_sort�̃e�X�g�Ŏg�p
		if(check==0)	
		{
			printf("%d",test);
			return;
		}
		*/
					
		if(check==0)	return;						//swap���Ă��Ȃ�������I��

	}

	return;
}

/*
�e�X�g
case1
�t�@�C���Fabcdegf
���ʁFdata[k]=g,data[l]=f��data[k]=f,data[l]=g

�֐��̐���
�����ł����Ă����ԍ��̔��̒��g�����ւ���֐�

�����P�F�����Q�̔��Ə��Ԃ����ւ��������̔ԍ�
�����Q�F�����P�̔��Ə��Ԃ����ւ��������̔ԍ�
�߂�l�F�Ȃ�
*/
void	swap	(int	k,int	l)
{
	char	*save;								//���Ԃ��������邽�߂Ɉꎞ�I�ɃA�h���X��ۑ����邽�߂̕ϐ�
	save=data[k];
	data[k]=data[l];
	data[l]=save;
	return;
}

/*
�e�X�g
�t�@�C���Faaabbcc
���ʁFdata[1]=a��data[1]=b
	  data[2]=a��data[2]=c
	  wordnum=7,pre=3
�֐��̐���
�啶���A��������ʂ����ɏd���������Ȃ����������̒P�����������
�Ȃ�悤�ɕ��ёւ���i���̂悤�Ƀ|�C���^���q���Ȃ����j
���̌�P�ꐔ��Ԃ��֐��B

�����F�啶���A��������ʂ����ɏd�����������ۂ̒P�ꐔ
�߂�l�F�啶���A��������ʂ����ɏd���������Ȃ������ۂ̒P�ꐔ
*/

int uniq(int	wordnum)
{
	int	t,pre;									//t:�J�E���^�[�ϐ�
												//pre:��������ꏊ��ۑ�����J�E���^�[�ϐ�
	
	pre=0;

	for(t=0;t<wordnum-1;t++)					//�z����͂ݏo���Ȃ����߂�wordnum-1
	{
		if(stricmp(data[t],data[t+1])!=0)		//�������ɂȂ��Ă��Ȃ������ꍇ
		{
			pre++;
			data[pre]=data[t+1];				//�V�����ł��P����w��
		}
	}
	pre++;
	
	return	pre;
}
