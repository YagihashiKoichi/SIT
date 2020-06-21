/**
 * 歌手のデータをデータベース(animedb)に追加するクラス
 * @author Koichi.Yagihashi
 * @version 1.0
 */
import java.sql.ResultSet;
import java.sql.SQLException;

public class AddSinger extends AbstractAdder{
	
	/**
	 * 既存の主キー（歌手ID）の最大値を検索する条件式を作成する
	 * @return 既存の主キー（歌手ID）の最大値を検索する条件式
	 */
	public String makeKeyQuery(){
		String sql = "SELECT max(歌手ID) as maxid FROM 歌手";
		return sql;
    }
	
	/**
	 * 追加する歌手と同じ歌手名を検索する条件式を作成する
	 * @param value1 追加する歌手の歌手名を示すString
	 * @return 追加する歌手の歌手名と同じデータを検索する条件式
	 */
	public String makeQuery(String value1) {
		String sql = "SELECT *  FROM 歌手 WHERE 歌手名='" + value1 + "'";
		return sql;
	}

	public String makeQuery(String value1, String value2) {
		return null;
	}

	public String makeQuery(String value1, String value2, String value3) {
		return null;
	}

	/**
	 * 歌手を追加するための条件式を作成する
	 * @param result 既存の主キー（歌手ID）の最大値の検索結果を示すResultSet 
	 * @param value1 追加する歌手の歌手名を示すString
	 * @return 歌手を追加するための条件式
	 */
	public String addMakeQuery(ResultSet result, String value1) {
		String sql = null;
		try {
			result.next();
			int maxid = result.getInt("maxid");
			
		    sql = "insert into 歌手 value(" + (maxid+1) + ",'" + value1 + "')";
		    
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
	 * 追加する歌手の歌手名と重複するものを表示
	 * @param result 追加する歌手の歌手名と重複するデータの検索結果を示すResultSet 
	 */
	public void showItem(ResultSet result) {
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("番号\t歌手ID\t歌手名");
			
			while(result.next()){
				int id=result.getInt("歌手ID");
				String singer=result.getString("歌手名");
				System.out.println(count + ":" + id + ":" + singer);
				count++;
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}			
	}
}