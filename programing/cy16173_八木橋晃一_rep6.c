/*
CY16173 ���؋��W��	�쐬���F2017�N5��25��	�ۑ�V

�e�X�g





�֐��̐���
���C���֐��̂Ȃ��ɏ�����Ă��镶����ibuff�j�ɑ΂��Ĉȉ��̑�����s���֐��B
�ŏ��̓��͂̑�����d�Ɠ��͂���ƍ폜�������������̓��͂�������A��������͂���Ɠ����琔����
���������폜���ꂽ�����񂪏o�͂����B����ōŏ��̓��͂̑�����i�Ɠ��͂���ƁA�}��������������
�̓��͂������ꕶ�������͂���Ƃ��̕����񂪌��X�̕�����̐擪�ɑ}�������B


�e�X�g
�폜�̎�
case1:
���́Fijeijdofieofjopjd	,6				���ʁFofieofjopjd

case2:
���́Fabcdef,0						���ʁFabcdef

case3:
���́Fabcdef,1									���ʁFbcdef

case4:
���́Fabcdef,5								���ʁFf

case5:
���́F	abcdef,6							���ʁF�i�����o�͂��ꂸ�j

case6:
���́F	abcdef,7							���ʁF�i���ɐ����̓��͂��s����


�}���̎�
case1:
���́Fijeijdofieofjopjd,iojfiowfi								���ʁFiojfiowfiijeijdofieofjopjd

case2:
���́Fa,whduwqh							���ʁFwhduwqha

case3:
���́Fabcdef,123								���ʁF123abcdef

case4:
���́Fabcdef,12 3								���ʁF12abcdef

case5:
���́Fabc def	,123					���ʁF123abc def

case6:
���́F	abcdef	,����						���ʁF����abcdef

case7:
���́F	����	,����						���ʁF��������


*/

#include<stdio.h>

int	length(char	*p);																																//�v���g�^�C�v�錾�A������̕������𐔂��Ă��̕�������Ԃ��֐�
void	copy(char	*p_to,char	*p_from);						/*�v���g�^�C�v�錾�A�����������E�ɂ���ăR�s�[������A
																																												���̕��������̏ォ��R�s�[����֐�*/


int	main	(void)
{
	char	buff[100]="����";							//������s��������̐錾
	char	in[100];																									//�}������������������邽�߂̔���錾
	char	*p,which,c;																								/*p:�|�C���^�[,which:���͎҂�d(�폜)�Ai(�}��)�̂ǂ����I�񂾂����肷�邽�߂̕ϐ�
																																		c:�}���̍ۂ̍Ō��\0�ƌ������邽�߂ɑ�����s��������̍ŏ��̕�����ۑ�����ϐ�*/


	int	count,count_in,n;																	/*	count:���삷�镶����i�폜�܂��͑}������镶����j�̕�������ۑ�����ϐ�,
																															count_in:�}�����镶����̕�������ۑ�����ϐ�,n:�폜���镶������ۑ�����ϐ�*/
	
	while(1)
	{
		printf("�������폜�������ꍇ��d���A�}���������ꍇ��i����͂��Ă��������B\n");
		scanf("%c",&which);
		if((which=='d')||(which=='i'))				break;
		printf("�����ȓ��͂ł��B\n");																		
	}

	p=buff;																																//buff�̃A�h���X��p�ɑ��		
	count=length(buff);																											//���삷�镶����̕�������ۑ�
	
	if(which=='d')																													//������ɑ΂��č폜���s���Ƃ�
	{
		printf("�폜����������������͂��Ă��������B\n");
		scanf("%d",&n);
	
		while(1)																															//buff�̕�������葽���������폜���Ȃ����A�܂��͕��̒l�����͂���Ă��Ȃ����̔���
		{
			if(0<=n&&n<=count)	break;										//���͂��ꂽ�����񂪐���Ȃ�break
			scanf("%d",&n);																											//���͂��ꂽ�����񂪈ُ�̏ꍇ�ēx���͂𑣂�
		}
	
		p=p+n;																														//p�̃A�h���X�����炷
		copy(buff,p);																											//copy�̂P�ɑΉ��B���炵������������Ƃ̕�����ɏ㏑��
	}	


	if(which=='i')																										//������ɑ΂��đ}�����s���Ƃ�
	{
		printf("���͂��������������͂��Ă��������B\n");
		scanf("%s",in);
		count_in=length(in);										//�}�����镶����̕�������ۑ�
		c=*p;																			//������s��������̍ŏ��̕�����ۑ�
		p=p+count_in;																//�}�����镶�����̕�����p�̃A�h���X�����炷
		copy(p,buff);																/*copy��2�ɑΉ��B�}�����镶�����̃X�y�[�X��O�̕����ɍ��B
																									�����܂ł��炵�ĕ�������R�s�[���Ă���̂ŃX�y�[�X���󗓂ł͂Ȃ�*/
		
		copy(buff,in);														//copy��3�ɑΉ��B���삷�镶����̖`���ɑ}�����镶������㏑���i\0���܂ށj
		*p=c;																		/*�}������������ɂ����\0�ɏ㏑�����ꂽ�����ɑ΂��A
																							�ۑ����Ă������}�����镶����̓������ŏ㏑��*/
	}

	printf("%s",buff);														//�ŏI�I��������o��

	return	0;
}


/*
�֐��̐���
�����i������̃A�h���X�j���w��������̕������𐔂��āA���̒l��Ԃ��֐�

�����F��������m�肽��������̃A�h���X
�߂�l�F�����̃A�h���X�͎w��������̕�����

�e�X�g
�֐��̒��Ɏ����ʂ��printf��count�̒l���o��(length�P�̂ōs����)

case1:
���́Fd								���ʁF1

case2:
���́Ffofkjf						���ʁF6

case3:
���́Fjf1k3ok						���ʁF7

*/
int	length(char	*p)
{
	int	count;									//���������J�E���g����J�E���^�[�ϐ�
	count=0;	

	while(1)
	{
		count++;
		p++;
		if(*p=='\0')	break;
	}

	//printf("%d",count);

	return	count;
}




/*
�֐��̐���
�R�s�[������������𑼂̕�����ɃR�s�[���ď㏑������֐�

�����P�F�R�s�[����鑤�̕�����̃A�h���X
�����Q�F�R�s�[���鑤�̕�����̃A�h���X
�߂�l�F�Ȃ�


�e�X�g
�֐��̃R�����g�ɂ���Ƃ���ŃA�h���X����ԍ��ɐݒ肵p_from��printf�ŏo�͂����B


1�ɑ΂���e�X�g
case1:
�����Fabcdef�Acdef						���ʁFcdef

case2:
�����F123456�A456				���ʁF456



2�ɑ΂���e�X�g
case1:
���́Fabcdef�i2�����}�����j							���ʁFababcdef

case2:
���́F123456�i3�����}�����j					���ʁF123123456



3�ɑ΂���e�X�g
case1:
���́Fababcdef�i12�}�����j							���ʁF12(\0�łƂ܂邽��)

case2:
���́F123123456�iabc�}�����j					���ʁFabc(\0�łƂ܂邽��)


*/




void	copy(char	*p_to,char	*p_from)
{
	
	int	i,t,count;		/*i��2��ڂ�copy�̌Ăяo���ɑ΂��đ}���ɑΉ����镔���ȊO�������Ȃ��悤�ɂ��邽�߂̃J�E���^�[�ϐ�
														t�̓J�E���^�[�ϐ��Acount�͕�������ۑ�����ϐ�*/
	i=0;
	t=0;

	if((p_to<=p_from)&&(i==0))						//1,�E���獶�ɕ������R�s�[����Ƃ�(�폜����Ƃ�)
	{
		while(1)
		{
			*p_to=*p_from;
			if(*p_from=='\0')	break;							
			p_from++;
			p_to++;		
		}
		printf("%s\n",p_to);													//1�̂Ƃ��̃e�X�g
	}

	if((p_from<p_to)&&(i==0))									//2,������E�ɕ������R�s�[����Ƃ�(�}���̂Ƃ��ۂɃX�y�[�X�����Ƃ�)
	{
		count=length(p_from);	
		p_from=p_from+count;							//���̂Ƃ�*p_from='\0'
		p_to=p_to+count;

		while(1)
		{
			*p_to=*p_from;
			if(t==count)	break;
			t++;														
			p_from--;
			p_to--;
		}

																																											//2�̂Ƃ��̃e�X�g
		i=i+1;
	}
	
	if(i==1)					//3,�����}������
	{
		while(1)
		{
			*p_to=*p_from;
			if(*p_from=='\0')	break;													//\0���R�s�[���邽�߂��̈ʒu
			p_from--;
			p_to--;
		}
																																		//3�̂Ƃ��̃e�X�g
	}	
}

