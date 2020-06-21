/**
 * �z�M�T�[�r�X�̃f�[�^���f�[�^�x�[�X(animedb)�ɒǉ�����N���X
 * @author Koichi.Yagihashi
 * @version 1.0
 */
import java.sql.ResultSet;
import java.sql.SQLException;

public class AddService extends AbstractAdder{
	
	/**
	 * �����̎�L�[�i�T�[�r�XID�j�̍ő�l������������������쐬����
	 * @return �����̎�L�[�i�T�[�r�XID�j�̍ő�l���������������
	 */
	public String makeKeyQuery(){
		String sql = "SELECT max(�z�M�T�[�r�XID) as maxid FROM �z�M�T�[�r�X";
		return sql;
    }
	
	public String makeQuery(String value1) {
		return null;
	}

	/**
	 * �ǉ�����z�M�T�[�r�X�̃T�[�r�X���AURL�Ɠ����f�[�^������������������쐬����
	 * @param value1 �ǉ�����z�M�T�[�r�X�̃T�[�r�X��������String
	 * @param value2 �ǉ�����z�M�T�[�r�X��URL������String 
	 * @return �ǉ�����z�M�T�[�r�X�̃T�[�r�X���AURL�������f�[�^���������������
	 */
	public String makeQuery(String value1, String value2) {
		String sql = "SELECT *  FROM �z�M�T�[�r�X WHERE �T�[�r�X��='" + value1 + "' AND URL='" + value2 + "'";
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
	 * @param result �����̎�L�[�i�z�M�T�[�r�XID�j�̍ő�l�̌������ʂ�����ResultSet 
	 * @param value1 �ǉ�����z�M�T�[�r�X�̃T�[�r�X��������String
	 * @param value2 �ǉ�����z�M�T�[�r�X��URL������String 
	 * @return �z�M�T�[�r�X��ǉ����������
	 */
	public String addMakeQuery(ResultSet result, String value1, String value2) {
		String sql = null;
		try {
			result.next();
			int maxid = result.getInt("maxid");
			
		    sql = "insert into �z�M�T�[�r�X value(" + (maxid+1) + ",'" + value1 + "','" + value2 + "')";
		    
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
	 * �ǉ�����z�M�T�[�r�X�̃T�[�r�X���AURL�Əd��������̂�\��
	 * @param result �ǉ�����z�M�T�[�r�X�̃T�[�r�X���AURL�Əd������f�[�^�̌������ʂ�����ResultSet 
	 */
	public void showItem(ResultSet result) {
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("�ԍ�\t�T�[�r�X��\tURL");
			
			while(result.next()){
				String service = result.getString("�T�[�r�X��");
				String url = result.getString("URL");
				System.out.println(count + ":" + service + ":" + url);
				count++;
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}

