class Magazine implements Publication{ //Magazine���ؗp�A�ԋp�A�{�̏󋵔c�����邽�߂̃N���X
	int volume;	//����
	int number;	//��
	String title; // �^�C�g��
	String publisher; // �o�Ŏ�
	boolean	situation=true;

	Magazine(String title, String publisher, int volume, int number){
		this.title = title;
		this.publisher = publisher;
		this.volume = volume;
		this.number = number;
	}

	int GetVolume(){
		return volume;
	}

	int GetNumber(){
		return number;
	}

	public	String GetTitle() { 
		return title;
	}

	public	String GetPublisher(){
		return publisher;
	}

	public	boolean	lent(){

		if((situation==true)&&(volume<=10)){
			situation=false;
			//System.out.println("�݂��o������");
			//�m�F�p
			return	true;
		}

		else	if((situation==true)&&(volume>10)){
			System.out.println("�݂��o���܂���");
			return	false;
		}

		else{
			System.out.println("���ݑ݂��o�����ł�");
			return	false;
		}
	}

	public	boolean	returned(){

		if(situation==false){
			situation=true;
			//System.out.println("�ԋp����");
			//�m�F�p
			return	true;
		}

		else{
			System.out.println("�݂��o����Ă��܂���");
			return	false;
		}
	}

	public String toString() {
		if(situation==true)	return "Title: " + title + ", Publisher:" + publisher + ", ���F"+ volume + ", ���F"+ number+"  �ٓ��ɂ���܂�";

		else	return "Title: " + title + ", Publisher:" + publisher + ", ���F"+ volume + ", ���F"+ number+"  �݂��o����";

	}
}
	