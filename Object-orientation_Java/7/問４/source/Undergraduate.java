package	evaluation;
public	class	Undergraduate	extends	Student{

	int	sum=0;
	int	average;
	//���C�����Ȗڂ̕��ϓ_

	public Undergraduate(String number, String name) {
		this.number = number;
		this.name = name;
	}


	public	int	GetEvaluation(){

		for(int	i=0;i<res_list.size();i++){
			sum=sum+res_list.get(i);
		}

		average=sum/res_list.size();

		return	average;
	}
}