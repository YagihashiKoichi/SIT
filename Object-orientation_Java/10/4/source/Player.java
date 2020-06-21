// Player.java
// Strategy�p�^�[���Ŏ��̐������߂�헪��؂�ւ�����悤�ɂ����Q�[���̃v���C���[�N���X
// Player
public class Player {
	private String name; //�v���C���[�̖��O
	private Strategy strategy; //�v���C���[�����헪
	private int wincount; //�v���C���[�������܂ł̃Q�[���ŏ�������
	private int losecount; //�v���C���[�������܂ł̃Q�[���ŕ�������
	private int gamecount; //�v���C���[�������܂łɍs�����Q�[���̐�

	public Player(String name,Strategy strategy) {
		// ���O�Ɛ헪��^�����Đ�������R���X�g���N�^
		this.name = name;
		this.strategy = strategy;
	}


	public int nextNumber() {
		return strategy.nextNumber(); //���g�̎��헪�Ɏ��̐��̌�����Ϗ�����
	}

	public void win() { //�������ꍇ�ɂ��邱��
		strategy.lastGame(true);
		wincount++;
		gamecount++;
	}

	public void lose() { //�������ꍇ�ɂ��邱��
		strategy.lastGame(false);
		losecount++;
		gamecount++;
	}

	public void even() { //���������������ꍇ�ɂ��邱��
		gamecount++;
	}

	public String toString() {
		return "[" + name + ":" + gamecount + " games, " +
wincount + " win�C" + losecount + " lose" + "]";
	}
}
