class Point{

	double	gx,gy;

	Point	(){	//�_�̍��W�����_�̂Ƃ�
		gx=0;
		gy=0;
	}

	Point	(double	px,double py){
		gx=px;
		gy=py;
	}

/*
�_���ړ�������i��S�j�̂Ɏg�p
	void	move(double	dx,double	dy){
		gx=gx+dx;
		gy=gy+dy;
	}       	//�_���ړ�������
*/

	double	get_gx(){
		return	gx;
	}	        //�ړ���̂����W��Ԃ�

	double	get_gy(){
		return	gy;
	}		//�ړ���̂����W��Ԃ�
}