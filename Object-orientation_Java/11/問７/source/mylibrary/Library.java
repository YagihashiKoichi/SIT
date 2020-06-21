package	mylibrary;
import	mypub.*;
import	java.util.*;

public	class	Library{	//出版物を所蔵するクラス

	private	ArrayList<Publication> list=new ArrayList<Publication>();

/**
 *@author 八木橋晃一
 *@param p クラスを表すPublication 
 */
	void	addList(Publication p){	//リストに追加

		if(checkNumber(p.getIsbn()))
			System.out.println("既に同じ本があります");
		else
			list.add(p);
	}

/**
 *@author 八木橋晃一
 *@return list 書庫を表すArrayList
 */
	ArrayList<Publication>	getArrayList(){		//リストを返す
		return	list;
	}

/**
 *@author 八木橋晃一
 */
	void	libraryHas(){	//タイトルのみを出力

		for(Publication	content:list){
			System.out.println(content.getTitle());
		}
	}

/**
 *@author 八木橋晃一
 *@param new_isbn 新しく追加したい出版物のISBN
 *@return ISBNが一致したらtrue,違ったらfalse
 */
	public	Boolean	checkNumber(String	new_isbn){

		for(Publication	content:list){
			if(content.getIsbn().equals(new_isbn))
				return	true;
		}

		return	false;
	}
}