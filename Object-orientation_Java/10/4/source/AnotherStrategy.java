//AnotherStrategy.java
//�����Ȃ����蓯������o��������v���O����

import java.util.Random; //���������� Java �̃��[�e�B���e�C�N���X Random ���C���|�[�g

public	class AnotherStrategy implements Strategy{


	private boolean won = false; //�O��̏��s��\���B true �ł���ΑO�񏟂������Ƃ�����
	private int preHand; //�O�񎩕�������������\��
	private int reserve;  //�ꎞ�I�Ɏ��ۑ�
	private Random rnd = new Random(); //�����𔭐������� Random �I�u�W�F�N�g�������Ă���

	public	void	lastGame(boolean win){
		won=win; //�^����ꂽ�^�U�l�� won �ɐݒ�
	}

	public int nextNumber() { //���̐������߂郁�\�b�h�������Ŏ���

		if(won!=false){
			preHand=reserve;
			return	preHand;
		}
		else{
			reserve=rnd.nextInt(3); // 0 ���� 3 �͈̔͂̐������烉���_���ɑI��
					        //0=�O�[,1=�`���L,2=�p�[
			return	reserve;
		}
	}
}
	