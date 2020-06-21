package	evaluation;
import	java.util.*;
public	class StudentList{

	ArrayList<Student>	stu_list=new	ArrayList<Student>();

	public	void	AddStudent(Student	student){
		stu_list.add(student);
	}

	public	void	LookList(){	//学番、名前、評価を出力
		for(int	i=0;i<stu_list.size();i++){
			Student	student=stu_list.get(i);
			System.out.println("学生番号："+student.GetNumber()+"  名前："+student.GetName()+"  評価："+student.GetEvaluation());
		}
	}
}
