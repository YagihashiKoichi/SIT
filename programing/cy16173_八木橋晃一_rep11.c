#include<stdio.h>
#include<stdlib.h>
#include<time.h>
/*
CY16173	八木橋晃一	作成日：2017年7月6日		課題5-1,5-2

テスト
case1
データ：<<5,10,20>,15,<-,35,30>>
挿入：挿入不可
深さ：なし
結果：5
		10
		20
		incorect	order

case2
データ：<<5,10,15>,20,<-,30,35>>
挿入：30
深さ：0
結果：<<5,10,15>,20,<-,30,35>>

case3
データ：<<5,10,15>,20,<-,30,35>>
挿入：1
深さ：3
結果：<<<1,5,->,10,15>,20,<-,30,35>>

case4
データ：<<5,10,15>,20,<-,30,35>>
挿入：40
深さ：3
結果：<<5,10,15>,20,<-,30,<-,35,40>>>

case5
データ：<<5,10,15>,20,<-,30,35>>
挿入：0
深さ：3
結果：<<<0,5,->,10,15>,20,<-,30,35>>

case6
データ：0
挿入：22
深さ：1
結果：<-,0,22>

case8
データ：-
挿入：32
深さ：0
結果：32

case9(乱数)
データ：0
結果：
key=13,depth=1
<-,0,13>
key=3,depth=2
<-,0,<3,13,->>
key=43,depth=2
<-,0,<3,13,43>>
key=75,depth=3
<-,0,<3,13,<-,43,75>>>
key=31,depth=3
<-,0,<3,13,<31,43,75>>>
key=98,depth=4
<-,0,<3,13,<31,43,<-,75,98>>>>
key=43,depth=0
<-,0,<3,13,<31,43,<-,75,98>>>>
key=28,depth=4
<-,0,<3,13,<<28,31,->,43,<-,75,98>>>>
key=7,depth=3
<-,0,<<-,3,7>,13,<<28,31,->,43,<-,75,98>>>>
key=93,depth=5
<-,0,<<-,3,7>,13,<<28,31,->,43,<-,75,<93,98,->>>>>


case10(乱数)
データ：100000
結果：
key=96,depth=1
<96,100000,->
key=90,depth=2
<<90,96,->,100000,->
key=29,depth=3
<<<29,90,->,96,->,100000,->
key=33,depth=4
<<<<-,29,33>,90,->,96,->,100000,->
key=91,depth=3
<<<<-,29,33>,90,91>,96,->,100000,->
key=87,depth=5
<<<<-,29,<-,33,87>>,90,91>,96,->,100000,->
key=0,depth=4
<<<<0,29,<-,33,87>>,90,91>,96,->,100000,->
key=40,depth=6
<<<<0,29,<-,33,<40,87,->>>,90,91>,96,->,100000,->
key=84,depth=7
<<<<0,29,<-,33,<<-,40,84>,87,->>>,90,91>,96,->,100000,->
key=49,depth=8
<<<<0,29,<-,33,<<-,40,<49,84,->>,87,->>>,90,91>,96,->,100000,->

case11(乱数)
データ：<<5,10,15>,20,<-,30,35>>
結果：
key=17,depth=3
<<5,10,<-,15,17>>,20,<-,30,35>>
key=65,depth=3
<<5,10,<-,15,17>>,20,<-,30,<-,35,65>>>
key=43,depth=4
<<5,10,<-,15,17>>,20,<-,30,<-,35,<43,65,->>>>
key=40,depth=5
<<5,10,<-,15,17>>,20,<-,30,<-,35,<<40,43,->,65,->>>>
key=14,depth=3
<<5,10,<14,15,17>>,20,<-,30,<-,35,<<40,43,->,65,->>>>
key=36,depth=6
<<5,10,<14,15,17>>,20,<-,30,<-,35,<<<36,40,->,43,->,65,->>>>
key=89,depth=4
<<5,10,<14,15,17>>,20,<-,30,<-,35,<<<36,40,->,43,->,65,89>>>>
key=3,depth=3
<<<3,5,->,10,<14,15,17>>,20,<-,30,<-,35,<<<36,40,->,43,->,65,89>>>>
key=89,depth=0
<<<3,5,->,10,<14,15,17>>,20,<-,30,<-,35,<<<36,40,->,43,->,65,89>>>>
key=47,depth=5
<<<3,5,->,10,<14,15,17>>,20,<-,30,<-,35,<<<36,40,->,43,47>,65,89>>>>


case12
データ：<<a,b,c>,d,<-,e,f>>
結果：
エラーです1。
エラーです2。
エラーです2。




関数の説明
二分探索木のデータを入力し、挿入したい値を入力すると正しい場所にその値をもつ
節点を新しく作り、できあがった二分探索木を表示する関数。
ただし、誤った二分探索木が入力されたときは挿入を行わず誤りを見つけた時点で、
エラーメッセージを表示し終了する関数。
*/
int	reserve=-1;									//check_nodeで前の値を保存する変数
															//あり得ない負の値を初期値として代入としている

struct	node{
	int	value;
	struct	node	*left;
	struct	node	*right;
};
char	buff[100];
char	*nextch=buff;


struct	node*	create_node(struct	node	*left,int	value,struct	node	*right);								//プロトタイプ宣言
void	print_tree(struct	node	*p);
struct	node*	read_tree(void);
int	read_number(void);
int	search_bt(struct	node	*nodep,int	key);
int	check_node(struct	node	*nodep);
int	check_bt(struct	node	*nodep);
int	insert_bt(struct	node	*nodep,struct	node	**ptr,int	key,int	depth);


int	main(void)										
{
	struct	node*	nodep;
	int	key,r,i,depth=0;															//key:挿入したい値
																									//r:ランダムの値を代入する変数
																									//i:カウンター変数
																									//depth:挿入した節点の深さを代入する変数



	srand(time(0));			//関数randを使うための準備

	printf("データ入力してください。\n");
	scanf("%s",&buff);
	nodep=read_tree();
	
	if(check_bt(nodep)==0)	return	0;								//誤った二分探索木のときは途中で終了


	for(i=0;i<10;i++)
	{
		r=rand()%100;		//0?100までの乱数を作ってrに代入する
									//乱数を作る関数rand()の結果はとても大きい
									//100の余剰をとると手頃な値になる
		depth=0;
		depth=insert_bt(nodep,&nodep,r,depth);
		printf("key=%d,depth=%d\n",r,depth);
		print_tree(nodep);
		printf("\n");
	}

	/*		
	printf("挿入したい数を入力してください。\n");
	scanf("%d",&key);																											//挿入しち値を読み込む
									
	depth=insert_bt(nodep,&nodep,key,depth);					
	
	printf("深さ:%d",depth);
									
												
	printf("\n");
	print_tree(nodep);
	*/

	return	0;
}


struct	node*	create_node(struct	node	*left,int	value,struct	node	*right)
{
	struct	node		*new_node,*old_node;																																	
																																																																																																																																							
	new_node=(struct	node*)malloc(sizeof(struct	node));					
	new_node->value=value;																																																											
	new_node->left=left;						
	new_node->right=right;																									
	old_node=new_node;																																																													
	new_node++;
																																																														
	return	old_node;		
}


void	print_tree(struct	node	*p)
{
	if(p==0)		printf("-");

	//p=\0だとエラーになってしまうがそのときは上のifで対応
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


struct	node*	read_tree(void)
{
	int	number;
	struct	node	*left,*right;

	if(*nextch=='-')
	{
		nextch++;
		return	0;
	}
		
	//leftとrightが\0を指すときのvalue
	else	if(('0'<=*nextch)&&(*nextch<='9'))						return	create_node(0,read_number(),0);	
	
	else
	{
		if(*nextch=='<')
		{
			nextch++;
			left=read_tree();
		}
	
		else
		{
			printf("エラーです1。\n");
			return	0;
		}
		
		if(*nextch==',')
		{
			nextch++;
			number=read_number();									//value
		}

		else
		{
			printf("エラーです2。\n");
			return	0;
		}

		if(*nextch==',')
		{
			nextch++;																				//>を指す
			right=read_tree();						
		}
	
		else
		{
			printf("エラーです3。\n");
			return	0;
		}

		if(*nextch=='>')
		{
			nextch++;
			return	create_node(left,number,right);				
		}
			
		else
		{
			printf("エラーです4。\n");
			return	0;
		}
	}

	printf("エラーです5。\n");
	return	0;		
}


/*
関数の説明
入力されたデータの中に探している値があれば１を返し、
無ければ０を返す関数。また探す過程では自分を返す
再帰関数。

引数１：根または葉へのポインタ
引数２：探したい値
戻り値１：入力されたデータの中に探している値があれば１
戻り値２：入力されたデータの中に探している値が無い
				または一番下まで行ったとき（\0を指している時）０
戻り値３：探す過程では自分を返す
*/
int	search_bt(struct	node	*nodep,int	key)
{
	if(nodep==0)	return	0;																													//	探している値がデータの中にない
	else	if(nodep->value==key)	return	1;				//	探している値がデータの中にある
	else	if(key<nodep->value)																						//探している値とポインタが指すセルのvalueの大小を比較
	{
		return	search_bt(nodep->left,key);
	}
	else{
		return	search_bt(nodep->right,key);
	}
}



/*
テスト
case1
データ：<<5,10,20>,15,<-,35,30>>

結果：nodep->valueとreserveの値を出力
現在5,１つ前-1
現在10,１つ前5
現在20,１つ前
現在15,１つ前20
incorect	order


関数の説明
正しい二分探索木かどうか判定する関数。正しい場合は１を返し、
正しくない場合は０を返す。

引数１：根または葉へのポインタ
戻り値１：正しい二分探索木のときは１
戻り値２：誤った二分探索木のときは０
*/
int	check_node(struct	node	*nodep)
{
	//printf("現在%d,１つ前%d\n",nodep->value,reserve);
	//check_nodeのテストで使用

	if(nodep->value<reserve)					//１つ前のcheck_nodeで表示した値と現在の値を比較
	{
		printf("\nincorect	order");
		return	0;
	}		

	printf("%d\n",nodep->value);
	reserve=nodep->value;											//表示した値を保存
	return	1;
}



/*
テスト
case1
データ：<<5,10,20>,15,<-,35,30>>
結果：5
		10
		20
		incorect	order



関数の説明
正しい二分探索木かどうかをcheck_nodeを使って判定する関数。

引数１：根または葉へのポインタ
戻り値１：一番下まで行ったとき（\0を指している時）
				またはleftとrightのどちらも正しい二分探索木だったとき１
戻り値２；一度でも誤った二分探索木があったとき０を返す
*/
int	check_bt(struct	node	*nodep)
{
	if(nodep==0)	return	1;					//一番下まで行ったとき（\0を指している時）

	else
	{
		if(check_bt(nodep->left)==0)		return	0;					//一度でも誤った二分探索木があったとき
		if(check_node(nodep)==0)	return	0;													//一度でも誤った二分探索木があったとき
		if(check_bt(nodep->right)==0)		return	0;				//一度でも誤った二分探索木があったとき
	}	
	return	1;				//leftとrightのどちらも正しい二分探索木だったとき
}


/*
テスト
case1
データ：<<5,10,15>,20,<-,30,35>>					
挿入：10
結果：<<5,10,15>,20,<-,30,35>>
深さ：0

case2
データ：<<5,10,15>,20,<-,30,35>>		
挿入：0	
結果：<<<0,5,->,10,15>,20,<-,30,35>>
深さ：3

case3
データ：-
挿入：32
結果：32
深さ：0

関数の説明
入力した二分探索に挿入を行ったさいに、根を０として
挿入した節点への深さを測定し深さの値を返す関数。
挿入しなかったさいは０を返す。

引数１：根または葉へのポインタ
引数２：nodeを指すポインタへのポインタ
引数３：挿入したい値
引数４：初期の状態の深さ（最初は０）
戻り値１：挿入した節点の深さ
戻り値２：挿入が行われなかった際０
*/
int	insert_bt(struct	node	*nodep,struct	node	**ptr,int	key,int	depth)
{

	if(nodep==0)					//ポインタが\0をさすとき
	{
		*ptr=create_node(0,key,0);						//新しく節点を作る（挿入したい値を挿入）
		return	depth;
	}
	
	else	if(key==nodep->value)		return	0;							//挿入したい値が既に存在するとき

	
	else	if(key<nodep->value)
	{
		ptr=&(nodep->left);
		depth++;																																							//再帰するのでdepthの値を増やす
		depth=insert_bt(nodep->left,ptr,key,depth);
	}

	else
	{
		ptr=&(nodep->right);
		depth++;																																												//再帰するのでdepthの値を増やす
		depth=insert_bt(nodep->right,ptr,key,depth);
	}
	return	depth;
}




