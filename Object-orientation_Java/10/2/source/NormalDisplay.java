// NormalDisplay.java
//����������̂܂܏o�͂���N���X

public class NormalDisplay extends AbstractDisplay {	 // AbstractDisplay ���p������

	private String text ;
/*
* �^����ꂽ��������f�[�^�Ƃ��Ď������邽�߂̃R���X�g���N�^
* @param text private�ȃt�B�[���h�ɐݒ肳��镶����
*/

	public NormalDisplay(String text) {
		this.text = text;
	}
/*
* AbtractDisplay�N���X�̒��ۃ��\�b�hdisplayHeader()�̎���
*/
	public void displayHeader(){
		System.out.println("-- print text --");
	}
/*
* AbtractDisplay�N���X�̒��ۃ��\�b�hdisplayBody()�̎���
* ����������̂܂܏o�J����B
*/
	public void displayBody() {
		System.out.println(text);
	}
/*
* AbtractDisplay �N���X�̒��ۃ��\�b�h displayFooter()�̎���
*/
	public void displayFooter(){
		System.out.println("-- text end --");
	}
}