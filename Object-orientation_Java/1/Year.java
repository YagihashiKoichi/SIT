/*
�[�N���ǂ����𔻒肷��֐�
*/

class	Year
{
	public	static	void	main(String[]	args)
	{
		int	year=1996;

		if(((year%100)==0)&&((year%400)==0))	//100��400�̌��{��
			System.out.println(year+"�N�͉[�N�ł�");

		//100�̔{������4�̔{��
		else	if(((year%100)!=0)&&((year%4)==0)
			System.out.println(year+"�N�͉[�N�ł�");

		//���̑�
		else	System.out.println(year+"�N�͉[�N�ł͂���܂���");
	}
}
