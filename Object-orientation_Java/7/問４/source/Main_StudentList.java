package	teacher;	//ƒhƒƒCƒ“–¼‚ğg‚¤‚ÌH
import	evaluation.*;	//ƒhƒƒCƒ“–¼‚ğg‚¤‚ÌH

public class Main_StudentList{
	public	static	void	main(String[] args){

		Graduate g1=new Graduate("M1","ˆº’ÒŒ");
		Graduate g2=new Graduate("M6","÷ˆä—œ•äq");
		Graduate g3=new Graduate("M13","’I’¬ŒO");
		Graduate g4=new Graduate("M21","’†‘½Ñ]");
		Graduate g5=new Graduate("M22","µçˆ§");
		Graduate g6=new Graduate("M29","X“‡¥ƒ‰ƒuƒŠ[¥‚Í‚é‚©");
		Graduate g7=new Graduate("M12","‹kƒˆê");

		Undergraduate u1=new Undergraduate("2","ˆÉ“¡•c");
		Undergraduate u2=new Undergraduate("4","”~Œ´³‹g");
		Undergraduate u3=new Undergraduate("6","ãè—¡¹");
		Undergraduate u4=new Undergraduate("16","‚‹´–ƒ–ë");
		Undergraduate u5=new Undergraduate("18","‹k”ü–ç");
		Undergraduate u6=new Undergraduate("19","“c’†Œbq");
		Undergraduate u7=new Undergraduate("23","’ËŒ´‹¿");

		StudentList s=new StudentList();

		g1.AddResult(90);
		g1.AddResult(90);
		g1.AddResult(95);
		g1.AddResult(100);
		g1.AddResult(100);
		g1.Change_Res_result(95);
		s.AddStudent(g1);

		g2.AddResult(60);
		g2.AddResult(60);
		g2.AddResult(70);
		g2.AddResult(70);
		g2.AddResult(75);
		g2.Change_Res_result(75);
		s.AddStudent(g2);

		g3.AddResult(50);
		g3.AddResult(50);
		g3.AddResult(60);
		g3.AddResult(60);
		g3.AddResult(65);
		g3.Change_Res_result(65);
		s.AddStudent(g3);

		g4.AddResult(70);
		g4.AddResult(70);
		g4.AddResult(80);
		g4.AddResult(80);
		g4.AddResult(85);
		g4.Change_Res_result(85);
		s.AddStudent(g4);

		g5.AddResult(86);
		g5.AddResult(86);
		g5.AddResult(90);
		g5.AddResult(90);
		g5.AddResult(88);
		g5.Change_Res_result(88);
		s.AddStudent(g5);

		g6.AddResult(80);
		g6.AddResult(84);
		g6.AddResult(80);
		g6.AddResult(84);
		g6.AddResult(82);
		g6.Change_Res_result(82);
		s.AddStudent(g6);

		g7.AddResult(60);
		g7.AddResult(60);
		g7.AddResult(60);
		g7.AddResult(60);
		g7.AddResult(60);
		g7.Change_Res_result(60);
		s.AddStudent(g7);

		u1.AddResult(70);
		u1.AddResult(70);
		u1.AddResult(70);
		u1.AddResult(70);
		u1.AddResult(70);
		s.AddStudent(u1);


		u2.AddResult(30);
		u2.AddResult(30);
		u2.AddResult(40);
		u2.AddResult(40);
		u2.AddResult(35);
		s.AddStudent(u2);

		u3.AddResult(60);
		u3.AddResult(60);
		u3.AddResult(60);
		u3.AddResult(60);
		u3.AddResult(60);
		s.AddStudent(u3);

		u4.AddResult(80);
		u4.AddResult(80);
		u4.AddResult(90);
		u4.AddResult(90);
		u4.AddResult(85);
		s.AddStudent(u4);

		u5.AddResult(50);
		u5.AddResult(50);
		u5.AddResult(60);
		u5.AddResult(60);
		u5.AddResult(55);
		s.AddStudent(u5);

		u6.AddResult(70);
		u6.AddResult(70);
		u6.AddResult(70);
		u6.AddResult(70);
		u6.AddResult(70);
		s.AddStudent(u6);

		u7.AddResult(100);
		u7.AddResult(100);
		u7.AddResult(100);
		u7.AddResult(100);
		u7.AddResult(100);
		s.AddStudent(u7);

		s.LookList();
	}
}



