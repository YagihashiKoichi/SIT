/**
 * データベース(animedb)にある作品ID、タイトル、評価値、評価数を
 * データ表示するためのクラス
 * @author Koichi.Yagihashi
 * @version 1.0
 */
import java.sql.ResultSet;
import java.sql.SQLException;

public class ExecuteReview extends AbstractExecuter{

	/**
	 * アニメの評価一覧を表示するための条件式を作成する
	 * @return データ検索の条件式
	 */
	public String makeQuery() {
		String sql = "SELECT アニメ.作品ID,タイトル,評価値,評価数" +
					" FROM アニメ,評価" +
					" WHERE アニメ.作品ID=評価.作品ID";
		return sql;
	}

	/**
	 * 検索する条件式に該当したデータを表示する
	 * @param result 評価の一覧を示すResultSet
	 */
	public void showResult(ResultSet result) {
		
		try {
			result.beforeFirst();
			System.out.println("作品ID\tタイトル\t評価値\t評価数");
			
			while(result.next()){
				int id=result.getInt("作品ID");
				String title=result.getString("タイトル");
				double review=result.getDouble("評価値");
				int viewer=result.getInt("評価数");
				System.out.println(id + ":" + title + ":" + review + ":" + viewer);
			}
			
		} catch (SQLException e) {
			System.out.println("AddAnime:showItem");
			e.printStackTrace();
		}
		return;
	}
	
}	