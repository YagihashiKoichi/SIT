/*
�Q�̐��̑��a�����߂�֐�
*/

class	Cacl2		//java�̓N���X��K���錾
			//�N���X���͑啶���Ŏn�߂�
{
/*
�֐��̐���
�����Е��̈����܂ł̑��a�����߁A���̒l��Ԃ��֐�
�������G���߂������a�̎n�܂�܂��͏I���̐�
�������G���߂������a�̎n�܂�܂��͏I���̐�
�߂�l�F���߂����a
*/
	static	int	souwa	(int number1,int	number2)//static�Y�ꂸ��
	{
		int	sum=0;
		int	i,save;		//save:�ꎞ�I�ɒl��ۑ�

		if(number1>number2)	//�������̒l�̂ق����傫���ꍇ
		{
			save=number1;	
			number1=number2;
			number2=save;	//�l�����ւ���
		}		


		for(i=number1;i<=number2;i++)	//���a�����߂�
		{
			sum=sum+i;
		}

		return	sum;
	}


//�v���O�����̖��O�����N���X��main���\�b�h����������
//"���t"+�l+"���t"�A+�͌��t����������

	public	static	void	main(String[]	args)	
	{
		System.out.println("1����100�܂ł̘a��"+souwa(1,100)+"�ł�");
		System.out.println("100����150�܂ł̘a��"+souwa(150,100)+"�ł�");
	}
}
