#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/*
CY16173	八木橋晃一	作成日：2017年6月22日	課題5
テスト
case1
入力：<10,20,30>									結果：<10,20,30>

case2
入力：	<-,20,30>								結果：<-,20,30>

case3
入力：	<10,20,->								結果：<10,20,->

case4
入力：<-,20,->									結果：20(末端と判断される)

case5
入力：	20								結果：20

case6
入力：<10,20,<-,30,40>>									結果：<10,20,<-,30,40>>

case7
入力：<<40,10,50>,20,<30,60,70>>									結果：<<40,10,50>,20,<30,60,70>>

case8
入力：	<>								結果：エラーです。
																				エラーです。
case9
入力：wjeiwqd							結果：エラーです。

case10
入力：-									結果：何も出力されない

case11
入力：	<100,169,123>								結果：<100,169,123>

case12
入力：<-100,-169,-123>									結果：エラーです。

case13
入力：<100,-169,123>								結果：エラーです。

case14
入力：	<0,0,0>								結果：<0,0,0>

case15
入力：<-,-,->									結果：エラーです。

case16
入力：<10,20,30>,;w,dwqd					結果：<10,20,30>

case17
入力：10>									結果：10

case18
入力：	>10,20,30<								結果：エラーです。


関数の説明
入力された文字列から二分木をつくり、作った二分木から文字列になおし
出力する関数。ただし、無効な入力にはエラーメッセージが出力される。
*/

struct	node{											//構造体の宣言
	int	value;
	struct	node	*left;
	struct	node	*right;
};
char	buff[100];										//入力された文字列を収納する配列
char	*nextch=buff;									//配列の先頭を指す


struct	node*	create_node(struct	node	*left,int	value,struct	node	*right);
void	print_tree(struct	node	*p);
struct	node*	read_tree(void);
int	read_number(void);

int	main(void)
{
	struct	node*	root;							//reed_treeの返り値を代入するための変数
																		//	int	sum;		read_numberのテストに使用
																	//print_tree(0);			print_treeのテストで使用

	printf("データを入力してください。\n");
	scanf("%s",&buff);
	root=read_tree();
	if(root!=0)	print_tree(root);

	/*	read_numberのテストに使用
	sum=read_number();
	printf("sun=%d\n",sum);
	*/

	return	0;
}


/*
テスト		コメントにあるようにpritfを用意
case1
入力：<10,20,30>									結果：left=0		value=10	right=0
																								new_node->left=0			new_node->value=10		new_node->right=0
																								left=0		value=30	right=0
																								new_node->left=0			new_node->value=30		new_node->right=0
																								left=7627576		value=20	right=7627600
																								new_node->left=7627576			new_node->value=20		new_node->right=7627600



関数の説明
新しく作る節点のメンバーに代入したい値を引数とし、その分の容量を確保して
新しく作った節点のメンバーにそれぞれ代入する。その後新しく作った節点への
ポインタを返す関数。

引数1：新しく作る節点のメンバーleftに代入するアドレス
引数2:新しく作る節点のメンバーvalueに代入する値
引数3:新しく作る節点のメンバーrightに代入するアドレス
戻り値：新しく作った節点へのポインタ
*/
struct	node*	create_node(struct	node	*left,int	value,struct	node	*right)
{
	struct	node		*new_node;																																	

	/*create_nodeのテストに使用
		printf("left=%d		",left);
		printf("value=%d	",value);
		rintf("right=%d\n",right);						
	*/
																																																																																																																															
	new_node=(struct	node*)malloc(sizeof(struct	node));					//メモリの容量を確保
	new_node->value=value;																																																											
	new_node->left=left;						
	new_node->right=right;						
						
	/*create_nodeのテストに使用					
		printf("new_node->left=%d			",new_node->left);
		printf("new_node->value=%d		",new_node->value);
		printf("new_node->right=%d\n",new_node->right);
	*/												
																												
	return	new_node;		
}


/*
テスト
case1
入力：<10,20,30>									結果：<10,20,30>

case2
入力：	mainにprint_tree(0);を用意													結果：-

関数の説明
引数のポインタが指す節点からの二分木を表示する関数。

引数：節点または節点のメンバーへのポインタ
戻り値：なし
*/
void	print_tree(struct	node	*p)
{
	if(p==0)		printf("-");										//ポインタの指す先に節点が無いとき

	//p=\0(ポインタの指す先に節点がない)だとエラーになってしまうがそのときは上のifで対応している
	else	if((p->left==0)&&(p->right==0))				printf("%d",p->value);				

	else														//p(根,leftまたはright)が\0以外を指すとき
	{
		printf("<");
		print_tree(p->left);							
		printf(",%d,",p->value);
		print_tree(p->right);						
		printf(">");
	}	
}


/*
テスト	mainにてread_numberのみ呼び出してmainのコメントにあるように出力
case1
入力：10								結果：sum=10
																				
関数の説明
入力された文字列の中にある文字としての数字を
数値になおして返す関数。

引数：なし
戻り値：配列の中にある数字（入力された文字列の中にある数字）の1つ（箱１つだけとは限らない）
*/
int	read_number(void)
{
	int	sum=0;

	while(('0'<=*nextch)&&(*nextch<='9'))
	{
		sum=sum*10+(*nextch-'0');
		nextch++;
	}
	return	sum;
}


/*
テスト		コメントにあるようにprintfを用意し、if文の中身を変更
case1
入力：<10,20,30>									結果：0,10,0	構造体=10511160
																								0,30,0	構造体=10511184
																								10511160,20,10511184	構造体=10511208


関数の説明
（入力された文字列を元に）nextchの指す文字列から木を１つ読み込み、その根の構造体nodeへのポインタを
返す関数。

引数：なし
戻り値：新しく作った節点へのポインタまたは0
*/
struct	node*	read_tree(void)
{
	int	number;
	struct	node	*left,*right;
	//	struct	node	*test;read_treeのテストに使用

	if(*nextch=='-')			//ポインタが指す先が\0なので0を返す
	{
		nextch++;
		return	0;
	}
		
	//leftとrightが\0を指すとき
	else	if(('0'<=*nextch)&&(*nextch<='9'))						return		create_node(0,read_number(),0);
	
/*	read_treeのテストに使用
	else	if(('0'<=*nextch)&&(*nextch<='9'))		
	{
		number=read_number();
		test=create_node(0,number,0);
		printf("0,%d,0	構造体=%d\n",number,test);
		return		test;
	}
*/

	else
	{
		if(*nextch=='<')
		{
			nextch++;																		//指す先をずらす（次のbuffの箱を見る）
			left=read_tree();													//自分自身を呼ぶ。関数が終わったらここから
		}
	
		if(*nextch==',')
		{
			nextch++;																			
			number=read_number();									
		
			if(*nextch==',')
			{
				nextch++;																				
				right=read_tree();									//自分自身を呼ぶ。関数が終わったらここから
			}		

			if(*nextch=='>')
			{
				nextch++;
				return	create_node(left,number,right);				
			}

			/*read_treeのテストに使用
			if(*nextch=='>')							
			{
				nextch++;
				test=create_node(left,number,right);				
				printf("%d,%d,%d	構造体=%d\n",left,number,right,test);		
				return	test;
			}
			*/

		}
	}

	printf("エラーです。\n");
	return	0;		
}
