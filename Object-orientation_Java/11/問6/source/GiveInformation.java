//GiveInformation.java
//生徒の学番と氏名を書き出すプログラム

import	java.io.*;

public class GiveInformation{
	public static void main(String[] args) {

		try{
			FileReader in = new FileReader("number.txt");
			//ファイルを生成
			BufferedReader reader = new BufferedReader(in);

			FileWriter out = new FileWriter("student.txt");
			BufferedWriter bw = new BufferedWriter(out);
			PrintWriter writer = new PrintWriter(bw);

			String	line;

			while((line=reader.readLine())!=null){
				Student	s=new	Student(Integer.parseInt(line),"八木橋晃一");
				writer.println(s.toString());
			}

		reader.close();		//ファイルを閉じる
		writer.close();		//ファイルを閉じる

		}catch(FileNotFoundException	e){
			System.out.println("ファイルが見つかりません");
		}catch(IOException	e){
			System.out.println("その他のエラー");
		}
	}
}