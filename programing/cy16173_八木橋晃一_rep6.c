/*
CY16173 八木橋晃一	作成日：2017年5月25日	課題７

テスト





関数の説明
メイン関数のなかに書かれている文字列（buff）に対して以下の操作を行う関数。
最初の入力の促しにdと入力すると削除したい文字数の入力が促され、数字を入力すると頭から数えた
文字数分削除された文字列が出力される。一方で最初の入力の促しにiと入力すると、挿入したい文字列
の入力が促され文字列を入力するとその文字列が元々の文字列の先頭に挿入される。


テスト
削除の時
case1:
入力：ijeijdofieofjopjd	,6				結果：ofieofjopjd

case2:
入力：abcdef,0						結果：abcdef

case3:
入力：abcdef,1									結果：bcdef

case4:
入力：abcdef,5								結果：f

case5:
入力：	abcdef,6							結果：（何も出力されず）

case6:
入力：	abcdef,7							結果：永遠に数字の入力が行われる


挿入の時
case1:
入力：ijeijdofieofjopjd,iojfiowfi								結果：iojfiowfiijeijdofieofjopjd

case2:
入力：a,whduwqh							結果：whduwqha

case3:
入力：abcdef,123								結果：123abcdef

case4:
入力：abcdef,12 3								結果：12abcdef

case5:
入力：abc def	,123					結果：123abc def

case6:
入力：	abcdef	,あい						結果：あいabcdef

case7:
入力：	おう	,あい						結果：あいおう


*/

#include<stdio.h>

int	length(char	*p);																																//プロトタイプ宣言、文字列の文字数を数えてその文字数を返す関数
void	copy(char	*p_to,char	*p_from);						/*プロトタイプ宣言、文字列を左や右にずらてコピーしたり、
																																												他の文字をその上からコピーする関数*/


int	main	(void)
{
	char	buff[100]="おう";							//操作を行う文字列の宣言
	char	in[100];																									//挿入したい文字列を入れるための箱を宣言
	char	*p,which,c;																								/*p:ポインター,which:入力者がd(削除)、i(挿入)のどちらを選んだか判定するための変数
																																		c:挿入の際の最後に\0と交換するために操作を行う文字列の最初の文字を保存する変数*/


	int	count,count_in,n;																	/*	count:操作する文字列（削除または挿入される文字列）の文字数を保存する変数,
																															count_in:挿入する文字列の文字数を保存する変数,n:削除する文字数を保存する変数*/
	
	while(1)
	{
		printf("文字を削除したい場合はdを、挿入したい場合はiを入力してください。\n");
		scanf("%c",&which);
		if((which=='d')||(which=='i'))				break;
		printf("無効な入力です。\n");																		
	}

	p=buff;																																//buffのアドレスをpに代入		
	count=length(buff);																											//操作する文字列の文字数を保存
	
	if(which=='d')																													//文字列に対して削除を行うとき
	{
		printf("削除したい文字数を入力してください。\n");
		scanf("%d",&n);
	
		while(1)																															//buffの文字数より多い文字数削除しないか、または負の値が入力されていないかの判定
		{
			if(0<=n&&n<=count)	break;										//入力された文字列が正常ならbreak
			scanf("%d",&n);																											//入力された文字列が異常の場合再度入力を促す
		}
	
		p=p+n;																														//pのアドレスをずらす
		copy(buff,p);																											//copyの１に対応。ずらした文字列をもとの文字列に上書き
	}	


	if(which=='i')																										//文字列に対して挿入を行うとき
	{
		printf("入力したい文字列を入力してください。\n");
		scanf("%s",in);
		count_in=length(in);										//挿入する文字列の文字数を保存
		c=*p;																			//操作を行う文字列の最初の文字を保存
		p=p+count_in;																//挿入する文字数の分だけpのアドレスをずらす
		copy(p,buff);																/*copyの2に対応。挿入する文字数のスペースを前の部分に作る。
																									あくまでずらして文字列をコピーしているのでスペース＝空欄ではない*/
		
		copy(buff,in);														//copyの3に対応。操作する文字列の冒頭に挿入する文字列を上書き（\0も含む）
		*p=c;																		/*挿入した文字列によって\0に上書きされた部分に対し、
																							保存しておいた挿入する文字列の頭文字で上書き*/
	}

	printf("%s",buff);														//最終的文字列を出力

	return	0;
}


/*
関数の説明
引数（文字列のアドレス）が指す文字列の文字数を数えて、その値を返す関数

引数：文字数を知りたい文字列のアドレス
戻り値：引数のアドレスは指す文字列の文字数

テスト
関数の中に示す通りにprintfでcountの値を出力(length単体で行った)

case1:
入力：d								結果：1

case2:
入力：fofkjf						結果：6

case3:
入力：jf1k3ok						結果：7

*/
int	length(char	*p)
{
	int	count;									//文字数をカウントするカウンター変数
	count=0;	

	while(1)
	{
		count++;
		p++;
		if(*p=='\0')	break;
	}

	//printf("%d",count);

	return	count;
}




/*
関数の説明
コピーしたい文字列を他の文字列にコピーして上書きする関数

引数１：コピーされる側の文字列のアドレス
引数２：コピーする側の文字列のアドレス
戻り値：なし


テスト
関数のコメントにあるところでアドレスを一番左に設定しp_fromをprintfで出力した。


1に対するテスト
case1:
引数：abcdef、cdef						結果：cdef

case2:
引数：123456、456				結果：456



2に対するテスト
case1:
入力：abcdef（2文字挿入時）							結果：ababcdef

case2:
入力：123456（3文字挿入時）					結果：123123456



3に対するテスト
case1:
入力：ababcdef（12挿入時）							結果：12(\0でとまるため)

case2:
入力：123123456（abc挿入時）					結果：abc(\0でとまるため)


*/




void	copy(char	*p_to,char	*p_from)
{
	
	int	i,t,count;		/*iは2回目のcopyの呼び出しに対して挿入に対応する部分以外が働かないようにするためのカウンター変数
														tはカウンター変数、countは文字数を保存する変数*/
	i=0;
	t=0;

	if((p_to<=p_from)&&(i==0))						//1,右から左に文字をコピーするとき(削除するとき)
	{
		while(1)
		{
			*p_to=*p_from;
			if(*p_from=='\0')	break;							
			p_from++;
			p_to++;		
		}
		printf("%s\n",p_to);													//1のときのテスト
	}

	if((p_from<p_to)&&(i==0))									//2,左から右に文字をコピーするとき(挿入のとき際にスペースを作るとき)
	{
		count=length(p_from);	
		p_from=p_from+count;							//このとき*p_from='\0'
		p_to=p_to+count;

		while(1)
		{
			*p_to=*p_from;
			if(t==count)	break;
			t++;														
			p_from--;
			p_to--;
		}

																																											//2のときのテスト
		i=i+1;
	}
	
	if(i==1)					//3,文字挿入する
	{
		while(1)
		{
			*p_to=*p_from;
			if(*p_from=='\0')	break;													//\0もコピーするためこの位置
			p_from--;
			p_to--;
		}
																																		//3のときのテスト
	}	
}

