public class TemplateMethodTest {
	public static void main(String [] args) {

// "He11o, world."������ CapitalDisplay �̃C���X�^���X��1���
	AbstractDisplay d1 = new CapitalDisplay("He11ow");	
// "Hello�Cworld."������ NormalDisplay �̃C���X�^���X��1���
	AbstractDisplay d2 = new NormalDisplay("Hellow");	
	d1.display(); // CapitalDisplay ���g���đ啶���ŏo�J
	d2.display(); // NormalDisplay ���g���Ă��̂܂܏o��
	}
}