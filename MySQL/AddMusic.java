/**
 * 曲のデータをデータベース(animedb)に追加するクラス
 * @author Koichi.Yagihashi
 * @version 1.0
 */
import java.sql.ResultSet;
import java.sql.SQLException;

public class AddMusic extends AbstractAdder{
	
	/**
	 * 既存の主キー（ISRCコード）の最大値を検索する条件式を作成する
	 * @return 既存の主キー（ISRCコード）の最大値を検索する条件式
	 */
	public String makeKeyQuery(){
		String sql = "SELECT max(ISRCコード) as maxid FROM 曲";
		return sql;
    }
	
	/**
	 * 追加する曲と同じ曲名を検索する条件式を作成する
	 * @param value1 追加する曲の曲名を示すString
	 * @return 追加する曲の曲名と同じデータを検索する条件式
	 */
	public String makeQuery(String value1) {
		String sql = "SELECT *  FROM 曲 WHERE 曲名='" + value1 + "'";
		return sql;
	}

	public String makeQuery(String value1, String value2) {
		return null;
	}

	public String makeQuery(String value1, String value2, String value3) {
		return null;
	}

	/**
	 * 曲を追加するための条件式を作成する
	 * @param result 既存の主キー（ISRCコード）の最大値の検索結果を示すResultSet 
	 * @param value1 追加する曲の曲名を示すString
	 * @return 曲を追加するための条件式
	 */
	public String addMakeQuery(ResultSet result, String value1){
		String sql = null;
		try {
			result.next();
			int maxid = result.getInt("maxid");
			
		    sql = "insert into 曲 value(" + (maxid+1) + ",'" + value1 + "',null,null)";
		    
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
	 * 追加する曲の曲名と重複するものを表示
	 * @param result 追加する曲の曲名と重複するデータの検索結果を示すResultSet 
	 */
	public void showItem(ResultSet result) {
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("番号\tISRCコード\t曲名");
			
			while(result.next()){
				int id=result.getInt("ISRCコード");
				String music=result.getString("曲名");
				System.out.println(count + ":" + id + ":" + music);
				count++;
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}			
	}
	
}