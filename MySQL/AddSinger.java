/**
 * �̎�̃f�[�^���f�[�^�x�[�X(animedb)�ɒǉ�����N���X
 * @author Koichi.Yagihashi
 * @version 1.0
 */
import java.sql.ResultSet;
import java.sql.SQLException;

public class AddSinger extends AbstractAdder{
	
	/**
	 * �����̎�L�[�i�̎�ID�j�̍ő�l������������������쐬����
	 * @return �����̎�L�[�i�̎�ID�j�̍ő�l���������������
	 */
	public String makeKeyQuery(){
		String sql = "SELECT max(�̎�ID) as maxid FROM �̎�";
		return sql;
    }
	
	/**
	 * �ǉ�����̎�Ɠ����̎薼������������������쐬����
	 * @param value1 �ǉ�����̎�̉̎薼������String
	 * @return �ǉ�����̎�̉̎薼�Ɠ����f�[�^���������������
	 */
	public String makeQuery(String value1) {
		String sql = "SELECT *  FROM �̎� WHERE �̎薼='" + value1 + "'";
		return sql;
	}

	public String makeQuery(String value1, String value2) {
		return null;
	}

	public String makeQuery(String value1, String value2, String value3) {
		return null;
	}

	/**
	 * �̎��ǉ����邽�߂̏��������쐬����
	 * @param result �����̎�L�[�i�̎�ID�j�̍ő�l�̌������ʂ�����ResultSet 
	 * @param value1 �ǉ�����̎�̉̎薼������String
	 * @return �̎��ǉ����邽�߂̏�����
	 */
	public String addMakeQuery(ResultSet result, String value1) {
		String sql = null;
		try {
			result.next();
			int maxid = result.getInt("maxid");
			
		    sql = "insert into �̎� value(" + (maxid+1) + ",'" + value1 + "')";
		    
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
		
		return sql;
	}

	public String addMakeQuery(ResultSet result, String value1, String value2) {
		return null;
	}

	public String addMakeQuery(ResultSet result, String value1, String value2,
			String value3) {
		return null;
	}

	/**
	 * �ǉ�����̎�̉̎薼�Əd��������̂�\��
	 * @param result �ǉ�����̎�̉̎薼�Əd������f�[�^�̌������ʂ�����ResultSet 
	 */
	public void showItem(ResultSet result) {
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("�ԍ�\t�̎�ID\t�̎薼");
			
			while(result.next()){
				int id=result.getInt("�̎�ID");
				String singer=result.getString("�̎薼");
				System.out.println(count + ":" + id + ":" + singer);
				count++;
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}			
	}
}