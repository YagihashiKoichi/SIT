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
		x=x+mx;	//�����W���ړ�
		y=y+my;	//�����W���ړ�
	}

	boolean	areSame(Point	p1){
	//2��Point��xy���W�����������true�A�قȂ��false��Ԃ�
		if(p1==null){
			return	false;
		}else	if((x==p1.GetX())&&(y==p1.GetY())){
			return	true;
		}else{
			return	false;
		}
	}

	Point	(int	bx,int	by){	//�R���X�g���N�^
		x=bx;	//��_�ƂȂ邘���W
		y=by;	//��_�ƂȂ邙���W
	}
}