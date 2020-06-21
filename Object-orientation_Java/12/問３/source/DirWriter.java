import java.io.*;
import java.util.*;

/*
�������ł���t�@�C���ɑ������ł���J�����g�f�B���N�g��
���ɂ��閼�̂̃f�B���N�g���̒��ɂ���
�t�@�C���̈ꗗ�������o���N���X
*/
public class DirWriter{
	
	void Print(String dirname,String filename){

		File newfile = new File(filename);

		File dir = new File(dirname);				//�w�����ꂽ�f�B���N�g��
		File[] dirlist = dir.listFiles();			//�f�B���N�g�����̃t�@�C���ꗗ
		ArrayList<File> Directory = new ArrayList<File>();	//�f�B���N�g���ꗗ

		int dirlength;	//dirlength:�f�B���N�g���̐�
		int counter=0;
		int length=dirlist.length;	//�f�B���N�g�����̃t�@�C���̐�
		int i=0;	//�J�E���^�[�ϐ�
		int s=0;	//�J�E���^�[�ϐ�

		try{
			newfile.createNewFile();		 //�V�K�t�@�C�����쐬
			FileWriter out=new FileWriter(filename);
			BufferedWriter bw=new BufferedWriter(out);
			PrintWriter writer=new PrintWriter(bw);	//�������݂̐錾

			writer.println("Directory:"+dirname);
			while(true){	
				if(i!=0){				//�ŏ��͓���Ȃ�
					s=i-1;
					if(Directory.size()<i)	break;
					dirlist=Directory.get(s).listFiles();
					length=dirlist.length;
					writer.println("Directory:" + Directory.get(s).getName());
				}
				for(int t=0;t<length;t++){		//�f�B���N�g�����̃t�@�C�������ׂĊm�F
					if(dirlist[t].isDirectory()){   //�f�B���N�g���̂Ƃ��ǉ�
						Directory.add(dirlist[t]); 		
						writer.println("    " + dirlist[t].getName() + " �̓f�B���N�g���ł��B");
					          //�󔒃f�B���N�g���Ƌ�ʂ��₷�����邽��
				}

					else {	//�t�@�C��������������
						writer.println("    " + dirlist[t].getName());
					}
				}
				i++;
			}
			writer.close();   //�������ݏI��
		}

		catch (Exception e){      //�����s���̃G���[
			System.out.print(e);
		}
	}

}