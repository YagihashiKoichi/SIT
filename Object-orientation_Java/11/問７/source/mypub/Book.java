package	mypub;
public	class Book extends Publication{	//Bookを借用、返却、本の状況把握するためのクラス

	private	String author; // 著者

/**
 *@author 八木橋晃一
 *@param isbn その本のISBN番号
 *@param title その本のタイトル
 *@param author その本の著者
 *@param publisher その本の出版社
 *@param year その本の出版年
 */
	public	Book(String	isbn,String title, String author, String publisher,int	year) throws	UsersException{
		super(isbn,title,publisher,year);
		this.author = author;
	}

/**
 *@author 八木橋晃一
 *@return その本の著者
 */
	public	String GetAuthor() {
		return author;
	}

	public String toString() {

		if(situation==true)	return "Title: " + this.getTitle() + ", Author: " + author + ", Publisher:" + this.getPublisher()+"  館内にあります";

		else	return "Title: " + this.getTitle() + ", Author: " + author + ", Publisher:" + this.getPublisher()+"  貸し出し中";
	}

	public	boolean lent(){

		if(situation==true){
			situation=false;
			//System.out.println("貸し出し成功");
			//確認用
			return	false;
		}

		else{
			System.out.println("現在貸し出し中です");
			return	false;
		}
	}

	public	boolean	returned(){

		if(situation==false){
			situation=true;
			//System.out.println("返却成功");
			//確認用
			return	true;
		}

		else{
			System.out.println("貸し出されていません");
			return	false;
		}
	}


}