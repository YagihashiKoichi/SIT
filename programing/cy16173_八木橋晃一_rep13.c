#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
CY16173 八木橋晃一 作成日：2017年7月27日 課題D(拡張なし)

テスト
case1
ファイル：an arround and apple annaunce a
探す単語：a
結果：arround
      aunce
	  and
      annaunce
      apple
      an
      a

case2
ファイル：an arround and apple annaunce a
探す単語：n
結果：nce
      nd
      nnaunce
      nd
      n
      naunce

case3
ファイル：bbbbbbbbbb
探す単語：B
結果：何も出力されない

case4
ファイル：bbbbbbbbbb
探す単語：b
結果：bbbbb
      bbbbbbbb
      bbbbbbbbb
      bbbbbbbbbb
      bbbbbb
      bbbbbbb
      b
      bbb
      bbbb
      bb

case5
ファイル：BBBBBBBBBB
探す単語：B
結果：BBBBB
      BBBBBBBB
      BBBBBBBBB
      BBBBBBBBBB
      BBBBBB
      BBBBBBB
      B
      BBB
      BBBB
      BB

case6
ファイル：bbbbbbbbbb
探す単語：c
結果：何も出力されない

case7
ファイル：[EOF] a
探す単語：a
結果：a

case8
ファイル：存在しないファイル
探す単語：
結果：can	not	open


case9
ファイル：空のファイル
探す単語：a
結果：何も出力されない

関数の説明
ドキュメントの中に指定した文字列（大文字、小文字は区別する）があれば、その文字列を
含む部分とそれ以降の文字列を出力する関数。
探したい文字列の入力と探す工程が無限ループになっている
ためこの関数が終了する事はない。
*/

char	*data[100000];
char	buff[100];
int	wordnum=0;					//wordnum:並べ替えを行う単語が入っている配列の番号

void	create_string(char	*key);
void	copyfile	(FILE	*is);
void	string_sort	(int	end);
void	swap	(int	k,int	l);
void	search_word(int	left,char	key[],int	right,int	length);


int	main		(void)
{
	int	length,i;					//探したい単語の文字数を代入する変数
	char	key[30];				//探したい単語入れる配列
	FILE	*is;

	

	is=fopen("tom.txt","r");

	if(is==0)						//該当するファイルがない場合
	{
		printf("can	not	open\n");
		return	0;
	}

	copyfile(is);
	fclose(is);	


	
	while(1)
	{
		printf("探したい単語を入力してください。   ");
		scanf("%s",key);
		length=strlen(key);							//探したい単語の文字数
		search_word(0,key,wordnum-1,length);
		printf("\n");	
	}

	return	0;
}


/*
テスト
case1
ファイル：abcdegf
結果：abcdegf	(copyfile内で並び替えたあとでdata[0?wordnum]を出力)
	  bcdegf
      cdegf
      degf
      egf
      gf
      f
      
関数の説明
コピーしたい文字列のアドレスを引数として、新たなメモリを\0分も確保し
そこに指定した文字列をコピーし、その後、コピーした単語（文字列）と
その単語のサフィクスを全て作成しそのアドレスを返す関数。

引数：コピーしたい文字列
戻り値：なし
*/
void	create_string(char	*key)
{
	char	*p;						//p:コピーする先のアドレスをさす変数
	int	i;
									//	moziretu:buffの文字列をpにコピーしたさいそのアドレスをさす変数
	int	length;						//コピーしたい文字列（\0を含む）の長さを代入する変数

	length=strlen(key)+1;			//strlen(buff)でコピーしたい文字列の長さを求める（\0を含まない)、+1は\0				
	p=malloc(length);
	strcpy(p,key);					//buffの文字列をpの場所にコピー		
	data[wordnum]=p;

	for(i=0;i<length-2;i++)			//ヌルはささない、その単語の全てのサフィクスの作成
	{
		wordnum++;
		p++;	
		data[wordnum]=p;
	}
	return	;
}


/*
テスト
case1
ファイル：abcdegf
結果：abcdegf	（buffの中身）

関数の説明
引数１が指すファイルの文字列を大文字、小文字の区別せず、
重複を許してに辞書順に並べ替える関数。

引数１：辞書順に並べ替えたいファイルへのポインタ
戻り値：なし
*/
void	copyfile	(FILE	*is)
{
	int	i;				//i:カウンター変数

	while(1)
	{
		if(fscanf(is,"%s",buff)==EOF)	break;	//終わり(EOF)がきたらbreak																		
		create_string	(buff);					//容量を確保	
		wordnum++;	
	}

	
	string_sort(wordnum);						//重複を許して辞書順に並び替える

	return;
}


/*
テスト
case1
ファイル：abcdegf
結果：abcdegf	(copyfile内で並び替えたあとでdata[0?wordnum-1]を出力)
	  bcdegf
      cdegf
      degf
      egf
      f
      gf

関数の説明
大文字、小文字の区別をせず重複を許して、読み込まれた単語を
辞書順に並び替える（ポインタの指す先をかえている）関数。

引数：読み込まれた単語数
戻り値：なし
*/
void	string_sort	(int	end)
{
	int	t,s,check;								//t,s:カウンター変数
												//check:for文でswapしているかを確認するための変数

	for(end;1<end-1;end--)
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

		if(check==0)	return;					//swapしていなかったら終了

	}

	return;
}


/*
テスト
case1
ファイル：abcdegf
結果：data[k]=gf,data[l]=f→data[k]=f,data[l]=gf

関数の説明
引数でもってきた番号の箱の中身を入れ替える関数。

引数１：引数２の箱と順番を入れ替えたい箱の番号
引数２：引数１の箱と順番を入れ替えたい箱の番号
戻り値：なし
*/
void	swap	(int	k,int	l)
{
	char	*save;			//順番を交換するために一時的にアドレスを保存するための変数
	save=data[k];
	data[k]=data[l];
	data[l]=save;
	return;
}


/*
テスト
mainと統一

関数の説明
引数で持ってきた文字列（key）と比較し、その文字列で始まる
ファイル内の単語とサフィクスを出力する関数。

引数１：二分法用いた際の領域の左端の配列の番号
引数２：探したい文字列
引数３：二分法用いた際の領域の右端の配列の番号
引数４：探したい文字列の文字数（￥０を含まない）
戻り値：なし
*/
void	search_word(int	left,char	key[],int	right,int	length)
{
	int	middle;					//二分法を用いた場合の中間値

	middle=(left+right)/2;
	
	if(left>right)	return;		//二分法の左端と右端が入れ替わったとき（停止条件）

	else						//二分法を続行
	{
		if(strncmp(key,data[middle],length)==0)		//比較した文字列分が同じ
		{
			printf("%s\n",data[middle]);
			search_word(middle+1,key,right,length);
			search_word(left,key,middle-1,length);	
		}

		else	if(strncmp(key,data[middle],length)>0)	search_word(middle+1,key,right,length);	//探してる文字列が右側にある

		else		search_word(left,key,middle-1,length);	//探してる文字列が左側にある
	
	}
}
