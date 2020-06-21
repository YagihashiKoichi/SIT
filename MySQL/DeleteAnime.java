/**
 * �f�[�^�x�[�X(animedb)�ɂ���w�肳�ꂽ�A�j���̃^�C�g���̃f�[�^��
 * �P�f�[�^�x�[�X�ォ��폜����N���X
 * @author Koichi.Yagihashi
 * @version 1.0
 */
//��Ɖ��̎g��Ȃ����\�b�h���폜
import java.sql.ResultSet;
import java.sql.SQLException;

public class DeleteAnime extends AbstractDeleter{
	
	/**
	 * �폜�̏����ɊY������f�[�^������������������쐬����
	 * @param where �폜����A�j���̃^�C�g��������String
	 * @return �폜�̏����ɊY������f�[�^���������������
	 */
	public String makeQuery(String where){
		String sql = "SELECT * FROM �A�j�� WHERE �^�C�g��='" + where + "'";
		return sql;
    }
	
	/**
	 * �폜�̏����ɊY������f�[�^���P�̂Ƃ��폜������������쐬����
	 * @param where �폜����A�j���̃^�C�g��������String
	 * @return �폜�̏����ɊY������f�[�^���폜���������
	 */
	public String deleteMakeQuery(String where){
		String sql = "DELETE �A�j��,����,�z�M,�o��,����,������" +
				     " FROM �A�j��" +
				     " LEFT JOIN ���� ON �A�j��.��iID=����.��iID" +
				     " LEFT JOIN �z�M ON �A�j��.��iID=�z�M.��iID" +
				     " LEFT JOIN �o�� ON �A�j��.��iID=�o��.��iID" +
				     " LEFT JOIN ���� ON �A�j��.��iID=����.��iID" +
				     " LEFT JOIN ������ ON �A�j��.��iID=������.��iID" +
				     " WHERE �^�C�g��='" + where + "'";
		return sql;
    }

	/**
	 * (�폜�Ώۂ���������ꍇ)���[�U�[���I�������f�[�^�̎�L�[(��iID)���폜�̏����Ƃ���
	 * ���������쐬
	 * @param result �폜�Ώۂ̌������ʂ�����ResultSet
	 * @return ���[�U�[���I�������f�[�^�̎�L�[(��iID)���폜�̏����Ƃ���������
	 */
	public String redeleteMakeQuery(ResultSet result){
		String sql = null;
		String id;
		try {
			id = result.getString("��iID");
		    sql = "DELETE �A�j��,����,�z�M,�o��,����,������" +
				     " FROM �A�j��" +
				     " LEFT JOIN ���� ON �A�j��.��iID=����.��iID" +
				     " LEFT JOIN �z�M ON �A�j��.��iID=�z�M.��iID" +
				     " LEFT JOIN �o�� ON �A�j��.��iID=�o��.��iID" +
				     " LEFT JOIN ���� ON �A�j��.��iID=����.��iID" +
				     " LEFT JOIN ������ ON �A�j��.��iID=������.��iID" +
				     " WHERE �A�j��.��iID='" + id + "'";
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return sql;
	}
	
	/**
	 * (�폜�Ώۂ���������ꍇ)�폜�ΏۂƂȂ肤��f�[�^�̈ꗗ��ԍ�������
	 * ��L�[(��iID)���܂߂ĕ\��
	 * @param result �폜�ΏۂƂȂ肤��f�[�^�̌������ʂ�����ResultSet
	 */
	public void showItem(ResultSet result){
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("0:�폜�𒆎~���܂��B");
			System.out.println("�ԍ�\t��iID\t�^�C�g��");
			
			while(result.next()){
				int id=result.getInt("��iID");
				String title=result.getString("�^�C�g��");
				System.out.println(count + ":" + id + ":" + title);
				count++;
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}	
	}
}	