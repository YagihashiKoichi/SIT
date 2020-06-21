import	java.util.*;

class	Library{	//出版物を所蔵するクラス

	ArrayList<Publication> list=new ArrayList<Publication>();

	void	AddList(Book book){	//Bookをリストに追加
		list.add(book);
	}

	void	AddList(Magazine	magazine){  //Magazineをリストに追加
		list.add(magazine);
	}

	ArrayList<Publication>	GetArrayList(){
		return	list;
	}

}