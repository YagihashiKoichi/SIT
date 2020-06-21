package	mypub;
public	class Magazine extends Publication{ //Magazineを借用、返却、本の状況把握するためのクラス
	private	int volume;	//巻数
	private	int number;	//号

/**
 *@author 八木橋晃一
 *@param isbn その本のISBN番号
 *@param title その本のタイトル
 *@param publisher その本の出版社
 *@param volume その本の巻数
 *@param number その本の号
 *@param year その本の出版年
 */
	public	Magazine(String	isbn,String title, String publisher, int volume, int number,int	year)	throws	UsersException{
		super(isbn,title,publisher,year);
		this.volume = volume;
		this.number = number;
	}

/**
 *@author 八木橋晃一
 *@return その本の巻数
 */
	public	int getVolume(){
		return volume;
	}

/**
 *@author 八木橋晃一
 *@return その本の号
 */
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
	