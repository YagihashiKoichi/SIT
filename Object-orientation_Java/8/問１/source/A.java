package	mypkg;

public	class	A{

	public	int	atr1;
	int	atr2;
	protected	int	atr3;
	private	int	atr4;

	public	void	method1(){
		System.out.println("クラスAのmethod1");
	}

	void	method2(){
		System.out.println("クラスAのmethod2");
	}

	protected	void	method3(){
		System.out.println("クラスAのmethod3");
	}

	private	void	method4(){
		System.out.println("クラスAのmethod4");
	}
}



class	B	extends	A{

	B(){
		atr1=0;
		atr2=0;
		atr3=0;
	}

	@Override
	public	void	method1(){
		System.out.println("クラスBのmethod1");
	}

	@Override
	void	method2(){
		System.out.println("クラスBのmethod2");
	}

	@Override
	protected	void	method3(){
		System.out.println("クラスBのmethod3");
	}
}


class	C{

	public	A	atr1;

	C(){
		A	a=new	A();
		atr1=a;
	}

	void	method1(){
		atr1.atr1=1;
		atr1.atr2=1;
		atr1.atr3=1;
	}
}	