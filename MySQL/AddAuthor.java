/**
 * ��҂̃f�[�^���f�[�^�x�[�X(animedb)�ɒǉ�����N���X
 * @author Koichi.Yagihashi
 * @version 1.0
 */
import java.sql.ResultSet;
import java.sql.SQLException;

public class AddAuthor extends AbstractAdder{
	
	/**
	 * �����̎�L�[�i���ID�j�̍ő�l������������������쐬����
	 * @return �����̎�L�[�i���ID�j�̍ő�l���������������
	 */
	public String makeKeyQuery(){
		String sql = "SELECT max(���ID) as maxid FROM �����";
		return sql;
    }

	/**
	 * �ǉ������Җ��Ɠ�����Җ�������������������쐬����
	 * @param value1 �ǉ������Җ�������String
	 * @return �ǉ������Җ��Ɠ�����Җ����������������
	 */
	public String makeQuery(String value1) {
		String sql = "SELECT *  FROM ����� WHERE ��Җ�='" + value1 + "'";
		return sql;
	}

	public String makeQuery(String value1, String value2) {
		return null;
	}

	public String makeQuery(String value1, String value2, String value3) {
		return null;
	}

	/**
	 * �f�[�^��ǉ����邽�߂̏��������쐬����
	 * @param result �����̎�L�[�i���ID�j�̍ő�l�̌������ʂ�����ResultSet 
	 * @param value1 �ǉ������Җ�������String
	 * @return ��Җ���ǉ����������
	 */
	public String addMakeQuery(ResultSet result,String value1){
		String sql = null;
		try {
			result.next();
			int maxid = result.getInt("maxid");
			
		    sql = "insert into ����� value(" + (maxid+1) + ",'" + value1 + "')";
		    
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
		
		return sql;
    }

	public String addMakeQuery(ResultSet result, String value1, String value2) {
		return null;
	}

	public String addMakeQuery(ResultSet result, String value1, String value2,	String value3) {
		return null;
	}

	/**
	 * �ǉ������Җ��Əd��������̂�\��
	 * @param result �ǉ������Җ��Əd�������Җ��̌������ʂ�����ResultSet 
	 */
	public void showItem(ResultSet result) {
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("�ԍ�\t���ID\t��Җ�");
			
			while(result.next()){
				int id=result.getInt("���ID");
				String author=result.getString("��Җ�");
				System.out.println(count + ":" + id + ":" + author);
				count++;
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}			
	}
}