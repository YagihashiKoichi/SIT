// CapitalDisplay java
// NormalDisplayを参考にして、文字列を大文字にして出力するクラスを定義せよ。
// このクラスでは、ヘッダは==PRINT CAPITAL==と出カし、ヘッダは==TEXT END==と出カする。
// TemplateMethodTest.java
//テンプレートメソッドのテストのためのクラス

public	class	CapitalDisplay	extends AbstractDisplay{

	private String text ;
/*
* 与えられた文字列をデータとして持たせるためのコンストラクタ
* @param text privateなフィールドに設定される文字列
*/

	public CapitalDisplay(String text) {
		this.text = text.toUpperCase();
	}
/*
* AbtractDisplayクラスの抽象メソッドdisplayHeader()の実装
*/
	public void displayHeader(){
		System.out.println("== PRINT TEXT ==");
	}

/*
* AbtractDisplayクラスの抽象メソッドdisplayBody()の実装
* 文字列をそのまま出カする。
*/
	public void displayBody() {
		System.out.println(text);
	}

/*
* AbtractDisplayクラスの抽象メソッドdisplayBody()の実装
* 文字列をそのまま出カする。
*/

	public String toUpperCase(){
		return	text;
	}

/*
* AbtractDisplay クラスの抽象メソッド displayFooter()の実装
*/
	public void displayFooter(){
		System.out.println("== TEXT END ==");
	}
}
