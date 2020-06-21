/*
与えられた座標に対して与えられた数だけ座標を
移動させる関数
*/

#include<stdio.h>

struct	point	move(struct	point	original,int	x1,int	y1);

struct	point{		//座標を表す構造体
	int	x0;
	int	y0;
}; 

int	main(void)
{
	struct	point	original;

	int	x1,y1;

	printf("もとのｘ座標を入力してください。\n");
	scanf("%d",&original.x0);
	printf("もとのｙ座標を入力してください。\n");
	scanf("%d",&original.y0);
	printf("いくつｘ座標を動かすか入力してください。\n");
	scanf("%d",&x1);
	printf("いくつｙ座標を動かすか入力してください。\n");
	scanf("%d",&y1);

	original=move(original,x1,y1);

	printf("結果：(%d,%d)",original.x0,original.y0);

	return	0;
}

/*
第一引数のぶんだけｘ座標、第二引数のぶんだけｙ標を
移動させる関数
第一引数：ｘ座標にたいして移動させたい数
第二引数：ｙ座標にたいして移動させたい数
*/
struct	point	move(struct	point	original,int	x1,int	y1)
{
	original.x0=original.x0+x1;
	original.y0=original.y0+y1;
	return	original;
}

