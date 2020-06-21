/**
 * データベース(animedb)にある指定されたアニメのタイトルのデータを
 * １つデータベース上から削除するクラス
 * @author Koichi.Yagihashi
 * @version 1.0
 */
//上と下の使わないメソッドを削除
import java.sql.ResultSet;
import java.sql.SQLException;

public class DeleteAnime extends AbstractDeleter{
	
	/**
	 * 削除の条件に該当するデータを検索する条件式を作成する
	 * @param where 削除するアニメのタイトルを示すString
	 * @return 削除の条件に該当するデータを検索する条件式
	 */
	public String makeQuery(String where){
		String sql = "SELECT * FROM アニメ WHERE タイトル='" + where + "'";
		return sql;
    }
	
	/**
	 * 削除の条件に該当するデータが１つのとき削除する条件式を作成する
	 * @param where 削除するアニメのタイトルを示すString
	 * @return 削除の条件に該当するデータを削除する条件式
	 */
	public String deleteMakeQuery(String where){
		String sql = "DELETE アニメ,放送,配信,出演,制作,属する" +
				     " FROM アニメ" +
				     " LEFT JOIN 放送 ON アニメ.作品ID=放送.作品ID" +
				     " LEFT JOIN 配信 ON アニメ.作品ID=配信.作品ID" +
				     " LEFT JOIN 出演 ON アニメ.作品ID=出演.作品ID" +
				     " LEFT JOIN 制作 ON アニメ.作品ID=制作.作品ID" +
				     " LEFT JOIN 属する ON アニメ.作品ID=属する.作品ID" +
				     " WHERE タイトル='" + where + "'";
		return sql;
    }

	/**
	 * (削除対象が複数ある場合)ユーザーが選択したデータの主キー(作品ID)を削除の条件とした
	 * 条件式を作成
	 * @param result 削除対象の検索結果を示すResultSet
	 * @return ユーザーが選択したデータの主キー(作品ID)を削除の条件とした条件式
	 */
	public String redeleteMakeQuery(ResultSet result){
		String sql = null;
		String id;
		try {
			id = result.getString("作品ID");
		    sql = "DELETE アニメ,放送,配信,出演,制作,属する" +
				     " FROM アニメ" +
				     " LEFT JOIN 放送 ON アニメ.作品ID=放送.作品ID" +
				     " LEFT JOIN 配信 ON アニメ.作品ID=配信.作品ID" +
				     " LEFT JOIN 出演 ON アニメ.作品ID=出演.作品ID" +
				     " LEFT JOIN 制作 ON アニメ.作品ID=制作.作品ID" +
				     " LEFT JOIN 属する ON アニメ.作品ID=属する.作品ID" +
				     " WHERE アニメ.作品ID='" + id + "'";
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return sql;
	}
	
	/**
	 * (削除対象が複数ある場合)削除対象となりうるデータの一覧を番号をつけて
	 * 主キー(作品ID)を含めて表示
	 * @param result 削除対象となりうるデータの検索結果を示すResultSet
	 */
	public void showItem(ResultSet result){
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("0:削除を中止します。");
			System.out.println("番号\t作品ID\tタイトル");
			
			while(result.next()){
				int id=result.getInt("作品ID");
				String title=result.getString("タイトル");
				System.out.println(count + ":" + id + ":" + title);
				count++;
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}	
	}
}	