package	mypub;
public	abstract	class Publication{	//�o�ŕ��Ɋւ��钊�ۃN���X
	private	String title; // �^�C�g��
	private	String publisher; // �o�Ŏ�
	boolean	situation=true;

	Publication(String title,String publisher){
		this.title = title;
		this.publisher = publisher;
	}


	public	String getTitle() { 
		return title;
	}

	public	String getPublisher(){
		return publisher;
	}

	abstract public String toString();  //���݂̏󋵂��o��
	abstract public boolean lent();	    //���g�̏�Ԃ�݂��o�����ɂ���
	abstract public boolean returned(); //���g�̏�Ԃ�ԋp�ɂ���


}