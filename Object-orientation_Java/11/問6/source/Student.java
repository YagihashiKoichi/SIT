public class Student {
		private	int	number;	/**学生番号*/
		private	String	name;	/**氏名*/
		private	static	int	counter; /**生成されたオブジェクト数*/

		/**
	        * "学生番号 氏名"の文字列を返すメソッド
	        * @author 八木橋晃一
	        * @return "学生番号 氏名"の文字列
		*/
		public	String	toString(){
			return	"番号:"+number+"　氏名:"+name;
		}

		/**生成されたオブジェクト数を返す
                * "学生番号 氏名"の文字列を返すメソッド
	        * @author 八木橋晃一
	        * @return 生成されたオブジェクト数を表す整数
                */
		public	static	int	getCounter(){
			return	counter;
		}

		/**与えられた整数を学生番号、文字列を氏名とするコンストラクタ
	        * @author 八木橋晃一
	        * @param number	学生番号を表す整数
		* @param name	氏名を表す文字列
　　　　　　　　*/
		public	Student(int number,String name){
			this.number=number;
			this.name=name;
		}
	
}