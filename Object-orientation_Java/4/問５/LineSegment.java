class	LineSegment{

	double	gx,gy;
	int own_counter;
	static	int	counter=0;

	Point	p1;
	Point	p2;


	LineSegment(double x,double y){     //�[�_�̕Е������_�ɂ���Ƃ�
		p1=new	Point();
		p2=new	Point(x,y);
	
		counter++;
		own_counter=counter;

	}


/*
��P�����F�_�P�̂����W
��Q�����F�_�P�̂����W
��R�����F�_�Q�̂����W
��S�����F�_�Q�̂����W
*/
	LineSegment(double x,double y,double xx,double yy){
						 //�[�_�����Ɍ��_�ɂȂ��Ƃ�
		p1=new	Point(x,y);
		p2=new	Point(xx,yy);
		counter++;
		own_counter=counter;  
//�A���ŃR���X�g���N�^����������ɍŌ�̒l�����ۑ������̖h�����߂ɁA��x�u��

	}


/*
�_���ړ�������i��S�j�̂Ɏg�p

	void	move(double dx,double dy){
		p1.move(dx,dy);
		p2.move(dx,dy);
	}
*/

/*
���������߂�i��S�j
	double	length(){ //sqrt(double�@�ϐ�)�ŕϐ��̕�������Ԃ�
		return	Math.sqrt((p1.get_gx()-p2.get_gx())*(p1.get_gx()-p2.get_gx())+(p1.get_gy()-p2.get_gy())*(p1.get_gy()-p2.get_gy()));
	}
*/

	public	String	toString(){	//�_�P,�Q�̂�,�����W��Ԃ�
		return	own_counter+"�[�_�P("+p1.get_gx()+","+p1.get_gy()+")�ƒ[�_�Q("+p2.get_gx()+","+p2.get_gy()+")";
	}

}
		