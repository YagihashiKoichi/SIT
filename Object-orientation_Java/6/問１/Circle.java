class	Circle	extends	Figure{


	double	radius;		//���a
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
		return	"Circle"+own_counter+":���S���W=("+bx+","+by+"),���a="+radius;
	}
}

