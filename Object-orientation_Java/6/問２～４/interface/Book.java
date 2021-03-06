class Book implements Publication{ //Bookを借用、返却、本の状況把握するためのクラス

	String title; // タイトル
	String publisher; // 出版社
	String author; // 著者
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

		if(situation==true)	return "Title: " + title + ", Author: " + author + ", Publisher:" + publisher+"  館内にあります";

		else	return "Title: " + title + ", Author: " + author + ", Publisher:" + publisher+"  貸し出し中";
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