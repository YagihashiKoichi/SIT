public class Student {
		private	int	number;	/**�w���ԍ�*/
		private	String	name;	/**����*/
		private	static	int	counter; /**�������ꂽ�I�u�W�F�N�g��*/

		/**
	        * "�w���ԍ� ����"�̕������Ԃ����\�b�h
	        * @author ���؋��W��
	        * @return "�w���ԍ� ����"�̕�����
		*/
		public	String	toString(){
			return	"�ԍ�:"+number+"�@����:"+name;
		}

		/**�������ꂽ�I�u�W�F�N�g����Ԃ�
                * "�w���ԍ� ����"�̕������Ԃ����\�b�h
	        * @author ���؋��W��
	        * @return �������ꂽ�I�u�W�F�N�g����\������
                */
		public	static	int	getCounter(){
			return	counter;
		}

		/**�^����ꂽ�������w���ԍ��A������������Ƃ���R���X�g���N�^
	        * @author ���؋��W��
	        * @param number	�w���ԍ���\������
		* @param name	������\��������
�@�@�@�@�@�@�@�@*/
		public	Student(int number,String name){
			this.number=number;
			this.name=name;
		}
	
}