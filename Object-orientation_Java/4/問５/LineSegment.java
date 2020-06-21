class	LineSegment{

	double	gx,gy;
	int own_counter;
	static	int	counter=0;

	Point	p1;
	Point	p2;


	LineSegment(double x,double y){     //端点の片方が原点にあるとき
		p1=new	Point();
		p2=new	Point(x,y);
	
		counter++;
		own_counter=counter;

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
		counter++;
		own_counter=counter;  
//連続でコンストラクタを作った時に最後の値だけ保存されるの防ぐために、一度置く

	}


/*
点を移動させる（問４）のに使用

	void	move(double dx,double dy){
		p1.move(dx,dy);
		p2.move(dx,dy);
	}
*/

/*
長さを求める（問４）
	double	length(){ //sqrt(double　変数)で変数の平方根を返す
		return	Math.sqrt((p1.get_gx()-p2.get_gx())*(p1.get_gx()-p2.get_gx())+(p1.get_gy()-p2.get_gy())*(p1.get_gy()-p2.get_gy()));
	}
*/

	public	String	toString(){	//点１,２のｘ,ｙ座標を返す
		return	own_counter+"端点１("+p1.get_gx()+","+p1.get_gy()+")と端点２("+p2.get_gx()+","+p2.get_gy()+")";
	}

}
		