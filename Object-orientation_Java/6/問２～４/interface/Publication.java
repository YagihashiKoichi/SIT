interface Publication{

	String GetTitle();
	String GetPublisher();
	String toString();  //���݂̏󋵂��o��
        boolean lent();	    //���g�̏�Ԃ�݂��o�����ɂ���
        boolean returned(); //���g�̏�Ԃ�ԋp�ɂ���

}