/**
 * �f�[�^�x�[�X(animedb)�ɂ���w�肳�ꂽ�����ǂ̏Z����
 * �P�X�V����N���X
 * @author Koichi.Yagihashi
 * @version 1.0
 */

import java.sql.ResultSet;
import java.sql.SQLException;

public class UpdateBroadcasterAddress  extends AbstractUpdater{
	
	/**
	 * (�X�V�Ώۂ���������ꍇ)�X�V�ΏۂƂȂ肤��f�[�^�̈ꗗ��ԍ�������
	 * �ǖ��A�X�V�O�̏Z�����܂߂ĕ\��
	 * @param result �X�V�ΏۂƂȂ肤��f�[�^�̌������ʂ�����ResultSet
	 */
	public void showItem(ResultSet result){
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("0:�A�b�v�f�[�g�𒆎~���܂��B");
			System.out.println("�ԍ�\t�ǖ�\t�Z��");
			
			while(result.next()){
				String broadcaster=result.getString("�ǖ�");
				String address=result.getString("�Z��");
				System.out.println(count + ":" + broadcaster + ":"  + address );
				count++;
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}	
	}
	
	
	/**
	 * �X�V�̏����ɊY������f�[�^������������������쐬����
	 * @param where �Z�����X�V�����������ǂ̋ǖ�������String
	 * @return �X�V�̏����ɊY������f�[�^���������������
	 */
	public String makeQuery(String where){
		String sql = "SELECT * FROM ������ WHERE �ǖ�='" + where + "'";
		return sql;
    }
	
	/**
	 * �X�V�̏����ɊY������f�[�^���P�̂Ƃ��X�V������������쐬����
	 * @param where �Z�����X�V�����������ǂ̋ǖ�������String
	 * @return �X�V�̏����ɊY����������ǂ̏Z�����X�V���������
	 */
	public String updateMakeQuery(String set,String where,ResultSet result){
		String sql = "UPDATE ������ SET �Z��='" + set + "' WHERE �ǖ�='" + where + "'";
		return sql;
    }

	/**
	 * (�X�V�Ώۂ���������ꍇ)���[�U�[���I�������f�[�^�̎�L�[(������ID)���X�V�̏����Ƃ���
	 * ���������쐬
	 * @param result �X�V�Ώۂ̌������ʂ�����ResultSet
	 * @return ���[�U�[���I�����������ǂ̎�L�[(������ID)���X�V�̏����Ƃ���������
	 */
	public String reupdateMakeQuery(String set,ResultSet result){
		String sql = null;
		int id;
		try {
			id = result.getInt("������ID");
			sql = "UPDATE ������ SET �Z��='" + set + "' WHERE ������ID='" + id + "'";
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return sql;
	}
}	