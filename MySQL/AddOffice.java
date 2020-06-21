/**
 * 事務所のデータをデータベース(animedb)に追加するクラス
 * @author Koichi.Yagihashi
 * @version 1.0
 */
import java.sql.ResultSet;
import java.sql.SQLException;

public class AddOffice extends AbstractAdder{
	
	/**
	 * 既存の主キー（事務所ID）の最大値を検索する条件式を作成する
	 * @return 既存の主キー（事務所ID）の最大値を検索する条件式
	 */
	public String makeKeyQuery(){
		String sql = "SELECT max(事務所ID) as maxid FROM 事務所";
		return sql;
    }
	
	public String makeQuery(String value1) {
		return null;
	}

	public String makeQuery(String value1, String value2) {
		return null;
	}

	/**
	 * 追加する事務所の事務所名、電話番号、住所と同じデータを検索する条件式を作成する
	 * @param value1 追加する事務所の事務所名を示すString
	 * @param value2 追加する事務所の電話番号を示すString
	 * @param value3 追加する事務所の住所を示すString  
	 * @return 追加する事務所の事務所名、電話番号、住所と同じデータを検索する条件式
	 */
	public String makeQuery(String value1, String value2, String value3) {
		String sql = "SELECT *  FROM 事務所 WHERE 事務所名='" + value1 + "' AND 電話番号='" + value2 + "' AND 住所='" + value3 + "'";
		return sql;
	}

	public String addMakeQuery(ResultSet result, String value1) {
		return null;
	}

	public String addMakeQuery(ResultSet result, String value1, String value2) {
		return null;
	}

	/**
	 * データを追加するための条件式を作成する
	 * @param result 既存の主キー（事務所ID）の最大値の検索結果を示すResultSet 
	 * @param value1 追加する事務所の事務所名を示すString
	 * @param value2 追加する事務所の電話番号を示すString 
	 * @param value3 追加する事務所の住所を示すString  
	 * @return 制作会社を追加する条件式
	 */
	public String addMakeQuery(ResultSet result, String value1, String value2,
			String value3) {
		String sql = null;
		try {
			result.next();
			int maxid = result.getInt("maxid");
			
		    sql = "insert into 事務所 value(" + (maxid+1) + ",'" + value1 + "','" + value2 + "','" + value3 + "')";

		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
		
		return sql;
	}

	/**
	 * 追加する事務所の事務所名、電話番号、住所と重複するものを表示
	 * @param result 追加する事務所の事務所名、電話番号、住所と重複するデータの検索結果を示すResultSet 
	 */
	public void showItem(ResultSet result) {
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("番号\t事務所名\t電話番号\t住所");
			
			while(result.next()){
				String office = result.getString("事務所名");
				String number = result.getString("電話番号");
				String address = result.getString("住所");
				System.out.println(count + ":" + office + ":" + number + ":" + address);
				count++;
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}			
	}
}

