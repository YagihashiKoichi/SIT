/**
 * �Ȃ̃f�[�^���f�[�^�x�[�X(animedb)�ɒǉ�����N���X
 * @author Koichi.Yagihashi
 * @version 1.0
 */
import java.sql.ResultSet;
import java.sql.SQLException;

public class AddMusic extends AbstractAdder{
	
	/**
	 * �����̎�L�[�iISRC�R�[�h�j�̍ő�l������������������쐬����
	 * @return �����̎�L�[�iISRC�R�[�h�j�̍ő�l���������������
	 */
	public String makeKeyQuery(){
		String sql = "SELECT max(ISRC�R�[�h) as maxid FROM ��";
		return sql;
    }
	
	/**
	 * �ǉ�����ȂƓ����Ȗ�������������������쐬����
	 * @param value1 �ǉ�����Ȃ̋Ȗ�������String
	 * @return �ǉ�����Ȃ̋Ȗ��Ɠ����f�[�^���������������
	 */
	public String makeQuery(String value1) {
		String sql = "SELECT *  FROM �� WHERE �Ȗ�='" + value1 + "'";
		return sql;
	}

	public String makeQuery(String value1, String value2) {
		return null;
	}

	public String makeQuery(String value1, String value2, String value3) {
		return null;
	}

	/**
	 * �Ȃ�ǉ����邽�߂̏��������쐬����
	 * @param result �����̎�L�[�iISRC�R�[�h�j�̍ő�l�̌������ʂ�����ResultSet 
	 * @param value1 �ǉ�����Ȃ̋Ȗ�������String
	 * @return �Ȃ�ǉ����邽�߂̏�����
	 */
	public String addMakeQuery(ResultSet result, String value1){
		String sql = null;
		try {
			result.next();
			int maxid = result.getInt("maxid");
			
		    sql = "insert into �� value(" + (maxid+1) + ",'" + value1 + "',null,null)";
		    
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
	 * �ǉ�����Ȃ̋Ȗ��Əd��������̂�\��
	 * @param result �ǉ�����Ȃ̋Ȗ��Əd������f�[�^�̌������ʂ�����ResultSet 
	 */
	public void showItem(ResultSet result) {
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("�ԍ�\tISRC�R�[�h\t�Ȗ�");
			
			while(result.next()){
				int id=result.getInt("ISRC�R�[�h");
				String music=result.getString("�Ȗ�");
				System.out.println(count + ":" + id + ":" + music);
				count++;
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}			
	}
	
}