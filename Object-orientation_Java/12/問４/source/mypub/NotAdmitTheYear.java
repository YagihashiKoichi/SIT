package	mypub;
/**
出版年が負であるときの例外
*/
public	class	NotAdmitTheYear	extends UsersException{
	public	NotAdmitTheYear(){
		super("出版年が条件を満たしていません");
	}
}
