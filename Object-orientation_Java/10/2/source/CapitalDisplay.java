// CapitalDisplay java
// NormalDisplay���Q�l�ɂ��āA�������啶���ɂ��ďo�͂���N���X���`����B
// ���̃N���X�ł́A�w�b�_��==PRINT CAPITAL==�Əo�J���A�w�b�_��==TEXT END==�Əo�J����B
// TemplateMethodTest.java
//�e���v���[�g���\�b�h�̃e�X�g�̂��߂̃N���X

public	class	CapitalDisplay	extends AbstractDisplay{

	private String text ;
/*
* �^����ꂽ��������f�[�^�Ƃ��Ď������邽�߂̃R���X�g���N�^
* @param text private�ȃt�B�[���h�ɐݒ肳��镶����
*/

	public CapitalDisplay(String text) {
		this.text = text.toUpperCase();
	}
/*
* AbtractDisplay�N���X�̒��ۃ��\�b�hdisplayHeader()�̎���
*/
	public void displayHeader(){
		System.out.println("== PRINT TEXT ==");
	}

/*
* AbtractDisplay�N���X�̒��ۃ��\�b�hdisplayBody()�̎���
* ����������̂܂܏o�J����B
*/
	public void displayBody() {
		System.out.println(text);
	}

/*
* AbtractDisplay�N���X�̒��ۃ��\�b�hdisplayBody()�̎���
* ����������̂܂܏o�J����B
*/

	public String toUpperCase(){
		return	text;
	}

/*
* AbtractDisplay �N���X�̒��ۃ��\�b�h displayFooter()�̎���
*/
	public void displayFooter(){
		System.out.println("== TEXT END ==");
	}
}
