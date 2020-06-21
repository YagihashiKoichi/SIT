import	java.io.*;

class Division{
	public static void main(String[] args){

		String	linex="";	//xの文字列
		String	liney="";	//yの文字列
		int	x,y,answer;

		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

		while(true){

			try{
				linex=reader.readLine();	//ｘを標準入力
				liney=reader.readLine();	//ｙを標準入力

				x=Integer.parseInt(linex);	//数値に変換
				y=Integer.parseInt(liney);	//数値に変換
				answer=x/y;

				System.out.println(x+"を"+y+"で割った商は"+answer+"です");
			}

			catch(NumberFormatException	e){	//文字変換で例外
				if((linex.equals("END"))||(liney.equals("END"))){
					break;
				}else{
					System.out.println("入力が数値ではありません");
				}
			}

			catch(ArithmeticException	e){	//算術計算で例外
				System.out.println("計算が不可能です");
			}

			catch(Exception	e){
				System.out.println("原因不明のエラーです");
			}
		}
	}
}
		