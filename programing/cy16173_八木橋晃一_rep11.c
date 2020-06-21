#include<stdio.h>
#include<stdlib.h>
#include<time.h>
/*
CY16173	���؋��W��	�쐬���F2017�N7��6��		�ۑ�5-1,5-2

�e�X�g
case1
�f�[�^�F<<5,10,20>,15,<-,35,30>>
�}���F�}���s��
�[���F�Ȃ�
���ʁF5
		10
		20
		incorect	order

case2
�f�[�^�F<<5,10,15>,20,<-,30,35>>
�}���F30
�[���F0
���ʁF<<5,10,15>,20,<-,30,35>>

case3
�f�[�^�F<<5,10,15>,20,<-,30,35>>
�}���F1
�[���F3
���ʁF<<<1,5,->,10,15>,20,<-,30,35>>

case4
�f�[�^�F<<5,10,15>,20,<-,30,35>>
�}���F40
�[���F3
���ʁF<<5,10,15>,20,<-,30,<-,35,40>>>

case5
�f�[�^�F<<5,10,15>,20,<-,30,35>>
�}���F0
�[���F3
���ʁF<<<0,5,->,10,15>,20,<-,30,35>>

case6
�f�[�^�F0
�}���F22
�[���F1
���ʁF<-,0,22>

case8
�f�[�^�F-
�}���F32
�[���F0
���ʁF32

case9(����)
�f�[�^�F0
���ʁF
key=13,depth=1
<-,0,13>
key=3,depth=2
<-,0,<3,13,->>
key=43,depth=2
<-,0,<3,13,43>>
key=75,depth=3
<-,0,<3,13,<-,43,75>>>
key=31,depth=3
<-,0,<3,13,<31,43,75>>>
key=98,depth=4
<-,0,<3,13,<31,43,<-,75,98>>>>
key=43,depth=0
<-,0,<3,13,<31,43,<-,75,98>>>>
key=28,depth=4
<-,0,<3,13,<<28,31,->,43,<-,75,98>>>>
key=7,depth=3
<-,0,<<-,3,7>,13,<<28,31,->,43,<-,75,98>>>>
key=93,depth=5
<-,0,<<-,3,7>,13,<<28,31,->,43,<-,75,<93,98,->>>>>


case10(����)
�f�[�^�F100000
���ʁF
key=96,depth=1
<96,100000,->
key=90,depth=2
<<90,96,->,100000,->
key=29,depth=3
<<<29,90,->,96,->,100000,->
key=33,depth=4
<<<<-,29,33>,90,->,96,->,100000,->
key=91,depth=3
<<<<-,29,33>,90,91>,96,->,100000,->
key=87,depth=5
<<<<-,29,<-,33,87>>,90,91>,96,->,100000,->
key=0,depth=4
<<<<0,29,<-,33,87>>,90,91>,96,->,100000,->
key=40,depth=6
<<<<0,29,<-,33,<40,87,->>>,90,91>,96,->,100000,->
key=84,depth=7
<<<<0,29,<-,33,<<-,40,84>,87,->>>,90,91>,96,->,100000,->
key=49,depth=8
<<<<0,29,<-,33,<<-,40,<49,84,->>,87,->>>,90,91>,96,->,100000,->

case11(����)
�f�[�^�F<<5,10,15>,20,<-,30,35>>
���ʁF
key=17,depth=3
<<5,10,<-,15,17>>,20,<-,30,35>>
key=65,depth=3
<<5,10,<-,15,17>>,20,<-,30,<-,35,65>>>
key=43,depth=4
<<5,10,<-,15,17>>,20,<-,30,<-,35,<43,65,->>>>
key=40,depth=5
<<5,10,<-,15,17>>,20,<-,30,<-,35,<<40,43,->,65,->>>>
key=14,depth=3
<<5,10,<14,15,17>>,20,<-,30,<-,35,<<40,43,->,65,->>>>
key=36,depth=6
<<5,10,<14,15,17>>,20,<-,30,<-,35,<<<36,40,->,43,->,65,->>>>
key=89,depth=4
<<5,10,<14,15,17>>,20,<-,30,<-,35,<<<36,40,->,43,->,65,89>>>>
key=3,depth=3
<<<3,5,->,10,<14,15,17>>,20,<-,30,<-,35,<<<36,40,->,43,->,65,89>>>>
key=89,depth=0
<<<3,5,->,10,<14,15,17>>,20,<-,30,<-,35,<<<36,40,->,43,->,65,89>>>>
key=47,depth=5
<<<3,5,->,10,<14,15,17>>,20,<-,30,<-,35,<<<36,40,->,43,47>,65,89>>>>


case12
�f�[�^�F<<a,b,c>,d,<-,e,f>>
���ʁF
�G���[�ł�1�B
�G���[�ł�2�B
�G���[�ł�2�B




�֐��̐���
�񕪒T���؂̃f�[�^����͂��A�}���������l����͂���Ɛ������ꏊ�ɂ��̒l������
�ߓ_��V�������A�ł����������񕪒T���؂�\������֐��B
�������A������񕪒T���؂����͂��ꂽ�Ƃ��͑}�����s�킸�������������_�ŁA
�G���[���b�Z�[�W��\�����I������֐��B
*/
int	reserve=-1;									//check_node�őO�̒l��ۑ�����ϐ�
															//���蓾�Ȃ����̒l�������l�Ƃ��đ���Ƃ��Ă���

struct	node{
	int	value;
	struct	node	*left;
	struct	node	*right;
};
char	buff[100];
char	*nextch=buff;


struct	node*	create_node(struct	node	*left,int	value,struct	node	*right);								//�v���g�^�C�v�錾
void	print_tree(struct	node	*p);
struct	node*	read_tree(void);
int	read_number(void);
int	search_bt(struct	node	*nodep,int	key);
int	check_node(struct	node	*nodep);
int	check_bt(struct	node	*nodep);
int	insert_bt(struct	node	*nodep,struct	node	**ptr,int	key,int	depth);


int	main(void)										
{
	struct	node*	nodep;
	int	key,r,i,depth=0;															//key:�}���������l
																									//r:�����_���̒l��������ϐ�
																									//i:�J�E���^�[�ϐ�
																									//depth:�}�������ߓ_�̐[����������ϐ�



	srand(time(0));			//�֐�rand���g�����߂̏���

	printf("�f�[�^���͂��Ă��������B\n");
	scanf("%s",&buff);
	nodep=read_tree();
	
	if(check_bt(nodep)==0)	return	0;								//������񕪒T���؂̂Ƃ��͓r���ŏI��


	for(i=0;i<10;i++)
	{
		r=rand()%100;		//0?100�܂ł̗����������r�ɑ������
									//���������֐�rand()�̌��ʂ͂ƂĂ��傫��
									//100�̗]����Ƃ�Ǝ荠�Ȓl�ɂȂ�
		depth=0;
		depth=insert_bt(nodep,&nodep,r,depth);
		printf("key=%d,depth=%d\n",r,depth);
		print_tree(nodep);
		printf("\n");
	}

	/*		
	printf("�}��������������͂��Ă��������B\n");
	scanf("%d",&key);																											//�}�������l��ǂݍ���
									
	depth=insert_bt(nodep,&nodep,key,depth);					
	
	printf("�[��:%d",depth);
									
												
	printf("\n");
	print_tree(nodep);
	*/

	return	0;
}


struct	node*	create_node(struct	node	*left,int	value,struct	node	*right)
{
	struct	node		*new_node,*old_node;																																	
																																																																																																																																							
	new_node=(struct	node*)malloc(sizeof(struct	node));					
	new_node->value=value;																																																											
	new_node->left=left;						
	new_node->right=right;																									
	old_node=new_node;																																																													
	new_node++;
																																																														
	return	old_node;		
}


void	print_tree(struct	node	*p)
{
	if(p==0)		printf("-");

	//p=\0���ƃG���[�ɂȂ��Ă��܂������̂Ƃ��͏��if�őΉ�
	else	if((p->left==0)&&(p->right==0))				printf("%d",p->value);				

	else														//p(��,left�܂���right)��\0�ȊO���w���Ƃ�
	{
		printf("<");
		print_tree(p->left);							
		printf(",%d,",p->value);
		print_tree(p->right);						
		printf(">");
	}	
}


int	read_number(void)
{
	int	sum=0;

	while(('0'<=*nextch)&&(*nextch<='9'))
	{
		sum=sum*10+(*nextch-'0');
		nextch++;
	}

	return	sum;
}


struct	node*	read_tree(void)
{
	int	number;
	struct	node	*left,*right;

	if(*nextch=='-')
	{
		nextch++;
		return	0;
	}
		
	//left��right��\0���w���Ƃ���value
	else	if(('0'<=*nextch)&&(*nextch<='9'))						return	create_node(0,read_number(),0);	
	
	else
	{
		if(*nextch=='<')
		{
			nextch++;
			left=read_tree();
		}
	
		else
		{
			printf("�G���[�ł�1�B\n");
			return	0;
		}
		
		if(*nextch==',')
		{
			nextch++;
			number=read_number();									//value
		}

		else
		{
			printf("�G���[�ł�2�B\n");
			return	0;
		}

		if(*nextch==',')
		{
			nextch++;																				//>���w��
			right=read_tree();						
		}
	
		else
		{
			printf("�G���[�ł�3�B\n");
			return	0;
		}

		if(*nextch=='>')
		{
			nextch++;
			return	create_node(left,number,right);				
		}
			
		else
		{
			printf("�G���[�ł�4�B\n");
			return	0;
		}
	}

	printf("�G���[�ł�5�B\n");
	return	0;		
}


/*
�֐��̐���
���͂��ꂽ�f�[�^�̒��ɒT���Ă���l������΂P��Ԃ��A
������΂O��Ԃ��֐��B�܂��T���ߒ��ł͎�����Ԃ�
�ċA�֐��B

�����P�F���܂��͗t�ւ̃|�C���^
�����Q�F�T�������l
�߂�l�P�F���͂��ꂽ�f�[�^�̒��ɒT���Ă���l������΂P
�߂�l�Q�F���͂��ꂽ�f�[�^�̒��ɒT���Ă���l������
				�܂��͈�ԉ��܂ōs�����Ƃ��i\0���w���Ă��鎞�j�O
�߂�l�R�F�T���ߒ��ł͎�����Ԃ�
*/
int	search_bt(struct	node	*nodep,int	key)
{
	if(nodep==0)	return	0;																													//	�T���Ă���l���f�[�^�̒��ɂȂ�
	else	if(nodep->value==key)	return	1;				//	�T���Ă���l���f�[�^�̒��ɂ���
	else	if(key<nodep->value)																						//�T���Ă���l�ƃ|�C���^���w���Z����value�̑召���r
	{
		return	search_bt(nodep->left,key);
	}
	else{
		return	search_bt(nodep->right,key);
	}
}



/*
�e�X�g
case1
�f�[�^�F<<5,10,20>,15,<-,35,30>>

���ʁFnodep->value��reserve�̒l���o��
����5,�P�O-1
����10,�P�O5
����20,�P�O
����15,�P�O20
incorect	order


�֐��̐���
�������񕪒T���؂��ǂ������肷��֐��B�������ꍇ�͂P��Ԃ��A
�������Ȃ��ꍇ�͂O��Ԃ��B

�����P�F���܂��͗t�ւ̃|�C���^
�߂�l�P�F�������񕪒T���؂̂Ƃ��͂P
�߂�l�Q�F������񕪒T���؂̂Ƃ��͂O
*/
int	check_node(struct	node	*nodep)
{
	//printf("����%d,�P�O%d\n",nodep->value,reserve);
	//check_node�̃e�X�g�Ŏg�p

	if(nodep->value<reserve)					//�P�O��check_node�ŕ\�������l�ƌ��݂̒l���r
	{
		printf("\nincorect	order");
		return	0;
	}		

	printf("%d\n",nodep->value);
	reserve=nodep->value;											//�\�������l��ۑ�
	return	1;
}



/*
�e�X�g
case1
�f�[�^�F<<5,10,20>,15,<-,35,30>>
���ʁF5
		10
		20
		incorect	order



�֐��̐���
�������񕪒T���؂��ǂ�����check_node���g���Ĕ��肷��֐��B

�����P�F���܂��͗t�ւ̃|�C���^
�߂�l�P�F��ԉ��܂ōs�����Ƃ��i\0���w���Ă��鎞�j
				�܂���left��right�̂ǂ�����������񕪒T���؂������Ƃ��P
�߂�l�Q�G��x�ł�������񕪒T���؂��������Ƃ��O��Ԃ�
*/
int	check_bt(struct	node	*nodep)
{
	if(nodep==0)	return	1;					//��ԉ��܂ōs�����Ƃ��i\0���w���Ă��鎞�j

	else
	{
		if(check_bt(nodep->left)==0)		return	0;					//��x�ł�������񕪒T���؂��������Ƃ�
		if(check_node(nodep)==0)	return	0;													//��x�ł�������񕪒T���؂��������Ƃ�
		if(check_bt(nodep->right)==0)		return	0;				//��x�ł�������񕪒T���؂��������Ƃ�
	}	
	return	1;				//left��right�̂ǂ�����������񕪒T���؂������Ƃ�
}


/*
�e�X�g
case1
�f�[�^�F<<5,10,15>,20,<-,30,35>>					
�}���F10
���ʁF<<5,10,15>,20,<-,30,35>>
�[���F0

case2
�f�[�^�F<<5,10,15>,20,<-,30,35>>		
�}���F0	
���ʁF<<<0,5,->,10,15>,20,<-,30,35>>
�[���F3

case3
�f�[�^�F-
�}���F32
���ʁF32
�[���F0

�֐��̐���
���͂����񕪒T���ɑ}�����s���������ɁA�����O�Ƃ���
�}�������ߓ_�ւ̐[���𑪒肵�[���̒l��Ԃ��֐��B
�}�����Ȃ����������͂O��Ԃ��B

�����P�F���܂��͗t�ւ̃|�C���^
�����Q�Fnode���w���|�C���^�ւ̃|�C���^
�����R�F�}���������l
�����S�F�����̏�Ԃ̐[���i�ŏ��͂O�j
�߂�l�P�F�}�������ߓ_�̐[��
�߂�l�Q�F�}�����s���Ȃ������ۂO
*/
int	insert_bt(struct	node	*nodep,struct	node	**ptr,int	key,int	depth)
{

	if(nodep==0)					//�|�C���^��\0�������Ƃ�
	{
		*ptr=create_node(0,key,0);						//�V�����ߓ_�����i�}���������l��}���j
		return	depth;
	}
	
	else	if(key==nodep->value)		return	0;							//�}���������l�����ɑ��݂���Ƃ�

	
	else	if(key<nodep->value)
	{
		ptr=&(nodep->left);
		depth++;																																							//�ċA����̂�depth�̒l�𑝂₷
		depth=insert_bt(nodep->left,ptr,key,depth);
	}

	else
	{
		ptr=&(nodep->right);
		depth++;																																												//�ċA����̂�depth�̒l�𑝂₷
		depth=insert_bt(nodep->right,ptr,key,depth);
	}
	return	depth;
}




