#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/select.h>


int main(){
	struct sockaddr_in serv_addr;
	 int sockfd,p_connect,p_write,p_close,p_read;
	int i;
	int able=0;	//初回の入力かを確認
	fd_set readfds;
	char buff[121];
	char back_buff[121];
	char name_buff[20];

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1){
		perror("error_cil_socket");
		exit(1);
	}

	memset(&serv_addr,0,sizeof(struct sockaddr_in));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr("172.28.34.67");
	serv_addr.sin_port=htons(10000);
	
	printf("名前を入力してください\n");
	scanf("%s",name_buff);		//servで他のクライアント割り当て待ちにならないようにconnect前

	//コネクションを張るための要求をサーバーに送る
	p_connect=connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr_in));
	if(p_connect==-1){
		perror("error_cil_connect");
		exit(1);
	}

	if(write(sockfd,name_buff,20)==-1){
		perror("error_cil_write_namesend");
		exit(1);
	}

	while(1){
		FD_ZERO(&readfds);
		FD_SET(sockfd,&readfds);
		FD_SET(0,&readfds);
		
		if(select(sockfd+1,&readfds,NULL,NULL,NULL)==-1){
			perror("error_cil_nameselect");
			exit(1);
		}

		if(FD_ISSET(sockfd,&readfds)==1){


			if(read(sockfd,buff,10)==-1){				//名前が重複しているかの結果を受け取る
				perror("error_serv_read_resultname_receive");
				exit(1);
			}


		

			if(strcmp(buff,"OK")==0) break;	//名前が重複していなかったのでチャットへ		
			else{							//名前が重複しているので、再度名前設定
				printf("その名前はすでに使われています\n");
				printf("再度名前を入力してください\n");
				scanf("%s",name_buff);
				if(write(sockfd,name_buff,20)==-1){
					perror("error_cil_write_renamesend");
					exit(1);
				}
			}
		}
	}


	while(1){
	
		FD_ZERO(&readfds);
		FD_SET(0,&readfds);
		FD_SET(sockfd,&readfds);
		
		if(select(sockfd+1,&readfds,NULL,NULL,NULL)==-1){
			perror("error_cil_select");
			exit(1);
		}

		if(FD_ISSET(0,&readfds)==1){			//キーボード入力がある場合
			scanf("%s",buff);
			
			if((strcmp(buff,"$re")==0)&&(able!=0)){	   //最初の入力ではないかつコマンド$re
				if(write(sockfd,back_buff,100)==-1){  //前回と同じものを送信
					perror("error_cil_write_backsend");
					exit(1);
				}
				if(strncmp(back_buff,"$stamp",6)!=0){  //スタンプは自分にも送られてくるので除外
					printf("%s\n",back_buff);	   //再送信内容を自分にも表示
				}
			}
		
			else if((strcmp(buff,"$re")==0)&&(able==0)){   //最初の入力でかつコマンド$re
				printf("参照する入力がありません\n");      //前回と同じものを送信
				printf("コマンド$reは直近のコマンドの再実行またはメッセージの再送信です\n");
			}

			else if((strcmp(buff,"$all$")==0)){   //コマンド一覧を表示する
				printf("$members：参加者一覧を表示\n");
				printf("$kick[名前]：対象者をキックする\n");
				printf("$re：最後に送信したものを再送信\n");
				printf("$stamp1：頭を抱えるスタンプ\n");
				printf("$stamp2：ジョジョスタンプ1\n");
				printf("$stamp3：ジョジョスタンプ2\n");
				printf("$stamp4：ジョジョスタンプ3\n");
				printf("$[名前]@文：対象者へプライベートチャット送信\n");
				printf("$logout：ログアウトする\n");
				printf("$pass:[パスワード]:特権ユーザーへ切り替える\n");
				printf("#end：サーバーを終了させる（特権ユーザーのみ）\n");
			}

			else{
				if(write(sockfd,buff,100)==-1){	//通常メッセージをサーバーへ送信
					perror("error_cil_write_send");	
					exit(1);
				}
				able=1;
				
			}
			if(strcmp(buff,"$re")!=0){		//2回目以降のコマンド$reで保存されるの防ぐため
				strcpy(back_buff,buff);	//送信したもののバックアップをとる
			
			}

			if(strcmp(buff,"$logout")==0){		
				printf("%sさんが退出しました\n",name_buff);
				break;
			}				
			

		}
		
		if(FD_ISSET(sockfd,&readfds)==1){			//メッセージが着た場合
			if(read(sockfd,buff,121)==-1){
				perror("error_cil_read_receive");
				exit(1);
			}

			if(strcmp(buff,"$kick")==0){	//キックコマンドのとき
				printf("キックされました\n");
				break;
			}

			else if(strcmp(buff,"$stamp1")==0){
				printf("　　 ＿\n");
				printf(" ／∧ )∧ ⌒)\n");
				printf("｜(Д｀/ /\n");
				printf("｜レ、/ /＼\n");
				printf("＼／(＿_ノ＼\n");
				printf("　　　/　　 ｜\n");
				printf("　　 /　/＼　＼＿\n");
				printf("　　(＿ヘ_)＼＿_ ヽ\n");
				printf("　　　　　　 　(_ノ\n");
			
			}

			else if(strcmp(buff,"$stamp2")==0){
				printf("お　　　 ＿_＿　　　  さ\n");
				printf("れ　　 ／￣￣ ＼　 　 す\n");
				printf("た　　// / |　 ∧    　が\n");
				printf("ち　 ｜＿＿＿＿_｜\n");
				printf("に (⌒ ｿ　　　　 `ﾚ⌒)  デ\n");
				printf("で　＼_二二二二二_／  ィ\n");
				printf("き　 //=ヽノ≡ヽ( ヽ   オ\n");
				printf("な 〈((･ /　ｲ･)　Lノ  ！\n");
				printf("い　(| ~(ﾆヽ⌒　ﾉr)\n");
				printf("事　 |　ﾄ┬┬ｲ ｜ｲ|\n");
				printf("を＿ | ｜/￣~| ｜リ\n");
				printf("／へ＼　ﾋL＿ノ ｜|\n");
				printf("`へ ＼) `ー-′／ |\n");
				printf("へ ＼ﾉ| ＼＿／ / |\n");
				printf("Zヽﾉ(ノ ＼ ＼／　ヽ\n");
				printf("￣\n");
			}

			else if(strcmp(buff,"$stamp3")==0){
				printf(" 　　　　　 　へ\n");
				printf("あそ平　 (￣￣￣￣￣ヽ\n");
				printf("ここ然　( ヽ ヽ ノ　 ヽ\n");
				printf("がにと　 >＜二二二＞､ノ\n");
				printf("れシや　//へ　　ノ~ヽ|\n");
				printf("るビっ (Y (･>ッ<･)　|)\n");
				printf("！れて　|　-(＿)-　 Ｖ\n");
				printf("　るの /|　r＝＝-、 /＼\n");
				printf("　！け｜ヽ ＼/二ノ／/\n");
				printf("　　る　＼＞——イ／\n");
				printf("　　ッ　　ヽ　　 /\n");

			}

			else if(strcmp(buff,"$stamp4")==0){
				printf("こいつ\n");
				printf("最高に誇りの道を行く者\n");
				printf("\n");
				printf("　　　 _\n");
				printf("　　　( ヽ\n");
				printf("　　　｜ |\n");
				printf("　　　｜ |\n");
				printf("　　　 ﾚ-|＿_へ\n");
				printf("　　　/ ／ ／￣＼\n");
				printf("　　 ｜(ﾌ(~)(~)￣)､\n");
				printf("　　 ()丿 /　/ イ |\n");
				printf("　　 ｜| ｜ ｜　Lノ\n");
				printf("　　 ｜　　　　｜\n");
				printf("　　 ｜　　　　/\n");
				printf("　　／￣￣￣/-<\n");
				printf("　 //　 /　/　｜\n");
				printf("　｜／~￣￣　 /\n");
				printf("　/／￣￣￣＼/\n");
			}

			else{
				printf("%s\n",buff);
			}
		}
				

	}
		//ソケットを終了する
		if(close(sockfd)==-1){
			perror("error_cli_close");
			exit(1);
		}


 return 0;
}

