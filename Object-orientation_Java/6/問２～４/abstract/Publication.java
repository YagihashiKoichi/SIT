abstract	class Publication{	//出版物に関する抽象クラス
	String title; // タイトル
	String publisher; // 出版社
	boolean	situation=true;

	String GetTitle() { 
		return title;
	}

	String GetPublisher(){
		return publisher;
	}

	abstract public String toString();  //現在の状況を出力
	abstract public boolean lent();	    //自身の状態を貸し出し中にする
	abstract public boolean returned(); //自身の状態を返却にする


}