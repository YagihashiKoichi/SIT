/**
 * 作者のデータをデータベース(animedb)に追加するクラス
 * @author Koichi.Yagihashi
 * @version 1.0
 */
import java.sql.ResultSet;
import java.sql.SQLException;

public class AddAuthor extends AbstractAdder{
	
	/**
	 * 既存の主キー（作者ID）の最大値を検索する条件式を作成する
	 * @return 既存の主キー（作者ID）の最大値を検索する条件式
	 */
	public String makeKeyQuery(){
		String sql = "SELECT max(作者ID) as maxid FROM 原作者";
		return sql;
    }

	/**
	 * 追加する作者名と同じ作者名を検索する条件式を作成する
	 * @param value1 追加する作者名を示すString
	 * @return 追加する作者名と同じ作者名を検索する条件式
	 */
	public String makeQuery(String value1) {
		String sql = "SELECT *  FROM 原作者 WHERE 作者名='" + value1 + "'";
		return sql;
	}

	public String makeQuery(String value1, String value2) {
		return null;
	}

	public String makeQuery(String value1, String value2, String value3) {
		return null;
	}

	/**
	 * データを追加するための条件式を作成する
	 * @param result 既存の主キー（作者ID）の最大値の検索結果を示すResultSet 
	 * @param value1 追加する作者名を示すString
	 * @return 作者名を追加する条件式
	 */
	public String addMakeQuery(ResultSet result,String value1){
		String sql = null;
		try {
			result.next();
			int maxid = result.getInt("maxid");
			
		    sql = "insert into 原作者 value(" + (maxid+1) + ",'" + value1 + "')";
		    
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
		
		return sql;
    }

	public String addMakeQuery(ResultSet result, String value1, String value2) {
		return null;
	}

	public String addMakeQuery(ResultSet result, String value1, String value2,	String value3) {
		return null;
	}

	/**
	 * 追加する作者名と重複するものを表示
	 * @param result 追加する作者名と重複する作者名の検索結果を示すResultSet 
	 */
	public void showItem(ResultSet result) {
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("番号\t作者ID\t作者名");
			
			while(result.next()){
				int id=result.getInt("作者ID");
				String author=result.getString("作者名");
				System.out.println(count + ":" + id + ":" + author);
				count++;
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}			
	}
}