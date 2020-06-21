package	mylibrary;
import	mypub.*;
import	java.util.*;
import	java.util.Random;

public class LibraryTest{  //ランダムに借用と返却をし、Libraryの状況をみる
	public static void main(String[] args){
		Library	lib=new	Library();
		Book	b=new	Book("這い寄れ！ニャル子さん","逢空万太","GA文庫");
		Magazine m=new	Magazine("かぐや様は告らせたい", "集英社",1,1);

		int	Array_number;	//何番目の要素かを表す変数
		int	i=0;		//何回借りて返却するかのカウンター変数
		int	kaguya;		//magazineの巻数のカウンター変数

		lib.addList(b);
		lib.addList(new	Book("SAO","川原礫","KADOKAWA"));
		lib.addList(new	Book("これはゾンビですか？","木村心一","富士見書房"));
		lib.addList(new	Book("ストライク･ザ･ブラッド","三雲岳斗","KADOKAWA"));
		lib.addList(new	Book("転生したらスライムだった件","伏瀬","マイクロマガジン"));
		lib.addList(new	Book("この素晴らしい世界に祝福を","暁なつめ","KADOKAWA"));
		lib.addList(new	Book("とある魔術の禁書目録","鎌池和馬","KADOKAWA"));
		lib.addList(new	Book("緋弾のアリア","赤松中学","メディアファクトリー"));
		lib.addList(new	Book("緋色の研究","コナン･ドイル","新潮文庫"));
		lib.addList(m);
		lib.addList(new Magazine("ウロボロス", "新潮社",11,1));				lib.addList(new Magazine("七つの大罪", "講談社",1,1));				lib.addList(new Magazine("To LOVEる", "集英社",1,1));				lib.addList(new Magazine("To LOVEる　ダークネス", "集英社",21,1));		
		lib.addList(new Magazine("アカメが斬る！", "スクエア・エニックス",1,1));
		lib.addList(new Magazine("めだかボックス", "集英社",1,1));			lib.addList(new Magazine("日刊観音像", "集英社",1,1));
		while(true){	//ランダムで借りてくる
			Array_number=(int)(Math.random()*100);

			if(Array_number<lib.getArrayList().size()){
				lib.getArrayList().get(Array_number).lent();
				//System.out.println(lib.GetArrayList().get(Array_number));
				//確認用
				i++;
			}

			if(i==10)	break;
		}

		i=0;

		while(true){	//ランダムで返す
			Array_number=(int)(Math.random()*100);

			if(Array_number<lib.getArrayList().size()){
				lib.getArrayList().get(Array_number).returned();				//System.out.println(lib.GetArrayList().get(Array_number));
				//確認用
				i++;
			}

			if(i==10)	break;
		}

		lib.libraryHas(); //現在のLibraryの状態を表示


/*
//確認用
		for(int	s=0;s<lib.GetArrayList().size();s++) //現在のLibraryの状態を表示
		{
			System.out.println(lib.getArrayList().get(s));
		}
*/




		
	}
}
