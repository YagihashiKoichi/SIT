/**
 * �f�[�^�x�[�X(animedb)�ɂ���w�肳�ꂽ�����̃f�[�^��
 * �P�f�[�^�x�[�X�ォ��폜����N���X
 * @ Koichi.Yagihashi
 */
//��Ɖ��̎g��Ȃ����\�b�h���폜
import java.sql.ResultSet;
import java.sql.SQLException;

public class DeleteService extends AbstractDeleter{
	
	/**
	 * �폜�̏����ɊY������f�[�^������������������쐬����
	 * @param where �폜����z�M�T�[�r�X��������String
	 * @return �폜�̏����ɊY������f�[�^���������������
	 */
	public String makeQuery(String where){
		String sql = "SELECT * FROM �z�M�T�[�r�X WHERE �T�[�r�X��='" + where + "'";
		return sql;
    }
	
	/**
	 * �폜�̏����ɊY������f�[�^���P�̂Ƃ��폜������������쐬����
	 * @param where �폜����z�M�T�[�r�X��������String
	 * @return �폜�̏����ɊY������f�[�^���폜���������
	 */
	public String deleteMakeQuery(String where){
		String sql = "DELETE �z�M�T�[�r�X,�z�M FROM �z�M�T�[�r�X" +
				     " LEFT JOIN �z�M ON �z�M�T�[�r�X.�z�M�T�[�r�XID=�z�M.�z�M�T�[�r�XID" +
				     " WHERE �T�[�r�X��='" + where + "'";
		return sql;
    }


	/**
	 * (�폜�Ώۂ���������ꍇ)���[�U�[���I�������f�[�^�̎�L�[(�z�M�T�[�r�XID)���폜�̏����Ƃ���
	 * ���������쐬
	 * @param result �폜�Ώۂ̌������ʂ�����ResultSet
	 * @return ���[�U�[���I�������f�[�^�̎�L�[(�z�M�T�[�r�XID)���폜�̏����Ƃ���������
	 */
	public String redeleteMakeQuery(ResultSet result){
		String sql = null;
		String id;
		try {
			id = result.getString("�z�M�T�[�r�XID");
			sql = "DELETE �z�M�T�[�r�X,�z�M FROM �z�M�T�[�r�X" +
				     " LEFT JOIN �z�M ON �z�M�T�[�r�X.�z�M�T�[�r�XID=�z�M.�z�M�T�[�r�XID" +
				     " WHERE �z�M�T�[�r�X.�z�M�T�[�r�XID='" + id + "'";
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return sql;
	}
	
	/**
	 * (�폜�Ώۂ���������ꍇ)�폜�ΏۂƂȂ肤��f�[�^�̈ꗗ��ԍ�������
	 * URL���܂߂ĕ\��
	 * @param result �폜�ΏۂƂȂ肤��f�[�^�̌������ʂ�����ResultSet
	 */
	public void showItem(ResultSet result){
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("�ԍ��@�@�T�[�r�X���@�@�@�@�@�@URL");
			System.out.println("0:�폜�𒆎~���܂��B");
			
			while(result.next()){
				String service=result.getString("�T�[�r�X��");
				String url=result.getString("URL");
				System.out.println(count + ":" + service + ":" + url);
				count++;
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}	
	}
}	