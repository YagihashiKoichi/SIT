class	Distance{

	int	height;      //g’·
	int	step;        //•à”
	int	distance;    //‹——£

	void	setHeight(int	h){
		height=h;
	}

	void	setStep(int	s){
		step=s;
	}

	void	getDistance(){
		distance=(height-100)*step;  //‹——£ig’·|‚P‚O‚Oj–•à”
	}

	void	Result(){
		System.out.println("‚ ‚È‚½‚ª•à‚¢‚½‹——£‚Í" + distance + "cm‚Å‚·B");
	}
}