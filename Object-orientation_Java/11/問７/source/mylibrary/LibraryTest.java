package	mylibrary;
import	mypub.*;
import	java.util.*;
import	java.util.Random;

public class LibraryTest{  //ランダムに借用と返却をし、Libraryの状況をみる
	public static void main(String[] args){
		Library	lib=new	Library();



		try{
			Book	b=new	Book("0000000000001","這い寄れ！ニャル子さん","逢空万太","GA文庫",1996);
			lib.addList(b);
		}

		catch(Exception	e){
			System.out.println(e);
		}


		try{
			Magazine m=new	Magazine("0000000000017","かぐや様は告らせたい", "集英社",1,1,1996);
		}

		catch(Exception	e){
			System.out.println(e);
		}





		int	Array_number;	//何番目の要素かを表す変数
		int	i=0;		//何回借りて返却するかのカウンター変数
		int	kaguya;		//magazineの巻数のカウンター変数


		try{
			lib.addList(new	Book("0000000000002","SAO","川原礫","KADOKAWA",1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}

		
		try{
			lib.addList(new	Book("0000000000002","SAO","川原礫","KADOKAWA",1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}



		try{
			lib.addList(new	Book("0000000000003","これはゾンビですか？","木村心一","富士見書房",-1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}

		try{
			lib.addList(new	Book("0000000000004111","ストライク･ザ･ブラッド","三雲岳斗","KADOKAWA",1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}


		try{
			lib.addList(new	Book("0000000000005","転生したらスライムだった件","伏瀬","マイクロマガジン",1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}

		try{
			lib.addList(new	Book("0000000000006","この素晴らしい世界に祝福を","暁なつめ","KADOKAWA",1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}

		try{
			lib.addList(new	Book("0000000000007","とある魔術の禁書目録","鎌池和馬","KADOKAWA",1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}

		try{
			lib.addList(new	Book("0000000000008","緋弾のアリア","赤松中学","メディアファクトリー",1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}

		try{
		lib.addList(new	Book("0000000000009","緋色の研究","コナン･ドイル","新潮文庫",1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}

		try{
			lib.addList(new Magazine("0000000000010","ウロボロス", "新潮社",11,1,1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}

		try{				
			lib.addList(new Magazine("0000000000011","七つの大罪", "講談社",1,1,1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}

		try{
		lib.addList(new Magazine("0000000000012","To LOVEる", "集英社",1,1,1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}

		try{
			lib.addList(new Magazine("0000000000013","To LOVEる　ダークネス", "集英社",21,1,1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}


		try{
			lib.addList(new Magazine("0000000000014","アカメが斬る！", "スクエア・エニックス",1,1,1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}


		try{
			lib.addList(new Magazine("0000000000015","めだかボックス", "集英社",1,1,1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}


		try{
		lib.addList(new Magazine("0000000000016","日刊観音像", "集英社",1,1,1996));
		}

		catch(Exception	e){
			System.out.println(e);
		}



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
