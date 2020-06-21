class Magazine implements Publication{ //Magazineを借用、返却、本の状況把握するためのクラス
	int volume;	//巻数
	int number;	//号
	String title; // タイトル
	String publisher; // 出版社
	boolean	situation=true;

	Magazine(String title, String publisher, int volume, int number){
		this.title = title;
		this.publisher = publisher;
		this.volume = volume;
		this.number = number;
	}

	int GetVolume(){
		return volume;
	}

	int GetNumber(){
		return number;
	}

	public	String GetTitle() { 
		return title;
	}

	public	String GetPublisher(){
		return publisher;
	}

	public	boolean	lent(){

		if((situation==true)&&(volume<=10)){
			situation=false;
			//System.out.println("貸し出し成功");
			//確認用
			return	true;
		}

		else	if((situation==true)&&(volume>10)){
			System.out.println("貸し出せません");
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

	public String toString() {
		if(situation==true)	return "Title: " + title + ", Publisher:" + publisher + ", 巻："+ volume + ", 号："+ number+"  館内にあります";

		else	return "Title: " + title + ", Publisher:" + publisher + ", 巻："+ volume + ", 号："+ number+"  貸し出し中";

	}
}
	