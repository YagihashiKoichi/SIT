/*
�܂����͂������̂Ńt�@�C�����쐬����B
(���̂Ƃ��g���q���Y�ꂸ��)
���ɓ��͂��瓾�����O�̃f�B���N�g�����ɂ���t�@�C���̈ꗗ��
��قǍ�����t�@�C���ɏ������ރN���X
*/
public class DirList{
	public static void main(String[] args){
		Input in = new Input();
		DirWriter writer = new DirWriter();
		System.out.print("�t�@�C���̈ꗗ���������ރt�@�C���������߂Ă�������");
		String filename = in.inputString("");	//���͂𓾂�
		System.out.print("�f�B���N�g�����F");
		String dirname = in.inputString("");	//���͂𓾂�
		writer.Print(dirname,filename);		//�f�B���N�g���̈ꗗ����������
	}
}
