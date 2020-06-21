/**
 * データベース(animedb)にある指定されたアニメの評価値の平均と評価数のそれぞれ
 * １つを更新するクラス
 * @author Koichi.Yagihashi
 * @version 1.0
 */

import java.sql.ResultSet;
import java.sql.SQLException;

public class UpdateReview extends AbstractUpdater {
	
	/**
	 * (更新対象が複数ある場合)更新対象となりうるデータの一覧を番号をつけて
	 * 作品ID、タイトル、更新前の平均評価値、更新前の評価数を含めて表示
	 * @param result 更新対象となりうるデータの検索結果を示すResultSet
	 */
	public void showItem(ResultSet result){
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("0:アップデートを中止します。");
			System.out.println("番号\t作品ID\tタイトル\t評価値\t評価数");
			while(result.next()){
				int id=result.getInt("評価.作品ID");
				String title=result.getString("タイトル");
				double review=result.getDouble("評価値");
				int viewer=result.getInt("評価数");
				System.out.println(count + ":\t" + id + ":\t" + title + ":\t" + review + ":\t" + viewer);
				count++;
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}	
	}
	
	/**
	 * 更新の条件に該当するデータを検索する条件式を作成する
	 * @param where 評価値を更新したいアニメのタイトルを示すString
	 * @return 更新の条件に該当するデータを検索する条件式
	 */
	public String makeQuery(String where){	//検索する条件式をセット
		String sql = "SELECT 評価.作品ID,タイトル,評価値,評価数 FROM 評価,アニメ WHERE アニメ.作品ID=評価.作品ID AND タイトル='" + where + "'";
		return sql;
    }
	
	/**
	 * 更新の条件に該当するデータが１つのとき更新する条件式を作成する
	 * @param where 評価値を更新したいアニメのタイトルを示すString
	 * @return 更新の条件に該当するアニメの評価値と評価数を更新する条件式
	 */
	public String updateMakeQuery(String set,String where,ResultSet result){	//アップデートの条件式をセット
		double review;
		int viewer,id;
		String sql = null;
		try{
			while(result.next()){	//評価したいタイトル（作品）のIDを代入
				review = result.getDouble("評価値");
				viewer=result.getInt("評価数");
				id=result.getInt("作品ID");
				sql = "UPDATE 評価 SET 評価値=" + ((review*viewer+Double.parseDouble(set))/(viewer+1)) + ",評価数=" + (viewer+1) + " WHERE 作品ID='" + id + "'";
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return sql;
    }
	
	/**
	 * (更新対象が複数ある場合)ユーザーが選択したデータの主キー(作品ID)を更新の条件とした
	 * 条件式を作成
	 * @param result 更新対象の検索結果を示すResultSet
	 * @return ユーザーが選択した評価の主キー(作品ID)を更新の条件とした条件式
	 */
	public String reupdateMakeQuery(String set,ResultSet result){
		String sql = null;
		try {
			int id = result.getInt("評価.作品ID");
			double review = result.getDouble("評価値");
			int viewer=result.getInt("評価数");
			sql = "UPDATE 評価 SET 評価値=" + ((review*viewer+Double.parseDouble(set))/(viewer+1)) + ",評価数=" + (viewer+1) + " WHERE 評価.作品ID=" + id;

		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return sql;
	}
}	