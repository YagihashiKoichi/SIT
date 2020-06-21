class	LineSegment{

	double	gx,gy;

	Point	p1;
	Point	p2;


	LineSegment(double x,double y){     //端点の片方が原点にあるとき

		p1=new	Point(x,y);
		p2=new	Point();
	}


/*
第１引数：点１のｘ座標
第２引数：点１のｙ座標
第３引数：点２のｘ座標
第４引数：点２のｙ座標
*/
	LineSegment(double x,double y,double xx,double yy){
						 //端点が共に原点にないとき
		p1=new	Point(x,y);
		p2=new	Point(xx,yy);

	}

	void	move(double dx,double dy){
		p1.move(dx,dy);
		p2.move(dx,dy);
	}
		
	double	length(){ //sqrt(double　変数)で変数の平方根を返す
		return	Math.sqrt((p1.get_gx()-p2.get_gx())*(p1.get_gx()-p2.get_gx())+(p1.get_gy()-p2.get_gy())*(p1.get_gy()-p2.get_gy()));
	}


	public	String	toString(){	//点１,２のｘ,ｙ座標を返す
		return	"("+p2.get_gx()+","+p2.get_gy()+")と("+p1.get_gx()+","+p1.get_gy()+")";
	}

}
		