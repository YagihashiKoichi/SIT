class	Circle	extends	Figure{


	double	radius;		//”¼Œa
	static	int	cicounter=0;

	Circle(double	r){
		cicounter++;
		own_counter=cicounter;
		radius=r;
	}

	public	void	change(double	magni){
		radius=radius*magni;
	}



	public	String	toString(){
		return	"Circle"+own_counter+":’†SÀ•W=("+bx+","+by+"),”¼Œa="+radius;
	}
}

