
//�w�N�A�g�A�����A�����A���O���o�͂���֐��B

public	class	Pupil2{
	public	static	void	main(String[]	args){

		Pupil	p1=new	Pupil();
		p1.setYearAndClass(1,1);  //�w�N�ƃN���X������
		p1.setName("���؋�","�W��");
		System.out.println(p1.getsYear() + "�N" + p1.getsClass() + "�g�ł��B");

		String name[]=p1.getName();
		System.out.println("������" + name[0] + name[1]);
		System.out.println("������" + p1.getFamilyName());
		System.out.println("���O��" + p1.getFirstName());
	
	}
}
