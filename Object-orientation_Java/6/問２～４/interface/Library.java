import	java.util.*;

class	Library{	//�o�ŕ�����������N���X

	ArrayList<Publication> list=new ArrayList<Publication>();

	void	AddList(Book book){	//Book�����X�g�ɒǉ�
		list.add(book);
	}

	void	AddList(Magazine	magazine){  //Magazine�����X�g�ɒǉ�
		list.add(magazine);
	}

	ArrayList<Publication>	GetArrayList(){
		return	list;
	}

}