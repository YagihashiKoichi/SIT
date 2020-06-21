package	mypub;
public	class Magazine extends Publication{ //Magazineを借用、返却、本の状況把握するためのクラス
	private	int volume;	//巻数
	private	int number;	//号
	
	public	Magazine(String title, String publisher, int volume, int number){
		super(title,publisher);
		this.volume = volume;
		this.number = number;
	}


	public	int getVolume(){
		return volume;
	}

	public	int getNumber(){
		return number;
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
		if(situation==true)	return "Title: " + this.getTitle() + ", Publisher:" + this.getPublisher() + ", 巻："+ volume + ", 号："+ number+"  館内にあります";

		else	return "Title: " + this.getTitle() + ", Publisher:" + this.getPublisher() + ", 巻："+ volume + ", 号："+ number+"  貸し出し中";

	}
}
	