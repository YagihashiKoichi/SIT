abstract	class Publication{	//�o�ŕ��Ɋւ��钊�ۃN���X
	String title; // �^�C�g��
	String publisher; // �o�Ŏ�
	boolean	situation=true;

	String GetTitle() { 
		return title;
	}

	String GetPublisher(){
		return publisher;
	}

	abstract public String toString();  //���݂̏󋵂��o��
	abstract public boolean lent();	    //���g�̏�Ԃ�݂��o�����ɂ���
	abstract public boolean returned(); //���g�̏�Ԃ�ԋp�ɂ���


}