/**
 * データベース(animedb)にある指定された配信サービスのURLを
 * １つ更新するクラス
 * @author Koichi.Yagihashi
 * @version 1.0
 */

import java.sql.ResultSet;
import java.sql.SQLException;

public class UpdateURL extends AbstractUpdater{

	/**
	 * (更新対象が複数ある場合)更新対象となりうるデータの一覧を番号をつけて
	 * サービス名、更新前のURL、住所を含めて表示
	 * @param result 更新対象となりうるデータの検索結果を示すResultSet
	 */
	public void showItem(ResultSet result){
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("0:アップデートを中止します。");
			System.out.println("番号\tサービス名\tURL");
			
			while(result.next()){
				String service=result.getString("サービス名");
				String url=result.getString("URL");
				System.out.println(count + ":" + service + ":" + url);
				count++;
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}	
	}
	
	/**
	 * 更新の条件に該当するデータを検索する条件式を作成する
	 * @param where URLを更新したい配信サービスのサービス名を示すString
	 * @return 更新の条件に該当するデータを検索する条件式
	 */
	public String makeQuery(String where){
		String sql = "SELECT * FROM 配信サービス WHERE サービス名='" + where + "'";
		return sql;
    }
	
	/**
	 * 更新の条件に該当するデータが１つのとき更新する条件式を作成する
	 * @param where URLを更新したい配信サービスのサービス名を示すString
	 * @return 更新の条件に該当する配信サービスのURLを更新する条件式
	 */
	public String updateMakeQuery(String set,String where,ResultSet result){
		String sql = "UPDATE 配信サービス SET URL='" + set + "' WHERE サービス名='" + where + "'";
		return sql;
    }

	/**
	 * (更新対象が複数ある場合)ユーザーが選択したデータの主キー(配信サービスID)を更新の条件とした
	 * 条件式を作成
	 * @param result 更新対象の検索結果を示すResultSet
	 * @return ユーザーが選択した配信サービスの主キー(配信サービスID)を更新の条件とした条件式
	 */
	public String reupdateMakeQuery(String set,ResultSet result){
		String sql = null;
		int id;
		try {
			id = result.getInt("配信サービスID");
			sql = "UPDATE 配信サービス SET URL='" + set + "' WHERE URL='" + id + "'";
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return sql;
	}
}	