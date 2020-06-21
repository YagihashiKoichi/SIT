/**
 * �f�[�^�x�[�X(animedb)�ɂ���w�肳�ꂽ�z�M�T�[�r�X��URL��
 * �P�X�V����N���X
 * @author Koichi.Yagihashi
 * @version 1.0
 */

import java.sql.ResultSet;
import java.sql.SQLException;

public class UpdateURL extends AbstractUpdater{

	/**
	 * (�X�V�Ώۂ���������ꍇ)�X�V�ΏۂƂȂ肤��f�[�^�̈ꗗ��ԍ�������
	 * �T�[�r�X���A�X�V�O��URL�A�Z�����܂߂ĕ\��
	 * @param result �X�V�ΏۂƂȂ肤��f�[�^�̌������ʂ�����ResultSet
	 */
	public void showItem(ResultSet result){
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("0:�A�b�v�f�[�g�𒆎~���܂��B");
			System.out.println("�ԍ�\t�T�[�r�X��\tURL");
			
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
	
	/**
	 * �X�V�̏����ɊY������f�[�^������������������쐬����
	 * @param where URL���X�V�������z�M�T�[�r�X�̃T�[�r�X��������String
	 * @return �X�V�̏����ɊY������f�[�^���������������
	 */
	public String makeQuery(String where){
		String sql = "SELECT * FROM �z�M�T�[�r�X WHERE �T�[�r�X��='" + where + "'";
		return sql;
    }
	
	/**
	 * �X�V�̏����ɊY������f�[�^���P�̂Ƃ��X�V������������쐬����
	 * @param where URL���X�V�������z�M�T�[�r�X�̃T�[�r�X��������String
	 * @return �X�V�̏����ɊY������z�M�T�[�r�X��URL���X�V���������
	 */
	public String updateMakeQuery(String set,String where,ResultSet result){
		String sql = "UPDATE �z�M�T�[�r�X SET URL='" + set + "' WHERE �T�[�r�X��='" + where + "'";
		return sql;
    }

	/**
	 * (�X�V�Ώۂ���������ꍇ)���[�U�[���I�������f�[�^�̎�L�[(�z�M�T�[�r�XID)���X�V�̏����Ƃ���
	 * ���������쐬
	 * @param result �X�V�Ώۂ̌������ʂ�����ResultSet
	 * @return ���[�U�[���I�������z�M�T�[�r�X�̎�L�[(�z�M�T�[�r�XID)���X�V�̏����Ƃ���������
	 */
	public String reupdateMakeQuery(String set,ResultSet result){
		String sql = null;
		int id;
		try {
			id = result.getInt("�z�M�T�[�r�XID");
			sql = "UPDATE �z�M�T�[�r�X SET URL='" + set + "' WHERE URL='" + id + "'";
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return sql;
	}
}	