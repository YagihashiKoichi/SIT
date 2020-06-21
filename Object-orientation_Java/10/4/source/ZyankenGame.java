// ZyankenGame.java
// 異なる戦略を取るプレイヤーを戦わせるプログラム
public class ZyankenGame {
	public static void main(String[] args) {
		Player p1 = new Player("Taro",new RandomStrategy());
		//名前"Taro" ，戦略 AnotherStrategy のプレイヤーp1 を作る
		Player p2 = new Player("Hanako",new AnotherStrategy());
		//名前"Hanako"、戦略 RandomStrategy のプレイヤーp2 を作る

		for(int i=0; i<100; i++) {
			int p1_nextNo = p1.nextNumber();
			int p2_nextNo = p2.nextNumber();
			System.out.println(p2_nextNo);

			if ((p1_nextNo == 0 && p2_nextNo == 1)||(p1_nextNo == 1 && p2_nextNo == 2)||(p1_nextNo == 2 && p2_nextNo == 0)) {
			// p1 が勝ち
			System.out.println("Winner:" + p1);
			p1.win();
			p2.lose();
			} else if ((p2_nextNo == 0 && p1_nextNo == 1)||(p2_nextNo == 1 && p1_nextNo == 2)||(p2_nextNo == 2 && p1_nextNo == 0)) { // p2 が勝ち
				System.out.println("Winner:" + p2);
				p1.lose();
				p2.win();
			} else { // 引き分け
				System.out.println("Even.");
				p1.even();
				p2.even();
			}
		}
	}
}