//GiveNumber.java
//�t�@�C�����琮����ǂݍ���ŁA���k�Ɋw�Ԃ�^����v���O����

import	java.io.*;

public class GiveNumber {
	public static void main(String[] args) {

		try{
			FileReader in = new FileReader("number.txt");
			//�t�@�C���𐶐�
			BufferedReader reader = new BufferedReader(in);
			String	line;

			while((line=reader.readLine())!=null){
				Student	s=new	Student(Integer.parseInt(line),"No_name");
				System.out.println(s.toString());
			}

		reader.close();	//�t�@�C�������

		}catch(FileNotFoundException	e){
			System.out.println("�t�@�C����������܂���");
		}catch(IOException	e){
			System.out.println("���̑��̃G���[");
		}
	}
}