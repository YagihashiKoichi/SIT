package	mypub;
/**
ISBNが13桁ではないときの例外
*/
public	class	NotAdmitTheISBN	extends UsersException{
	public	NotAdmitTheISBN(){
		super("ISBN番号が条件を満たしていません");
	}
}