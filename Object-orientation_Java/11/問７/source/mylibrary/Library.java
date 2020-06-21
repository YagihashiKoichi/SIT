package	mylibrary;
import	mypub.*;
import	java.util.*;

public	class	Library{	//�o�ŕ�����������N���X

	private	ArrayList<Publication> list=new ArrayList<Publication>();

/**
 *@author ���؋��W��
 *@param p �N���X��\��Publication 
 */
	void	addList(Publication p){	//���X�g�ɒǉ�

		if(checkNumber(p.getIsbn()))
			System.out.println("���ɓ����{������܂�");
		else
			list.add(p);
	}

/**
 *@author ���؋��W��
 *@return list ���ɂ�\��ArrayList
 */
	ArrayList<Publication>	getArrayList(){		//���X�g��Ԃ�
		return	list;
	}

/**
 *@author ���؋��W��
 */
	void	libraryHas(){	//�^�C�g���݂̂��o��

		for(Publication	content:list){
			System.out.println(content.getTitle());
		}
	}

/**
 *@author ���؋��W��
 *@param new_isbn �V�����ǉ��������o�ŕ���ISBN
 *@return ISBN����v������true,�������false
 */
	public	Boolean	checkNumber(String	new_isbn){

		for(Publication	content:list){
			if(content.getIsbn().equals(new_isbn))
				return	true;
		}

		return	false;
	}
}