#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
CY16173 八木橋晃一 作成日：2017年7月13日 課題5

テスト
case1
ファイル：a a a a a a a a a a a a a
結果：a
case2
ファイル：a b c A B C
結果：a
	  b
      c

case3
ファイル：A B C a b c 
結果：A
      B
      C

case4
ファイル：g f e d c b a 
結果：a
      b
      c
      d
      e
      f
      g

case5
ファイル：CHAPTER I TOM No answer TOM 
          No answer  Whats gone with that
          boy I wonder You TOM No answer 
         The old lady pulled her spectacles down 
結果：answer
      boy
      CHAPTER
      down
      gone
      her
      I
      lady
      No
      old
      pulled
      spectacles
      that
      The
      TOM
      Whats
      with
      wonder
      You

case6
ファイル：（何も書かれていない）
結果：(null)

case7
ファイル：(存在しないファイル)
結果：can not open

case8
ファイル：お　え　う　い　あ
結果：お　え　う　い　あ

case9
ファイル：お え う い あ
結果：あ
      い
      う
      え
      お

case9
ファイル：9 8 7 6 5 5 4 3 2 2 11 1
結果：1   (数字の昇順ではなく辞書順のため)
      11
      2
      3
      4
      5
      6
      7
      8
      9


関数の説明
引数１が指すファイルの文字列を大文字、小文字の区別せず、
重複を許さずに辞書順に並べ替え、引数２のファイルにその
結果を書き込む関数。
引数１：辞書順に並べ替えたいファイルへのポインタ
引数２：辞書順に並べ替えたものを書き込みたいファイルへのポインタ
*/

char	*data[10000];
char	buff[100];

char	*create_string(char	*key);
void	copyfile	(FILE	*is,FILE	*os);
void	string_sort	(int	end);
void	swap	(int	k,int	l);
int uniq(int	wordnum);



int	main		(int	argc	,char	*argv[])
{
	FILE	*is,*os;
	
	is=fopen(argv[1],"r");

	if(is==0)									//該当するファイルがない場合
	{
		printf("can	not	open\n");
		return	0;
	}	
	
	os=fopen(argv[2],"w");
	

	if(os==0)									//該当するファイルがない場合
	{
		printf("can	not	open\n");
		return	0;
	}
	
	copyfile(is,os);
	fclose(is);
	fclose(os);
	
	return	0;
}




/*
関数の説明
コピーしたい文字列のアドレスを引数として、新たなメモリを\0分も確保しそこに指定した文字列を
コピーしてそのアドレスを返す関数

引数：コピーしたい文字列のアドレス
戻り値：コピーした文字列のアドレス
*/
char	*create_string(char	*key)
{
	char	*p,*moziretu;						//p:コピーする先のアドレスをさす変数
	
												//	moziretu:buffの文字列をpにコピーしたさいそのアドレスをさす変数
	int	length;									//コピーしたい文字列（\0を含む）の長さを代入する変数

	length=strlen(key)+1;						//strlen(buff)でコピーしたい文字列の長さを求める（\0を含まない)、+1は\0				
	p=malloc(length);
	moziretu=strcpy(p,key);						//buffの文字列をpの場所にコピー		

	return	moziretu;
}


/*
テスト
mainと統一

関数の説明
引数１が指すファイルの文字列を大文字、小文字の区別せず、
重複を許さずに辞書順に並べ替え、引数２のファイルにその
結果を書き込む関数。

引数１：辞書順に並べ替えたいファイルへのポインタ
引数２：辞書順に並べ替えたものを書き込みたいファイルへのポインタ
戻り値：なし
*/
void	copyfile	(FILE	*is,FILE	*os)
{
	int	wordnum,i;								//wordnum:並べ替えを行う単語数を代入する変数
												//i:カウンター変数
	wordnum=0;

	while(1)
	{
		if(fscanf(is,"%s",buff)==EOF)	break;	//終わり(EOF)がきたらbreak																		
		data[wordnum]=create_string	(buff);		//容量を確保	
		wordnum++;	
	}
	
	string_sort(wordnum);						//重複を許して辞書順に並び替える
	wordnum=uniq(wordnum);						//重複を許さず辞書順に並べ替える

	for(i=0;i<wordnum;i++)
		fprintf(os,"%s\n",data[i]);				//並び替えたモノを新しく作ったファイルに書き込む

	return;
}


/*
テスト
case1
ファイル：a b c d e g f
test=2
結果:a b c d e f g

case2
ファイル：a A b B c C
結果:a b c

関数の説明
大文字、小文字の区別をせず重複を許して、読み込まれた単語を
辞書順に並び替える（ポインタの指す先をかえている）

引数：読み込まれた単語数
戻り値：なし
*/
void	string_sort	(int	end)
{
	int	t,s,check;								//t,s:カウンター変数
												//check:for文でswapしているかを確認するための変数
	//int	test=0;								//string_sortのテストで使用


	for(s=0;s<end-1;s++)
	{
		check=0;
		for(t=0;t<end-1;t++)
		{
			if(stricmp(data[t],data[t+1])>0)	//辞書順になっていなかった場合
			{
				check++;
				swap	(t,t+1);				//順番を入れ替える
			}	
		}

		/*
		test++;								//string_sortのテストで使用
		if(check==0)	
		{
			printf("%d",test);
			return;
		}
		*/
					
		if(check==0)	return;						//swapしていなかったら終了

	}

	return;
}

/*
テスト
case1
ファイル：abcdegf
結果：data[k]=g,data[l]=f→data[k]=f,data[l]=g

関数の説明
引数でもってきた番号の箱の中身を入れ替える関数

引数１：引数２の箱と順番を入れ替えたい箱の番号
引数２：引数１の箱と順番を入れ替えたい箱の番号
戻り値：なし
*/
void	swap	(int	k,int	l)
{
	char	*save;								//順番を交換するために一時的にアドレスを保存するための変数
	save=data[k];
	data[k]=data[l];
	data[l]=save;
	return;
}

/*
テスト
ファイル：aaabbcc
結果：data[1]=a→data[1]=b
	  data[2]=a→data[2]=c
	  wordnum=7,pre=3
関数の説明
大文字、小文字区別せずに重複を許さなっかたさいの単語を辞書順に
なるように並び替える（そのようにポインタを繋ぎなおす）
その後単語数を返す関数。

引数：大文字、小文字区別せずに重複を許した際の単語数
戻り値：大文字、小文字区別せずに重複を許さなっかた際の単語数
*/

int uniq(int	wordnum)
{
	int	t,pre;									//t:カウンター変数
												//pre:交換する場所を保存するカウンター変数
	
	pre=0;

	for(t=0;t<wordnum-1;t++)					//配列をはみ出さないためにwordnum-1
	{
		if(stricmp(data[t],data[t+1])!=0)		//辞書順になっていなかった場合
		{
			pre++;
			data[pre]=data[t+1];				//新しくでた単語を指す
		}
	}
	pre++;
	
	return	pre;
}
