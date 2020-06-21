import java.sql.*;
import java.io.*;

public class Sample {
	public static void main(String[] args) {
		Connection con = null;
		try {
		    // DBに接続する
			con = DriverManager.getConnection(
				"jdbc:mysql://localhost/cy16137?useSSL=false", "root", "SITmeDB"
				);
			// System.out.println("MySQLに接続できました。");

			// Statementを作る
			Statement stm = con.createStatement();
			
			
			try{
				int x;
				System.out.println("品名を入力してください：");//テスト用「Goodnote」
				InputStreamReader isr = new InputStreamReader(System.in);
				BufferedReader br = new BufferedReader(isr);
				String buf = br.readLine();
				// 実行するSQLを文字列(String)にする
				String sql = "SELECT shop.ID, shop.name FROM product, shop, sales WHERE product.name='" + buf + "' AND product.ID=sales.productID AND sales.shopID=shop.ID";

				// SQLを実行して、実行結果をResultSetに入れる
				ResultSet rs = stm.executeQuery(sql);

				// 結果を１行ずつ見て、必要な処理(ここでは表示)をする
				while(rs.next()){
					int id = rs.getInt("shop.ID");
					String name = rs.getString("shop.name");
					System.out.println("取得結果 -> " + id + ":" + name);
				}
			} catch (IOException e) {
				System.out.println("IO Error: " + e.toString() + e.getMessage());
			} catch (Exception e) {
				System.out.println("Error: " + e.toString() + e.getMessage());
			}
			

			

		} catch (SQLException se) {
			System.out.println("SQL Error 1 : " + se.toString() + " "
				+ se.getErrorCode() + " " + se.getSQLState());
		} finally {
			if (con != null) {
				try {
					con.close();
				} catch (SQLException e) {
					System.out.println("MySQLのクローズに失敗しました。");
				}
			}
		}
	}
}
