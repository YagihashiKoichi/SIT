/*
身長と歩いた歩数から歩いた距離を求める関数。
第１引数：身長
第２引数：歩数
*/
public	class	Distance2{
	public	static	void	main(String[] args){
		Distance d1=new	Distance();

		d1.setHeight(Integer.parseInt(args[0]));
		d1.setStep(Integer.parseInt(args[1]));
		d1.getDistance();
		d1.Result();
	}
}