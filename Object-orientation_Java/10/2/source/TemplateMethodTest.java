public class TemplateMethodTest {
	public static void main(String [] args) {

// "He11o, world."を持つ CapitalDisplay のインスタンスを1個作る
	AbstractDisplay d1 = new CapitalDisplay("He11ow");	
// "Hello，world."を持つ NormalDisplay のインスタンスを1個作る
	AbstractDisplay d2 = new NormalDisplay("Hellow");	
	d1.display(); // CapitalDisplay を使って大文字で出カ
	d2.display(); // NormalDisplay を使ってそのまま出力
	}
}