package	mypub;
public	class Book extends Publication{	//Bookを借用、返却、本の状況把握するためのクラス

	private	String author; // 著者

	public	Book(String title, String author, String publisher) {
		super(title,publisher);
		this.author = author;
	}

	
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