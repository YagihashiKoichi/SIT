package	evaluation;
import	java.util.*;
public	class StudentList{

	ArrayList<Student>	stu_list=new	ArrayList<Student>();

	public	void	AddStudent(Student	student){
		stu_list.add(student);
	}

	public	void	LookList(){	//�w�ԁA���O�A�]�����o��
		for(int	i=0;i<stu_list.size();i++){
			Student	student=stu_list.get(i);
			System.out.println("�w���ԍ��F"+student.GetNumber()+"  ���O�F"+student.GetName()+"  �]���F"+student.GetEvaluation());
		}
	}
}
