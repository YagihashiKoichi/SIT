public	class	Point2{
	public	static	void	main(String[]	args){


		Point	p1=new	Point(4,6);
		Point	p2=new	Point(6,4);

		p1.MovePoint(5,3);
		p2.MovePoint(3,5);
		
		if(p2.areSame(p1)==true){
			System.out.println("‚Q“_‚Ì“à—e‚Í“™‚µ‚¢");
		}else{
			System.out.println("‚Q“_‚Ì“à—e‚Í“™‚µ‚­‚È‚¢");
		}
	}
}

			