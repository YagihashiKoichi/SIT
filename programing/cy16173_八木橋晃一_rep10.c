#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/*
CY16173	���؋��W��	�쐬���F2017�N6��22��	�ۑ�5
�e�X�g
case1
���́F<10,20,30>									���ʁF<10,20,30>

case2
���́F	<-,20,30>								���ʁF<-,20,30>

case3
���́F	<10,20,->								���ʁF<10,20,->

case4
���́F<-,20,->									���ʁF20(���[�Ɣ��f�����)

case5
���́F	20								���ʁF20

case6
���́F<10,20,<-,30,40>>									���ʁF<10,20,<-,30,40>>

case7
���́F<<40,10,50>,20,<30,60,70>>									���ʁF<<40,10,50>,20,<30,60,70>>

case8
���́F	<>								���ʁF�G���[�ł��B
																				�G���[�ł��B
case9
���́Fwjeiwqd							���ʁF�G���[�ł��B

case10
���́F-									���ʁF�����o�͂���Ȃ�

case11
���́F	<100,169,123>								���ʁF<100,169,123>

case12
���́F<-100,-169,-123>									���ʁF�G���[�ł��B

case13
���́F<100,-169,123>								���ʁF�G���[�ł��B

case14
���́F	<0,0,0>								���ʁF<0,0,0>

case15
���́F<-,-,->									���ʁF�G���[�ł��B

case16
���́F<10,20,30>,;w,dwqd					���ʁF<10,20,30>

case17
���́F10>									���ʁF10

case18
���́F	>10,20,30<								���ʁF�G���[�ł��B


�֐��̐���
���͂��ꂽ�����񂩂�񕪖؂�����A������񕪖؂��當����ɂȂ���
�o�͂���֐��B�������A�����ȓ��͂ɂ̓G���[���b�Z�[�W���o�͂����B
*/

struct	node{											//�\���̂̐錾
	int	value;
	struct	node	*left;
	struct	node	*right;
};
char	buff[100];										//���͂��ꂽ����������[����z��
char	*nextch=buff;									//�z��̐擪���w��


struct	node*	create_node(struct	node	*left,int	value,struct	node	*right);
void	print_tree(struct	node	*p);
struct	node*	read_tree(void);
int	read_number(void);

int	main(void)
{
	struct	node*	root;							//reed_tree�̕Ԃ�l�������邽�߂̕ϐ�
																		//	int	sum;		read_number�̃e�X�g�Ɏg�p
																	//print_tree(0);			print_tree�̃e�X�g�Ŏg�p

	printf("�f�[�^����͂��Ă��������B\n");
	scanf("%s",&buff);
	root=read_tree();
	if(root!=0)	print_tree(root);

	/*	read_number�̃e�X�g�Ɏg�p
	sum=read_number();
	printf("sun=%d\n",sum);
	*/

	return	0;
}


/*
�e�X�g		�R�����g�ɂ���悤��pritf��p��
case1
���́F<10,20,30>									���ʁFleft=0		value=10	right=0
																								new_node->left=0			new_node->value=10		new_node->right=0
																								left=0		value=30	right=0
																								new_node->left=0			new_node->value=30		new_node->right=0
																								left=7627576		value=20	right=7627600
																								new_node->left=7627576			new_node->value=20		new_node->right=7627600



�֐��̐���
�V�������ߓ_�̃����o�[�ɑ���������l�������Ƃ��A���̕��̗e�ʂ��m�ۂ���
�V����������ߓ_�̃����o�[�ɂ��ꂼ��������B���̌�V����������ߓ_�ւ�
�|�C���^��Ԃ��֐��B

����1�F�V�������ߓ_�̃����o�[left�ɑ������A�h���X
����2:�V�������ߓ_�̃����o�[value�ɑ������l
����3:�V�������ߓ_�̃����o�[right�ɑ������A�h���X
�߂�l�F�V����������ߓ_�ւ̃|�C���^
*/
struct	node*	create_node(struct	node	*left,int	value,struct	node	*right)
{
	struct	node		*new_node;																																	

	/*create_node�̃e�X�g�Ɏg�p
		printf("left=%d		",left);
		printf("value=%d	",value);
		rintf("right=%d\n",right);						
	*/
																																																																																																																															
	new_node=(struct	node*)malloc(sizeof(struct	node));					//�������̗e�ʂ��m��
	new_node->value=value;																																																											
	new_node->left=left;						
	new_node->right=right;						
						
	/*create_node�̃e�X�g�Ɏg�p					
		printf("new_node->left=%d			",new_node->left);
		printf("new_node->value=%d		",new_node->value);
		printf("new_node->right=%d\n",new_node->right);
	*/												
																												
	return	new_node;		
}


/*
�e�X�g
case1
���́F<10,20,30>									���ʁF<10,20,30>

case2
���́F	main��print_tree(0);��p��													���ʁF-

�֐��̐���
�����̃|�C���^���w���ߓ_����̓񕪖؂�\������֐��B

�����F�ߓ_�܂��͐ߓ_�̃����o�[�ւ̃|�C���^
�߂�l�F�Ȃ�
*/
void	print_tree(struct	node	*p)
{
	if(p==0)		printf("-");										//�|�C���^�̎w����ɐߓ_�������Ƃ�

	//p=\0(�|�C���^�̎w����ɐߓ_���Ȃ�)���ƃG���[�ɂȂ��Ă��܂������̂Ƃ��͏��if�őΉ����Ă���
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


/*
�e�X�g	main�ɂ�read_number�̂݌Ăяo����main�̃R�����g�ɂ���悤�ɏo��
case1
���́F10								���ʁFsum=10
																				
�֐��̐���
���͂��ꂽ������̒��ɂ��镶���Ƃ��Ă̐�����
���l�ɂȂ����ĕԂ��֐��B

�����F�Ȃ�
�߂�l�F�z��̒��ɂ��鐔���i���͂��ꂽ������̒��ɂ��鐔���j��1�i���P�����Ƃ͌���Ȃ��j
*/
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


/*
�e�X�g		�R�����g�ɂ���悤��printf��p�ӂ��Aif���̒��g��ύX
case1
���́F<10,20,30>									���ʁF0,10,0	�\����=10511160
																								0,30,0	�\����=10511184
																								10511160,20,10511184	�\����=10511208


�֐��̐���
�i���͂��ꂽ����������Ɂjnextch�̎w�������񂩂�؂��P�ǂݍ��݁A���̍��̍\����node�ւ̃|�C���^��
�Ԃ��֐��B

�����F�Ȃ�
�߂�l�F�V����������ߓ_�ւ̃|�C���^�܂���0
*/
struct	node*	read_tree(void)
{
	int	number;
	struct	node	*left,*right;
	//	struct	node	*test;read_tree�̃e�X�g�Ɏg�p

	if(*nextch=='-')			//�|�C���^���w���悪\0�Ȃ̂�0��Ԃ�
	{
		nextch++;
		return	0;
	}
		
	//left��right��\0���w���Ƃ�
	else	if(('0'<=*nextch)&&(*nextch<='9'))						return		create_node(0,read_number(),0);
	
/*	read_tree�̃e�X�g�Ɏg�p
	else	if(('0'<=*nextch)&&(*nextch<='9'))		
	{
		number=read_number();
		test=create_node(0,number,0);
		printf("0,%d,0	�\����=%d\n",number,test);
		return		test;
	}
*/

	else
	{
		if(*nextch=='<')
		{
			nextch++;																		//�w��������炷�i����buff�̔�������j
			left=read_tree();													//�������g���ĂԁB�֐����I������炱������
		}
	
		if(*nextch==',')
		{
			nextch++;																			
			number=read_number();									
		
			if(*nextch==',')
			{
				nextch++;																				
				right=read_tree();									//�������g���ĂԁB�֐����I������炱������
			}		

			if(*nextch=='>')
			{
				nextch++;
				return	create_node(left,number,right);				
			}

			/*read_tree�̃e�X�g�Ɏg�p
			if(*nextch=='>')							
			{
				nextch++;
				test=create_node(left,number,right);				
				printf("%d,%d,%d	�\����=%d\n",left,number,right,test);		
				return	test;
			}
			*/

		}
	}

	printf("�G���[�ł��B\n");
	return	0;		
}
