#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
CY16173 ���؋��W�� �쐬���F2017�N7��27�� �ۑ�D(�g���Ȃ�)

�e�X�g
case1
�t�@�C���Fan arround and apple annaunce a
�T���P��Fa
���ʁFarround
      aunce
	  and
      annaunce
      apple
      an
      a

case2
�t�@�C���Fan arround and apple annaunce a
�T���P��Fn
���ʁFnce
      nd
      nnaunce
      nd
      n
      naunce

case3
�t�@�C���Fbbbbbbbbbb
�T���P��FB
���ʁF�����o�͂���Ȃ�

case4
�t�@�C���Fbbbbbbbbbb
�T���P��Fb
���ʁFbbbbb
      bbbbbbbb
      bbbbbbbbb
      bbbbbbbbbb
      bbbbbb
      bbbbbbb
      b
      bbb
      bbbb
      bb

case5
�t�@�C���FBBBBBBBBBB
�T���P��FB
���ʁFBBBBB
      BBBBBBBB
      BBBBBBBBB
      BBBBBBBBBB
      BBBBBB
      BBBBBBB
      B
      BBB
      BBBB
      BB

case6
�t�@�C���Fbbbbbbbbbb
�T���P��Fc
���ʁF�����o�͂���Ȃ�

case7
�t�@�C���F[EOF] a
�T���P��Fa
���ʁFa

case8
�t�@�C���F���݂��Ȃ��t�@�C��
�T���P��F
���ʁFcan	not	open


case9
�t�@�C���F��̃t�@�C��
�T���P��Fa
���ʁF�����o�͂���Ȃ�

�֐��̐���
�h�L�������g�̒��Ɏw�肵��������i�啶���A�������͋�ʂ���j������΁A���̕������
�܂ޕ����Ƃ���ȍ~�̕�������o�͂���֐��B
�T������������̓��͂ƒT���H�����������[�v�ɂȂ��Ă���
���߂��̊֐����I�����鎖�͂Ȃ��B
*/

char	*data[100000];
char	buff[100];
int	wordnum=0;					//wordnum:���בւ����s���P�ꂪ�����Ă���z��̔ԍ�

void	create_string(char	*key);
void	copyfile	(FILE	*is);
void	string_sort	(int	end);
void	swap	(int	k,int	l);
void	search_word(int	left,char	key[],int	right,int	length);


int	main		(void)
{
	int	length,i;					//�T�������P��̕�������������ϐ�
	char	key[30];				//�T�������P������z��
	FILE	*is;

	

	is=fopen("tom.txt","r");

	if(is==0)						//�Y������t�@�C�����Ȃ��ꍇ
	{
		printf("can	not	open\n");
		return	0;
	}

	copyfile(is);
	fclose(is);	


	
	while(1)
	{
		printf("�T�������P�����͂��Ă��������B   ");
		scanf("%s",key);
		length=strlen(key);							//�T�������P��̕�����
		search_word(0,key,wordnum-1,length);
		printf("\n");	
	}

	return	0;
}


/*
�e�X�g
case1
�t�@�C���Fabcdegf
���ʁFabcdegf	(copyfile���ŕ��ёւ������Ƃ�data[0?wordnum]���o��)
	  bcdegf
      cdegf
      degf
      egf
      gf
      f
      
�֐��̐���
�R�s�[������������̃A�h���X�������Ƃ��āA�V���ȃ�������\0�����m�ۂ�
�����Ɏw�肵����������R�s�[���A���̌�A�R�s�[�����P��i������j��
���̒P��̃T�t�B�N�X��S�č쐬�����̃A�h���X��Ԃ��֐��B

�����F�R�s�[������������
�߂�l�F�Ȃ�
*/
void	create_string(char	*key)
{
	char	*p;						//p:�R�s�[�����̃A�h���X�������ϐ�
	int	i;
									//	moziretu:buff�̕������p�ɃR�s�[�����������̃A�h���X�������ϐ�
	int	length;						//�R�s�[������������i\0���܂ށj�̒�����������ϐ�

	length=strlen(key)+1;			//strlen(buff)�ŃR�s�[������������̒��������߂�i\0���܂܂Ȃ�)�A+1��\0				
	p=malloc(length);
	strcpy(p,key);					//buff�̕������p�̏ꏊ�ɃR�s�[		
	data[wordnum]=p;

	for(i=0;i<length-2;i++)			//�k���͂����Ȃ��A���̒P��̑S�ẴT�t�B�N�X�̍쐬
	{
		wordnum++;
		p++;	
		data[wordnum]=p;
	}
	return	;
}


/*
�e�X�g
case1
�t�@�C���Fabcdegf
���ʁFabcdegf	�ibuff�̒��g�j

�֐��̐���
�����P���w���t�@�C���̕������啶���A�������̋�ʂ����A
�d���������ĂɎ������ɕ��בւ���֐��B

�����P�F�������ɕ��בւ������t�@�C���ւ̃|�C���^
�߂�l�F�Ȃ�
*/
void	copyfile	(FILE	*is)
{
	int	i;				//i:�J�E���^�[�ϐ�

	while(1)
	{
		if(fscanf(is,"%s",buff)==EOF)	break;	//�I���(EOF)��������break																		
		create_string	(buff);					//�e�ʂ��m��	
		wordnum++;	
	}

	
	string_sort(wordnum);						//�d���������Ď������ɕ��ёւ���

	return;
}


/*
�e�X�g
case1
�t�@�C���Fabcdegf
���ʁFabcdegf	(copyfile���ŕ��ёւ������Ƃ�data[0?wordnum-1]���o��)
	  bcdegf
      cdegf
      degf
      egf
      f
      gf

�֐��̐���
�啶���A�������̋�ʂ������d���������āA�ǂݍ��܂ꂽ�P���
�������ɕ��ёւ���i�|�C���^�̎w����������Ă���j�֐��B

�����F�ǂݍ��܂ꂽ�P�ꐔ
�߂�l�F�Ȃ�
*/
void	string_sort	(int	end)
{
	int	t,s,check;								//t,s:�J�E���^�[�ϐ�
												//check:for����swap���Ă��邩���m�F���邽�߂̕ϐ�

	for(end;1<end-1;end--)
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

		if(check==0)	return;					//swap���Ă��Ȃ�������I��

	}

	return;
}


/*
�e�X�g
case1
�t�@�C���Fabcdegf
���ʁFdata[k]=gf,data[l]=f��data[k]=f,data[l]=gf

�֐��̐���
�����ł����Ă����ԍ��̔��̒��g�����ւ���֐��B

�����P�F�����Q�̔��Ə��Ԃ����ւ��������̔ԍ�
�����Q�F�����P�̔��Ə��Ԃ����ւ��������̔ԍ�
�߂�l�F�Ȃ�
*/
void	swap	(int	k,int	l)
{
	char	*save;			//���Ԃ��������邽�߂Ɉꎞ�I�ɃA�h���X��ۑ����邽�߂̕ϐ�
	save=data[k];
	data[k]=data[l];
	data[l]=save;
	return;
}


/*
�e�X�g
main�Ɠ���

�֐��̐���
�����Ŏ����Ă���������ikey�j�Ɣ�r���A���̕�����Ŏn�܂�
�t�@�C�����̒P��ƃT�t�B�N�X���o�͂���֐��B

�����P�F�񕪖@�p�����ۂ̗̈�̍��[�̔z��̔ԍ�
�����Q�F�T������������
�����R�F�񕪖@�p�����ۂ̗̈�̉E�[�̔z��̔ԍ�
�����S�F�T������������̕������i���O���܂܂Ȃ��j
�߂�l�F�Ȃ�
*/
void	search_word(int	left,char	key[],int	right,int	length)
{
	int	middle;					//�񕪖@��p�����ꍇ�̒��Ԓl

	middle=(left+right)/2;
	
	if(left>right)	return;		//�񕪖@�̍��[�ƉE�[������ւ�����Ƃ��i��~�����j

	else						//�񕪖@�𑱍s
	{
		if(strncmp(key,data[middle],length)==0)		//��r���������񕪂�����
		{
			printf("%s\n",data[middle]);
			search_word(middle+1,key,right,length);
			search_word(left,key,middle-1,length);	
		}

		else	if(strncmp(key,data[middle],length)>0)	search_word(middle+1,key,right,length);	//�T���Ă镶���񂪉E���ɂ���

		else		search_word(left,key,middle-1,length);	//�T���Ă镶���񂪍����ɂ���
	
	}
}
