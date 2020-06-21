// RandomStrategy.java
//ランダムに次の手を出すプログラム

import java.util.Random; //乱教を扱う Java のユーティリテイクラス Random をインポート
			 // Strategyインタフェースを実装するクラス RandomStrategy を宣言
public class RandomStrategy implements Strategy {

	private Random rnd = new Random(); //乱数を発生させる Random オブジェクトを持っておく
	private boolean won = false; //前回の勝敗を表す。 true であれば前回勝ったことを示す


	public int nextNumber() { //次の数を決めるメソッドをここで実装
		return rnd.nextInt(3); // 0 から 9 の範囲の整数からランダムに選んで返す
				       //0=グー,1=チョキ,2=パー
	}

	public void lastGame(boolean win) { //前の回の勝敗を覚えるメソッドをここで実装
		won = win; //与えられた真偽値を won に設定
	}
}