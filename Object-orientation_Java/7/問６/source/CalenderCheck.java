package	calender;
class CalenderCheck{


//�󂯎�����N���[�N�Ȃ�true��Ԃ�
	static	boolean	isLeapYear(int	year){
		if(year%100==0){	//100�̔{���̂Ƃ�

			if(year%400==0)	return	true;	//400�̔{���Ȃ�[�N
			else	return	false;
		}

		//4�̔{���Ȃ�[�N
		else	if(year%4==0)	return	true;

		//���̑�
		else	return	false;
	}

/*
�������F�[�N���ǂ���
�������G��
�߂�l�F���̌��̓���
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
			System.out.println("���͂��s���ł�");
			return	-1;
		}
	}
}