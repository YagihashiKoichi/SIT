/*
���O�ƔN����o�͂��A���̌�P��̔N���
���O�ƔN����o�͂���֐��B
*/
public	class Person2{
	public	static	void	main(String[]	args){
		Person	p1=new	Person();
		p1.setName(args[0]);		      
		p1.setAge(Integer.parseInt(args[1])); //�����𐔒l�ɕϊ�
		p1.greet();
		p1.sumAge();
		p1.greet();
	}
}