// Strategy.java
public interface Strategy { // Stragegy パターンにおける、戦略を表すインタフェース

	int nextNumber(); //次の数を決める抽象メソッド
	void lastGame(boolean win); //前の回の勝敗を覚える抽象メソッド
}
