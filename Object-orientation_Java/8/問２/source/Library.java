package	mylibrary;
import	mypub.*;
import	java.util.*;

class	Library{	//�o�ŕ�����������N���X

	private	ArrayList<Publication> list=new ArrayList<Publication>();

	void	addList(Book book){	//Book�����X�g�ɒǉ�
		list.add(book);
	}

	void	addList(Magazine	magazine){  //Magazine�����X�g�ɒǉ�
		list.add(magazine);
	}

	ArrayList<Publication>	getArrayList(){		//���X�g��Ԃ�
		return	list;
	}


	void	libraryHas(){	//�^�C�g���݂̂��o��

		for(Publication	content:list){
			System.out.println(content.getTitle());
		}
	}

}