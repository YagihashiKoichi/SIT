public	class	Main_LineSegment{
	public	static	void	main(String[]	args){

	LineSegment	p1=new	LineSegment(3,4);
			//�������Q�Ȃ̂ň���̍��W�����_

	System.out.println("������"+p1.length());
	p1.move(10,20);		//�����W�A�����W�����ꂼ��10,20���ړ�
	System.out.println(p1.toString());
	}
}