package	evaluation;
public	class	Graduate	extends	Student{

	int	sum=0;		//���C�����Ȗڂ̍��v�_
	int	res_result;	//�C�������̐���
	int	average;
	//�u���C�����Ȗڂ̕��ϓ_�v�Ɓu�C�������̐��т́v����

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

		return	(average+res_result)/2;	//���ς�Ԃ�
	}
}