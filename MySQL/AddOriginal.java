/**
 * ����̃f�[�^���f�[�^�x�[�X(animedb)�ɒǉ�����N���X
 * @author Koichi.Yagihashi
 * @version 1.0
 */
import java.sql.ResultSet;
import java.sql.SQLException;

public class AddOriginal extends AbstractAdder{
	
	/**
	 * �����̎�L�[�i����ID�j�̍ő�l������������������쐬����
	 * @return �����̎�L�[�i����ID�j�̍ő�l���������������
	 */
	public String makeKeyQuery(){
		String sql = "SELECT max(����ID) as maxid FROM ����";
		return sql;
    }

	/**
	 * �ǉ����錴��Ɠ�������^�C�g��������������������쐬����
	 * @param value1 �ǉ����錴��̌���^�C�g��������String
	 * @return �ǉ����錴��̌���^�C�g���Ɠ����f�[�^���������������
	 */
	public String makeQuery(String value1) {
		String sql = "SELECT *  FROM ���� WHERE ����^�C�g��='" + value1 + "'";
		return sql;
	}

	public String makeQuery(String value1, String value2) {
		return null;
	}

	public String makeQuery(String value1, String value2, String value3) {
		return null;
	}

	/**
	 * �����ǉ����邽�߂̏��������쐬����
	 * @param result �����̎�L�[�i����ID�j�̍ő�l�̌������ʂ�����ResultSet 
	 * @param value1 �ǉ����錴��̌���^�C�g��������String
	 * @return �����ǉ����邽�߂̏�����
	 */
	public String addMakeQuery(ResultSet result, String value1) {
		String sql = null;
		try {
			result.next();
			int maxid = result.getInt("maxid");
			
		    sql = "insert into ���� value(" + (maxid+1) + ",null,'" + value1 + "')";
		    
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
	 * �ǉ����錴��̌���^�C�g���Əd��������̂�\��
	 * @param result �ǉ����錴��̌���^�C�g���Əd������f�[�^�̌������ʂ�����ResultSet 
	 */
	public void showItem(ResultSet result) {
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("�ԍ�\t����ID\t����^�C�g��");
			
			while(result.next()){
				int id=result.getInt("����ID");
				String title=result.getString("����^�C�g��");
				System.out.println(count + ":" + id + ":" + title);
				count++;
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}			
	}
}
