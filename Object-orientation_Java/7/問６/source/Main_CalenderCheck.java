package	calender;

/*
第１引数：年
第２引数；月
その年のその月の日数を表示する
*/
public	class	Main_CalenderCheck{
	public	static	void	main(String[]	args){

	   System.out.println(CalenderCheck.daysOfMonth(CalenderCheck.isLeapYear(Integer.parseInt(args[0])),args[1])+"日");
	}
}
	