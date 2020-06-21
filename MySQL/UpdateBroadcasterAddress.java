/**
 * データベース(animedb)にある指定された放送局の住所を
 * １つ更新するクラス
 * @author Koichi.Yagihashi
 * @version 1.0
 */

import java.sql.ResultSet;
import java.sql.SQLException;

public class UpdateBroadcasterAddress  extends AbstractUpdater{
	
	/**
	 * (更新対象が複数ある場合)更新対象となりうるデータの一覧を番号をつけて
	 * 局名、更新前の住所を含めて表示
	 * @param result 更新対象となりうるデータの検索結果を示すResultSet
	 */
	public void showItem(ResultSet result){
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("0:アップデートを中止します。");
			System.out.println("番号\t局名\t住所");
			
			while(result.next()){
				String broadcaster=result.getString("局名");
				String address=result.getString("住所");
				System.out.println(count + ":" + broadcaster + ":"  + address );
				count++;
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}	
	}
	
	
	/**
	 * 更新の条件に該当するデータを検索する条件式を作成する
	 * @param where 住所を更新したい放送局の局名を示すString
	 * @return 更新の条件に該当するデータを検索する条件式
	 */
	public String makeQuery(String where){
		String sql = "SELECT * FROM 放送局 WHERE 局名='" + where + "'";
		return sql;
    }
	
	/**
	 * 更新の条件に該当するデータが１つのとき更新する条件式を作成する
	 * @param where 住所を更新したい放送局の局名を示すString
	 * @return 更新の条件に該当する放送局の住所を更新する条件式
	 */
	public String updateMakeQuery(String set,String where,ResultSet result){
		String sql = "UPDATE 放送局 SET 住所='" + set + "' WHERE 局名='" + where + "'";
		return sql;
    }

	/**
	 * (更新対象が複数ある場合)ユーザーが選択したデータの主キー(放送局ID)を更新の条件とした
	 * 条件式を作成
	 * @param result 更新対象の検索結果を示すResultSet
	 * @return ユーザーが選択した放送局の主キー(放送局ID)を更新の条件とした条件式
	 */
	public String reupdateMakeQuery(String set,ResultSet result){
		String sql = null;
		int id;
		try {
			id = result.getInt("放送局ID");
			sql = "UPDATE 放送局 SET 住所='" + set + "' WHERE 放送局ID='" + id + "'";
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return sql;
	}
}	