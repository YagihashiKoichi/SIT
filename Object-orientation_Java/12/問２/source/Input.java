import java.io.*;
/**
* �L�[�{�[�h����̓��͂��s�����߂̃N���X
*/
public class Input {
	private final String ERROR_INPUT = "�G���[�F���͂Ɍ�肪����܂��B";

	private String input() throws IOException {

		String line;
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
			//�����⑫�B�W�����͂�����͂̂��߂�reader
		line = reader.readLine();// �����⑫�Breader ����1 �s�ǂ�

		return line;
	}
/**
* ������̓���
* �����ŗ^����ꂽ���b�Z�[�W�o�͌�A�L�[�{�[�h������͂��ꂽ�������Ԃ��B
* ���͂ɂ������O�����������ꍇ�ɂ́A�ē��͂𑣂�
* @param String prompt:���͂𑣂����b�Z�[�W
*/

	public String inputString(String prompt) {
	
		System.out.println(prompt);

		try {
			String n = this.input(); // �����⑫�B���͂����o�����߂ɂ�?
			return n;
		    }catch(IOException e){ // �����⑫�B��O��ߑ�����悤�ɂ�
			System.out.println(ERROR_INPUT);
			return this.inputString(prompt);
		}
	}
}