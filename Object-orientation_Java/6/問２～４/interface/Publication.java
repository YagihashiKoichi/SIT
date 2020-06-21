interface Publication{

	String GetTitle();
	String GetPublisher();
	String toString();  //現在の状況を出力
        boolean lent();	    //自身の状態を貸し出し中にする
        boolean returned(); //自身の状態を返却にする

}