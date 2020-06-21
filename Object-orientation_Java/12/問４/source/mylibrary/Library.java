package	mylibrary;
import	mypub.*;
import	java.util.*;

public	class	Library{	//出版物を所蔵するクラス

	//private	ArrayList<Publication> list=new ArrayList<Publication>();
	private	Map<String,Publication>map=new HashMap<String,Publication>();

/**
 *@author 八木橋晃一
 *@param p クラスを表すPublication 
 */
	void	addMap(Publication p){	//mapに追加

		if(checkNumber(p.getIsbn()))
			System.out.println("既に同じ本があります");
		else
			map.put(p.getIsbn(),p);
	}

/**
 *@author 八木橋晃一
 *@return map 書庫を表すmap
 */
	Map getMap(){		//mapを返す
		return	map;
	}



/**
 *@author 八木橋晃一
 */
/*
	void	libraryHas(){	//タイトルのみを出力

		for(Publication	content:list){
			System.out.println(content.getTitle());
		}
	}
*/




/**
 *@author 八木橋晃一
 *@param new_isbn 新しく追加したい出版物のISBN
 *@return ISBNが一致したらtrue,違ったらfalse
 */
	public	Boolean	checkNumber(String	new_isbn){

		if(map.containsKey(new_isbn))
			return	true;
		else
			return	false;
	}



	void	checkout(String	isbn){
		if(map.containsKey(isbn))
			map.get(isbn).lent();
		else
			System.out.println("本が存在しません");
	}


	void	returnPublication(String isbn){

		if(map.containsKey(isbn))
			map.get(isbn).returned();
		else
			System.out.println("本が存在しません");
	}
}