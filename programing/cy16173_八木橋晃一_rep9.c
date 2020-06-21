#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
CY16173	八木橋晃一	作成日：2017年6月15日			課題7


テスト
case	1
ファイル：空のファイル							削除したい単語：		am																								結果：何も出力されない

case2
ファイル：存在しないファイル							削除したい単語：		問われない																								結果：can	not	open

case3
ファイル：This shit hist tHis sit						削除したい単語：	this																				結果：=><sit,1>
																																																																																													=><hist,1>=><shit,1>
case4
ファイル：This shit hist tHis sit						削除したい単語：	THIS																					結果：=><sit,1>
																																																																																													=><hist,1>=><shit,1>
case5
ファイル：This shit hist tHis sit					削除したい単語：		shit																												結果：=><sit,1>
																																																																																														=><hist,1>=><this,2>																								
case6
ファイル：This shit hist tHis sit							削除したい単語：hist																										結果：=><sit,1>
																																																																																																		=><shit,1>=><this,2>
case7
ファイル：This shit hist tHis sit								削除したい単語：	sit																									結果：=><hist,1>=><shit,1>=><this,2>


case8
ファイル：This shit hist tHis sit								削除したい単語：am																										結果：=><sit,1>
																																																																																																=><hist,1>=><shit,1>=><this,2>
case9
ファイル：a							削除したい単語：a																										結果：何も出力されない

case10
ファイル：am	am	am	am	am	am	am								削除したい単語：am																										結果：何も出力されない


関数の説明
azurにある既存のファイルを呼び出して開き、そのなかに書かれている単語を大文字、小文字の区別無く出現回数を数え
衝突した場合は新しいセルを左に作る。その後削除したい単語を入力するとその単語が削除された状態で単語が入っている
リストを出力する関数。
*/
struct	item	*create_item(char	*key,struct	item	*p);				
void	print_list(struct	item	*p);
char	*create_string(char	*key);
struct	item	*search_item(char	*key,struct	item	*p);
int	hash	(char	*key);
void	dump_ht(void);
void	chainhash	(char	*key);
struct	item	*delete_item(char	*key,struct	item	*p);


struct	item{																																						//構造体の宣言：要素は上から出現回数、単語、構造体へのポインタ
	int	count;
	char	*word;
	struct	item	*next;
};
char	men[100000];																																				//単語を保存しとく配列
char	buff[100];																																				//単語を一時的に保存しとく配列
struct	item	*hashtable[256];																						//構造体へのポインタの配列


int	main(void)
{
	char	delete[100];																																	//delete[100]:削除したい文字列を収納するための配列
	int	s,hashti;																																			//s:カウンター変数,hashti:ハッシュ値（今回は256の剰余）
	FILE	*istream;	
																														
	istream=fopen("text.txt","r");												//ファイルを開く、r:読み込む

	if(istream==0)																						//該当するファイルがない場合
	{
		printf("can	not	open\n");
		return	0;
	}

	printf("削除したい単語を入力してください。");
	scanf("%s",delete);
	hashti=hash(delete);

	for(s=0;s<2000;s++)
	{
		if(fscanf(istream,"%s",buff)==EOF)	break;				//終わり(EOF)がきたらbreak																		
		chainhash	(buff);
	}

	hashtable[hashti]=delete_item(delete,hashtable[hashti]);
	fclose(istream);													//ファイルを閉じる
	dump_ht();																//構造体の要素を出力

	return	0;
}


/*
関数の説明
構造体itemから成るリストを表示する
引数：表示したいリストの先頭の構造体itemへのポインタ（0でもよい）
戻り値：なし
注意：引数が0の場合は改行だけする
*/
void	print_list(struct	item	*p)
{
	while(p!=0)
	{
		printf("=><%s,%d>",p->word,p->count);				//表示形式の修正はここ
		p=p->next;
	}

	printf("\n");
}


/*
テスト						コメントにあるようにprint_list(p)、printf("%s\n",moziretu)を用意
case	1
ファイル：	This shit hist this sit									削除したい単語：	this				結果：=><this,1>
																																																																																		=><this,1>
																																																																																		=><shit,1>=><this,1>
																																																																																		=><shit,1>=><this,1>
																																																																																		=><hist,1>=><shit,1>=><this,1>

																																																																																		=><sit,1>

関数の説明
セルに入れたい単語と新しく作ったセルのnextが指したいアドレスを引数とし、
新しくセルを作りそのセルに単語をいれ新しく作ったセルのアドレスを返す関数。

引数1：wordにいれたい単語
引数2：新しく作ったセルのnextが指したいアドレス
戻り値：新しく作ったセルのアドレス
*/
struct	item	*	create_item(char	*key,struct	item	*p)
{
	struct	item		*new_item,*old_item;																																		//*new_item:確保したメモリのアドレスを代入するための変数
																																																																					//*old_item:new_itemのアドレスを代入して一時的に値を保存するための変数

																																																																					//print_list(p);							//	create_itemのcase1において使用
	new_item=(struct	item*)malloc(sizeof(struct	item));						//確保したメモリのアドレスをnew_itemに代入
	new_item->count=1;																																																												//初めて現れる単語なのでcountを1にする
	new_item->word=create_string(key);											
	new_item->next=p;																
	old_item=new_item;																																																													//new_itemのアドレスを代入して一時的に値を保存する
	new_item++;
																																																																//	print_list(old_item);						//	create_itemのcase1において使用
	return	old_item;		
}


/*
テスト		コメントにあるようにprintf("%s   ",buff)、printf("%s\n",moziretu)を用意
case	1
ファイル：This shit hist this sit									削除したい単語：	this													結果：this   this
																																																																																								shit   shit
																																																																																								hist   hist
																																																																																								sit   sit


関数の説明
コピーしたい文字列のアドレスを引数として、新たなメモリを\0分も確保しそこに指定した文字列を
コピーしてそのアドレスを返す関数

引数：コピーしたい文字列のアドレス
戻り値：コピーした文字列のアドレス

*/
char	*create_string(char	*key)
{
	char	*p,*moziretu;																													//p:コピーする先のアドレスをさす変数
																																					//	moziretu:buffの文字列をpにコピーしたさいそのアドレスをさす変数
	int	length;																															//コピーしたい文字列（\0を含む）の長さを代入する変数
															
																																					//			printf("%s   ",buff);		//create_stringのcase1において使用

	length=strlen(key)+1;																									//strlen(buff)でコピーしたい文字列の長さを求める（\0を含まない)、+1は\0
	p=malloc(length);
	moziretu=strcpy(p,key);																					//buffの文字列をpの場所にコピー
																																			//printf("%s\n",moziretu);						//create_stringのcase1において使用
	return	moziretu;
}



/*
テスト									コメントにあるようにprintfを利用
case	1
ファイル：	This shit hist this sit									削除したい単語：	this										結果：this   7103000
																																																																																								this   4350752


関数の説明
探したい単語のアドレスと探したい単語のハッシュ値に対応するhashtableのアドレスを引数とし
リストのなかから探したい単語を探し、該当する単語があるセルのアドレスを返す関数。

引数1：探したい単語のアドレス
引数2：探したい単語のハッシュ値に対応するhashtableのアドレス
戻り値：該当する単語があるセルのアドレス
*/
struct	item	*search_item(char	*key,struct	item	*p)
{
	int	hantei;	

	while(p!=0)
	{
		hantei=strcmp(p->word,key);																				//pが指すリストのwordがkeyと同じか判定
																																													/*
																																														if(hantei==0)								//search_itemのcase1において使用
																																														{
																																																	printf("%s   ",p->word);	
																																																	printf("%d\n",p);		
																																																	printf("%s   ",key);	
																																																	printf("%d\n",key);		
																																														}				
																																												*/

		if(hantei==0)		return	p;																							//見つけたのでそのリストのアドレスを返す
		p=p->next;
	}

	return	0;											//見つからずに最後のリストにきたので0を返す
}


/*
テスト		コメントにあるようにprintf("%d",key)、	printf("合計%d  ",hashval)を用意
case1	
ファイル:adk			結果:97  100  107  合計304

case2
ファイル:ADK			結果:97  100  107		合計304

case3
ファイル:this			結果:116  104  105  115  合計440

case4
ファイル:htsi			結果:104  116  115  105  合計440

関数の説明
文字列を受け取り大文字を小文字に直しそのハッシュ値を返す関数（今回は256の余剰）

引数：ハッシュ値を調べたい文字列
戻り値：引数である文字列のハッシュ値
*/
int	hash	(char	*key)
{
	int	hashval,hashti;				
													
	
	hashval=0;

	while(*key!='\0')
	{
		if((65<=*key)&&(*key<=90))						//65<=大文字<=90
			*key=*key+32;																					//小文字になおす
																													//printf("%d  ",*key);
		hashval=hashval+*key;														
		key++;
	}

	hashti=hashval%256;																			
	return	hashti;
}


/*
関数の説明
構造体の単語にあたる要素が\0の時はそのセルは出力しないが、それ以外のときはセルのなかにある単語と
countを出力する関数。

引数:なし
戻り値：なし
*/
void	dump_ht(void)
{
	int	t;												//カウンター変数

	for(t=0;t<256;t++)
	{
		if(hashtable[t]!=0)														//構造体の単語にあたる要素が\0の時はそのセルは出力しない
			print_list(hashtable[t]);
	}
}


/*
テスト						コメントにあるようにprintfを利用
case	1
ファイル：This shit hist this sit																						結果：1,2

case	2
ファイル：This shit hist this sit							削除したい単語：this														結果：this
																																																																																						this
																																																																																						shit
																																																																																						shit
																																																																																						hist
																																																																																						hist
																																																																																						sit
																																																																																						sit
		

関数の説明
登録したい文字列を引数とし、ハッシュ値が衝突したときにその単語を入れるためのセルをcreate_itemを使って新しく左に作り、
衝突しないときは、そのセルのcountを１つ増やす関数。

引数：登録したい文字列
戻り値：なし
*/
void	chainhash	(char	*key)
{
	int	hashti;
	struct	item	*list,*p;																																	//list:リストの先頭のアドレスを代入するための変数
																																														//p:該当する単語があるセルのアドレス（search_itemの戻り値）
	hashti=hash(buff);
	list=hashtable[hashti];																																//リストの先頭のアドレスを指す
	p=search_item(key,list);

	if(p!=0)																																															//既存の単語なのでcountを増やす
		p->count++;																																												//	chainhashのcase1においてthisのカウンタを出力
	
	else
		hashtable[hashti]=create_item(key,list);					//listが指す先は最初0を指しているので場合分けの必要は無い
		
																																																		/*																																																		
																																																			else																											//chainhashのcase2において使用
																																																			{	hashtable[hashti]=create_item(key,list);					
																																																						printf("%s\n",hashtable[hashti]->word);
																																																						printf("%s\n",key);
																																																			}	
																																																		*/	
}


/*
テスト			コメントにあるようにprintf("%s\n",p->word)、printf("%d\n",p)を用意
case	1
ファイル：This shit hist this sit			削除したい単語：	hist																	結果：hist
																																																																																							shit
case	2
ファイル：This shit hist this sit					削除したい単語：	this																	結果：this

関数の説明
削除したい単語のアドレスとリストの先頭のアドレスを引数とし、目的の単語があるセルのアドレスをpとすると、
pの前のセルのnextの指す先をpの次のセルにし、pが指すセルを空にして単語を削除したあとのリストの先頭の
セルのアドレスを返す関数。


引数1：削除したい単語のアドレス
引数2：リストの先頭のセルのアドレス（hashtable[hashti]は指すアドレス）
戻り値：目的の単語を削除したあとのリストの先頭のセルのアドレス
*/
struct	item	*delete_item(char	*key,struct	item	*p)
{
	struct	item	*p_back,*p_head;																		//p_back:p->backが指す１つ前のセルのアドレスを保存するための変数
																																									//p_head:目的の単語を削除したあとのリストの先頭のセルのアドレス
																																								
	p_head=p;

	if(p==0)		return	p_head;
	
	if(strcmp(p->word,key)==0)																//削除したい単語とセルの中の単語が一致したとき
	{
																																							//	printf("%s\n",p->word);				//delete_itemのcase1に利用
		p_head=p->next;																														//リストの先頭のセルを削除するので、2番目のセルが先頭となる
		free(p);																																	//削除した単語があるセルのデータを空にする
																																							//	printf("%s\n",p_head->word);																//delete_itemのcase1に利用

		return	p_head;																													//リストの先頭を返す
	}
		
		
	p_head=p;																																							//リストの先頭のセルを削除するので、1番目のセルが先頭となる
		
	while(p->next!=0)																																			//着目しているセルがリストの最後じゃないとき
	{				
		p_back=p;																																						//pが指すセルの１つ前のセルを使いたいのでのアドレスを保存
																																							
		p=p->next;																																					//次のセルを基準に考える
		
		if(strcmp(p->word,key)==0)																			//削除したい単語とセルの中の単語が一致した場合
		{
																																										//printf("%s\n",p->word);								//delete_itemのcase2に利用			
																																											
			p_back->next=p->next;																							//削除したい単語があるセルをとばしてセルを繋ぐ
			free(p);																																			//削除した単語があるセルのデータを空にする
			break;
		}
	}
			
	return	p_head;																									//リストの先頭を返す
}
	



	




