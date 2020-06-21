#include <arpa/inet.h>
#include<sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/select.h>

int main(){
	
	struct cliant{
	int sockfd;
	char name[20];
	int super;	   //特権ユーザーは1
	int situation;   //-1のとき空いてるとする
			   //0の時は名前重複のため準備中
	};
 
	struct cliant user[20];
	
	
	struct sockaddr_in serv_addr;
	int	i,s,t,l,bu,ki,pri;	//カウンタ変数
	int	connect=0;		//クライアントの接続数
	int	sockfd;
	int	maxfd=0;	//selectの際の管理番号の最大値
	int	user_num;
	int	pri_flag;	//プライベートチャットを送ろうとしたかのフラッグ
	int	out_sockfd;	//ユーザー数上限の旨を入れない人に伝えるため
	char	kickname[20];
	char	buff[100];
	char	back_name[20];
	char	pri_name[20];
	char	pri_buff[121];
	char	co_buff[121];

	fd_set readfds;


	//空いているアカウントはsituation=-1
	//全てを空いている状態に（初期化）
	for(i=0;i<20;i++){
		user[i].situation=-1;
  	}

	//全てを一般ユーザーに（初期化）
	for(i=0;i<20;i++){
		user[i].super=0;
  	}


	//ソケットを作る
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1){
		perror("error_serv_socket");
		exit(1);
 	}

	//アドレスを作る
	memset(&serv_addr,0,sizeof(struct sockaddr_in));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(10000);
/*
	//デバック時のみ有効
	//ソケットの再利用を許可
	int flag=1;
	if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&flag,sizeof(int))==-1){
 		perror("error_serv_setso");
 		exit(1);
	}
*/

	//ソケットにアドレスを割り当てる
	if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr_in))==-1){
		perror("error_serv_bind");
		exit(1);
  	}

	//コネクション要求を待ち始めるように指示
	if(listen(sockfd,5)==-1){
		perror("error_serv_listen");
		exit(1);
	}

	while(1){
	
		FD_ZERO(&readfds);	//FD_SETの初期化
		

		
		FD_SET(sockfd,&readfds);			//sockfd(接続要求があるか)を監視対象に追加
		if(maxfd<sockfd)	maxfd=sockfd;	//最大値を更新

		
		
		for(i=0;i<20;i++){
			if((user[i].situation==1)||(user[i].situation==0)){			//使用中または準備中なら
				FD_SET(user[i].sockfd,&readfds); //select()で待つ読み込みソケットとして登録
				if(user[i].sockfd>maxfd)	maxfd=user[i].sockfd;		//最大値を更新
				
			}
		}
		

		if(select(maxfd+1,&readfds,NULL,NULL,NULL)==-1){
			perror("error_serv_select");
			exit(1);
		}
		

		
		if((FD_ISSET(sockfd,&readfds)==1)&&(connect<20)){	      //接続要求があった場合かつまだ空きがある場合
			connect++;
			for(i=0;i<20;i++){
				if(user[i].situation==-1){						//未使用
					user[i].sockfd=accept(sockfd,NULL,NULL);	//一番若い未使用に割り当てる
					if(user[i].sockfd==-1){						//acccept()のエラーチェック
						perror("error_serv_accept");
						exit(1);
					}

					
					if(read(user[i].sockfd,back_name,20)==-1){		//送られてきた名前のバックアップをとる
						perror("error_serv_read_backname");			//重複しないかの判断のため
						exit(1);
					}

					for(s=0;s<20;s++){
						if((strcmp(user[s].name,back_name)==0)&&(user[s].situation==1)){ 	//使用中のアカウントと名前が重複	 
							if(write(user[i].sockfd,"NOT",10)==-1){	//名前の重複を伝える
								perror("error_serv_write_name_errorsend");
								exit(1);
							}
							user[i].situation=0;	//準備中に設定	
													//内容のやりとりはできないが未使用と判断されて上書きされないように
							
							break;					//同じ名前が一人でもいたら
						}
					}

					if(s==20){						//最後までみても名前の重複が確認されないとき
						strcpy(user[i].name,back_name);		//バックアップの名前を割り当てる
						if(write(user[i].sockfd,"OK",10)==-1){	//名前が重複しなかったことを伝える
								perror("error_serv_write_name_OKsend");
								exit(1);
						}

					}
					else	break;		//名前が重複したので入室などの処理を行わない	



					user[i].situation=1;	//使用中に設定

					if(sprintf(co_buff,"%sさんが入室しました",user[i].name)==-1){
						perror("error_serv_sprintf_enter");	
						exit(1);
					}
						
						
					for(l=0;l<20;l++){
						if(user[l].situation==1){						//使用中の人に
							if(write(user[l].sockfd,co_buff,121)==-1){	//入室があったことを伝える
								perror("error_serv_write_enter");
								exit(1);
							}
						}
					}

					if(connect==20){			//ユーザーの上限に達した
						for(i=0;i<20;i++){
							if(user[i].situation==1){
								if(write(user[i].sockfd,"ユーザーの数が上限に達しました",121)==-1){	//上限を使用者に伝える
									perror("error_serv_write_max_send");
									exit(1);
								}
							}
						}
					}
					break;
				}
			}
		}

		else if((connect==3)&&(FD_ISSET(sockfd,&readfds)==1)){	//上限にも関わらず、接続要求があったとき
			out_sockfd=accept(sockfd,NULL,NULL);	//ユーザーが上限に達していることを伝えるため繋ぐ
			if(write(out_sockfd,"OK",10)==-1){		//クライアント側の名前の重複判定のプロセスを飛ばさせるため
				perror("error_serv_write_processbreak_send");
				exit(1);
			}			
			if(write(out_sockfd,"既にユーザーの数が上限に達しています",121)==-1){	//入れないことを伝える
				perror("error_serv_write_maxed_send");
				exit(1);
			}
			if(write(out_sockfd,"$kick",121)==-1){	//KICKを伝える(上限のため)
				perror("error_serv_write_kick_send_tobemax");
				exit(1);
			}
			sleep(1);
			if(close(out_sockfd)==-1){			//通達用のソケットを閉じる
				perror("error_serv_maxed_close");
				exit(1);
			}
		}		
		
		
		
		for(t=0;t<20;t++){		
			if((user[t].situation==1)&&(FD_ISSET(user[t].sockfd,&readfds)==1)){	//使用中のアカウントから送られてきた場合
				
				if(read(user[t].sockfd,buff,100)==-1){			//クライアントからメッセージを受け取る
					perror("error_serv_read_message_receive");
					exit(1);
				}
								
				if(strcmp(buff,"$logout")==0){				//送られた内容が$logoutコマンドだったら
					sleep(1);
					if(close(user[t].sockfd)==-1){				//対象者とのソケットを閉じる
						perror("error_serv_close_logout");
						exit(1);
					
					}
					user[t].situation=-1;
					user[t].super=0;
					connect--;		//使用者のカウントを減らす
					
					if(sprintf(co_buff,"%sさんが退出しました",user[t].name)==-1){
						perror("error_serv_sprintf_logout");
						exit(1);
					
					}
						
					for(i=0;i<20;i++){			//使用中の全員に
						if(user[i].situation==1){
							if(write(user[i].sockfd,co_buff,121)==-1){	//退出メッセージを送る
								perror("error_serv_write_logoutmessage_send");
								exit(1);
							}
						}
					}
				}

				else if(strcmp(buff,"$members")==0){	//メンバー一覧を表示させるコマンドのとき
					for(i=0;i<20;i++){
						if(user[i].situation==1){
							if(write(user[t].sockfd,user[i].name,121)==-1){	//メンバー一覧を伝える
								perror("error_serv_write_kick_send");
								exit(1);
							}
						}	
					}
				}

				else if(strncmp(buff,"$pass:",6)==0){	//パスワードの入力を行おうとした

					if(strcmp(buff,"$pass:miku")==0){	//正しいパスワードが入力されたとき
						if(user[t].super==0){
							user[t].super=1;
							if(write(user[t].sockfd,"特権ユーザーに切り替えました",121)==-1){	//特権ユーザーになったことを伝える
								perror("error_serv_write_besuper_send");
								exit(1);
							}
						}
						else if(user[t].super==1){	//すでに特権ユーザーのとき
							if(write(user[t].sockfd,"既に特権ユーザーです",121)==-1){	//すでに特権ユーザーであることを伝える
								perror("error_serv_write_already_super_send");
								exit(1);
							}
						}	
					}

					else{	//パスワードが異なる時
						if(write(user[t].sockfd,"パスワードが違います",121)==-1){	//パスワードが違うことを伝える
							perror("error_serv_write_pass_erroer_send");
							exit(1);
						}
					}

				}



				else if(strcmp(buff,"#end")==0){	//サーバー終了コマンド

					if(user[t].super==1){	//コマンド入力者が特権ユーザーなら
						for(i=0;i<20;i++){
							if((user[i].situation==1)||(user[i].situation==0)){	//使用中または準備中のユーザーに
								if(write(user[i].sockfd,"特権ユーザによりサーバーが停止しました",121)==-1){	//サーバーの停止を伝える
									perror("error_serv_write_endmessage_send");
									exit(1);
								}
								if(write(user[i].sockfd,"$kick",121)==-1){	//全てのユーザーをキックする
									perror("error_serv_write_endkick_send");
									exit(1);
								}
								sleep(1);
								
							}
						}

						if(close(sockfd)==-1){	//listenのソケットを閉じる
							perror("error_serv_close_listen");
							exit(1);
						}
						return	0;
					}

					else{
						if(write(user[t].sockfd,"権限がありません",121)==-1){	//一般ユーザーにアクセス権限がないことを伝える
							perror("error_serv_write_notsuper_send");
							exit(1);
						}
					}
					
				}
				
				else if((strcmp(buff,"$stamp1")==0)||(strcmp(buff,"$stamp2")==0)||(strcmp(buff,"$stamp3")==0)||(strcmp(buff,"$stamp4")==0)){
											//何かしらのスタンプコマンドが送られてきたら
											
					sprintf(co_buff,"%s:",user[t].name);
					printf("co_buff=%s",co_buff);
				
					for(i=0;i<20;i++){

						if((i!=t)&&(user[i].situation==1)){
							if(write(user[i].sockfd,co_buff,121)==-1){		//送り主を伝える
								perror("error_serv_write_STAMP_namesend");
								exit(1);
							}
						}
						if(user[i].situation==1){
							if(write(user[i].sockfd,buff,121)==-1){	//スタンプコマンドを送る
								perror("error_serv_write_STAMP_send");
								exit(1);
							}
						}
					}
				}
				
				
				else if(strncmp(buff,"$kick",5)==0){	//キックコマンドが送られてきたら
					ki=0;
					
					for(bu=5;bu<25;bu++){//キック対象者の名前を取得
						kickname[ki]=buff[bu];
						ki++;
						if(buff[bu]=='\0')	break;
						//}
					}
					
					for(i=0;i<20;i++){
					//名前一致かつ使用中かつ送り主じゃない（未使用にしても名前は消していないので）かつ特権ユーザーではない
						if((strcmp(user[i].name,kickname)==0)&&(user[i].situation==1)&&(strcmp(user[t].name,kickname)!=0)&&(user[i].super==0)){
							if(write(user[i].sockfd,"$kick",121)==-1){	//KICKを伝える
								perror("error_serv_write_kick_send");
								exit(1);
							}
							sleep(1);
							if(close(user[i].sockfd)==-1){
								perror("error_serv_kick_close");
								exit(1);
							}
							user[i].situation=-1;
							connect--;
							
							if(sprintf(co_buff,"%sさんが%sさんをキックしました",user[t].name,user[i].name)==-1){
								perror("error_serv_sprintf_kick");
								exit(1);
							}
								
							for(s=0;s<20;s++){
								if(user[s].situation==1){	//使用者全員に
									if(write(user[s].sockfd,co_buff,121)==-1){	//誰が誰をキックしたのかを伝える
										perror("error_serv_write_message_send");
										exit(1);
									}
								}
							}
						break;
						}
						
						else if(strcmp(user[t].name,kickname)==0){	//自分自身をキックしようとしたとき
							if(write(user[t].sockfd,"自分自身はキックできません",121)==-1){
								perror("error_serv_write_message_kickself");
								exit(1);
							}
							if(write(user[t].sockfd,"退出のコマンドは$logoutです",121)==-1){	//ログアウトを勧める
								perror("error_serv_write_message_kickadvice");
								exit(1);
							}
							break;
						}
						
						
						else if(i==19){	//キックの対象者が存在しないとき
							if(write(user[t].sockfd,"キック対象者が存在しません",121)==-1){
								perror("error_serv_write_message_kicknone");
								exit(1);
							}
							if(write(user[t].sockfd,"メンバーの一覧はコマンド$membersでみられます",121)==-1){	//メンバーの確認を勧める
								perror("error_serv_write_message_kicknone_advice");
								exit(1);
							}
						}
					}
				}
				
				else if(strncmp(buff,"$",1)==0){
					pri=0;
					pri_flag=0;
					for(i=1;i<22;i++){			//名前が20バイト＋@
						if(buff[i]=='@'){		//相手の名前を取得
							pri_flag=1;
							break;
						}
						pri_name[pri]=buff[i];
						pri++;

					}
					pri_name[pri]='\0';
					
					i++;
					for(s=0;s<20;s++){		
						if((strcmp(user[s].name,pri_name)==0)&&(user[s].situation==1)&&(strcmp(user[t].name,pri_name)!=0)){
							for(l=0;l<120;l++){
								pri_buff[l]=buff[i];
								if(buff[i]=='\0')
									break;
								i++;
							}
							//printf("pri_buff=%s\n",pri_buff);
							sprintf(co_buff,"%s>>",user[t].name);	//送り先でコマンドの認識が出きるように
																	//名前と内容は別々に送信
							
							if(write(user[s].sockfd,co_buff,121)==-1){	//送り主を伝える
								perror("error_serv_write_priname_send");
								exit(1);
							}

							if(write(user[s].sockfd,pri_buff,121)==-1){	//送られてきたメッセージを送る
								perror("error_serv_write_primessage_send");
								exit(1);
							}

							break;
						}

						else if(strcmp(user[t].name,pri_name)==0){		//自分自身にプライベートチャット
							if(write(user[t].sockfd,"自分自身とチャットはできません",121)==-1){
								perror("error_serv_write_primessage_sendself");
								exit(1);
							}
							if(write(user[t].sockfd,"$名前@〜はプライベートチャットのコマンドです",121)==-1){	//プライベートチャットの説明
								perror("error_serv_write_primessage_advice");
								exit(1);
							}
							break;
						}

						else if((s==19)&&(pri_flag==1)){
							if(write(user[t].sockfd,"チャット対象者が存在しません",121)==-1){	//チャット対象者がいない
								perror("error_serv_write_message_none");
								exit(1);
							}
							if(write(user[t].sockfd,"メンバーの一覧はコマンド$membersでみられます",121)==-1){	//メンバーの確認を勧める
								perror("error_serv_write_primessage_noneadvice");
								exit(1);
							}
						}
						
						else if((s==19)&&(pri_flag==0)){
							if(write(user[t].sockfd,"$はコマンドに使用します",121)==-1){	//$で始まっているがどのコマンドにも当てはまらない
								perror("error_serv_write_message_none$");
								exit(1);
							}
							if(write(user[t].sockfd,"コマンド一覧はコマンド$all$でみられます",121)==-1){	//コマンドの確認を勧める
								perror("error_serv_write_message_$all$_advice");
								exit(1);
							}
						}
						
						
					}

				}

				else {						//通常のメッセージ
					sprintf(co_buff,"%s:%s",user[t].name,buff);	//cliのprintfの\nと被るので、\n不要
//エラーチェックし忘れ
					for(i=0;i<20;i++){
						if((i!=t)&&(user[i].situation==1)){				//送り主以外に
							if(write(user[i].sockfd,co_buff,121)==-1){	//送られてきたメッセージを送る
								perror("error_serv_write_message_send");
								exit(1);
							}
						}
					}
				}
			}

			if((user[t].situation==0)&&(FD_ISSET(user[t].sockfd,&readfds)==1)){	//準備中のアカウントから送られてきた場合
												//名前を受けとってもまだ入力があると思われないように、使用中、準備中の順でみてる
				if(read(user[t].sockfd,back_name,20)==-1){		//送られてきた名前のバックアップをとる
					perror("error_serv_read_backname2");			
					exit(1);
				}

				for(s=0;s<20;s++){
					if((strcmp(user[s].name,back_name)==0)&&(user[s].situation==1)){  	
						printf("test1\n"); 
						if(write(user[t].sockfd,"NOT",10)==-1){	//名前の重複を伝える
							perror("error_serv_write_name_errorsend");
							exit(1);
						}
						break;				//同じ名前が一人でもいたら
					}
				}

				if(s==20){						//最後までみても名前の重複が確認されないとき
					strcpy(user[t].name,back_name);		//バックアップの名前を割り当てる
					if(write(user[t].sockfd,"OK",10)==-1){	//名前が重複しなかったことを伝える
						perror("error_serv_write_name_OKsend2");
						exit(1);
					}

					user[t].situation=1;						//使用中に設定

					sprintf(co_buff,"%sさんが入室しました",user[t].name);
					for(l=0;l<20;l++){
						if(user[l].situation==1){						//使用中の人に
							if(write(user[l].sockfd,co_buff,121)==-1){	
								perror("error_serv_write_enter2");			//入室を全員に伝える
								exit(1);
							}
						}
					}
					
					if(connect==20){			//ユーザーの上限に達した
						for(i=0;i<20;i++){
							if(user[i].situation==1){
								if(write(user[i].sockfd,"ユーザーの数が上限に達しました",121)==-1){	//上限を使用者に伝える
									perror("error_serv_write_max_send2");
									exit(1);
								}
							}
						}
					}

				}
			}
		 }
	}

	return 0;
}
