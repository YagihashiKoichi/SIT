package	evaluation;
import	java.util.*;

abstract	public	class	Student{

	String	number;	//�w���ԍ�
	String	name;   //����
	ArrayList<Integer>	res_list=new	ArrayList<Integer>();
	//���C�����Ȗڂ̐��т̃��X�g

	public	String	GetNumber(){	//�w�Дԍ���Ԃ�
		return	number;
	}

	public	String	GetName(){	//���O��Ԃ�
		return	name;
	}

	public	void	AddResult(int	result){  //���C�����Ȗڂ̓_����ǉ�
		res_list.add(result);
	}

	abstract	int	GetEvaluation();	//�]����Ԃ�
}
	