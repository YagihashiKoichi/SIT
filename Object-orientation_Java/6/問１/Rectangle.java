class	Rectangle	extends	Figure{


	double	wide;	//��
	double	hight;	//����
	static	int	recounter=0;



	Rectangle(double w,double h){
		wide=w;
		hight=h;
		recounter++;
		own_counter=recounter;
	}

	public	void	change(double	magni){
		wide=wide*magni;
		hight=hight*magni;
	}

	


	public	String	toString(){
		return	"Rectangle"+own_counter+":��������W=("+bx+","+by+"),��="+wide+",����="+hight;
	}
}