package	mypub;
public	abstract	class Publication{	//�o�ŕ��Ɋւ��钊�ۃN���X
	private	String title; // �^�C�g��
	private	String publisher; // �o�Ŏ�
	boolean	situation=true;
	private	int	year;
	private	String	isbn;

/**
 *@author ���؋��W��
 *@param isbn ���̖{��ISBN�ԍ�
 *@param title ���̖{�̃^�C�g��
 *@param publisher ���̖{�̏o�Ŏ�
 *@param year ���̖{�̏o�ŔN
 */
	public Publication(String	isbn,String title,String publisher,int	year)	throws	UsersException{
		if(isbn.length()!=13)
			throw	new	NotAdmitTheISBN();
		if(year<0)
			throw	new	NotAdmitTheYear();


		this.isbn=isbn;
		this.title = title;
		this.publisher = publisher;
		this.year=year;
	}

/**
 *@author ���؋��W��
 *@return ���̏o�ŕ���ISBN
 */
	public	String getIsbn(){
		return	isbn;
	}

/**
 *@author ���؋��W��
 *@return ���̖{�̃^�C�g��
 */
	public	String getTitle() { 
		return title;
	}

/**
 *@author ���؋��W��
 *@return ���̖{�̏o�Ŏ�
 */
	public	String getPublisher(){
		return publisher;
	}
/**
 *@author ���؋��W��
 *@return ���̖{�̌��݂̏󋵂�����������
 */
	abstract public String toString();  //���݂̏󋵂��o��

/**
 *@author ���؋��W��
 *@return ���g�̏�Ԃ�݂��o���ɂ���
 */
	abstract public boolean lent();	    //���g�̏�Ԃ�݂��o�����ɂ���

/**
 *@author ���؋��W��
 *@return ���g�̏�Ԃ�ԋp�ɂ���
 */
	abstract public boolean returned(); //���g�̏�Ԃ�ԋp�ɂ���


}