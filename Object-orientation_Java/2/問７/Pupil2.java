
//学年、組、氏名、名字、名前を出力する関数。

public	class	Pupil2{
	public	static	void	main(String[]	args){

		Pupil	p1=new	Pupil();
		p1.setYearAndClass(1,1);  //学年とクラスを引数
		p1.setName("八木橋","晃一");
		System.out.println(p1.getsYear() + "年" + p1.getsClass() + "組です。");

		String name[]=p1.getName();
		System.out.println("氏名は" + name[0] + name[1]);
		System.out.println("名字は" + p1.getFamilyName());
		System.out.println("名前は" + p1.getFirstName());
	
	}
}
