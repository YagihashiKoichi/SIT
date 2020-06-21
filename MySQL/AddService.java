/**
 * 配信サービスのデータをデータベース(animedb)に追加するクラス
 * @author Koichi.Yagihashi
 * @version 1.0
 */
import java.sql.ResultSet;
import java.sql.SQLException;

public class AddService extends AbstractAdder{
	
	/**
	 * 既存の主キー（サービスID）の最大値を検索する条件式を作成する
	 * @return 既存の主キー（サービスID）の最大値を検索する条件式
	 */
	public String makeKeyQuery(){
		String sql = "SELECT max(配信サービスID) as maxid FROM 配信サービス";
		return sql;
    }
	
	public String makeQuery(String value1) {
		return null;
	}

	/**
	 * 追加する配信サービスのサービス名、URLと同じデータを検索する条件式を作成する
	 * @param value1 追加する配信サービスのサービス名を示すString
	 * @param value2 追加する配信サービスのURLを示すString 
	 * @return 追加する配信サービスのサービス名、URLが同じデータを検索する条件式
	 */
	public String makeQuery(String value1, String value2) {
		String sql = "SELECT *  FROM 配信サービス WHERE サービス名='" + value1 + "' AND URL='" + value2 + "'";
		return sql;
	}

	public String makeQuery(String value1, String value2, String value3) {
		return null;
	}

	public String addMakeQuery(ResultSet result, String value1) {
		return null;
	}

	/**
	 * データを追加するための条件式を作成する
	 * @param result 既存の主キー（配信サービスID）の最大値の検索結果を示すResultSet 
	 * @param value1 追加する配信サービスのサービス名を示すString
	 * @param value2 追加する配信サービスのURLを示すString 
	 * @return 配信サービスを追加する条件式
	 */
	public String addMakeQuery(ResultSet result, String value1, String value2) {
		String sql = null;
		try {
			result.next();
			int maxid = result.getInt("maxid");
			
		    sql = "insert into 配信サービス value(" + (maxid+1) + ",'" + value1 + "','" + value2 + "')";
		    
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
		
		return sql;
	}

	public String addMakeQuery(ResultSet result, String value1, String value2,
			String value3) {
		return null;
	}

	/**
	 * 追加する配信サービスのサービス名、URLと重複するものを表示
	 * @param result 追加する配信サービスのサービス名、URLと重複するデータの検索結果を示すResultSet 
	 */
	public void showItem(ResultSet result) {
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("番号\tサービス名\tURL");
			
			while(result.next()){
				String service = result.getString("サービス名");
				String url = result.getString("URL");
				System.out.println(count + ":" + service + ":" + url);
				count++;
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}

