// ZyankenGame.java
// �قȂ�헪�����v���C���[���킹��v���O����
public class ZyankenGame {
	public static void main(String[] args) {
		Player p1 = new Player("Taro",new RandomStrategy());
		//���O"Taro" �C�헪 AnotherStrategy �̃v���C���[p1 �����
		Player p2 = new Player("Hanako",new AnotherStrategy());
		//���O"Hanako"�A�헪 RandomStrategy �̃v���C���[p2 �����

		for(int i=0; i<100; i++) {
			int p1_nextNo = p1.nextNumber();
			int p2_nextNo = p2.nextNumber();
			System.out.println(p2_nextNo);

			if ((p1_nextNo == 0 && p2_nextNo == 1)||(p1_nextNo == 1 && p2_nextNo == 2)||(p1_nextNo == 2 && p2_nextNo == 0)) {
			// p1 ������
			System.out.println("Winner:" + p1);
			p1.win();
			p2.lose();
			} else if ((p2_nextNo == 0 && p1_nextNo == 1)||(p2_nextNo == 1 && p1_nextNo == 2)||(p2_nextNo == 2 && p1_nextNo == 0)) { // p2 ������
				System.out.println("Winner:" + p2);
				p1.lose();
				p2.win();
			} else { // ��������
				System.out.println("Even.");
				p1.even();
				p2.even();
			}
		}
	}
}