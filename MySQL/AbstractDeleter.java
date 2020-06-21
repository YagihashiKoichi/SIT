/**
 * データベース(animedb)にある指定された条件のデータを
 * １つデータベース上から削除するクラス
 * @author Koichi.Yagihashi
 * @version 1.0
 */

import java.io.*;
import java.sql.*;

public abstract class AbstractDeleter {
	
	/**
	 * 削除の条件に該当するデータを検索する条件式を作成する
	 * @param where 削除する対象の条件を示すString
	 * @return 削除の条件に該当するデータを検索する条件式
	 */
	public abstract String makeQuery(String where);		//該当するデータを持ってくるための条件式の作成
	
	/**
	 * 削除の条件に該当するデータが１つのとき削除する条件式を作成する
	 * @param where 削除する対象の条件を示すString
	 * @return 削除の条件に該当するデータを削除する条件式
	 */
	public abstract String deleteMakeQuery(String where);	//削除の条件式の作成
	
	/**
	 * (削除対象が複数ある場合)ユーザーが選択したデータの主キーを削除の条件とした
	 * 条件式を作成
	 * @param result 削除対象の検索結果を示すResultSet
	 * @return ユーザーが選択したデータの主キーを削除の条件とした条件式
	 */
	public abstract String redeleteMakeQuery(ResultSet result);	//選択されたデータの削除する条件式を作成
	
	/**
	 * (削除対象が複数ある場合)削除対象となりうるデータの一覧を番号をつけて表示
	 * @param result 削除対象となりうるデータの検索結果を示すResultSet
	 */
	public abstract void showItem(ResultSet result);
	
	/**
	 * データベース(animedb)にある指定された条件のデータを
	 * データベース上から１つ削除する
	 * @param where 削除対象になりうるデータの条件
	 * @return 削除が成功した場合はtrue,失敗した場合はfalse
	 */
	public final Boolean SetAndDelete(String where) {
		Connection conn = null;
		try {
			conn = DriverManager.getConnection(
			"jdbc:mysql://localhost/animedb?useSSL=false", "root", "SITmeDB"
			);
			
			BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
			
			Statement stm=conn.createStatement();
			String sql = makeQuery(where);		//条件式をセット
			ResultSet old_result=stm.executeQuery(sql);
			old_result.last();
			int item_count=old_result.getRow();
			old_result.beforeFirst();
			
			switch(item_count){
				case 0:
					System.out.println("削除するための条件が存在しません。");
					return false;
			
				case 1:
					String sql2=deleteMakeQuery(where);	//削除の条件式をセット
					System.out.println(sql2);
					stm.executeUpdate(sql2);;		//削除を実行
					System.out.println("削除が成功しました。");
					return true;
				
				default:
					int item_number;
					System.out.println("該当する項目が複数見つかりました。");
					System.out.println("削除したい番号を選択してください");
					System.out.println("該当する項目ない場合0を入力すると削除を中止できます。");
					showItem(old_result);
					
					while(true){
						item_number = Integer.parseInt(reader.readLine());
						if(item_number==0){
							System.out.println("削除を中止します。");
							return false;
						}else if((0<item_number)&&(item_number<=item_count)){
							old_result.absolute(item_number);	//ユーザーが選んだ行に移動
							String sql3=redeleteMakeQuery(old_result);
							stm.executeUpdate(sql3);
							break;
						}else{
							System.out.println("選択項目の番号から選んでください。");
						}
					}
					System.out.println("削除が成功しました。");
			}
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
		
		return true;
	}
}
