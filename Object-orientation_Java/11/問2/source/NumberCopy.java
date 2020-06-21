import	java.io.*;

public class NumberCopy {
	public static void main(String[] args) {

	//String	filename;

		try{
			FileReader in = new FileReader("number.txt");
			BufferedReader reader = new BufferedReader(in);

			FileWriter out = new FileWriter("copynumber.txt");
			BufferedWriter bw = new BufferedWriter(out);
			PrintWriter writer = new PrintWriter(bw);

			String	line;

			while((line=reader.readLine())!=null){
				writer.println(line);
			}

		reader.close();
		writer.close();

		}catch(FileNotFoundException	e){
			System.out.println("ファイルが見つかりません");
		}catch(IOException	e){
			System.out.println("その他のエラー");
		}
	}
}
	