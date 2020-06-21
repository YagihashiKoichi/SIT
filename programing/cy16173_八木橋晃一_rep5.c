/*
cy16173	八木橋晃一	作成日：2017年5月18日	課題３

関数の説明
英語の場合はe,数学はm,物理はpで不等式または等式を５文字以内で入力すると、その条件を満たす生徒の
学籍番号を表示するプログラム。
e>m>pと入力した場合はe>mかつm>pの条件を満たす生徒を表示し、e>mと入力した場合はその条件を満たす生徒を表示する。
ただし、使える演算子は<,=,>のみであり、学籍番号は０から始まるものとする。
また、リセットを押さない限りプログラムは終わらない。
入力者への注意：空白には対応していないので入力しないこと。

テスト
正しい入力1
入力：e<p					結果：No.0  No.1  No.2  No.3  No.4  No.6  No.8  No.9  No.13  No.16  No.18  No.19  

正しい入力2
入力：e>p					結果：No.5  No.7  No.10  No.11  No.12  No.14  No.15  No.17  

正しい入力3
入力：e>p>m				結果：何も出力されず（エラーメッセージがないので該当なし）

正しい入力4
入力：e>p=m				結果：No.10  

正しい入力5
入力：e<m>p				結果：No.0  No.1  No.4  No.7  No.8  No.12  No.14  No.15  No.16  No.19  

正しい入力6
入力：e<m<p				結果：No.3  No.13  No.18  

正しい入力7
入力：	e=e				結果：No.0  No.1  No.2  No.3  No.4  No.5  No.6  No.7  No.8  No.9  No.10  No.11  No.12  No.13  No.14  No.15  No.16  No.17  No.18  No.19  

正しい入力8
入力：m=m=m				結果：  No.0  No.1  No.2  No.3  No.4  No.5  No.6  No.7  No.8  No.9  No.10  No.11  No.12  No.13  No.14  No.15  No.16  No.17  No.18  No.19  

誤った入力1
入力：	m					結果：  入力が不完全です。

誤った入力2
入力：m>						結果： 入力が不完全です。

誤った入力3
入力：		m>e=				結果： 入力が不完全です。

誤った入力4
入力：	a						結果： 入力が不完全です。

誤った入力5
入力：ajhf				結果： 入力が不完全です。

誤った入力6
入力：s<d						結果： 科目が無効な入力です。

誤った入力7
入力：s<p					結果： 科目が無効な入力です。

誤った入力8
入力：	p<f					結果： 科目が無効な入力です。


誤った入力9
入力：d<e>n					結果： 科目が無効な入力です

誤った入力10
入力：		p<s>n				結果： 科目が無効な入力です

誤った入力11
入力：		p<e>k				結果： 科目が無効な入力です

誤った入力12
入力：	p< >k					結果： 入力が不完全です。

誤った入力13
入力：01234567891				結果： 1つ目の演算子が無効な入力です。

誤った入力14
入力：e<m>p>					結果： 入力が多すぎませんか？
																					No.0  No.1  No.4  No.7  No.8  No.12  No.14  No.15  No.16  No.19 



*/

#include<stdio.h>

int	check;															//グローバル変数、エラーメッセージを２個表示せないためのカウンター変数

struct	record{												//教科を表す構造体
	int	eng,math,phy;
};

struct	record	database[20]={{27,54,49},																						//与えられているデータの構造体
																					{55,99,56},
																					{96,81,100},
																					{28,80,90},
																					{22,57,31},
																					{94,75,73},
																					{60,59,67},
																					{64,79,30},
																					{29,77,57},
																					{62,47,95},
																					{93,23,23},
																					{73,63,59},
																					{34,57,27},
																					{51,62,86},
																					{73,76,28},
																					{72,96,64},
																					{24,76,73},
																					{98,91,88},
																					{70,78,80},
																					{60,98,95}
																					};

struct	query{																														//グローバル変数；fは文字、opは演算子、右の数字はそれぞれ何番目かを表している
	char	f1,op1,f2,op2,f3;
};



double	calc_mean(struct	record	r);							//プロトタイプ宣言；１人の3科目の点数を引数として、その3科目の平均値を計算する関数
struct	query	input_query();																//プロトタイプ宣言；引数は無く、入力された不等式または等式を返す関数
int	check_record(struct	query	q,struct	record	r);							//プロトタイプ宣言；入力された不等式または等式が正しいか判定する関数
int	get_field(char	c,struct	record	r);						//プロトタイプ宣言；それぞれの科目と点数を一致させその値を代入する関数





int	main(void)
{
	while(1)
	{
		int	hantei,i;				//hanteiは入力された不等式または等式が正しいかを判定する変数、iは学籍番号兼カウンター変数
		struct	record	r;						//生徒1人の各科目の点数を代入するための変数
		struct	query	q;							//入力された文字列を代入するための変数

		printf("科目に関する不等式または等式を５文字以内で立ててください。\n");

		q=input_query();									//入力された文字列を代入

		for(i=0;i<=19;i++)																											//20人分の点数を見るまで繰り返す
		{
			r=database[i];																															//databaseの0から数えてi行目のデータをrに代入
			hantei=check_record(q,	r);
			if(hantei==1)		printf("No.%d  ",i);			
		if(i==19)	printf("\n\n");																								//連続で入力したさい見やすくするための改行
		}
		fflush(stdin);																																	//scanfの入力にたまっている文字列をクリア
	}
	return	0;
}


/*
生徒１人の3科目の平均点を出す関数
ただし、この課題3では使用しない

引数：生徒1人の各科目の点数
戻り値：生徒１人の平均点
*/
double	calc_mean(struct	record	r)
{
	double	average;	
	average=(r.eng+r.math+r.phy)/3;
	return	average;
}


/*
不等式または等式を入力する関数
また入力された不等式または等式が不完全ではないか判定し、
次に使用されている演算子が正しいかどうかを判定する。
ただし、他の関数と合わせてもエラーメッセージは1つしか表示されず、
”不完全な入力＞演算子＞科目”の優先順位で表示され、エラーは左から判定していくとする。

引数:なし
戻り値：入力された文字列

テスト
case1
入力：e				結果：入力が不完全です。

case2
入力：e>			結果：入力が不完全です。

case3
入力：e>m>		結果：入力が不完全です。

case4
入力：e1m>p	結果：1つ目の演算子が無効な入力です。

case5
入力：e<map		結果：2つ目の演算子が無効な入力です。



*/
struct	query	input_query(void)												
{
	struct	query	q;
	char	buffer[10];
	scanf("%s",buffer);
	q.f1=buffer[0];
	q.op1=buffer[1];
	q.f2=buffer[2];
	q.op2=buffer[3];
	q.f3=buffer[4];																		//bufferの中身が何もないときは\0が代入される

	check=0;																					//エラーのカウンター変数を0に初期化

																								//以下のif分はそれぞれのエラーメッセージに対応
	
	if(buffer[1]=='\0')																			//1文字しか入力がないとき
	{
		printf("入力が不完全です。\n");
		check++;
	}
	
	else	if((buffer[2]=='\0')&&(check==0))																					//2文字しか入力がないとき
	{
		printf("入力が不完全です。\n");
		check++;
	}
	
	else	if((buffer[3]=='\0')&&(check==0))	;				//3文字で終わりの時。これがないと3文字しか入力がなくても下のelse ifに引っかかる

	else	if((buffer[4]=='\0')&&(check==0))				//4文字しか入力がないとき
	{
		printf("入力が不完全です。\n");											
		check++;
	}

	else	if((buffer[1]!='<')&&(buffer[1]!='>'))							//1つ目の演算子が非対応
	{
		if((buffer[1]!='=')&&(check==0))			
		{																											
			printf("1つ目の演算子が無効な入力です。\n");
			check++;	
		}
	}

	else	if((buffer[3]!='<')&&(buffer[3]!='>'))							//2つ目の演算子が非対応
	{
		if((buffer[3]!='=')&&(check==0))																														
		{
			printf("2つ目の演算子が無効な入力です。\n");
			check++;
		}	
	}

	else	if(buffer[5]!='\0')							//2つ目の演算子が非対応
	{
		printf("入力が多すぎませんか？\n");
		check++;
	}

	return	q;
}


/*
入力された不等式または等式が正しいはどうかを判定する関数。
まず左の不等式または等式が正しいか判定し、次に右の不等式または等式が
正しいかどうかを判定する。どちらも正しい場合は１を返しそれ以外は０を返す。
また無効な科目（e,m,p以外）が入力された場合はエラーメッセージを表示する。
ただし、他の関数と合わせてもエラーメッセージは1つしか表示されず、
”不完全な入力＞演算子＞科目”の優先順位で表示され、エラーは左から判定していく。

引数１：入力された文字列
引数２：生徒１人の点数
戻り値１：入力された不等式または等式が正しいときは1
戻り値２：入力された不等式または等式が正しくないきは0


テスト
case1
入力：q>m		結果：科目が無効な入力です。

case2
入力：m>a		結果：科目が無効な入力です。

case3
入力：m>p>a		結果：科目が無効な入力です。

case4
入力：e<m>p		結果：hidari=1,migi=1,zentai=2(最初の1回だけを表示)
コメントにある部分のpurintfで出力

case5
入力：e>m>p		結果：hidari=0,migi=1,zentai=1(最初の1回だけを表示)
コメントにある部分のpurintfで出力

*/
int	check_record(struct	query	q,struct	record	r)
{
	int	e1,e2,e3,hidari,migi,zentai;
	hidari=0;
	migi=0;
	zentai=0;																		//hidari,migi,zentaiはそれぞれ左、右、全体の不等式または等式の正誤判定に使用	

	e1=get_field(q.f1,r);											//入力に対応した科目(1科目目)の点数を代入
	e2=get_field(q.f2,r);											//入力に対応した科目(2科目目)の点数を代入

	if((0<=e1)&&(0<=e2))
	{
		if((q.op1=='<')&&(e1<e2))																	hidari=1;
		else	if((q.op1=='=')&&(e1==e2))					hidari=1;
		else	if((q.op1=='>')&&(e1>e2))						hidari=1;					//左の不等式が正しかったらhidariに1を代入
	}
	
	if((q.op2=='\0')&&(hidari==1))		return	1;														//q.f2で入力が終わっている

	if(check==0)																																					//科目に対する無効な入力に対してエラーメッセージを表示
	{
		if((check==0)&&(e1<0))	
		{
			printf("科目が無効な入力です。\n");		
			check++;
		}

		else	if((check==0)&&(e2<0))	
		{
			printf("科目が無効な入力です。\n");
			check++;
		}

	}


	if((q.op2=='\0')&&(hidari==0))		return	0;		

	//printf("hidari=%d\n",hidari);


	e3=get_field(q.f3,r);																																														//入力に対応した科目(3科目目)の点数を代入
									
	if((0<=e2)&&(0<=e3))
	{
		if((q.op2=='<')&&(e2<e3))																	migi=1;
		else	if((q.op2=='=')&&(e2==e3))				migi=1;
		else	if((q.op2=='>')&&(e2>e3))					migi=1;												//右の不等式が正しかったらmigiに1を代入
	}

	zentai=hidari+migi;																																																//左、右の不等式共に正しかったらzentaiの値は2となる


	if(check==0)																																					//科目に対する無効な入力に対してエラーメッセージを表示
	{
		if((check==0)&&(e3<0))	
		{
			printf("科目が無効な入力です。\n");
			check++;
		}	
	}
	
	//printf("migi=%d\n",migi);
	//printf("zentai=%d\n",zentai);

	if(zentai==2)		return	1;
	else	return	0;
}


/*
入力された科目に対応した点数を判定し、対応した点数を返す関数。
ただし、無効な入力が行われた場合、返す変数の値の分からない初期値で
比較するのを防ぐため、点数としてあり得ない負の値（-1）を返す。

引数１：科目にあたる部分の入力された文字
引数２：生徒１人の点数
戻り値：入力された科目に対応した点数、また無効な入力の場合は-1を返す

テスト
case1
入力：q>m		結果：atai=-1,atai=54,atai=-1,atai=99（最初の4個だけを記入）
コメントにある部分でataiの値をprintfで出力

case2
入力：p>m		結果：atai=49,atai=54,atai=-56,atai=99（最初の4個だけを記入）
コメントにある部分でataiの値をprintfで出力

case3
入力：p>m>e		結果：atai=49,atai=54,atai=27（最初の3個だけを記入）
コメントにある部分でataiの値をprintfで出力



*/
int	get_field(char	c,struct	record	r)
{
	int	atai;									
	
	if(c=='e')					atai=r.eng;									//対応している科目の点数をataiに代入
	else	if(c=='m')		atai=r.math;
	else	if(c=='p')		atai=r.phy;								

	else	atai=-1;							/*e,m,p以外の文字が入力されたときにataiが初期の値で返るのを防ぎ、
																	check_recordで判断するため点数としてあり得ない負の値を代入*/

	//printf("atai=%d\n",atai);																	

	return	atai;
}





