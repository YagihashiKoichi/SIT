class	Pupil{

	int	syear;	//�����F�w�N
	int	sclass;	//�����F�N���X
	String[] name = {"",""};  //���Ɩ�

	void	setYearAndClass(int	s1,int	s2){
		syear=s1;
		sclass=s2;
	}

	void	setName(String	f1,String	f2){
		name[0]=f1;
		name[1]=f2;
	}

	int	getsYear(){
		return	syear;	//�w�N��Ԃ�
	}

	int	getsClass(){
		return	sclass;	//�N���X��Ԃ�
	}

	String[] getName(){
		return	name;	//�����̔z���Ԃ�
	}

	String	getFamilyName(){
		return	name[0]; //������Ԃ�
	}

	String	getFirstName(){
		return	name[1]; //���O��Ԃ�
	}
}