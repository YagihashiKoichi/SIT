public	class	Main_Figure{
	public	static	void	main(String[]	args){

		Rectangle	p1=new	Rectangle(10.0,20.0);
		Circle	p2=new	Circle(10.0);
		Rectangle	p3=new	Rectangle(40.0,60.0);
		Circle	p4=new	Circle(40.0);

		p1.get_point(0.0,0.0);
		System.out.println(p1.toString());
		p1.move(10.0,30.0);
		p1.change(8.0);
		System.out.println(p1.toString());
		p2.get_point(0.0,0.0);
		System.out.println(p2.toString());
		p2.move(20.0,20.0);
		p2.change(5.0);
		System.out.println(p2.toString());
	}
}