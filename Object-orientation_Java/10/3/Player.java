// PlusOneStrategy.java
// NormalStrategyを参考にして、前の回で勝っていれば1足した数(前の回が9で、勝っていれば 0) // を次の回の数とする戦略を表す PlusOneStrategy を定義せよ。
// Player.java
// Strategyパターンで次の数を決める戦略を切り替えられるようにしたゲームのプレイヤークラス
// Player
public class Player {
	private String name; //プレイヤーの名前
	private RandomStrategy strategy; //プレイヤーが取る戦略
	private int wincount; //プレイヤーがここまでのゲームで勝った数
	private int losecount; //プレイヤーがここまでのゲームで負けた数
	private int gamecount; //プレイヤーがここまでに行ったゲームの数

	public Player(String name,RandomStrategy strategy) {
		// 名前と戦略を与えられて生成するコンストラクタ
		this.name = name;
		this.strategy = strategy;
	}

	public int nextNumber() {
		return strategy.nextNumber(); //自身の持つ戦略に次の数の決定を委譲する
	}

	public void win() { //勝った場合にすること
		strategy.lastGame(true);
		wincount++;
		gamecount++;
	}

	public void lose() { //負けた場合にすること
		strategy.lastGame(false);
		losecount++;
		gamecount++;
	}

	public void even() { //引き分けだった場合にすること
		gamecount++;
	}

	public String toString() {
		return "[" + name + ":" + gamecount + " games, " +
wincount + " win，" + losecount + " lose" + "]";
	}
}
