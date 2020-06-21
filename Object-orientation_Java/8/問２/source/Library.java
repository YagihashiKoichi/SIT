package	mylibrary;
import	mypub.*;
import	java.util.*;

class	Library{	//出版物を所蔵するクラス

	private	ArrayList<Publication> list=new ArrayList<Publication>();

	void	addList(Book book){	//Bookをリストに追加
		list.add(book);
	}

	void	addList(Magazine	magazine){  //Magazineをリストに追加
		list.add(magazine);
	}

	ArrayList<Publication>	getArrayList(){		//リストを返す
		return	list;
	}


	void	libraryHas(){	//タイトルのみを出力

		for(Publication	content:list){
			System.out.println(content.getTitle());
		}
	}

}