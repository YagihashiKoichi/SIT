abstract	class	Figure{

	double	bx,by;		//基点の座標
	int	own_counter;	//図形の番号

	void	get_point(double x,double y){	//基点の座標を得る
		bx=x;
		by=y;
	}


	void	move(double	x,double	y){	////図形の基点を移動
		bx=bx+x;
		by=by+y;
	}

	abstract	public	void	change(double	maguni);   //図形を拡大
	abstract	public	String	toString();	//結果の文字列を返す

//抽象化することで、引き継いだ先のクラスでオーバーライドを強制できる
}
	