abstract	class	Figure{

	double	bx,by;		//��_�̍��W
	int	own_counter;	//�}�`�̔ԍ�

	void	get_point(double x,double y){	//��_�̍��W�𓾂�
		bx=x;
		by=y;
	}


	void	move(double	x,double	y){	////�}�`�̊�_���ړ�
		bx=bx+x;
		by=by+y;
	}

	abstract	public	void	change(double	maguni);   //�}�`���g��
	abstract	public	String	toString();	//���ʂ̕������Ԃ�

//���ۉ����邱�ƂŁA�����p������̃N���X�ŃI�[�o�[���C�h�������ł���
}
	