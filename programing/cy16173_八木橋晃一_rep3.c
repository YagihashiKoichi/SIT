/*
cy16173	八木橋晃一	2017年5月8日

関数の説明
Σ1/n!をn=0からkまでの計算してネイピア数e（自然対数）の近似値を求める
n=kまで計算した値からn=k-1まで計算した値を引いた値すなわち1/k!の値があるスレッショルド（閾値）以下になったときに
収束したとみなし計算をやめ、n=kまで計算した値をeの近似値として出力する関数。
ただし今回はスレッショルド（閾値）を1e-10とする。

テスト
関数のなかのコメントに書いてある通りに計算途中の値をdoubleの限界である下15桁までをprintfで出力した
・n!の計算結果は増加、Σ計算の値は増加、1/n!の値は減少していることを確認。
・k=14の時に計算を終了するため14!に注目した。
	14!の値が87178291200.000000000000000と表示されこの値は正しかった。



課題7において
printfを用いてwa(n=0からn=kまで和),ikiti（napier(k)-napier(k-1)）,bunnbo(n!)の計算途中の値をprintfで出力した結果
k=12のとき、wa=2.71828182829
					bunnbo=12!=479001600
k=13のとき、wa=2.71828182782
					bunnbo=13!=-2147483648
となり、waの値が減少しているためikiti（napier(k)-napier(k-1)）の値が負になってしまう。
これは13の階上がintの型の範囲外にあるからである。
改善策としてbunnboとkaijouに対してはintではなくdoubleを使った
*/

#include<stdio.h>

double	napier(int) ;											//問題文におけるそのときのnの階乗を求める関数のプロトタイプ宣言
double	fact(int);											//問題文のΣ計算をする関数プロトタイプ宣言

int	k;																																	//何番目の計算かを数えるカウンタ変数(グローバル変数)
double	wa,ikiti,bunnbo,kaijou=1;						/*bunnbo=kaijou:問題文におけるそのときのnの階乗
																																				ikiti:閾値(グローバル変数)*/
int	main(void)
{

	k=1;																																														//何番目の計算かを数えるカウンタ変数
	wa=1;																																												//事前に0の階乗分を事前に足しておく
	while(1)
	{
		wa=napier(k);	
		/*
		printf("(%d)wa=%.15lf\n",k,wa);																	//waの値とそのときのkの値をpintf(%.15lf)で出力
		printf("(%d)ikiti=%.15lf\n\n",k,ikiti);				//ikitiの値とそのときのkの値をpintf(%.15lf)で出力
		*/
		if(ikiti<=1e-10)			break;																									//napier(k)-napier(k-1)=1/k!なのでikitiで判断
		k++;
	}

	printf("e=%.15lf",wa);
	return	0;
}

/*
関数factの説明
問題文におけるそのときのnの階乗を求める関数
引数：問題文におけるそのときのnの値（k)
戻り値：問題文におけるnの階乗(kaijou)
*/
double	fact(int	k)	
{
	kaijou=k*kaijou;
	return	kaijou;
}

/*
関数napierの説明
問題文におけるそのときのnの階乗の値で1を割ってn-1までのΣ計算の値に加算する関数
引数：問題文におけるそのときのnの値(k)
戻り値：問題文におけるnまでのΣ計算(wa)
*/
double	napier(int	k)
{
	bunnbo=fact(k);

	/*printf("(%d)bunnbo=%.15lf\n",k,bunnbo);				//waの値とそのときのkの値をpintf((%.15lf))で出力*/

	ikiti=1/bunnbo;																																							//	問題文におけるそのときのnの階乗の値で1を割る		
	wa=wa+ikiti;
	return	wa;
}


