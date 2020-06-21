/**
 *ModeManager
 *それぞれのクラスのインスタンスを生成し、サービスメニュー一覧の中からユーザーの選択した機能を判別するクラスである。
 *@author 山木淳弘
 *modified by Koichi.Yagihashi
 *インスタンスの生成をwhileの外で行うように変更
 *アプリケーションを終了させた際の文言を追加
 *アプリケーションの使用を続けるかどうか促す分を各機能毎から最後の１つに統合
 *それに伴いそのメソッドを削除
 *switch分のbreakの追加
 *全ての引数を定数から標準入力に変更
 *追加に対応する文を追加
 */

import java.io.*;

public class ModeManager{
	public static void main(String[] args) {
		
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		
		Anime b = new Anime();
		
		AbstractUpdater r1 = new UpdateReview();
		AbstractExecuter r2 = new ExecuteReview();
		
		AbstractUpdater u1 = new UpdateURL();
		AbstractUpdater u2 = new UpdateOfficeAddress();
		AbstractUpdater u3 = new UpdateOfficeNumber();
		AbstractUpdater u4 = new UpdateCompanyAddress();
		AbstractUpdater u5 = new UpdateCompanyNumber();
		AbstractUpdater u6 = new UpdateBroadcasterAddress();
		
		AbstractDeleter d1 = new DeleteService();
		AbstractDeleter d2 = new DeleteAnime();
		
		AbstractAdder a1 = new AddService();
		AbstractAdder a2 = new AddBroadcaster();
		AbstractAdder a3 = new AddSinger();
		
		AbstractAdder a4 = new AddMusic();
		AbstractAdder a5 = new AddAnime();
		AbstractAdder a6 = new AddOriginal();
		AbstractAdder a7 = new AddAuthor();
		AbstractAdder a8 = new AddRadioActor();
		AbstractAdder a9 = new AddOffice();
		AbstractAdder a10 = new AddCompany();
		
		String pass;
		String set,where;
		String value1,value2,value3;
		int last=1;
		
		try{
			while(last==1){
					
				System.out.println("=== アニメ情報管理アプリケーション ===");
				System.out.println("以下の中から実行したいサービスメニューの番号からひとつ選択してください：");
				System.out.println("1：アニメを検索する");
				System.out.println("2：アニメの評価または閲覧をする");
				System.out.println("3：データの更新をする");
				System.out.println("4：データの削除をする");
				System.out.println("5：データの追加をする");
			
				int select_number = Integer.parseInt(reader.readLine());
					
				switch(select_number) {
					case 1:
						b.bigSearch();
						break;
								
					case 2:
						System.out.println("評価か評価の閲覧を選択してください");
						System.out.println("1:評価 / 2:評価の閲覧");
						int review_number = Integer.parseInt(reader.readLine());
						
						switch(review_number){
							case 1:
								System.out.println("評価したいアニメタイトルを入力してください。");
								where=reader.readLine();
								
								while(true){
									System.out.println("1から5の範囲の整数で評価を入力してください。");
									set = reader.readLine();
									if(set.equals("1")||set.equals("2")||set.equals("3")||set.equals("4")||set.equals("5"))
											break;
								}
								r1.SetAndUpdate(where,set);
								break;
								
							case 2:
								r2.queryAndShow();
								break;
								
							default:
								System.out.println("番号が不正です");
								break;
						}
						break;
								
					case 3:
						System.out.println("パスワードを入力してください");//データの編集をむやみに行うことができないように
						pass = reader.readLine();
						if(pass.equals("enshu")){
							System.out.println("ログイン成功\n");
							System.out.println("以下の中から更新したいものの番号を選択してください：");
							System.out.println("1：配信サービスのURL");
							System.out.println("2：事務所の住所");
							System.out.println("3：事務所の電話番号");
							System.out.println("4：制作会社の本社住所");
							System.out.println("5：制作会社の電話番号");
							System.out.println("6：放送局の住所");
								
							int upnumber = Integer.parseInt(reader.readLine());
							switch(upnumber) {
								case 1:
									System.out.println("URLを変更したいサービス名を入力してください");
									where = reader.readLine();
									System.out.println("変更後のURLを入力してください。");
									set = reader.readLine();
									u1.SetAndUpdate(where,set);
									break;
							
								case 2: 
									System.out.println("住所を変更したい事務所名を入力してください");
									where = reader.readLine();
									System.out.println("変更後の住所を入力してください。");
									set = reader.readLine();
									u2.SetAndUpdate(where,set);
									break;
								
								case 3: 
									System.out.println("電話番号を変更したい事務所名を入力してください");
									where = reader.readLine();
									System.out.println("変更後の電話番号を入力してください。");
									set = reader.readLine();
									u3.SetAndUpdate(where,set);
									break;
						
								case 4: 
									System.out.println("住所を変更したい制作会社名を入力してください");
									where = reader.readLine();
									System.out.println("変更後の住所を入力してください。");
									set = reader.readLine();
									u4.SetAndUpdate(where,set);
									break;	
										
								case 5: 
									System.out.println("電話番号を変更したい制作会社名を入力してください");
									where = reader.readLine();
									System.out.println("変更後の電話番号を入力してください。");
									set = reader.readLine();
									u5.SetAndUpdate(where,set);
									break;
									
								case 6:
									System.out.println("住所を変更したい放送局名を入力してください");
									where = reader.readLine();
									System.out.println("変更後の住所を入力してください。");
									set = reader.readLine();
									u6.SetAndUpdate(where,set);
									break;
										
								default:
									System.out.println("番号が不正です");
									break;
							}
						}else
							System.out.println("ログイン失敗\nパスワードが間違っています");
						break;
						
					case 4:			
						System.out.println("パスワードを入力してください");//データの削除をむやみに行うことができないように
					    pass = reader.readLine();
						if(pass.equals("enshu")){
							System.out.println("ログイン成功\n");
							System.out.println("以下の中から削除したいものの番号を選択してください：");
							System.out.println("1：配信サービス");
							System.out.println("2：アニメ");
							
							int delnumber = Integer.parseInt(reader.readLine());
									
							switch(delnumber){
								case 1:
									System.out.println("削除したい配信サービス名を入力してください");
									where = reader.readLine();
									d1.SetAndDelete(where);
									break;
									
								case 2:
									System.out.println("削除したいアニメのタイトルを入力してください");
									where = reader.readLine();
									d2.SetAndDelete(where);
									break;
					
								default:
									System.out.println("番号が不正です");
									break;
							}
						} else 
							System.out.println("ログイン失敗\nパスワードが間違っています");
						break;
						
					case 5:
						System.out.println("パスワードを入力してください");//データの追加をむやみに行うことができないように
						pass = reader.readLine();
						if(pass.equals("enshu")){
							System.out.println("ログイン成功\n");
							System.out.println("以下の中から追加したいものの番号を選択してください：");
							System.out.println("1：配信サービス");
							System.out.println("2：放送局");
							System.out.println("3：歌手");
							System.out.println("4：曲");
							System.out.println("5：アニメ");
							System.out.println("6：原作");
							System.out.println("7：原作者");
							System.out.println("8：声優");
							System.out.println("9：事務所");
							System.out.println("10：制作会社");
							
							int addnumber = Integer.parseInt(reader.readLine());
							switch(addnumber) {
									
								case 1:
									System.out.println("追加したいサービス名を入力してください。");
									value1 = reader.readLine();
									System.out.println("追加したいサービスのURLを入力してください。");
									value2 = reader.readLine();									
									a1.SetAndAdd(value1,value2);
									break;
								
								case 2:
									System.out.println("追加したい放送局を入力してください。");
									value1 = reader.readLine();
									System.out.println("追加したい放送局の住所を入力してください。");
									value2 = reader.readLine();
									a2.SetAndAdd(value1,value2);
									break;
									
								case 3:
									System.out.println("追加したい歌手名を入力してください。");
									value1 = reader.readLine();	
									a3.SetAndAdd(value1);
									break;
										
								case 4:
									System.out.println("追加したい曲名を入力してください。");
									value1 = reader.readLine();
									a4.SetAndAdd(value1);
									break;
								
								case 5:
									System.out.println("追加したいアニメのタイトルを入力してください。");
									value1 = reader.readLine();
									a5.SetAndAdd(value1);
									break;
										
								case 6:
									System.out.println("追加したい原作のタイトルを入力してください。");
									value1 = reader.readLine();
									a6.SetAndAdd(value1);
									break;
									
								case 7:
									System.out.println("追加したい原作者名を入力してください。");
									value1 = reader.readLine();
									a7.SetAndAdd(value1);
									break;
									
								case 8:
									System.out.println("追加したい声優の名前を入力してください。");
										value1 = reader.readLine();
									while(true){
										System.out.println("追加したい声優の性別を'男性'か'女性'で入力してください。");
										value2 = reader.readLine();
										if(value2.equals("男性")||value2.equals("女性"))
											break;
									}
									a8.SetAndAdd(value1,value2);
									break;
										
								case 9:
									System.out.println("追加したい事務所名を入力してください。");
									value1 = reader.readLine();
									System.out.println("追加したい事務所の電話番号を入力してください。");
									value2 = reader.readLine();
									System.out.println("追加したい事務所の住所を入力してください。");
									value3 = reader.readLine();
									a9.SetAndAdd(value1,value2,value3);
									break;
										
								case 10:
									System.out.println("追加したい制作会社名を入力してください。");
									value1 = reader.readLine();
									System.out.println("追加したい制作会社の本社住所を入力してください。");
									value2 = reader.readLine();
									System.out.println("追加したい制作会社の電話番号を入力してください。");
									value3 = reader.readLine();
									a10.SetAndAdd(value1,value2,value3);
									break;
									
								default:
									System.out.println("番号が不正です");
									break;
							}
					} else
						System.out.println("ログイン失敗\nパスワードが間違っています");
					break;
					
				default:
					System.out.println("番号が不正です");
					break;
				}
				
				System.out.println("まだアプリケーションを利用しますか？");
				System.out.println("1:YES / 0:NO");
				last = Integer.parseInt(reader.readLine());
			}
			System.out.println("ご利用ありがとうございました。");
		} catch (IOException e) {
			System.out.println("IO Error: " + e.toString() + e.getMessage());
		} catch (Exception e) {
			System.out.println("Error: " + e.toString() + e.getMessage());
		}
	}	
}
