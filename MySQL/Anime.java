/**このクラスは指定された条件に従いアニメの情報を検索するクラスである。
*「アニメタイトル」、「ジャンル」、「声優」の3要素について検索が可能である。
* どの要素について検索するかを選択した後、次に検索する文字列を入力するとそれに関する情報が出力される。
* @author Masato Suemura
* modified by Koichi.Yagihashi
* 未使用の変数を削除
* 未使用importの削除
* メインメソッドからクラスに変更
* テスト用の標準出力を削除
* 選択肢以外の番号が入力された際の注意を促す文を追加
*/

import java.sql.*;
import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class Anime {
	void bigSearch(){
		Connection con = null;
		try {
		    // DBに接続する
			con = DriverManager.getConnection(
				"jdbc:mysql://localhost/animedb?useSSL=false", "root", "SITmeDB"
				);

			// Statementを作る
			Statement stm = con.createStatement();
			
			try{
				System.out.println("何について検索しますか？");
				System.out.println("1：アニメタイトル\n2：ジャンル\n3：声優");
				InputStreamReader isr = new InputStreamReader(System.in);
				BufferedReader br = new BufferedReader(isr);
				String buf3 = br.readLine();
				int buf1 = Integer.parseInt(buf3);
				String sqlA = "";
				String sqlB = "アニメ.タイトル ";
				String sqlC = " ";
				if(buf1==2){
					System.out.println("\nジャンルから検索します");
					sqlB = "ジャンル.ジャンル名 ";
					sqlA = " and アニメ.作品ID=属する.作品ID and 属する.ジャンル名=ジャンル.ジャンル名";
					sqlC = ",属する,ジャンル ";
				}else if(buf1==3){
					System.out.println("\n声優から検索します");
					sqlB = "声優.名前 ";
					sqlA = " and 声優.声優ID=出演.声優ID and アニメ.作品ID=出演.作品ID";
					sqlC = ",出演,声優 ";
				}else if(buf1==1){
					sqlB = "アニメ.タイトル ";
				}
				
				System.out.println("検索する文字列を入力してください");
				InputStreamReader isr2 = new InputStreamReader(System.in);
				BufferedReader br2 = new BufferedReader(isr2);
				String buf2 = br2.readLine();
				
				// タイトル
				String sql0 = "select アニメ.タイトル from アニメ"+ sqlC +" where "+ sqlB +"= '" + buf2 +"'"+ sqlA;
				List<String> titles = new ArrayList<String>();
				ResultSet rs0 = stm.executeQuery(sql0);
				while(rs0.next()){
					String title = rs0.getString("タイトル");
					titles.add(title);
					//System.out.println("\t" + title);
				}
				
				if(buf1==1){
					for(String title : titles) {
					
						System.out.println("\n----------------------------------------\n");
						System.out.println("タイトル：" + title);
						
						// ジャンル
						String sql5 = "";
						if(buf1 == 2){
							sql5 = "select ジャンル.ジャンル名 from アニメ,属する,ジャンル where アニメ.作品ID=属する.作品ID and 属する.ジャンル名=ジャンル.ジャンル名 and "+ sqlB +"= '"+ buf2 +"'"+ sqlA;
							
						}else{
							sql5 = "select ジャンル.ジャンル名 from アニメ,属する,ジャンル"+ sqlC +"where アニメ.作品ID=属する.作品ID and 属する.ジャンル名=ジャンル.ジャンル名 and "+ sqlB +"= '"+ buf2 +"'"+ sqlA;
						}
						//System.out.println(sql5);
						ResultSet rs5 = stm.executeQuery(sql5);
						System.out.println("ジャンル：");
						while(rs5.next()){
							String genre = rs5.getString("ジャンル名");
							System.out.println("\t" + genre);
						}
							
						// 原作
						String sql6 = "select 原作タイトル from アニメ,原作"+ sqlC +" where アニメ.原作ID=原作.原作ID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA;
						//System.out.println(sql6);
						ResultSet rs6 = stm.executeQuery(sql6);
						System.out.println("原作：");
						while(rs6.next()){
							String original = rs6.getString("原作タイトル");
							System.out.println("\t" + original);
						}
						
						// キャラクター
						String sql1 = "select 名前,キャラクター名 from アニメ,出演,声優"+ sqlC +" where アニメ.作品ID=出演.作品ID and 出演.声優ID=声優.声優ID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA;
						ResultSet rs1 = stm.executeQuery(sql1);
						System.out.println("キャラクター：");
						while(rs1.next()){
							String name = rs1.getString("名前");
							String caracter = rs1.getString("キャラクター名");
							System.out.println("\t" + caracter + " (CV:" + name + ")");
						}
						
						// 制作会社
						String sql2 = "select 会社名 from アニメ,制作,制作会社"+ sqlC +" where アニメ.作品ID=制作.作品ID and 制作会社.制作会社ID=制作.制作会社ID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA;
						ResultSet rs2 = stm.executeQuery(sql2);
						System.out.println("製作：");
						while(rs2.next()){
							String campany = rs2.getString("会社名");
							System.out.println("\t" + campany);
						}
						
						// 制作スタッフ
						String sql3 = "select 氏名,役職 from アニメ,制作,制作会社,スタッフ"+ sqlC +" where アニメ.作品ID=制作.作品ID and 制作.制作会社ID=制作会社.制作会社ID and スタッフ.制作会社ID=制作会社.制作会社ID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA;
						ResultSet rs3 = stm.executeQuery(sql3);
						System.out.println("制作スタッフ：");
						while(rs3.next()){
							String position = rs3.getString("役職");
							String staff = rs3.getString("氏名");
							System.out.println("\t" + position + " : " + staff);
						}
						
						// 放送局
						String sql4 = "select 局名 from アニメ,放送,放送局"+ sqlC +" where アニメ.作品ID=放送.作品ID and 放送.放送局ID=放送局.放送局ID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA;
						ResultSet rs4 = stm.executeQuery(sql4);
						System.out.println("放送局：");
						while(rs4.next()){
							String broadcaster = rs4.getString("局名");
							System.out.println("\t" + broadcaster);
						}
					}
				}else if(buf1 == 2){
					
					for(String title : titles) {
						
						System.out.println("\n----------------------------------------\n");
						System.out.println("タイトル：" + title);
						
						String current_title = title;
					
						// ジャンル
						String sql5 = "select ジャンル.ジャンル名 from アニメ,属する,ジャンル where アニメ.作品ID=属する.作品ID and 属する.ジャンル名=ジャンル.ジャンル名 and "+ sqlB +"= '"+ buf2 +"'"+ sqlA + " and アニメ.タイトル ='" + current_title +"'";
						//System.out.println(sql5);
						ResultSet rs5 = stm.executeQuery(sql5);
						System.out.println("ジャンル：");
						while(rs5.next()){
							String genre = rs5.getString("ジャンル名");
							System.out.println("\t" + genre);
						}
						
						// 原作
						String sql6 = "select 原作タイトル from アニメ,原作,属する,ジャンル where アニメ.原作ID=原作.原作ID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA + " and アニメ.タイトル ='" + current_title +"'";
						//System.out.println(sql6);
						ResultSet rs6 = stm.executeQuery(sql6);
						System.out.println("原作：");
						while(rs6.next()){
							String original = rs6.getString("原作タイトル");
							System.out.println("\t" + original);
						}
						
						// キャラクター
						String sql1 = "select 名前,キャラクター名 from アニメ,出演,声優,属する,ジャンル where アニメ.作品ID=出演.作品ID and 出演.声優ID=声優.声優ID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA + " and アニメ.タイトル ='" + current_title +"'";
						ResultSet rs1 = stm.executeQuery(sql1);
						System.out.println("キャラクター：");
						while(rs1.next()){
							String name = rs1.getString("名前");
							String caracter = rs1.getString("キャラクター名");
							System.out.println("\t" + caracter + " (CV:" + name + ")");
						}
						
						// 制作会社
						String sql2 = "select 会社名 from アニメ,制作,制作会社,属する,ジャンル where アニメ.作品ID=制作.作品ID and 制作会社.制作会社ID=制作.制作会社ID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA + " and アニメ.タイトル ='" + current_title +"'";
						ResultSet rs2 = stm.executeQuery(sql2);
						System.out.println("製作：");
						while(rs2.next()){
							String campany = rs2.getString("会社名");
							System.out.println("\t" + campany);
						}
						
						// 制作スタッフ
						String sql3 = "select 氏名,役職 from アニメ,制作,制作会社,スタッフ,属する,ジャンル where アニメ.作品ID=制作.作品ID and 制作.制作会社ID=制作会社.制作会社ID and スタッフ.制作会社ID=制作会社.制作会社ID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA + " and アニメ.タイトル ='" + current_title +"'";
						ResultSet rs3 = stm.executeQuery(sql3);
						System.out.println("制作スタッフ：");
						while(rs3.next()){
							String position = rs3.getString("役職");
							String staff = rs3.getString("氏名");
							System.out.println("\t" + position + " : " + staff);
						}
						
						// 放送局
						String sql4 = "select 局名 from アニメ,放送,放送局,属する,ジャンル where アニメ.作品ID=放送.作品ID and 放送.放送局ID=放送局.放送局ID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA + " and アニメ.タイトル ='" + current_title +"'";
						ResultSet rs4 = stm.executeQuery(sql4);
						System.out.println("放送局：");
						while(rs4.next()){
							String broadcaster = rs4.getString("局名");
							System.out.println("\t" + broadcaster);
						}
					}
				}else if(buf1 == 3){
					
					for(String title : titles) {
						
						System.out.println("\n----------------------------------------\n");
						System.out.println("タイトル：" + title);
						
						String current_title = title;
					
						// ジャンル
						String sql5 = "select ジャンル.ジャンル名 from アニメ,属する,ジャンル,出演,声優 where アニメ.作品ID=属する.作品ID and 属する.ジャンル名=ジャンル.ジャンル名 and "+ sqlB +"= '"+ buf2 +"'"+ sqlA + " and アニメ.タイトル ='" + current_title +"'";
						//System.out.println(sql5);
						ResultSet rs5 = stm.executeQuery(sql5);
						System.out.println("ジャンル：");
						while(rs5.next()){
							String genre = rs5.getString("ジャンル名");
							System.out.println("\t" + genre);
						}
						
						// 原作
						String sql6 = "select 原作タイトル from アニメ,原作,出演,声優 where アニメ.原作ID=原作.原作ID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA + " and アニメ.タイトル ='" + current_title +"'";
						//System.out.println(sql6);
						ResultSet rs6 = stm.executeQuery(sql6);
						System.out.println("原作：");
						while(rs6.next()){
							String original = rs6.getString("原作タイトル");
							System.out.println("\t" + original);
						}
						
						// キャラクター
						String sql1 = "select 名前,キャラクター名 from アニメ,出演,声優 where アニメ.作品ID=出演.作品ID and 出演.声優ID=声優.声優ID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA + " and アニメ.タイトル ='" + current_title +"'";
						System.out.println(sql5);
						ResultSet rs1 = stm.executeQuery(sql1);
						System.out.println("キャラクター：");
						while(rs1.next()){
							String name = rs1.getString("名前");
							String caracter = rs1.getString("キャラクター名");
							System.out.println("\t" + caracter + " (CV:" + name + ")");
						}
						
						// 制作会社
						String sql2 = "select 会社名 from アニメ,制作,制作会社,出演,声優 where アニメ.作品ID=制作.作品ID and 制作会社.制作会社ID=制作.制作会社ID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA + " and アニメ.タイトル ='" + current_title +"'";
						ResultSet rs2 = stm.executeQuery(sql2);
						System.out.println("製作：");
						while(rs2.next()){
							String campany = rs2.getString("会社名");
							System.out.println("\t" + campany);
						}
						
						// 制作スタッフ
						String sql3 = "select 氏名,役職 from アニメ,制作,制作会社,スタッフ,出演,声優 where アニメ.作品ID=制作.作品ID and 制作.制作会社ID=制作会社.制作会社ID and スタッフ.制作会社ID=制作会社.制作会社ID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA + " and アニメ.タイトル ='" + current_title +"'";
						ResultSet rs3 = stm.executeQuery(sql3);
						System.out.println("制作スタッフ：");
						while(rs3.next()){
							String position = rs3.getString("役職");
							String staff = rs3.getString("氏名");
							System.out.println("\t" + position + " : " + staff);
						}
						
						// 放送局
						String sql4 = "select 局名 from アニメ,放送,放送局,出演,声優 where アニメ.作品ID=放送.作品ID and 放送.放送局ID=放送局.放送局ID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA + " and アニメ.タイトル ='" + current_title +"'";
						ResultSet rs4 = stm.executeQuery(sql4);
						System.out.println("放送局：");
						while(rs4.next()){
							String broadcaster = rs4.getString("局名");
							System.out.println("\t" + broadcaster);
						}
					}
				}
				else
					System.out.println("番号が不正です");
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
