public	class	Point{
	int	x;
	int	y;

	int	GetX(){
		return	x;
	}

	int	GetY(){
		return	y;
	}

	void	MovePoint(int	mx,int	my){
		x=x+mx;	//ｘ座標を移動
		y=y+my;	//ｙ座標を移動
	}

	boolean	areSame(Point	p1){
	//2つのPointのxy座標が等しければtrue、異なればfalseを返す
		if(p1==null){
			return	false;
		}else	if((x==p1.GetX())&&(y==p1.GetY())){
			return	true;
		}else{
			return	false;
		}
	}

	Point	(int	bx,int	by){	//コンストラクタ
		x=bx;	//基点となるｘ座標
		y=by;	//基点となるｙ座標
	}
}