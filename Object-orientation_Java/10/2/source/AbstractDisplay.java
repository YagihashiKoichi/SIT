// AbstractDisplay.java
/**
* Template Method �p�^�[���� AbstractClass
* �w�b�_�ƃt�b�^�����Ė{�̂��o�͂��邽�߂̒��ۃN���X
*/
public abstract	class AbstractDisplay {		//�w�b�_���o�J���钊�ۃ��\�b�h
	
	public	abstract void displayHeader();	//�{�̂��o�͂��钊�ۃ��\�b�h
	public	abstract void displayBody();		//�t�b�^���o�͂��钊�ۃ��\�b�h
	public abstract void displayFooter();	//�S�̂��o�J���邽�߂̃e���v���[�g�ƂȂ郁�\�b�h

	public final void display() { 		//�o�J�̎�����^����B�������ЂȌ^�̂݁B

		displayHeader();
		displayBody();
		displayFooter();
	}
}