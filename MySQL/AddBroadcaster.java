/**
 * �����ǂ̃f�[�^���f�[�^�x�[�X(animedb)�ɒǉ�����N���X
 * @author Koichi.Yagihashi
 * @version 1.0
 */
import java.sql.ResultSet;
import java.sql.SQLException;

public class AddBroadcaster extends AbstractAdder{
	
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

	/**
	 * �ǉ�����ǖ��A�Z���Ɠ����ǖ��A�Z��������������������쐬����
	 * @param value1 �ǉ���������ǂ̋ǖ�������String
	 * @param value2 �ǉ���������ǂ̏Z��������String 
	 * @return �ǉ�����ǖ��A�Z���Ɠ����ǖ��A�Z�����������������
	 */
	public String makeQuery(String value1, String value2) {
		String sql = "SELECT *  FROM ������ WHERE �ǖ�='" + value1 + "' AND �Z��='" + value2 + "'";
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
	 * @param result �����̎�L�[�i������ID�j�̍ő�l�̌������ʂ�����ResultSet 
	 * @param value1 �ǉ���������ǂ̋ǖ�������String
	 * @param value2 �ǉ���������ǂ̏Z��������String 
	 * @return �����ǂ�ǉ����������
	 */
	public String addMakeQuery(ResultSet result,String value1,String value2){
		String sql = null;
		try {
			result.next();
			int maxid = result.getInt("maxid");
			
		    sql = "insert into ������ value(" + (maxid+1) + ",'" + value1 + "','" + value2 + "')";
		    
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return sql;
    }

	public String addMakeQuery(ResultSet result, String value1, String value2,String value3) {
		return null;
	}

	/**
	 * �ǉ���������ǂ̋ǖ��A�Z���Əd��������̂�\��
	 * @param result �ǉ���������ǂ̋ǖ��A�Z���Əd������f�[�^�̌������ʂ�����ResultSet 
	 */
	public void showItem(ResultSet result) {
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("�ԍ�\t�ǖ�\t�Z��");
			
			while(result.next()){
				String broadcaster = result.getString("�ǖ�");
				String address = result.getString("�Z��");
				System.out.println(count + ":" + broadcaster + ":" + address);
				count++;
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}			
	}
}

