class	Distance{

	int	height;      //�g��
	int	step;        //����
	int	distance;    //����

	void	setHeight(int	h){
		height=h;
	}

	void	setStep(int	s){
		step=s;
	}

	void	getDistance(){
		distance=(height-100)*step;  //�������i�g���|�P�O�O�j������
	}

	void	Result(){
		System.out.println("���Ȃ���������������" + distance + "cm�ł��B");
	}
}