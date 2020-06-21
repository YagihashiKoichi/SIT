/**
 * データベース(animedb)にある指定された事務所の電話番号を
 * １つ更新するクラス
 * @author Koichi.Yagihashi
 * @version 1.0
 */

import java.sql.ResultSet;
import java.sql.SQLException;

public class UpdateOfficeNumber extends AbstractUpdater{
	
	/**
	 * (更新対象が複数ある場合)更新対象となりうるデータの一覧を番号をつけて
	 * 事務所名、更新前の電話番号、住所を含めて表示
	 * @param result 更新対象となりうるデータの検索結果を示すResultSet
	 */
	public void showItem(ResultSet result){
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("0:アップデートを中止します。");
			System.out.println("番号\t事務所名\t電話番号\t住所");
			
			while(result.next()){
				String office=result.getString("事務所名");
				String number=result.getString("電話番号");
				String address=result.getString("住所");
				System.out.println(count + ":" + office + ":" + number + ":" + address );
				count++;
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}	
	}
	
	/**
	 * 更新の条件に該当するデータを検索する条件式を作成する
	 * @param where 電話番号を更新したい事務所の事務所名を示すString
	 * @return 更新の条件に該当するデータを検索する条件式
	 */
	public String makeQuery(String where){
		String sql = "SELECT * FROM 事務所 WHERE 事務所名='" + where + "'";
		return sql;
    }

	/**
	 * 更新の条件に該当するデータが１つのとき更新する条件式を作成する
	 * @param where 電話番号を更新したい事務所の事務所名を示すString
	 * @return 更新の条件に該当する事務所の電話番号を更新する条件式
	 */
	public String updateMakeQuery(String set,String where,ResultSet result){
		String sql = "UPDATE 事務所 SET 電話番号='" + set + "' WHERE 事務所名='" + where + "'";
		return sql;
    }

	/**
	 * (更新対象が複数ある場合)ユーザーが選択したデータの主キー(事務所ID)を更新の条件とした
	 * 条件式を作成
	 * @param result 更新対象の検索結果を示すResultSet
	 * @return ユーザーが選択した事務所の主キー(事務所ID)を更新の条件とした条件式
	 */
	public String reupdateMakeQuery(String set,ResultSet result){
		String sql = null;
		int id;
		try {
			id = result.getInt("事務所ID");
			sql = "UPDATE 事務所 SET 電話番号='" + set + "' WHERE 事務所ID='" + id + "'";
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return sql;
	}
}	