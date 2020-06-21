/**
 * アニメのデータをデータベース(animedb)に追加するクラス
 * @author Koichi.Yagihashi
 * @version 1.0
 */
import java.sql.ResultSet;
import java.sql.SQLException;

public class AddAnime extends AbstractAdder{
	
	/**
	 * 既存の主キー（アニメの作品ID）の最大値を検索する条件式を作成する
	 * @return 既存の主キー（アニメの作品ID）の最大値を検索する条件式
	 */
	public String makeKeyQuery(){
		String sql = "SELECT max(作品ID) as maxid FROM アニメ";
		return sql;
    }
	
	/**
	 * 追加するタイトルと同じタイトルを検索する条件式を作成する
	 * @param value1 追加するタイトルを示すString
	 * @return 追加するタイトルと同じタイトルを検索する条件式
	 */
	public String makeQuery(String value1) {
		String sql = "SELECT *  FROM アニメ WHERE タイトル='" + value1 + "'";
		return sql;
	}

	public String makeQuery(String value1, String value2) {
		// TODO Auto-generated method stub
		return null;
	}

	public String makeQuery(String value1, String value2, String value3) {
		// TODO Auto-generated method stub
		return null;
	}

	/**
	 * データを追加するための条件式を作成する
	 * @param result 既存の主キー（アニメの作品ID）の最大値の検索結果を示すResultSet 
	 * @param value1 追加するタイトルを示すString
	 * @return タイトルを追加する条件式
	 */
	public String addMakeQuery(ResultSet result,String value1){
		String sql = null;
		try {
			result.next();
			int maxid = result.getInt("maxid");
			
		    sql = "insert into アニメ value(" + (maxid+1) + ",'" + value1 + "',null)";
		    
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
		
		return sql;
    }
	
	public String addMakeQuery(ResultSet result, String value1, String value2) {
		// TODO Auto-generated method stub
		return null;
	}

	public String addMakeQuery(ResultSet result, String value1, String value2,
			String value3) {
		// TODO Auto-generated method stub
		return null;
	}

	/**
	 * 追加するタイトルと重複するものを表示
	 * @param result 追加するタイトルと重複するデータの検索結果を示すResultSet 
	 */
	public void showItem(ResultSet result) {
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("番号\t作品ID\tタイトル");
			
			while(result.next()){
				int id=result.getInt("作品ID");
				String title=result.getString("タイトル");
				System.out.println(count + ":" + id + ":" + title);
				count++;
			}
			
		} catch (SQLException e) {
			System.out.println("AddAnime:showItem");
			e.printStackTrace();
		}			
	}
}

