package	mylibrary;
import	mypub.*;
import	java.util.*;

public	class	Library{	//�o�ŕ�����������N���X

	//private	ArrayList<Publication> list=new ArrayList<Publication>();
	private	Map<String,Publication>map=new HashMap<String,Publication>();

/**
 *@author ���؋��W��
 *@param p �N���X��\��Publication 
 */
	void	addMap(Publication p){	//map�ɒǉ�

		if(checkNumber(p.getIsbn()))
			System.out.println("���ɓ����{������܂�");
		else
			map.put(p.getIsbn(),p);
	}

/**
 *@author ���؋��W��
 *@return map ���ɂ�\��map
 */
	Map getMap(){		//map��Ԃ�
		return	map;
	}



/**
 *@author ���؋��W��
 */
/*
	void	libraryHas(){	//�^�C�g���݂̂��o��

		for(Publication	content:list){
			System.out.println(content.getTitle());
		}
	}
*/




/**
 *@author ���؋��W��
 *@param new_isbn �V�����ǉ��������o�ŕ���ISBN
 *@return ISBN����v������true,�������false
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
			System.out.println("�{�����݂��܂���");
	}


	void	returnPublication(String isbn){

		if(map.containsKey(isbn))
			map.get(isbn).returned();
		else
			System.out.println("�{�����݂��܂���");
	}
}