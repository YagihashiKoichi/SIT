import java.io.*;

public	class Search{

	public void searchString(String fileName,String searchString){

		try{

			//�t�@�C����ǂݍ���
			FileReader fr=new FileReader(fileName);
			BufferedReader br=new BufferedReader(fr);

			//�����ɂ����s����ʏo��
			System.out.println(searchString+"�̏o����");
			String line;
			int	counter=0;
			while((line=br.readLine())!=null){
				if(line.indexOf(searchString)!=-1)
					System.out.println(counter+":"+line);

				counter++;
			}

			br.close();
			fr.close();
		}

		catch(Exception e){
			System.out.println("�����s���̃G���[");
		}
	}
}
