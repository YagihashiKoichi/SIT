/**
 * データベース(animedb)にある指定された条件のデータを
 * １つ更新するクラス
 * @author Koichi.Yagihashi
 * @version 1.0
 */

import java.io.*;
import java.sql.*;

public abstract class AbstractUpdater {
	
	/**
	 * 更新の条件に該当するデータを検索する条件式を作成する
	 * @param where 更新する対象の条件を示すString
	 * @return 更新の条件に該当するデータを検索する条件式
	 */
	public abstract String makeQuery(String where);	//該当するデータを持ってくるための条件式の作成
	
	/**
	 * 更新の条件に該当するデータが１つのとき更新する条件式を作成する
	 * @param where 更新する対象の条件を示すString
	 * @return 更新の条件に該当するデータを更新する条件式
	 */
	public abstract String updateMakeQuery(String set,String where,ResultSet result);	//アップデートの条件式の作成
	
	/**
	 * (更新対象が複数ある場合)ユーザーが選択したデータの主キーを更新の条件とした
	 * 条件式を作成
	 * @param result 更新対象の検索結果を示すResultSet
	 * @return ユーザーが選択したデータの主キーを更新の条件とした条件式
	 */
	public abstract String reupdateMakeQuery(String set,ResultSet result);	//複数ある場合選択されたものに対する条件式の作成
	
	/**
	 * (更新対象が複数ある場合)更新対象となりうるデータの一覧を番号をつけて表示
	 * @param result 更新対象となりうるデータの検索結果を示すResultSet
	 */
	public abstract void showItem(ResultSet result);	//該当したデータ一覧を表示
	
	/**
	 * データベース(animedb)にある指定された条件のデータを
	 * １つ更新する
	 * @param where 更新対象になりうるデータの条件
	 * @return 更新が成功した場合はtrue,失敗した場合はfalse
	 */
	public final Boolean SetAndUpdate(String where,String set) {
		Connection conn = null;
		try {
			
			BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
			conn = DriverManager.getConnection(
				"jdbc:mysql://localhost/animedb?useSSL=false", "root", "SITmeDB"
				);

			Statement stm1=conn.createStatement();
			
			String sql1 = makeQuery(where);	//該当するデータを絞る条件式
			ResultSet old_result=stm1.executeQuery(sql1);
		
			old_result.last();
			int item_count=old_result.getRow();
			old_result.beforeFirst();
			
			switch(item_count){
				case 0:
					System.out.println("変更するための条件が存在しません。");
					return false;
			
				case 1:
					String sql2=updateMakeQuery(set,where,old_result);	//アップデートの条件式をセット
					stm1.executeUpdate(sql2);		//アップデートを実行
					System.out.println("アップデートが成功しました。");
					return true;
				
				default:
					int item_number;
					System.out.println("該当する項目が複数見つかりました。");
					System.out.println("変更したい番号を選択してください");
					System.out.println("該当する項目ない場合0を入力するとアップデートを中止できます。");
					showItem(old_result);
					
					while(true){
						item_number = Integer.parseInt(reader.readLine());
						if(item_number==0){
							System.out.println("アップデートを中止します。");
							return false;
						}else if((0<item_number)&&(item_number<=item_count)){
							old_result.absolute(item_number);	//ユーザーが選んだ行に移動
							String sql3=reupdateMakeQuery(set,old_result);
							stm1.executeUpdate(sql3);
							break;
			
						}else{
							System.out.println("選択項目の番号から選んでください。");
						}
					}
					System.out.println("アップデートが成功しました。");
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