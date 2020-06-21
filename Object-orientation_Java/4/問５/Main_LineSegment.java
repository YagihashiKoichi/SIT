public	class	Main_LineSegment{
	public	static	void	main(String[]	args){

	LineSegment	p1=new	LineSegment(4,3);
	LineSegment	p2=new	LineSegment(4,3,1,4);
	LineSegment	p3=new	LineSegment(1,4);
			
			//引数が２つなので一方の座標が原点

//	System.out.println("長さは"+p1.length());
//	p1.move(10,20);		//ｘ座標、ｙ座標をそれぞれ10,20ずつ移動
	System.out.println(p1.toString());
	System.out.println(p2.toString());
	System.out.println(p3.toString());
	}
}