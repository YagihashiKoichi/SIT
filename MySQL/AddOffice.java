/**
 * �������̃f�[�^���f�[�^�x�[�X(animedb)�ɒǉ�����N���X
 * @author Koichi.Yagihashi
 * @version 1.0
 */
import java.sql.ResultSet;
import java.sql.SQLException;

public class AddOffice extends AbstractAdder{
	
	/**
	 * �����̎�L�[�i������ID�j�̍ő�l������������������쐬����
	 * @return �����̎�L�[�i������ID�j�̍ő�l���������������
	 */
	public String makeKeyQuery(){
		String sql = "SELECT max(������ID) as maxid FROM ������";
		return sql;
    }
	
	public String makeQuery(String value1) {
		return null;
	}

	public String makeQuery(String value1, String value2) {
		return null;
	}

	/**
	 * �ǉ����鎖�����̎��������A�d�b�ԍ��A�Z���Ɠ����f�[�^������������������쐬����
	 * @param value1 �ǉ����鎖�����̎�������������String
	 * @param value2 �ǉ����鎖�����̓d�b�ԍ�������String
	 * @param value3 �ǉ����鎖�����̏Z��������String  
	 * @return �ǉ����鎖�����̎��������A�d�b�ԍ��A�Z���Ɠ����f�[�^���������������
	 */
	public String makeQuery(String value1, String value2, String value3) {
		String sql = "SELECT *  FROM ������ WHERE ��������='" + value1 + "' AND �d�b�ԍ�='" + value2 + "' AND �Z��='" + value3 + "'";
		return sql;
	}

	public String addMakeQuery(ResultSet result, String value1) {
		return null;
	}

	public String addMakeQuery(ResultSet result, String value1, String value2) {
		return null;
	}

	/**
	 * �f�[�^��ǉ����邽�߂̏��������쐬����
	 * @param result �����̎�L�[�i������ID�j�̍ő�l�̌������ʂ�����ResultSet 
	 * @param value1 �ǉ����鎖�����̎�������������String
	 * @param value2 �ǉ����鎖�����̓d�b�ԍ�������String 
	 * @param value3 �ǉ����鎖�����̏Z��������String  
	 * @return �����Ђ�ǉ����������
	 */
	public String addMakeQuery(ResultSet result, String value1, String value2,
			String value3) {
		String sql = null;
		try {
			result.next();
			int maxid = result.getInt("maxid");
			
		    sql = "insert into ������ value(" + (maxid+1) + ",'" + value1 + "','" + value2 + "','" + value3 + "')";

		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
		
		return sql;
	}

	/**
	 * �ǉ����鎖�����̎��������A�d�b�ԍ��A�Z���Əd��������̂�\��
	 * @param result �ǉ����鎖�����̎��������A�d�b�ԍ��A�Z���Əd������f�[�^�̌������ʂ�����ResultSet 
	 */
	public void showItem(ResultSet result) {
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("�ԍ�\t��������\t�d�b�ԍ�\t�Z��");
			
			while(result.next()){
				String office = result.getString("��������");
				String number = result.getString("�d�b�ԍ�");
				String address = result.getString("�Z��");
				System.out.println(count + ":" + office + ":" + number + ":" + address);
				count++;
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}			
	}
}

