// NormalDisplay.java
//文字列をそのまま出力するクラス

public class NormalDisplay extends AbstractDisplay {	 // AbstractDisplay を継承する

	private String text ;
/*
* 与えられた文字列をデータとして持たせるためのコンストラクタ
* @param text privateなフィールドに設定される文字列
*/

	public NormalDisplay(String text) {
		this.text = text;
	}
/*
* AbtractDisplayクラスの抽象メソッドdisplayHeader()の実装
*/
	public void displayHeader(){
		System.out.println("-- print text --");
	}
/*
* AbtractDisplayクラスの抽象メソッドdisplayBody()の実装
* 文字列をそのまま出カする。
*/
	public void displayBody() {
		System.out.println(text);
	}
/*
* AbtractDisplay クラスの抽象メソッド displayFooter()の実装
*/
	public void displayFooter(){
		System.out.println("-- text end --");
	}
}