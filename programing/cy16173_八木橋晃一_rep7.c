#include<stdio.h>
/*
CY16173	八木橋晃一	作成日：作成日：2017年6月1日	課題4-3
テスト( print_listではアドレスも出力するprintfを使用)
case1
値：cell1=create_cell(2,0)
		cell2=create_cell(5,cell1)
		cell3=create_cell(1,cell2)
		cell4=create_cell(6,0)
		cell5=create_cell(7,cell4)
		cell6=create_cell(8,cell5)
プリント:print_list(cell3),	print_list(p)
結果:=>8(4250632)=>7(4250624)=>6(4250616)
		=>8(4250640)=>7(4250648)=>6(4250656)=>1(4250608)=>5(4250600)=>2(4250592)


case2
値：cell1=create_cell(2,0),cell4=create_cell(6,0);
プリント:print_list(cell3),	print_list(p)
結果:


case3
値：cell1=create_cell(2,0);																									
	cell2=create_cell(0,cell1);
	cell3=create_cell(0,cell2);
	cell4=create_cell(6,0);
	cell5=create_cell(0,cell4);
	cell6=create_cell(0,cell5);
	
プリント:print_list(cell3),	print_list(p)
結果:0(4250640)=>0(4250648)=>6(4250656)=>0(4250608)=>0(4250600)=>2(4250592)


case4			p=concat(copy(cell3),cell3);		
値：cell1=create_cell(2,0);																												
	cell2=create_cell(3,cell1);
	cell3=create_cell(4,cell2);
プリント:print_list(cell3),	print_list(p)
結果:=>2(4250592)
=>4(4250640)=>3(4250648)=>2(4250656)=>4(4250608)=>3(4250600)=>2(4250592)

関数の説明
セルのなかの構造に値とアドレスを代入し、リストを2つ作る。その後リストを繋げるが、前方に当たる部分のリストはコピーしたものである。
上記の流れを行う関数。
*/

struct	cell				//構造の宣言
{
	int	data;
	struct	cell	*next;
};


struct	cell	cell_pool[1000];														//グローバル変数
struct	cell	*new_cell=cell_pool;				
		

void print_list(struct	cell	*list);																																			//プロトタイプ宣言:リストを引数として受け取り、各セルのdataメンバを出力する関数
struct	cell	*create_cell(int	data,struct	cell	*next);					//プロトタイプ宣言:代入したいデータの値とつなげたいアドレスを引数とし、新しく作ったセルの１つまえのアドレスを返す関数
struct	cell	*tail_list(struct	cell	*tail);																						//プロタイプ宣言:リストの先頭のセルのアドレスを引数とし、リストの終わりのセルへのポインタのアドレスを返す関数
struct	cell	*concat(struct	cell	*cell6,struct	cell	*cell3);						//プロタイプ宣言:繋げたいリストの先頭のセルのそれぞれのアドレスを引数とし、できあがったリストの先頭のセルのアドレスを返す関数
struct	cell	*copy(struct	cell	*list2);																												//プロタイプ宣言:コピーしたいリストのセルの先頭のアドレスを引数とし、コピーしたリストのセルの先頭のアドレスを返り値とする関数


int	main	(void)
{
	struct	cell	*cell1,*cell2,*cell3,*p	,*cell4,*cell5,*cell6;															//cell1?6はcreate_cellの引数のアドレス、pは2つのリストを結合したあとのリストの先頭のセルのアドレス

	cell1=create_cell(2,0);																													//新しく作るセルへの値とアドレスを代入
	cell2=create_cell(3,cell1);
	cell3=create_cell(4,cell2);

																																											//print_list(cell1);					print_listとmainのテストに使用

	cell4=create_cell(6,0);
	cell5=create_cell(5,cell4);
	cell6=create_cell(4,cell5);
	

	p=concat(copy(cell6),cell3);																			//結合したリストの先頭のセルのアドレスをpに代入
	print_list(p);

	return	0;
}



/*
テスト( print_listではアドレスも出力するprintfを使用)
case1
値：cell1=create_cell(2,0),cell2=create_cell(5,cell1);
		cell3=create_cell(1,cell2);
プリント:cell3を引数としprint_list(p);	
結果:=>2(4250592)
			
関数の説明
リストの終わりのセルを引数で受け取ったリストの先頭のセルのアドレスから順に探し、リストのセル最後のセルを見つけそのアドレスを返す関数

引数：最後のセルのアドレスを調べたいリストの先頭のアドレス
戻り値：調べたいリストの最後のセルのアドレス
*/
struct	cell	*tail_list(struct	cell	*tail)
{
	struct	cell	*p;
	p=tail;
	while(1)
	{
																																					//		if(p->next==0)		print_list(p);					tail_list
		if(p->next==0)		return	p;												//リストの最後のセルのnextはナル数なのでそれをもって判断
		p=p->next;																															//次のセルのアドレスを指す（そのセルのnextが次のセルを指している）
	}
}




/*
テスト( print_listではアドレスも出力するprintfを使用)
case1
値：cell1=create_cell(2,0),cell2=create_cell(5,cell1);
		cell3=create_cell(1,cell2);
プリント:print_list(cell3);	
結果:=>1(4250608)=>5(4250600)=>2(4250592)


関数の説明
引数で受け取ったリスト（リストの先頭のセルのアドレス）をたどって各セルのdataメンバを表示する関数

引数：各セルのdataメンバを表示したリストの先頭のセルのアドレス
戻り値：なし
*/
void print_list(struct	cell	*list)
{
	struct	cell	*p;
	p=list;
	while(p!=0)
	{
		printf("=>%d",p->data);

		//	printf("=>%d(%d)",p->data,p);				テストのためのアドレスも表示するprintf

		p=p->next;																			//次のセルのアドレスを指す
	}
	printf("\n");

	return;
}




/*
テスト( print_listではアドレスも出力するprintfを使用)
case1
値：cell1=create_cell(2,0),cell2=create_cell(5,cell1);
		cell3=create_cell(1,cell2);
プリント:上の値をそれぞれ引数としprint_list(new_cell);	
結果:=>2(4250592)
		=>5(4250600)=>2(4250592)
		=>1(4250608)=>5(4250600)=>2(4250592)

関数の説明
引数で受け取った値とアドレスを新しく作った構造体のセルに代入する

引数１：新しく作る構造体のセルに代入したい値
引数２：新しく作る構造体のセルに代入したいアドレス
戻り値：新しく作ったセルのアドレス
*/
struct	cell	*create_cell(int	data,struct	cell	*next)
{
	struct	cell	*old_cell;
	new_cell->data =data;									//	引数で受け取った値を新しく作った構造体のセルに代入する
	new_cell->next=next;											//引数で受け取ったアドレスを新しく作った構造体のセルに代入する
																			//print_list(new_cell);				create_cellのテストに使用

	old_cell=new_cell;											//現在のnew_cellの値をとっておく
	new_cell++;
	return	old_cell;
}



/*
テスト( print_listではアドレスも出力するprintfを使用)
case1
値：cell1=create_cell(2,0)
		cell2=create_cell(5,cell1);
		cell3=create_cell(1,cell2)
		cell4=create_cell(6,0);
		cell5=create_cell(7,cell4)
		cell6=create_cell(8,cell5);
プリント:cell6を第一引数、cell3を第二引数としprint_list(p1),print_list(p2),print_list(p1);	
結果:
=>8(4250632)=>7(4250624)=>6(4250616)
=>1(4250608)=>5(4250600)=>2(4250592)
=>8(4250632)=>7(4250624)=>6(4250616)=>1(4250608)=>5(4250600)=>2(4250592)

関数の説明
繋げたいリストの前方にしたい方の先頭のセルのアドレスを第一引数とし、
後方にしたい方の先頭のセルのアドレスを第二引数としてリストを繋げ１つのリストにして、
できあがったリストの先頭のセルのアドレスを返す関数

引数１：繋げたいリストの前方にしたい方の先頭のセルのアドレス
引数２：繋げたいリストの後方にしたい方の先頭のセルのアドレス
戻り値：リストを繋げることでできた新しいリストの先頭のセルのアドレス
*/
struct	cell	*concat(struct	cell	*cell6,struct	cell	*cell3)
{
	struct	cell	*tail,*p1,*p2;

	p1=cell6;
	p2=cell3;
														//	print_list(p1);関数concatのテストに使用
															//print_list(p2);関数concatのテストに使用

	tail=tail_list(p1);											//リストの最後のセルのアドレスを求める
	tail->next=p2;															//リストを繋げる

															//	print_list(p1);	関数concatのテストに使用

	return	p1;
}



/*
テスト( print_listではアドレスも出力するprintfを使用)
case1
値：cell4=create_cell(6,0);
		cell5=create_cell(7,cell4)
		cell6=create_cell(8,cell5);
プリント:cell6を引数とし、print_list(p),print_list(head)
結果:=>8(4250632)=>7(4250624)=>6(4250616)
		=>8(4250640)=>7(4250648)=>6(4250656)




関数の説明
リストの先頭のセルのアドレスを引数としそのリストをコピーし、コピーしてできたリストの
先頭のセルのアドレスを返す関数

引数：コピーしたいリストの先頭のセルのアドレス
戻り値：コピーしてできたリストの先頭のセルのアドレス
*/
struct	cell	*copy(struct	cell	*list2)									
{
	struct	cell	*new,*p,*head,*back;								
	int	i;

/*
new:新しく作ったセルのアドレスを代入するための変数
p：コピーしたいリストの先頭のセルのアドレスを代入するための変数
head:コピーしてできたリストの先頭のセルのアドレスを保存するための変数
back:新しく作ったセルのアドレスを一時的に保存するための変数
i:whileの中で最初の一回と他を区別するためのカウンター変数
*/

	i=0;
	p=list2;

																																								//print_list(p);//関数copyのテストに使用
	
	while(1)	
	{
		new=create_cell(p->data,0);																//まだ次のセルができていないため、次のセルのアドレスをさせないので、一時的処置としてナル数を代入
	
	
		if(i==0)
			head=new;																														//コピーしてできたリストの先頭のセルのアドレスを保存
		if(i!=0)
			back->next=new;																												//２回目以降のループでは次のセルができているので次のセルのアドレスを指す
	
		if(p->next==0)			break;

		
		back=new;																														//新しく作ったセルのアドレスを一時的に保存
		i++;
		p=p->next;																														//コピー元の次のセルを指す
	}

																																					//print_list(head);関数copyのテストに使用

	return	head;
}







