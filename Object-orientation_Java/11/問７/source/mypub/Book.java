package	mypub;
public	class Book extends Publication{	//Book���ؗp�A�ԋp�A�{�̏󋵔c�����邽�߂̃N���X

	private	String author; // ����

/**
 *@author ���؋��W��
 *@param isbn ���̖{��ISBN�ԍ�
 *@param title ���̖{�̃^�C�g��
 *@param author ���̖{�̒���
 *@param publisher ���̖{�̏o�Ŏ�
 *@param year ���̖{�̏o�ŔN
 */
	public	Book(String	isbn,String title, String author, String publisher,int	year) throws	UsersException{
		super(isbn,title,publisher,year);
		this.author = author;
	}

/**
 *@author ���؋��W��
 *@return ���̖{�̒���
 */
	public	String GetAuthor() {
		return author;
	}

	public String toString() {

		if(situation==true)	return "Title: " + this.getTitle() + ", Author: " + author + ", Publisher:" + this.getPublisher()+"  �ٓ��ɂ���܂�";

		else	return "Title: " + this.getTitle() + ", Author: " + author + ", Publisher:" + this.getPublisher()+"  �݂��o����";
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