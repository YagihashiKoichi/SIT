public class ArrayTesta{
	public	static	void	main(String[]	args){
		int[]	ar;
		ar=new	int[3];
		ar[0]=10;
		ar[1]=100;
		ar[2]=1000;
		for(int	i=0;i<3;i++){
			System.out.println(i+1+"番目の要素："+ar[i]);
		}
	}
}