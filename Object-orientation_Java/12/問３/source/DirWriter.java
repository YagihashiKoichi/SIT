import java.io.*;
import java.util.*;

/*
第二引数であるファイルに第一引数であるカレントディレクトリ
内にある名称のディレクトリの中にある
ファイルの一覧を書き出すクラス
*/
public class DirWriter{
	
	void Print(String dirname,String filename){

		File newfile = new File(filename);

		File dir = new File(dirname);				//指示されたディレクトリ
		File[] dirlist = dir.listFiles();			//ディレクトリ内のファイル一覧
		ArrayList<File> Directory = new ArrayList<File>();	//ディレクトリ一覧

		int dirlength;	//dirlength:ディレクトリの数
		int counter=0;
		int length=dirlist.length;	//ディレクトリ内のファイルの数
		int i=0;	//カウンター変数
		int s=0;	//カウンター変数

		try{
			newfile.createNewFile();		 //新規ファイルを作成
			FileWriter out=new FileWriter(filename);
			BufferedWriter bw=new BufferedWriter(out);
			PrintWriter writer=new PrintWriter(bw);	//書き込みの宣言

			writer.println("Directory:"+dirname);
			while(true){	
				if(i!=0){				//最初は入らない
					s=i-1;
					if(Directory.size()<i)	break;
					dirlist=Directory.get(s).listFiles();
					length=dirlist.length;
					writer.println("Directory:" + Directory.get(s).getName());
				}
				for(int t=0;t<length;t++){		//ディレクトリ内のファイルをすべて確認
					if(dirlist[t].isDirectory()){   //ディレクトリのとき追加
						Directory.add(dirlist[t]); 		
						writer.println("    " + dirlist[t].getName() + " はディレクトリです。");
					          //空白ディレクトリと区別しやすくするため
				}

					else {	//ファイル名を書き込む
						writer.println("    " + dirlist[t].getName());
					}
				}
				i++;
			}
			writer.close();   //書き込み終了
		}

		catch (Exception e){      //原因不明のエラー
			System.out.print(e);
		}
	}

}