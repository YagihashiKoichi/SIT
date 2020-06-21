//AnotherStrategy.java
//負けない限り同じ手を出し続けるプログラム

import java.util.Random; //乱教を扱う Java のユーティリテイクラス Random をインポート

public	class AnotherStrategy implements Strategy{


	private boolean won = false; //前回の勝敗を表す。 true であれば前回勝ったことを示す
	private int preHand; //前回自分が言った数を表す
	private int reserve;  //一時的に手を保存
	private Random rnd = new Random(); //乱数を発生させる Random オブジェクトを持っておく

	public	void	lastGame(boolean win){
		won=win; //与えられた真偽値を won に設定
	}

	public int nextNumber() { //次の数を決めるメソッドをここで実装

		if(won!=false){
			preHand=reserve;
			return	preHand;
		}
		else{
			reserve=rnd.nextInt(3); // 0 から 3 の範囲の整数からランダムに選ぶ
					        //0=グー,1=チョキ,2=パー
			return	reserve;
		}
	}
}
	