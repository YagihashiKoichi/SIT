/**
 * �����Ђ̃f�[�^���f�[�^�x�[�X(animedb)�ɒǉ�����N���X
 * @author Koichi.Yagihashi
 * @version 1.0
 */
import java.sql.ResultSet;
import java.sql.SQLException;

public class AddCompany extends AbstractAdder{
	
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
	 * �ǉ����鐧���Ђ̐����Ж��A�d�b�ԍ��A�{�ЏZ���Ɠ����f�[�^������������������쐬����
	 * @param value1 �ǉ����鐧���Ђ̉�Ж�������String
	 * @param value2 �ǉ����鐧���Ђ̓d�b�ԍ�������String
	 * @param value3 �ǉ����鐧���Ђ̖{�ЏZ��������String  
	 * @return �ǉ������Ж��A�d�b�ԍ��A�{�ЏZ���Ɠ����f�[�^���������������
	 */
	public String makeQuery(String value1, String value2, String value3) {
		String sql = "SELECT *  FROM ������ WHERE ��Ж�='" + value1 + "' AND �d�b�ԍ�='" + value2 + "' AND �{�ЏZ��='" + value3 + "'";
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
	 * @param value1 �ǉ����鐧���Ђ̉�Ж�������String
	 * @param value2 �ǉ����鐧���Ђ̓d�b�ԍ�������String 
	 * @param value3 �ǉ����鐧���Ђ̖{�ЏZ��������String  
	 * @return �����Ђ�ǉ����������
	 */
	public String addMakeQuery(ResultSet result, String value1, String value2,
			String value3){
		String sql = null;
		try {
			result.next();
			int maxid = result.getInt("maxid");
			
		    sql = "insert into ������ value(" + (maxid+1) + ",'" + value1 + ",'" + value2  + ",'" + value3 + "')";
		    
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
		
		return sql;
    }

	/**
	 * �ǉ����鐧���Ђ̉�Ж��A�d�b�ԍ��A�{�ЏZ���Əd��������̂�\��
	 * @param result �ǉ����鐧���Ђ̉�Ж��A�d�b�ԍ��A�{�ЏZ���Əd������f�[�^�̌������ʂ�����ResultSet 
	 */
	public void showItem(ResultSet result) {
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("�ԍ�\t��Ж�\t�d�b�ԍ�\t�{�ЏZ��");
			
			while(result.next()){
				String company = result.getString("��Ж�");
				String number = result.getString("�d�b�ԍ�");
				String address = result.getString("�{�ЏZ��");
				System.out.println(count + ":" + company + ":" + number + ":" + address);
				count++;
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}			
	}
}

