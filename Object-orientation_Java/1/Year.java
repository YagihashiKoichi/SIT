/*
‰[”N‚©‚Ç‚¤‚©‚ğ”»’è‚·‚éŠÖ”
*/

class	Year
{
	public	static	void	main(String[]	args)
	{
		int	year=1996;

		if(((year%100)==0)&&((year%400)==0))	//100‚Æ400‚ÌŒö”{”
			System.out.println(year+"”N‚Í‰[”N‚Å‚·");

		//100‚Ì”{”‚©‚Â4‚Ì”{”
		else	if(((year%100)!=0)&&((year%4)==0)
			System.out.println(year+"”N‚Í‰[”N‚Å‚·");

		//‚»‚Ì‘¼
		else	System.out.println(year+"”N‚Í‰[”N‚Å‚Í‚ ‚è‚Ü‚¹‚ñ");
	}
}
