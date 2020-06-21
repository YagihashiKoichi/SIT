/*
まず入力した名称でファイルを作成する。
(このとき拡張子も忘れずに)
次に入力から得た名前のディレクトリ内にあるファイルの一覧を
先ほど作ったファイルに書き込むクラス
*/
public class DirList{
	public static void main(String[] args){
		Input in = new Input();
		DirWriter writer = new DirWriter();
		System.out.print("ファイルの一覧を書き込むファイル名を決めてください");
		String filename = in.inputString("");	//入力を得る
		System.out.print("ディレクトリ名：");
		String dirname = in.inputString("");	//入力を得る
		writer.Print(dirname,filename);		//ディレクトリの一覧を書き込む
	}
}
