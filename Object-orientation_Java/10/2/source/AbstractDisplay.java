// AbstractDisplay.java
/**
* Template Method パターンの AbstractClass
* ヘッダとフッタをつけて本体を出力するための抽象クラス
*/
public abstract	class AbstractDisplay {		//ヘッダを出カする抽象メソッド
	
	public	abstract void displayHeader();	//本体を出力する抽象メソッド
	public	abstract void displayBody();		//フッタを出力する抽象メソッド
	public abstract void displayFooter();	//全体を出カするためのテンプレートとなるメソッド

	public final void display() { 		//出カの実装を与える。ただしひな型のみ。

		displayHeader();
		displayBody();
		displayFooter();
	}
}