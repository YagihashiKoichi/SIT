package	mypub;
public	abstract	class Publication{	//出版物に関する抽象クラス
	private	String title; // タイトル
	private	String publisher; // 出版社
	boolean	situation=true;
	private	int	year;
	private	String	isbn;

/**
 *@author 八木橋晃一
 *@param isbn その本のISBN番号
 *@param title その本のタイトル
 *@param publisher その本の出版社
 *@param year その本の出版年
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
 *@author 八木橋晃一
 *@return その出版物のISBN
 */
	public	String getIsbn(){
		return	isbn;
	}

/**
 *@author 八木橋晃一
 *@return その本のタイトル
 */
	public	String getTitle() { 
		return title;
	}

/**
 *@author 八木橋晃一
 *@return その本の出版社
 */
	public	String getPublisher(){
		return publisher;
	}
/**
 *@author 八木橋晃一
 *@return その本の現在の状況を示す文字列
 */
	abstract public String toString();  //現在の状況を出力

/**
 *@author 八木橋晃一
 *@return 自身の状態を貸し出しにする
 */
	abstract public boolean lent();	    //自身の状態を貸し出し中にする

/**
 *@author 八木橋晃一
 *@return 自身の状態を返却にする
 */
	abstract public boolean returned(); //自身の状態を返却にする


}