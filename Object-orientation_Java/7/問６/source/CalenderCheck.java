package	calender;
class CalenderCheck{


//ó‚¯æ‚Á‚½”N‚ª‰[”N‚È‚çtrue‚ğ•Ô‚·
	static	boolean	isLeapYear(int	year){
		if(year%100==0){	//100‚Ì”{”‚Ì‚Æ‚«

			if(year%400==0)	return	true;	//400‚Ì”{”‚È‚ç‰[”N
			else	return	false;
		}

		//4‚Ì”{”‚È‚ç‰[”N
		else	if(year%4==0)	return	true;

		//‚»‚Ì‘¼
		else	return	false;
	}

/*
‘æˆêˆø”F‰[”N‚©‚Ç‚¤‚©
‘æ“ñˆø”GŒ
–ß‚è’lF‚»‚ÌŒ‚Ì“ú”
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
			System.out.println("“ü—Í‚ª•s³‚Å‚·");
			return	-1;
		}
	}
}