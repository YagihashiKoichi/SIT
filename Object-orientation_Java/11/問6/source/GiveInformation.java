//GiveInformation.java
//���k�̊w�ԂƎ����������o���v���O����

import	java.io.*;

public class GiveInformation{
	public static void main(String[] args) {

		try{
			FileReader in = new FileReader("number.txt");
			//�t�@�C���𐶐�
			BufferedReader reader = new BufferedReader(in);

			FileWriter out = new FileWriter("student.txt");
			BufferedWriter bw = new BufferedWriter(out);
			PrintWriter writer = new PrintWriter(bw);

			String	line;

			while((line=reader.readLine())!=null){
				Student	s=new	Student(Integer.parseInt(line),"���؋��W��");
				writer.println(s.toString());
			}

		reader.close();		//�t�@�C�������
		writer.close();		//�t�@�C�������

		}catch(FileNotFoundException	e){
			System.out.println("�t�@�C����������܂���");
		}catch(IOException	e){
			System.out.println("���̑��̃G���[");
		}
	}
}