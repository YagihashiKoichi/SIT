/**
 * 原作のデータをデータベース(animedb)に追加するクラス
 * @author Koichi.Yagihashi
 * @version 1.0
 */
import java.sql.ResultSet;
import java.sql.SQLException;

public class AddOriginal extends AbstractAdder{
	
	/**
	 * 既存の主キー（原作ID）の最大値を検索する条件式を作成する
	 * @return 既存の主キー（原作ID）の最大値を検索する条件式
	 */
	public String makeKeyQuery(){
		String sql = "SELECT max(原作ID) as maxid FROM 原作";
		return sql;
    }

	/**
	 * 追加する原作と同じ原作タイトルを検索する条件式を作成する
	 * @param value1 追加する原作の原作タイトルを示すString
	 * @return 追加する原作の原作タイトルと同じデータを検索する条件式
	 */
	public String makeQuery(String value1) {
		String sql = "SELECT *  FROM 原作 WHERE 原作タイトル='" + value1 + "'";
		return sql;
	}

	public String makeQuery(String value1, String value2) {
		return null;
	}

	public String makeQuery(String value1, String value2, String value3) {
		return null;
	}

	/**
	 * 原作を追加するための条件式を作成する
	 * @param result 既存の主キー（原作ID）の最大値の検索結果を示すResultSet 
	 * @param value1 追加する原作の原作タイトルを示すString
	 * @return 原作を追加するための条件式
	 */
	public String addMakeQuery(ResultSet result, String value1) {
		String sql = null;
		try {
			result.next();
			int maxid = result.getInt("maxid");
			
		    sql = "insert into 原作 value(" + (maxid+1) + ",null,'" + value1 + "')";
		    
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
		
		return sql;
	}

	public String addMakeQuery(ResultSet result, String value1, String value2) {
		return null;
	}

	public String addMakeQuery(ResultSet result, String value1, String value2,
			String value3) {
		return null;
	}

	/**
	 * 追加する原作の原作タイトルと重複するものを表示
	 * @param result 追加する原作の原作タイトルと重複するデータの検索結果を示すResultSet 
	 */
	public void showItem(ResultSet result) {
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("番号\t原作ID\t原作タイトル");
			
			while(result.next()){
				int id=result.getInt("原作ID");
				String title=result.getString("原作タイトル");
				System.out.println(count + ":" + id + ":" + title);
				count++;
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}			
	}
}

