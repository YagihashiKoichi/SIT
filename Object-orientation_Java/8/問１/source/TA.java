package	testpkg;
import	mypkg.*;

public	class	TA	extends	A{

	TA(){
		atr1=0;
		atr3=0;
	}

	@Override
	public	void	method1(){
		System.out.println("�N���XB��method1");
	}



	@Override
	protected	void	method3(){
		System.out.println("�N���XB��method3");
	}
}