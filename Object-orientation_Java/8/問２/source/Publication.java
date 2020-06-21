package	mypub;
public	abstract	class Publication{	//出版物に関する抽象クラス
	private	String title; // タイトル
	private	String publisher; // 出版社
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

	abstract public String toString();  //現在の状況を出力
	abstract public boolean lent();	    //自身の状態を貸し出し中にする
	abstract public boolean returned(); //自身の状態を返却にする


}