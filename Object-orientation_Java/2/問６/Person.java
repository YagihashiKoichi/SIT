class	Person{
	String	name;   //�����F���O
	int	age;    //�����F�N��

	void	setName(String	s){
		name=s;               //���O����
	}

	void	setAge(int	t){
		age=t;		      //�N�����
	}

	void	sumAge(){
		age++;
	}

	void	greet(){
		System.out.println("���O��"+ name +"�ŁA�N���"+ age +"�˂ł��B");
	}
}