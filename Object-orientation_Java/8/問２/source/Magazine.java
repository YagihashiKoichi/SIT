package	mypub;
public	class Magazine extends Publication{ //Magazine���ؗp�A�ԋp�A�{�̏󋵔c�����邽�߂̃N���X
	private	int volume;	//����
	private	int number;	//��
	
	public	Magazine(String title, String publisher, int volume, int number){
		super(title,publisher);
		this.volume = volume;
		this.number = number;
	}


	public	int getVolume(){
		return volume;
	}

	public	int getNumber(){
		return number;
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
		if(situation==true)	return "Title: " + this.getTitle() + ", Publisher:" + this.getPublisher() + ", ���F"+ volume + ", ���F"+ number+"  �ٓ��ɂ���܂�";

		else	return "Title: " + this.getTitle() + ", Publisher:" + this.getPublisher() + ", ���F"+ volume + ", ���F"+ number+"  �݂��o����";

	}
}
	