/**
 * ���D�̃f�[�^���f�[�^�x�[�X(animedb)�ɒǉ�����N���X
 * @author Koichi.Yagihashi
 * @version 1.0
 */
import java.sql.ResultSet;
import java.sql.SQLException;

public class AddRadioActor extends AbstractAdder{
	
	/**
	 * �����̎�L�[�i���DID�j�̍ő�l������������������쐬����
	 * @return �����̎�L�[�i���DID�j�̍ő�l���������������
	 */
	public String makeKeyQuery(){
		String sql = "SELECT max(���DID) as maxid FROM ���D";
		return sql;
    }

	public String makeQuery(String value1) {
		return null;
	}

	/**
	 * �ǉ����鐺�D�̖��O�A���ʂƓ����f�[�^������������������쐬����
	 * @param value1 �ǉ����鐺�D�̖��O������String
	 * @param value2 �ǉ����鐺�D�̐��ʂ�����String 
	 * @return �ǉ����鐺�D�̖��O�A���ʂ������f�[�^���������������
	 */
	public String makeQuery(String value1, String value2) {
		String sql = "SELECT *  FROM ���D WHERE ���O='" + value1 + "' AND ����='" + value2 + "'";
		return sql;
	}

	public String makeQuery(String value1, String value2, String value3) {
		return null;
	}

	public String addMakeQuery(ResultSet result, String value1) {
		return null;
	}

	/**
	 * �f�[�^��ǉ����邽�߂̏��������쐬����
	 * @param result �����̎�L�[�i���DID�j�̍ő�l�̌������ʂ�����ResultSet 
	 * @param value1 �ǉ����鐺�D�̖��O������String
	 * @param value2 �ǉ����鐺�D�̐��ʂ�����String 
	 * @return ���D��ǉ����������
	 */
	public String addMakeQuery(ResultSet result, String value1, String value2) {
		String sql = null;
		try {
			result.next();
			int maxid = result.getInt("maxid");
			
		    sql = "insert into ���D value(" + (maxid+1) + ",'" + value1 + "','" + value2 + "',null)";
		    
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
		
		return sql;
	}

	public String addMakeQuery(ResultSet result, String value1, String value2,
			String value3) {
		return null;
	}

	/**
	 * �ǉ����鐺�D�̖��O�A���ʂƏd��������̂�\��
	 * @param result �ǉ����鐺�D�̖��O�A���ʂƏd������f�[�^�̌������ʂ�����ResultSet 
	 */
	public void showItem(ResultSet result) {
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("�ԍ�\t���O\t����");
			
			while(result.next()){
				String name = result.getString("���O");
				String sex = result.getString("����");
				System.out.println(count + ":" + name + ":" + sex);
				count++;
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}			
	}
}

