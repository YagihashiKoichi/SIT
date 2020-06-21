import java.io.*;

public	class Search{

	public void searchString(String fileName,String searchString){

		try{

			//ファイルを読み込む
			FileReader fr=new FileReader(fileName);
			BufferedReader br=new BufferedReader(fr);

			//条件にあう行を画面出力
			System.out.println(searchString+"の出現は");
			String line;
			int	counter=0;
			while((line=br.readLine())!=null){
				if(line.indexOf(searchString)!=-1)
					System.out.println(counter+":"+line);

				counter++;
			}

			br.close();
			fr.close();
		}

		catch(Exception e){
			System.out.println("原因不明のエラー");
		}
	}
}
