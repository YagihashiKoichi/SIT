/*
�^����ꂽ���W�ɑ΂��ė^����ꂽ���������W��
�ړ�������֐�
*/

#include<stdio.h>

struct	point	move(struct	point	original,int	x1,int	y1);

struct	point{		//���W��\���\����
	int	x0;
	int	y0;
}; 

int	main(void)
{
	struct	point	original;

	int	x1,y1;

	printf("���Ƃ̂����W����͂��Ă��������B\n");
	scanf("%d",&original.x0);
	printf("���Ƃ̂����W����͂��Ă��������B\n");
	scanf("%d",&original.y0);
	printf("���������W�𓮂��������͂��Ă��������B\n");
	scanf("%d",&x1);
	printf("���������W�𓮂��������͂��Ă��������B\n");
	scanf("%d",&y1);

	original=move(original,x1,y1);

	printf("���ʁF(%d,%d)",original.x0,original.y0);

	return	0;
}

/*
�������̂Ԃ񂾂������W�A�������̂Ԃ񂾂����W��
�ړ�������֐�
�������F�����W�ɂ������Ĉړ�����������
�������F�����W�ɂ������Ĉړ�����������
*/
struct	point	move(struct	point	original,int	x1,int	y1)
{
	original.x0=original.x0+x1;
	original.y0=original.y0+y1;
	return	original;
}

