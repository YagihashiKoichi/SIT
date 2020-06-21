/**
 * 放送局のデータをデータベース(animedb)に追加するクラス
 * @author Koichi.Yagihashi
 * @version 1.0
 */
import java.sql.ResultSet;
import java.sql.SQLException;

public class AddBroadcaster extends AbstractAdder{
	
	/**
	 * 既存の主キー（放送局ID）の最大値を検索する条件式を作成する
	 * @return 既存の主キー（放送局ID）の最大値を検索する条件式
	 */
	public String makeKeyQuery(){
		String sql = "SELECT max(放送局ID) as maxid FROM 放送局";
		return sql;
    }
	
	public String makeQuery(String value1) {
		return null;
	}

	/**
	 * 追加する局名、住所と同じ局名、住所を検索する条件式を作成する
	 * @param value1 追加する放送局の局名を示すString
	 * @param value2 追加する放送局の住所を示すString 
	 * @return 追加する局名、住所と同じ局名、住所を検索する条件式
	 */
	public String makeQuery(String value1, String value2) {
		String sql = "SELECT *  FROM 放送局 WHERE 局名='" + value1 + "' AND 住所='" + value2 + "'";
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
	 * @param result 既存の主キー（放送局ID）の最大値の検索結果を示すResultSet 
	 * @param value1 追加する放送局の局名を示すString
	 * @param value2 追加する放送局の住所を示すString 
	 * @return 放送局を追加する条件式
	 */
	public String addMakeQuery(ResultSet result,String value1,String value2){
		String sql = null;
		try {
			result.next();
			int maxid = result.getInt("maxid");
			
		    sql = "insert into 放送局 value(" + (maxid+1) + ",'" + value1 + "','" + value2 + "')";
		    
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return sql;
    }

	public String addMakeQuery(ResultSet result, String value1, String value2,String value3) {
		return null;
	}

	/**
	 * 追加する放送局の局名、住所と重複するものを表示
	 * @param result 追加する放送局の局名、住所と重複するデータの検索結果を示すResultSet 
	 */
	public void showItem(ResultSet result) {
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("番号\t局名\t住所");
			
			while(result.next()){
				String broadcaster = result.getString("局名");
				String address = result.getString("住所");
				System.out.println(count + ":" + broadcaster + ":" + address);
				count++;
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}			
	}
}

