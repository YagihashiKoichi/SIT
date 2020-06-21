package	evaluation;
import	java.util.*;

abstract	public	class	Student{

	String	number;	//学生番号
	String	name;   //氏名
	ArrayList<Integer>	res_list=new	ArrayList<Integer>();
	//履修した科目の成績のリスト

	public	String	GetNumber(){	//学籍番号を返す
		return	number;
	}

	public	String	GetName(){	//名前を返す
		return	name;
	}

	public	void	AddResult(int	result){  //履修した科目の点数を追加
		res_list.add(result);
	}

	abstract	int	GetEvaluation();	//評価を返す
}
	