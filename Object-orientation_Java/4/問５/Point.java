class Point{

	double	gx,gy;

	Point	(){	//点の座標が原点のとき
		gx=0;
		gy=0;
	}

	Point	(double	px,double py){
		gx=px;
		gy=py;
	}

/*
点を移動させる（問４）のに使用
	void	move(double	dx,double	dy){
		gx=gx+dx;
		gy=gy+dy;
	}       	//点を移動させる
*/

	double	get_gx(){
		return	gx;
	}	        //移動後のｘ座標を返す

	double	get_gy(){
		return	gy;
	}		//移動後のｙ座標を返す
}