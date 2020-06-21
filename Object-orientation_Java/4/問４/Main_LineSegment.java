public	class	Main_LineSegment{
	public	static	void	main(String[]	args){

	LineSegment	p1=new	LineSegment(3,4);
			//引数が２つなので一方の座標が原点

	System.out.println("長さは"+p1.length());
	p1.move(10,20);		//ｘ座標、ｙ座標をそれぞれ10,20ずつ移動
	System.out.println(p1.toString());
	}
}