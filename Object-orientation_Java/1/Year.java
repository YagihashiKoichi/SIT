/*
閏年かどうかを判定する関数
*/

class	Year
{
	public	static	void	main(String[]	args)
	{
		int	year=1996;

		if(((year%100)==0)&&((year%400)==0))	//100と400の公倍数
			System.out.println(year+"年は閏年です");

		//100の倍数かつ4の倍数
		else	if(((year%100)!=0)&&((year%4)==0)
			System.out.println(year+"年は閏年です");

		//その他
		else	System.out.println(year+"年は閏年ではありません");
	}
}
