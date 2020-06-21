package	evaluation;
public	class	Graduate	extends	Student{

	int	sum=0;		//履修した科目の合計点
	int	res_result;	//修了研究の成績
	int	average;
	//「履修した科目の平均点」と「修了研究の成績の」平均

	public	Graduate(String number, String name) {
		this.number = number;
		this.name = name;
		res_result=0;
	}

	public	void	Change_Res_result(int	res_result){
		this.res_result=res_result;
	}

	public	int	GetEvaluation(){

		for(int	i=0;i<res_list.size();i++){
			sum=sum+res_list.get(i);
		}

		average=sum/res_list.size();

		return	(average+res_result)/2;	//平均を返す
	}
}