#include<stdio.h>
/*
CY16173	���؋��W��	�쐬���F�쐬���F2017�N6��1��	�ۑ�4-3
�e�X�g( print_list�ł̓A�h���X���o�͂���printf���g�p)
case1
�l�Fcell1=create_cell(2,0)
		cell2=create_cell(5,cell1)
		cell3=create_cell(1,cell2)
		cell4=create_cell(6,0)
		cell5=create_cell(7,cell4)
		cell6=create_cell(8,cell5)
�v�����g:print_list(cell3),	print_list(p)
����:=>8(4250632)=>7(4250624)=>6(4250616)
		=>8(4250640)=>7(4250648)=>6(4250656)=>1(4250608)=>5(4250600)=>2(4250592)


case2
�l�Fcell1=create_cell(2,0),cell4=create_cell(6,0);
�v�����g:print_list(cell3),	print_list(p)
����:


case3
�l�Fcell1=create_cell(2,0);																									
	cell2=create_cell(0,cell1);
	cell3=create_cell(0,cell2);
	cell4=create_cell(6,0);
	cell5=create_cell(0,cell4);
	cell6=create_cell(0,cell5);
	
�v�����g:print_list(cell3),	print_list(p)
����:0(4250640)=>0(4250648)=>6(4250656)=>0(4250608)=>0(4250600)=>2(4250592)


case4			p=concat(copy(cell3),cell3);		
�l�Fcell1=create_cell(2,0);																												
	cell2=create_cell(3,cell1);
	cell3=create_cell(4,cell2);
�v�����g:print_list(cell3),	print_list(p)
����:=>2(4250592)
=>4(4250640)=>3(4250648)=>2(4250656)=>4(4250608)=>3(4250600)=>2(4250592)

�֐��̐���
�Z���̂Ȃ��̍\���ɒl�ƃA�h���X�������A���X�g��2���B���̌ナ�X�g���q���邪�A�O���ɓ����镔���̃��X�g�̓R�s�[�������̂ł���B
��L�̗�����s���֐��B
*/

struct	cell				//�\���̐錾
{
	int	data;
	struct	cell	*next;
};


struct	cell	cell_pool[1000];														//�O���[�o���ϐ�
struct	cell	*new_cell=cell_pool;				
		

void print_list(struct	cell	*list);																																			//�v���g�^�C�v�錾:���X�g�������Ƃ��Ď󂯎��A�e�Z����data�����o���o�͂���֐�
struct	cell	*create_cell(int	data,struct	cell	*next);					//�v���g�^�C�v�錾:����������f�[�^�̒l�ƂȂ������A�h���X�������Ƃ��A�V����������Z���̂P�܂��̃A�h���X��Ԃ��֐�
struct	cell	*tail_list(struct	cell	*tail);																						//�v���^�C�v�錾:���X�g�̐擪�̃Z���̃A�h���X�������Ƃ��A���X�g�̏I���̃Z���ւ̃|�C���^�̃A�h���X��Ԃ��֐�
struct	cell	*concat(struct	cell	*cell6,struct	cell	*cell3);						//�v���^�C�v�錾:�q���������X�g�̐擪�̃Z���̂��ꂼ��̃A�h���X�������Ƃ��A�ł������������X�g�̐擪�̃Z���̃A�h���X��Ԃ��֐�
struct	cell	*copy(struct	cell	*list2);																												//�v���^�C�v�錾:�R�s�[���������X�g�̃Z���̐擪�̃A�h���X�������Ƃ��A�R�s�[�������X�g�̃Z���̐擪�̃A�h���X��Ԃ�l�Ƃ���֐�


int	main	(void)
{
	struct	cell	*cell1,*cell2,*cell3,*p	,*cell4,*cell5,*cell6;															//cell1?6��create_cell�̈����̃A�h���X�Ap��2�̃��X�g�������������Ƃ̃��X�g�̐擪�̃Z���̃A�h���X

	cell1=create_cell(2,0);																													//�V�������Z���ւ̒l�ƃA�h���X����
	cell2=create_cell(3,cell1);
	cell3=create_cell(4,cell2);

																																											//print_list(cell1);					print_list��main�̃e�X�g�Ɏg�p

	cell4=create_cell(6,0);
	cell5=create_cell(5,cell4);
	cell6=create_cell(4,cell5);
	

	p=concat(copy(cell6),cell3);																			//�����������X�g�̐擪�̃Z���̃A�h���X��p�ɑ��
	print_list(p);

	return	0;
}



/*
�e�X�g( print_list�ł̓A�h���X���o�͂���printf���g�p)
case1
�l�Fcell1=create_cell(2,0),cell2=create_cell(5,cell1);
		cell3=create_cell(1,cell2);
�v�����g:cell3�������Ƃ�print_list(p);	
����:=>2(4250592)
			
�֐��̐���
���X�g�̏I���̃Z���������Ŏ󂯎�������X�g�̐擪�̃Z���̃A�h���X���珇�ɒT���A���X�g�̃Z���Ō�̃Z�����������̃A�h���X��Ԃ��֐�

�����F�Ō�̃Z���̃A�h���X�𒲂ׂ������X�g�̐擪�̃A�h���X
�߂�l�F���ׂ������X�g�̍Ō�̃Z���̃A�h���X
*/
struct	cell	*tail_list(struct	cell	*tail)
{
	struct	cell	*p;
	p=tail;
	while(1)
	{
																																					//		if(p->next==0)		print_list(p);					tail_list
		if(p->next==0)		return	p;												//���X�g�̍Ō�̃Z����next�̓i�����Ȃ̂ł���������Ĕ��f
		p=p->next;																															//���̃Z���̃A�h���X���w���i���̃Z����next�����̃Z�����w���Ă���j
	}
}




/*
�e�X�g( print_list�ł̓A�h���X���o�͂���printf���g�p)
case1
�l�Fcell1=create_cell(2,0),cell2=create_cell(5,cell1);
		cell3=create_cell(1,cell2);
�v�����g:print_list(cell3);	
����:=>1(4250608)=>5(4250600)=>2(4250592)


�֐��̐���
�����Ŏ󂯎�������X�g�i���X�g�̐擪�̃Z���̃A�h���X�j�����ǂ��Ċe�Z����data�����o��\������֐�

�����F�e�Z����data�����o��\���������X�g�̐擪�̃Z���̃A�h���X
�߂�l�F�Ȃ�
*/
void print_list(struct	cell	*list)
{
	struct	cell	*p;
	p=list;
	while(p!=0)
	{
		printf("=>%d",p->data);

		//	printf("=>%d(%d)",p->data,p);				�e�X�g�̂��߂̃A�h���X���\������printf

		p=p->next;																			//���̃Z���̃A�h���X���w��
	}
	printf("\n");

	return;
}




/*
�e�X�g( print_list�ł̓A�h���X���o�͂���printf���g�p)
case1
�l�Fcell1=create_cell(2,0),cell2=create_cell(5,cell1);
		cell3=create_cell(1,cell2);
�v�����g:��̒l�����ꂼ������Ƃ�print_list(new_cell);	
����:=>2(4250592)
		=>5(4250600)=>2(4250592)
		=>1(4250608)=>5(4250600)=>2(4250592)

�֐��̐���
�����Ŏ󂯎�����l�ƃA�h���X��V����������\���̂̃Z���ɑ������

�����P�F�V�������\���̂̃Z���ɑ���������l
�����Q�F�V�������\���̂̃Z���ɑ���������A�h���X
�߂�l�F�V����������Z���̃A�h���X
*/
struct	cell	*create_cell(int	data,struct	cell	*next)
{
	struct	cell	*old_cell;
	new_cell->data =data;									//	�����Ŏ󂯎�����l��V����������\���̂̃Z���ɑ������
	new_cell->next=next;											//�����Ŏ󂯎�����A�h���X��V����������\���̂̃Z���ɑ������
																			//print_list(new_cell);				create_cell�̃e�X�g�Ɏg�p

	old_cell=new_cell;											//���݂�new_cell�̒l���Ƃ��Ă���
	new_cell++;
	return	old_cell;
}



/*
�e�X�g( print_list�ł̓A�h���X���o�͂���printf���g�p)
case1
�l�Fcell1=create_cell(2,0)
		cell2=create_cell(5,cell1);
		cell3=create_cell(1,cell2)
		cell4=create_cell(6,0);
		cell5=create_cell(7,cell4)
		cell6=create_cell(8,cell5);
�v�����g:cell6��������Acell3��������Ƃ�print_list(p1),print_list(p2),print_list(p1);	
����:
=>8(4250632)=>7(4250624)=>6(4250616)
=>1(4250608)=>5(4250600)=>2(4250592)
=>8(4250632)=>7(4250624)=>6(4250616)=>1(4250608)=>5(4250600)=>2(4250592)

�֐��̐���
�q���������X�g�̑O���ɂ��������̐擪�̃Z���̃A�h���X��������Ƃ��A
����ɂ��������̐擪�̃Z���̃A�h���X��������Ƃ��ă��X�g���q���P�̃��X�g�ɂ��āA
�ł������������X�g�̐擪�̃Z���̃A�h���X��Ԃ��֐�

�����P�F�q���������X�g�̑O���ɂ��������̐擪�̃Z���̃A�h���X
�����Q�F�q���������X�g�̌���ɂ��������̐擪�̃Z���̃A�h���X
�߂�l�F���X�g���q���邱�Ƃłł����V�������X�g�̐擪�̃Z���̃A�h���X
*/
struct	cell	*concat(struct	cell	*cell6,struct	cell	*cell3)
{
	struct	cell	*tail,*p1,*p2;

	p1=cell6;
	p2=cell3;
														//	print_list(p1);�֐�concat�̃e�X�g�Ɏg�p
															//print_list(p2);�֐�concat�̃e�X�g�Ɏg�p

	tail=tail_list(p1);											//���X�g�̍Ō�̃Z���̃A�h���X�����߂�
	tail->next=p2;															//���X�g���q����

															//	print_list(p1);	�֐�concat�̃e�X�g�Ɏg�p

	return	p1;
}



/*
�e�X�g( print_list�ł̓A�h���X���o�͂���printf���g�p)
case1
�l�Fcell4=create_cell(6,0);
		cell5=create_cell(7,cell4)
		cell6=create_cell(8,cell5);
�v�����g:cell6�������Ƃ��Aprint_list(p),print_list(head)
����:=>8(4250632)=>7(4250624)=>6(4250616)
		=>8(4250640)=>7(4250648)=>6(4250656)




�֐��̐���
���X�g�̐擪�̃Z���̃A�h���X�������Ƃ����̃��X�g���R�s�[���A�R�s�[���Ăł������X�g��
�擪�̃Z���̃A�h���X��Ԃ��֐�

�����F�R�s�[���������X�g�̐擪�̃Z���̃A�h���X
�߂�l�F�R�s�[���Ăł������X�g�̐擪�̃Z���̃A�h���X
*/
struct	cell	*copy(struct	cell	*list2)									
{
	struct	cell	*new,*p,*head,*back;								
	int	i;

/*
new:�V����������Z���̃A�h���X�������邽�߂̕ϐ�
p�F�R�s�[���������X�g�̐擪�̃Z���̃A�h���X�������邽�߂̕ϐ�
head:�R�s�[���Ăł������X�g�̐擪�̃Z���̃A�h���X��ۑ����邽�߂̕ϐ�
back:�V����������Z���̃A�h���X���ꎞ�I�ɕۑ����邽�߂̕ϐ�
i:while�̒��ōŏ��̈��Ƒ�����ʂ��邽�߂̃J�E���^�[�ϐ�
*/

	i=0;
	p=list2;

																																								//print_list(p);//�֐�copy�̃e�X�g�Ɏg�p
	
	while(1)	
	{
		new=create_cell(p->data,0);																//�܂����̃Z�����ł��Ă��Ȃ����߁A���̃Z���̃A�h���X�������Ȃ��̂ŁA�ꎞ�I���u�Ƃ��ăi��������
	
	
		if(i==0)
			head=new;																														//�R�s�[���Ăł������X�g�̐擪�̃Z���̃A�h���X��ۑ�
		if(i!=0)
			back->next=new;																												//�Q��ڈȍ~�̃��[�v�ł͎��̃Z�����ł��Ă���̂Ŏ��̃Z���̃A�h���X���w��
	
		if(p->next==0)			break;

		
		back=new;																														//�V����������Z���̃A�h���X���ꎞ�I�ɕۑ�
		i++;
		p=p->next;																														//�R�s�[���̎��̃Z�����w��
	}

																																					//print_list(head);�֐�copy�̃e�X�g�Ɏg�p

	return	head;
}







