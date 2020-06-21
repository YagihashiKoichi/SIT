class	Person{
	String	name;   //属性：名前
	int	age;    //属性：年齢

	void	setName(String	s){
		name=s;               //名前を代入
	}

	void	setAge(int	t){
		age=t;		      //年齢を代入
	}

	void	sumAge(){
		age++;
	}

	void	greet(){
		System.out.println("名前は"+ name +"で、年齢は"+ age +"才です。");
	}
}