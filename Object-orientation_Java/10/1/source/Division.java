import	java.io.*;

class Division{
	public static void main(String[] args){

		String	linex="";	//x�̕�����
		String	liney="";	//y�̕�����
		int	x,y,answer;

		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

		while(true){

			try{
				linex=reader.readLine();	//����W������
				liney=reader.readLine();	//����W������

				x=Integer.parseInt(linex);	//���l�ɕϊ�
				y=Integer.parseInt(liney);	//���l�ɕϊ�
				answer=x/y;

				System.out.println(x+"��"+y+"�Ŋ���������"+answer+"�ł�");
			}

			catch(NumberFormatException	e){	//�����ϊ��ŗ�O
				if((linex.equals("END"))||(liney.equals("END"))){
					break;
				}else{
					System.out.println("���͂����l�ł͂���܂���");
				}
			}

			catch(ArithmeticException	e){	//�Z�p�v�Z�ŗ�O
				System.out.println("�v�Z���s�\�ł�");
			}

			catch(Exception	e){
				System.out.println("�����s���̃G���[�ł�");
			}
		}
	}
}
		