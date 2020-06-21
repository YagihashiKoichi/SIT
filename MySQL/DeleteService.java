/**
 * データベース(animedb)にある指定された条件のデータを
 * １つデータベース上から削除するクラス
 * @ Koichi.Yagihashi
 */
//上と下の使わないメソッドを削除
import java.sql.ResultSet;
import java.sql.SQLException;

public class DeleteService extends AbstractDeleter{
	
	/**
	 * 削除の条件に該当するデータを検索する条件式を作成する
	 * @param where 削除する配信サービス名を示すString
	 * @return 削除の条件に該当するデータを検索する条件式
	 */
	public String makeQuery(String where){
		String sql = "SELECT * FROM 配信サービス WHERE サービス名='" + where + "'";
		return sql;
    }
	
	/**
	 * 削除の条件に該当するデータが１つのとき削除する条件式を作成する
	 * @param where 削除する配信サービス名を示すString
	 * @return 削除の条件に該当するデータを削除する条件式
	 */
	public String deleteMakeQuery(String where){
		String sql = "DELETE 配信サービス,配信 FROM 配信サービス" +
				     " LEFT JOIN 配信 ON 配信サービス.配信サービスID=配信.配信サービスID" +
				     " WHERE サービス名='" + where + "'";
		return sql;
    }


	/**
	 * (削除対象が複数ある場合)ユーザーが選択したデータの主キー(配信サービスID)を削除の条件とした
	 * 条件式を作成
	 * @param result 削除対象の検索結果を示すResultSet
	 * @return ユーザーが選択したデータの主キー(配信サービスID)を削除の条件とした条件式
	 */
	public String redeleteMakeQuery(ResultSet result){
		String sql = null;
		String id;
		try {
			id = result.getString("配信サービスID");
			sql = "DELETE 配信サービス,配信 FROM 配信サービス" +
				     " LEFT JOIN 配信 ON 配信サービス.配信サービスID=配信.配信サービスID" +
				     " WHERE 配信サービス.配信サービスID='" + id + "'";
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return sql;
	}
	
	/**
	 * (削除対象が複数ある場合)削除対象となりうるデータの一覧を番号をつけて
	 * URLを含めて表示
	 * @param result 削除対象となりうるデータの検索結果を示すResultSet
	 */
	public void showItem(ResultSet result){
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("番号　　サービス名　　　　　　URL");
			System.out.println("0:削除を中止します。");
			
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
}	