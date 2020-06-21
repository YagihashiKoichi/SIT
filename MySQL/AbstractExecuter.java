/**
 * データベース(animedb)にあるデータ表示するための
 * 抽象クラス
 * @author Koichi.Yagihashi
 * @version 1.0
 */
import java.sql.*;
public abstract class AbstractExecuter {
	
	/**
	 * データ検索の条件式を作成する
	 * @return データ検索の条件式
	 */
	public abstract String makeQuery();		//条件式をセット
	
	/**
	 * 検索する条件式に該当したデータを表示する
	 * @param result 検索結果を示すResultSet
	 */
	public abstract void showResult(ResultSet result);	//検索結果一覧を表示
	
	/**
	 * データベース(animedb)にあるデータから
	 * 条件式に該当するデータを表示する
	 */
	public final void queryAndShow() {
		Connection conn = null;
		try {
			 
			conn = DriverManager.getConnection(
				"jdbc:mysql://localhost/animedb?useSSL=false", "root", "SITmeDB"
				);
			Statement stm=conn.createStatement();
			String sqlString = makeQuery();		//条件式をセット
			ResultSet result=stm.executeQuery(sqlString);
			showResult(result);			//検索結果一覧表示
			conn.close();
		} catch (SQLException se) {
			System.out.println("SQL Error 1: " + se.toString() + " "
				+ se.getErrorCode() + " " + se.getSQLState());
		} catch (Exception e) {
			System.out.println("Error: " + e.toString() + e.getMessage());
		}finally {
			if (conn != null) {
				try {
					conn.close();
				} catch (SQLException e) {
					System.out.println("MySQLのクローズに失敗しました。");
				}
			}
		}
	}
}
