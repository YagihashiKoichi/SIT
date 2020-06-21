#include<stdio.h>
#include<string.h>
/*
CY16173	八木橋晃一	作成日：2017年6月8日	課題6
テスト
case1	
文字列:	(空のファイル)					結果:何も表示されない

case	2
文字列:	ｋ										結果:出現:1回  衝突:0回  k

case	3
文字列:	there	are	pens				結果:出現:1回  衝突:0回  there
																					出現:1回  衝突:0回  are
																					出現:1回  衝突:0回  pens

case	4
文字列:	I am student * / - +		結果:出現:1回  衝突:0回  student
																										出現:1回  衝突:0回  *
																										出現:1回  衝突:0回  +
																										出現:1回  衝突:0回  -
																										出現:1回  衝突:0回  /
																										出現:1回  衝突:0回  i
																										出現:1回  衝突:0回  am



case	5
文字列:I aM Pen i Am pEN 			結果:出現:2回  衝突:0回  pen
																								出現:2回  衝突:0回  i
																								出現:2回  衝突:0回  am
case	6
文字列:あいう 			結果:何も出ない

case	7
文字列: this hist desk isth this			結果:出現:1回  衝突:0回  desk
																																			出現:2回  衝突:2回  this


case	8
文字列:Are you a man?	 				結果:出現:1回  衝突:0回  are
																							出現:1回  衝突:0回  you
																							出現:1回  衝突:0回  a
																						出現:1回  衝突:0回  man?


case	9
文字列:Are you a man ?	 			結果:出現:1回  衝突:0回  are
																						出現:1回  衝突:0回  man
																						出現:1回  衝突:0回  ?
																						出現:1回  衝突:0回  you
																					出現:1回  衝突:0回  a


case	10
文字列:tomのファイル 			結果:出現:1回  衝突:2回  jimpson
																		出現:4回  衝突:3回  through
																出現:1回  衝突:0回  thought
															出現:2回  衝突:0回  child
															現:1回  衝突:3回  heads
															出現:1回  衝突:0回  alike
															出現:2回  衝突:0回  angle
															出現:1回  衝突:2回  board							(一部のみを表示)


case	11
text(存在しないファイル）			結果:can	not	open


関数の説明
azurにある既存のファイルを呼び出して開き、そのなかに書かれている単語を大文字、小文字の区別無く出現回数と衝突回数を数え
その文字と一緒に出力する関数
*/
char	men[100000];																						//単語を保存しとく配列
char	buff[100];																							//単語を一時的に保存しとく配列
char	*p_newmen=men;																					//menのポインタ
struct	point{																								//構造体の宣言：要素は上から出現回数、単語、衝突回数
	int	syutugen;
	char	*word;
	int	syoutotu;
};
struct	point	hashtable[256];							//構造体の配列



char	*create_string(char	buff[100]);								
char	*mem_alloc(int	length);																				
int	hash	(char	*key);																																	
void	dump_ht(void);


int	main	(void)
{
	int	s,amari;											//s:カウンター変数
																				//	amari:ハッシュ値
																	
	char	*moziretu;
	FILE	*istream;
	istream=fopen("tom.txt","r");												//ファイルを開く、r:読み込む

	if(istream==0)																						//該当するファイルがない場合
	{
		printf("can	not	open\n");
		return	1;
	}

	for(s=0;s<2000;s++)
	{
		if(fscanf(istream,"%s",buff)==EOF)	break;				//終わり(EOF)がきたらbreak
																							
		
		amari=hash(buff);											//ハッシュ値を代入
		
		if(hashtable[amari].syutugen==0)							//まだ代入されていないとき
		{		
			moziretu=create_string(buff);								//新しいメモリを確保
			hashtable[amari].word=moziretu;					//文字を代入
			hashtable[amari].syutugen++;										//出現回数をカウント
		}								

		else	if(strcmp(hashtable[amari].word,buff)==0)																			//文字列を比較										
			hashtable[amari].syutugen++;							

		else
			hashtable[amari].syoutotu++;							//衝突回数をカウント
			

	}

	fclose(istream);													//ファイルを閉じる
	dump_ht();																//構造体の要素を出力
	return	0;
}



/*
テスト		コメントにあるようにprintf("%s   ",buff)、printf("%s\n",moziretu)を用意

case1
配列：	there are	pens							結果：there   there
																			are   are
																			pens   pens


関数の説明
コピーしたい文字列のアドレスを引数として、新たなメモリを\0分も確保しそこに指定した文字列を
コピーしてそのアドレスを返す関数

引数：コピーしたい文字列のアドレス
戻り値：コピーした文字列のアドレス
*/
char	*create_string(char	buff[100])
{
	char	*p,*moziretu;										//p:コピーする先のアドレスをさす変数
																			//	moziretu:buffの文字列をpにコピーしたさいそのアドレスをさす変数
	int	length;													//コピーしたい文字列（\0を含む）の長さを代入する変数

																			//	printf("%s   ",buff);
	length=strlen(buff)+1;						//strlen(buff)でコピーしたい文字列の長さを求める（\0を含まない)、+1は\0
	p=mem_alloc(length);
	moziretu=strcpy(p,buff);			//buffの文字列をpの場所にコピー
																		//		printf("%s\n",moziretu);

	return	moziretu;
}




/*
テスト		コメントにあるようにprintf("%d　　",p)、		printf("%d\n",p_newmen)を用意
case1	
文字列:	there are	pens						結果:4250624　　4250630
																							4250630　　4250634
																							4250634　　4250639

関数の説明
メモリを確保してコピー先のアドレスを返す関数

引数：コピーしたい文字列おアドレス
戻り値：コピー先のアドレス
*/
char	*mem_alloc(int	length)
{
	char	*p;																			//コピーする先のアドレスをさす変数																							
	p=p_newmen;																		//コピーする先のアドレスをさす
																							//		printf("%d　　",p);
	p_newmen=p_newmen+length;					//次にコピーする先のアドレスをさす
																							//			printf("%d\n",p_newmen);
	return	p;
}



/*
テスト		コメントにあるようにprintf("%d",key)、	printf("合計%d  ",hashval)を用意
case1	
文字列:adk			結果:97  100  107  合計304

case2
文字列:ADK			結果:97  100  107		合計304

case3
文字列:this			結果:116  104  105  115  合計440

case4
文字列:htsi			結果:104  116  115  105  合計440

関数の説明
文字列を受け取り大文字を小文字に直しそのハッシュ値を返す関数（今回は256の余剰）

引数：ハッシュ値を調べたい文字列
戻り値：引数である文字列のハッシュ値
*/
int	hash	(char	*key)
{
	int	hashval,amari;				//hashval:文字コードを全て足し合わせた値を代入する変数
													//amari:ハッシュ値
	
	hashval=0;

	while(*key!='\0')
	{
		if((65<=*key)&&(*key<=90))						//65<=大文字<=90
			*key=*key+32;																					//小文字になおす
	
																														//printf("%d  ",*key);
		
		hashval=hashval+*key;														//文字コードを足し合わせる
		key++;
	}
	
																														//printf("合計%d  ",hashval);

	amari=hashval%256;																				//ハッシュ値を求める、文字コードの和の256の余剰

	return	amari;
}



/*
関数の説明
構造体の要素に代入されたものをprintfで出力する関数
ただし、構造体の単語にあたる要素が\0の時はそのセルは出力しない

引数：なし
戻り値：なし
*/
void	dump_ht(void)
{
	int	t;												//カウンター変数

	for(t=0;t<265;t++)
	{
		if(hashtable[t].word!=0)																																						//構造体の単語にあたる要素が\0の時はそのセルは出力しない
		{	
			printf("出現:%d回  ",hashtable[t].syutugen);				//その単語が出現した回数
			printf("衝突:%d回  ",hashtable[t].syoutotu);				//その単語が衝突した回数
			printf("%s\n",hashtable[t].word);																					//なんの単語についてか
		}
	}
}

