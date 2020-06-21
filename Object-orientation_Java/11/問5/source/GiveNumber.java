//GiveNumber.java
//ファイルから整数を読み込んで、生徒に学番を与えるプログラム

import	java.io.*;

public class GiveNumber {
	public static void main(String[] args) {

		try{
			FileReader in = new FileReader("number.txt");
			//ファイルを生成
			BufferedReader reader = new BufferedReader(in);
			String	line;

			while((line=reader.readLine())!=null){
				Student	s=new	Student(Integer.parseInt(line),"No_name");
				System.out.println(s.toString());
			}

		reader.close();	//ファイルを閉じる

		}catch(FileNotFoundException	e){
			System.out.println("ファイルが見つかりません");
		}catch(IOException	e){
			System.out.println("その他のエラー");
		}
	}
}