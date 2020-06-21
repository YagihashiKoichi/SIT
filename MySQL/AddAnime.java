/**
 * �A�j���̃f�[�^���f�[�^�x�[�X(animedb)�ɒǉ�����N���X
 * @author Koichi.Yagihashi
 * @version 1.0
 */
import java.sql.ResultSet;
import java.sql.SQLException;

public class AddAnime extends AbstractAdder{
	
	/**
	 * �����̎�L�[�i�A�j���̍�iID�j�̍ő�l������������������쐬����
	 * @return �����̎�L�[�i�A�j���̍�iID�j�̍ő�l���������������
	 */
	public String makeKeyQuery(){
		String sql = "SELECT max(��iID) as maxid FROM �A�j��";
		return sql;
    }
	
	/**
	 * �ǉ�����^�C�g���Ɠ����^�C�g��������������������쐬����
	 * @param value1 �ǉ�����^�C�g��������String
	 * @return �ǉ�����^�C�g���Ɠ����^�C�g�����������������
	 */
	public String makeQuery(String value1) {
		String sql = "SELECT *  FROM �A�j�� WHERE �^�C�g��='" + value1 + "'";
		return sql;
	}

	public String makeQuery(String value1, String value2) {
		// TODO Auto-generated method stub
		return null;
	}

	public String makeQuery(String value1, String value2, String value3) {
		// TODO Auto-generated method stub
		return null;
	}

	/**
	 * �f�[�^��ǉ����邽�߂̏��������쐬����
	 * @param result �����̎�L�[�i�A�j���̍�iID�j�̍ő�l�̌������ʂ�����ResultSet 
	 * @param value1 �ǉ�����^�C�g��������String
	 * @return �^�C�g����ǉ����������
	 */
	public String addMakeQuery(ResultSet result,String value1){
		String sql = null;
		try {
			result.next();
			int maxid = result.getInt("maxid");
			
		    sql = "insert into �A�j�� value(" + (maxid+1) + ",'" + value1 + "',null)";
		    
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
		
		return sql;
    }
	
	public String addMakeQuery(ResultSet result, String value1, String value2) {
		// TODO Auto-generated method stub
		return null;
	}

	public String addMakeQuery(ResultSet result, String value1, String value2,
			String value3) {
		// TODO Auto-generated method stub
		return null;
	}

	/**
	 * �ǉ�����^�C�g���Əd��������̂�\��
	 * @param result �ǉ�����^�C�g���Əd������f�[�^�̌������ʂ�����ResultSet 
	 */
	public void showItem(ResultSet result) {
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("�ԍ�\t��iID\t�^�C�g��");
			
			while(result.next()){
				int id=result.getInt("��iID");
				String title=result.getString("�^�C�g��");
				System.out.println(count + ":" + id + ":" + title);
				count++;
			}
			
		} catch (SQLException e) {
			System.out.println("AddAnime:showItem");
			e.printStackTrace();
		}			
	}
}

