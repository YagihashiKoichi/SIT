class	LineSegment{

	double	gx,gy;

	Point	p1;
	Point	p2;


	LineSegment(double x,double y){     //�[�_�̕Е������_�ɂ���Ƃ�

		p1=new	Point(x,y);
		p2=new	Point();
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

	}

	void	move(double dx,double dy){
		p1.move(dx,dy);
		p2.move(dx,dy);
	}
		
	double	length(){ //sqrt(double�@�ϐ�)�ŕϐ��̕�������Ԃ�
		return	Math.sqrt((p1.get_gx()-p2.get_gx())*(p1.get_gx()-p2.get_gx())+(p1.get_gy()-p2.get_gy())*(p1.get_gy()-p2.get_gy()));
	}


	public	String	toString(){	//�_�P,�Q�̂�,�����W��Ԃ�
		return	"("+p2.get_gx()+","+p2.get_gy()+")��("+p1.get_gx()+","+p1.get_gy()+")";
	}

}
		