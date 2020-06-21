import java.io.*;
/**
* キーボードからの入力を行うためのクラス
*/
public class Input {
	private final String ERROR_INPUT = "エラー：入力に誤りがあります。";

	private String input() throws IOException {

		String line;
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
			//ここ補足。標準入力から入力のためのreader
		line = reader.readLine();// ここ補足。reader から1 行読む

		return line;
	}
/**
* 文字列の入力
* 引数で与えられたメッセージ出力後、キーボードから入力された文字列を返す。
* 入力における例外が発生した場合には、再入力を促す
* @param String prompt:入力を促すメッセージ
*/

	public String inputString(String prompt) {
	
		System.out.println(prompt);

		try {
			String n = this.input(); // ここ補足。入力を取り出すためには?
			return n;
		    }catch(IOException e){ // ここ補足。例外を捕捉するようにせ
			System.out.println(ERROR_INPUT);
			return this.inputString(prompt);
		}
	}
}