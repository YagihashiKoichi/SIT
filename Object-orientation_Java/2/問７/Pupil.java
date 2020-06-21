class	Pupil{

	int	syear;	//属性：学年
	int	sclass;	//属性：クラス
	String[] name = {"",""};  //姓と名

	void	setYearAndClass(int	s1,int	s2){
		syear=s1;
		sclass=s2;
	}

	void	setName(String	f1,String	f2){
		name[0]=f1;
		name[1]=f2;
	}

	int	getsYear(){
		return	syear;	//学年を返す
	}

	int	getsClass(){
		return	sclass;	//クラスを返す
	}

	String[] getName(){
		return	name;	//氏名の配列を返す
	}

	String	getFamilyName(){
		return	name[0]; //名字を返す
	}

	String	getFirstName(){
		return	name[1]; //名前を返す
	}
}