package	calender;
class CalenderCheck{


//受け取った年が閏年ならtrueを返す
	static	boolean	isLeapYear(int	year){
		if(year%100==0){	//100の倍数のとき

			if(year%400==0)	return	true;	//400の倍数なら閏年
			else	return	false;
		}

		//4の倍数なら閏年
		else	if(year%4==0)	return	true;

		//その他
		else	return	false;
	}

/*
第一引数：閏年かどうか
第二引数；月
戻り値：その月の日数
*/
	static	int	daysOfMonth(boolean	isLeap,String	month){

		switch(month){

		case	"January":	return 31;
		
		case	"Febrary":
			if(isLeap)	return	29;
			else	return	28;
		
		case	"March":	return	31;
		case	"April":	return	30;
		case	"May":		return	31;
		case	"June":		return	30;
		case	"July":		return	31;
		case	"August":	return	31;
		case	"September":	return	30;
		case	"October":	return	31;
		case	"November":	return	30;
		case	"Deccember":	return	31;
		default:
			System.out.println("入力が不正です");
			return	-1;
		}
	}
}