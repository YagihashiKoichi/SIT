/*
名前と年齢を出力し、その後１つ上の年齢で
名前と年齢を出力する関数。
*/
public	class Person2{
	public	static	void	main(String[]	args){
		Person	p1=new	Person();
		p1.setName(args[0]);		      
		p1.setAge(Integer.parseInt(args[1])); //数字を数値に変換
		p1.greet();
		p1.sumAge();
		p1.greet();
	}
}