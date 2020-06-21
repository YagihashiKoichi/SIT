/**
 * 声優のデータをデータベース(animedb)に追加するクラス
 * @author Koichi.Yagihashi
 * @version 1.0
 */
import java.sql.ResultSet;
import java.sql.SQLException;

public class AddRadioActor extends AbstractAdder{
	
	/**
	 * 既存の主キー（声優ID）の最大値を検索する条件式を作成する
	 * @return 既存の主キー（声優ID）の最大値を検索する条件式
	 */
	public String makeKeyQuery(){
		String sql = "SELECT max(声優ID) as maxid FROM 声優";
		return sql;
    }

	public String makeQuery(String value1) {
		return null;
	}

	/**
	 * 追加する声優の名前、性別と同じデータを検索する条件式を作成する
	 * @param value1 追加する声優の名前を示すString
	 * @param value2 追加する声優の性別を示すString 
	 * @return 追加する声優の名前、性別が同じデータを検索する条件式
	 */
	public String makeQuery(String value1, String value2) {
		String sql = "SELECT *  FROM 声優 WHERE 名前='" + value1 + "' AND 性別='" + value2 + "'";
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
	 * @param result 既存の主キー（声優ID）の最大値の検索結果を示すResultSet 
	 * @param value1 追加する声優の名前を示すString
	 * @param value2 追加する声優の性別を示すString 
	 * @return 声優を追加する条件式
	 */
	public String addMakeQuery(ResultSet result, String value1, String value2) {
		String sql = null;
		try {
			result.next();
			int maxid = result.getInt("maxid");
			
		    sql = "insert into 声優 value(" + (maxid+1) + ",'" + value1 + "','" + value2 + "',null)";
		    
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
	 * 追加する声優の名前、性別と重複するものを表示
	 * @param result 追加する声優の名前、性別と重複するデータの検索結果を示すResultSet 
	 */
	public void showItem(ResultSet result) {
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("番号\t名前\t性別");
			
			while(result.next()){
				String name = result.getString("名前");
				String sex = result.getString("性別");
				System.out.println(count + ":" + name + ":" + sex);
				count++;
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}			
	}
}

