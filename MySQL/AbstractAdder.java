/**
 * データをデータベース(animedb)に追加する抽象クラス
 * @author Koichi.Yagihashi
 * @version 1.0
 */
import java.io.*;
import java.sql.*;

public abstract class AbstractAdder {
	
	/**
	 * 追加するデータと同じデータを検索する条件式を作成する
	 * @param value1 追加するデータ内容を示すString
	 * @return 追加するデータと同じデータを検索する条件式
	 */
	public abstract String makeQuery(String value1);
	
	/**
	 * 追加するデータと同じデータを検索する条件式を作成する
	 * @param value1 追加するデータ内容を示すString
	 * @param value2 追加するデータ内容を示すString
	 * @return 追加するデータと同じデータを検索する条件式
	 */
	public abstract String makeQuery(String value1,String value2);
	
	/**
	 * 追加するデータと同じデータを検索する条件式を作成する
	 * @param value1 追加するデータ内容を示すString
	 * @param value2 追加するデータ内容を示すString
	 * @param value3 追加するデータ内容を示すString
	 * @return 追加するデータと同じデータを検索する条件式
	 */
	public abstract String makeQuery(String value1,String value2,String value3);
	
	/**
	 * 追加するテーブル上の既存の主キー（ID）の最大値を検索する条件式を作成する
	 * @return 追加するテーブル上の既存の主キー（ID）の最大値を検索する条件式
	 */
	public abstract String makeKeyQuery();	//該当するデータを持ってくるための条件式の作成
	
	/**
	 * データを追加するための条件式を作成する
	 * @param result 既存の主キー（ID）の最大値の検索結果を示すResultSet 
	 * @param value1 追加するデータ内容を示すString
	 * @return データを追加する条件式
	 */
	public abstract String addMakeQuery(ResultSet result,String value1);	//アップデートの条件式の作成
	
	/**
	 * データを追加するための条件式を作成する
	 * @param result 既存の主キー（ID）の最大値の検索結果を示すResultSet 
	 * @param value1 追加するデータ内容を示すString
	 * @param value2 追加するデータ内容を示すString
	 * @return データを追加する条件式
	 */
	public abstract String addMakeQuery(ResultSet result,String value1,String value2);	//アップデートの条件式の作成
	
	/**
	 * データを追加するための条件式を作成する
	 * @param result 既存の主キー（ID）の最大値の検索結果を示すResultSet 
	 * @param value1 追加するデータ内容を示すString
	 * @param value2 追加するデータ内容を示すString
	 * @param value3 追加するデータ内容を示すString 
	 * @return データを追加する条件式
	 */
	public abstract String addMakeQuery(ResultSet result,String value1,String value2,String value3);	//アップデートの条件式の作成
	
	/**
	 * 追加するデータと重複すると思われるものを表示
	 * @param result 追加するデータと重複すると思われるデータの検索結果を示すResultSet 
	 */
	public abstract void showItem(ResultSet result);	//重複したデータ一覧を表示
	
	/**
	 * 重複しない場合はそのままデータを追加するが
	 * 重複した場合は追加するかはユーザーの判断に従う
	 * @param value1 追加するデータ内容を示すString
	 * @return 追加が成功した場合はtrue,失敗した場合はfalse
	 */
	public Boolean SetAndAdd(String value1) {
		Connection conn = null;
		try {
			
			BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
			
			conn = DriverManager.getConnection(
				"jdbc:mysql://localhost/animedb?useSSL=false", "root", "SITmeDB"
				);
			
			Statement stm1=conn.createStatement();
			Statement stm2=conn.createStatement();
			
			String sql1 = makeQuery(value1);	//追加するデータの重複を絞る条件式
			ResultSet exi_result=stm1.executeQuery(sql1);
		
			exi_result.last();
			int item_count=exi_result.getRow();
			exi_result.beforeFirst();
			
			String sql2 = makeKeyQuery();	//IDの最大値を検索する条件式
			ResultSet key_result=stm2.executeQuery(sql2);
			
			String sql3=addMakeQuery(key_result,value1);	//追加の条件式を作成
			
			if(item_count==0)	//重複がない
				stm1.executeUpdate(sql3);
			else{				//重複あり
				System.out.println("追加しようとしたデータと同じものが既に存在しました。");
				showItem(exi_result);	//重複したデータ一覧を表示
				System.out.println("データを追加しますか？");
				System.out.println("1:YES / 0:NO");
				int judge = Integer.parseInt(reader.readLine());
				if(judge==1)
					stm1.executeUpdate(sql3);
				else{
					System.out.println("追加を中止しました。");
					return false;
				}
			}
			
			System.out.println("追加に成功しました。");

		} catch (SQLException se) {
			System.out.println("SQL Error 1: " + se.toString() + " "
				+ se.getErrorCode() + " " + se.getSQLState());
		} catch (Exception e) {
			System.out.println("Error: " + e.toString() + e.getMessage());
		}finally {
			if (conn != null) {
				try {
					conn.close();
				} catch (SQLException e) {
					System.out.println("MySQLのクローズに失敗しました。");
				}
			}
		}
		
		return true;
	}

	/**
	 * 重複しない場合はそのままデータを追加するが
	 * 重複した場合は追加するかはユーザーの判断に従う
	 * @param value1 追加するデータ内容を示すString
	 * @param value2 追加するデータ内容を示すString
	 * @return 追加が成功した場合はtrue,失敗した場合はfalse
	 */
	public Boolean SetAndAdd(String value1,String value2) {
		Connection conn = null;
		try {
			
			BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
			
			conn = DriverManager.getConnection(
				"jdbc:mysql://localhost/animedb?useSSL=false", "root", "SITmeDB"
				);
			
			Statement stm1=conn.createStatement();
			Statement stm2=conn.createStatement();
			
			String sql1 = makeQuery(value1,value2);	//追加するデータの重複を絞る条件式
			ResultSet exi_result=stm1.executeQuery(sql1);
		
			exi_result.last();
			int item_count=exi_result.getRow();
			exi_result.beforeFirst();
			
			String sql2 = makeKeyQuery();	//IDの最大値を検索する条件式
			ResultSet key_result=stm2.executeQuery(sql2);
			
			String sql3=addMakeQuery(key_result,value1,value2);	//追加の条件式を作成
			
			if(item_count==0)	//重複がない
				stm1.executeUpdate(sql3);
			else{				//重複あり
				System.out.println("追加しようとしたデータと同じものが既に存在しました。");
				showItem(exi_result);	//重複したデータ一覧を表示
				System.out.println("データを追加しますか？");
				System.out.println("1:YES / 0:NO");
				int judge = Integer.parseInt(reader.readLine());
				if(judge==1)
					stm1.executeUpdate(sql3);
				else{
					System.out.println("追加を中止しました。");
					return false;
				}
			}
			
			System.out.println("追加に成功しました。");

		} catch (SQLException se) {
			System.out.println("SQL Error 1: " + se.toString() + " "
				+ se.getErrorCode() + " " + se.getSQLState());
		} catch (Exception e) {
			System.out.println("Error: " + e.toString() + e.getMessage());
		}finally {
			if (conn != null) {
				try {
					conn.close();
				} catch (SQLException e) {
					System.out.println("MySQLのクローズに失敗しました。");
				}
			}
		}
		
		return true;
	}

	/**
	 * 重複しない場合はそのままデータを追加するが
	 * 重複した場合は追加するかはユーザーの判断に従う
	 * @param value1 追加するデータ内容を示すString
	 * @param value2 追加するデータ内容を示すString
	 * @param value3 追加するデータ内容を示すString
	 * @return 追加が成功した場合はtrue,失敗した場合はfalse
	 */
	public Boolean SetAndAdd(String value1,String value2,String value3) {
		Connection conn = null;
		try {
		
			BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
			
			conn = DriverManager.getConnection(
				"jdbc:mysql://localhost/animedb?useSSL=false", "root", "SITmeDB"
				);
			
			Statement stm1=conn.createStatement();
			Statement stm2=conn.createStatement();
			
			String sql1 = makeQuery(value1,value2,value3);	//追加するデータの重複を絞る条件式
			ResultSet exi_result=stm1.executeQuery(sql1);
		
			exi_result.last();
			int item_count=exi_result.getRow();
			exi_result.beforeFirst();
			
			String sql2 = makeKeyQuery();	//IDの最大値を検索する条件式
			ResultSet key_result=stm2.executeQuery(sql2);
			
			String sql3=addMakeQuery(key_result,value1,value2,value3);	//追加の条件式を作成
			
			if(item_count==0)	//重複がない
				stm1.executeUpdate(sql3);
			else{				//重複あり
				System.out.println("追加しようとしたデータと同じものが既に存在しました。");
				showItem(exi_result);	//重複したデータ一覧を表示
				System.out.println("データを追加しますか？");
				System.out.println("1:YES / 0:NO");
				int judge = Integer.parseInt(reader.readLine());
				if(judge==1)
					stm1.executeUpdate(sql3);
				else{
					System.out.println("追加を中止しました。");
					return false;
				}
			}
			
			System.out.println("追加に成功しました。");
	
		} catch (SQLException se) {
			System.out.println("SQL Error 1: " + se.toString() + " "
				+ se.getErrorCode() + " " + se.getSQLState());
		} catch (Exception e) {
			System.out.println("Error: " + e.toString() + e.getMessage());
		}finally {
			if (conn != null) {
				try {
					conn.close();
				} catch (SQLException e) {
					System.out.println("MySQLのクローズに失敗しました。");
				}
			}
		}
		
		return true;
	}
}
