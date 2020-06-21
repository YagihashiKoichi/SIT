// RandomStrategy.java
//�����_���Ɏ��̎���o���v���O����

import java.util.Random; //���������� Java �̃��[�e�B���e�C�N���X Random ���C���|�[�g
			 // Strategy�C���^�t�F�[�X����������N���X RandomStrategy ��錾
public class RandomStrategy implements Strategy {

	private Random rnd = new Random(); //�����𔭐������� Random �I�u�W�F�N�g�������Ă���
	private boolean won = false; //�O��̏��s��\���B true �ł���ΑO�񏟂������Ƃ�����


	public int nextNumber() { //���̐������߂郁�\�b�h�������Ŏ���
		return rnd.nextInt(3); // 0 ���� 9 �͈̔͂̐������烉���_���ɑI��ŕԂ�
				       //0=�O�[,1=�`���L,2=�p�[
	}

	public void lastGame(boolean win) { //�O�̉�̏��s���o���郁�\�b�h�������Ŏ���
		won = win; //�^����ꂽ�^�U�l�� won �ɐݒ�
	}
}