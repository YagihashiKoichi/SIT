class	Distance{

	int	height;      //身長
	int	step;        //歩数
	int	distance;    //距離

	void	setHeight(int	h){
		height=h;
	}

	void	setStep(int	s){
		step=s;
	}

	void	getDistance(){
		distance=(height-100)*step;  //距離＝（身長−１００）＊歩数
	}

	void	Result(){
		System.out.println("あなたが歩いた距離は" + distance + "cmです。");
	}
}