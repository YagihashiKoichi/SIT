class Book implements Publication{ //Book���ؗp�A�ԋp�A�{�̏󋵔c�����邽�߂̃N���X

	String title; // �^�C�g��
	String publisher; // �o�Ŏ�
	String author; // ����
	boolean	situation=true;

	Book(String title, String author, String publisher) {
		this.title = title;
		this.author = author;
		this.publisher = publisher;
	}

	public	String GetTitle() { 
		return title;
	}

	public	String GetPublisher(){
		return publisher;
	}

	String GetAuthor() {
		return author;
	}

	public String toString() {

		if(situation==true)	return "Title: " + title + ", Author: " + author + ", Publisher:" + publisher+"  �ٓ��ɂ���܂�";

		else	return "Title: " + title + ", Author: " + author + ", Publisher:" + publisher+"  �݂��o����";
	}

	public	boolean lent(){

		if(situation==true){
			situation=false;
			//System.out.println("�݂��o������");
			//�m�F�p
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


}