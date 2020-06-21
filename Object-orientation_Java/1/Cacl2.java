/*
２つの数の総和を求める関数
*/

class	Cacl2		//javaはクラスを必ず宣言
			//クラス名は大文字で始める
{
/*
関数の説明
もう片方の引数までの総和を求め、その値を返す関数
第一引数；求めたい総和の始まりまたは終わりの数
第二引数；求めたい総和の始まりまたは終わりの数
戻り値：求めた総和
*/
	static	int	souwa	(int number1,int	number2)//static忘れずに
	{
		int	sum=0;
		int	i,save;		//save:一時的に値を保存

		if(number1>number2)	//第二引数の値のほうが大きい場合
		{
			save=number1;	
			number1=number2;
			number2=save;	//値を入れ替える
		}		


		for(i=number1;i<=number2;i++)	//総和を求める
		{
			sum=sum+i;
		}

		return	sum;
	}


//プログラムの名前を持つクラスにmainメソッドを持たせる
//"言葉"+値+"言葉"、+は言葉をくっつける

	public	static	void	main(String[]	args)	
	{
		System.out.println("1から100までの和は"+souwa(1,100)+"です");
		System.out.println("100から150までの和は"+souwa(150,100)+"です");
	}
}
