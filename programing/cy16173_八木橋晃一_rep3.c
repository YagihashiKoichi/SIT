/*
cy16173	���؋��W��	2017�N5��8��

�֐��̐���
��1/n!��n=0����k�܂ł̌v�Z���ăl�C�s�A��e�i���R�ΐ��j�̋ߎ��l�����߂�
n=k�܂Ōv�Z�����l����n=k-1�܂Ōv�Z�����l���������l���Ȃ킿1/k!�̒l������X���b�V�����h�i臒l�j�ȉ��ɂȂ����Ƃ���
���������Ƃ݂Ȃ��v�Z����߁An=k�܂Ōv�Z�����l��e�̋ߎ��l�Ƃ��ďo�͂���֐��B
����������̓X���b�V�����h�i臒l�j��1e-10�Ƃ���B

�e�X�g
�֐��̂Ȃ��̃R�����g�ɏ����Ă���ʂ�Ɍv�Z�r���̒l��double�̌��E�ł��鉺15���܂ł�printf�ŏo�͂���
�En!�̌v�Z���ʂ͑����A���v�Z�̒l�͑����A1/n!�̒l�͌������Ă��邱�Ƃ��m�F�B
�Ek=14�̎��Ɍv�Z���I�����邽��14!�ɒ��ڂ����B
	14!�̒l��87178291200.000000000000000�ƕ\�����ꂱ�̒l�͐����������B



�ۑ�7�ɂ�����
printf��p����wa(n=0����n=k�܂Řa),ikiti�inapier(k)-napier(k-1)�j,bunnbo(n!)�̌v�Z�r���̒l��printf�ŏo�͂�������
k=12�̂Ƃ��Awa=2.71828182829
					bunnbo=12!=479001600
k=13�̂Ƃ��Awa=2.71828182782
					bunnbo=13!=-2147483648
�ƂȂ�Awa�̒l���������Ă��邽��ikiti�inapier(k)-napier(k-1)�j�̒l�����ɂȂ��Ă��܂��B
�����13�̊K�オint�̌^�͈̔͊O�ɂ��邩��ł���B
���P��Ƃ���bunnbo��kaijou�ɑ΂��Ă�int�ł͂Ȃ�double���g����
*/

#include<stdio.h>

double	napier(int) ;											//��蕶�ɂ����邻�̂Ƃ���n�̊K������߂�֐��̃v���g�^�C�v�錾
double	fact(int);											//��蕶�̃��v�Z������֐��v���g�^�C�v�錾

int	k;																																	//���Ԗڂ̌v�Z���𐔂���J�E���^�ϐ�(�O���[�o���ϐ�)
double	wa,ikiti,bunnbo,kaijou=1;						/*bunnbo=kaijou:��蕶�ɂ����邻�̂Ƃ���n�̊K��
																																				ikiti:臒l(�O���[�o���ϐ�)*/
int	main(void)
{

	k=1;																																														//���Ԗڂ̌v�Z���𐔂���J�E���^�ϐ�
	wa=1;																																												//���O��0�̊K�敪�����O�ɑ����Ă���
	while(1)
	{
		wa=napier(k);	
		/*
		printf("(%d)wa=%.15lf\n",k,wa);																	//wa�̒l�Ƃ��̂Ƃ���k�̒l��pintf(%.15lf)�ŏo��
		printf("(%d)ikiti=%.15lf\n\n",k,ikiti);				//ikiti�̒l�Ƃ��̂Ƃ���k�̒l��pintf(%.15lf)�ŏo��
		*/
		if(ikiti<=1e-10)			break;																									//napier(k)-napier(k-1)=1/k!�Ȃ̂�ikiti�Ŕ��f
		k++;
	}

	printf("e=%.15lf",wa);
	return	0;
}

/*
�֐�fact�̐���
��蕶�ɂ����邻�̂Ƃ���n�̊K������߂�֐�
�����F��蕶�ɂ����邻�̂Ƃ���n�̒l�ik)
�߂�l�F��蕶�ɂ�����n�̊K��(kaijou)
*/
double	fact(int	k)	
{
	kaijou=k*kaijou;
	return	kaijou;
}

/*
�֐�napier�̐���
��蕶�ɂ����邻�̂Ƃ���n�̊K��̒l��1��������n-1�܂ł̃��v�Z�̒l�ɉ��Z����֐�
�����F��蕶�ɂ����邻�̂Ƃ���n�̒l(k)
�߂�l�F��蕶�ɂ�����n�܂ł̃��v�Z(wa)
*/
double	napier(int	k)
{
	bunnbo=fact(k);

	/*printf("(%d)bunnbo=%.15lf\n",k,bunnbo);				//wa�̒l�Ƃ��̂Ƃ���k�̒l��pintf((%.15lf))�ŏo��*/

	ikiti=1/bunnbo;																																							//	��蕶�ɂ����邻�̂Ƃ���n�̊K��̒l��1������		
	wa=wa+ikiti;
	return	wa;
}


