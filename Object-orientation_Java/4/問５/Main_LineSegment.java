public	class	Main_LineSegment{
	public	static	void	main(String[]	args){

	LineSegment	p1=new	LineSegment(4,3);
	LineSegment	p2=new	LineSegment(4,3,1,4);
	LineSegment	p3=new	LineSegment(1,4);
			
			//�������Q�Ȃ̂ň���̍��W�����_

//	System.out.println("������"+p1.length());
//	p1.move(10,20);		//�����W�A�����W�����ꂼ��10,20���ړ�
	System.out.println(p1.toString());
	System.out.println(p2.toString());
	System.out.println(p3.toString());
	}
}