import	java.io.*;

public class NumberReader {
	public static void main(String[] args) {

		try{
			FileReader in = new FileReader("number.txt");
			BufferedReader reader = new BufferedReader(in);
			String	line;

			while((line=reader.readLine())!=null){
				System.out.println(line);
			}

		reader.close();

		}catch(FileNotFoundException	e){
			System.out.println("ファイルが見つかりません");
		}catch(IOException	e){
			System.out.println("その他のエラー");
		}
	}
}
	