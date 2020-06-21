/**
 * �f�[�^�x�[�X(animedb)�ɂ���w�肳�ꂽ�����Ђ̓d�b�ԍ���
 * �P�X�V����N���X
 * @author Koichi.Yagihashi
 * @version 1.0
 */

import java.sql.ResultSet;
import java.sql.SQLException;

public class UpdateCompanyNumber extends AbstractUpdater{
	
	/**
	 * (�X�V�Ώۂ���������ꍇ)�X�V�ΏۂƂȂ肤��f�[�^�̈ꗗ��ԍ�������
	 * ��Ж��A�X�V�O�̓d�b�ԍ��A�{�ЏZ�����܂߂ĕ\��
	 * @param result �X�V�ΏۂƂȂ肤��f�[�^�̌������ʂ�����ResultSet
	 */
	public void showItem(ResultSet result){
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("0:�A�b�v�f�[�g�𒆎~���܂��B");
			System.out.println("�ԍ�\t������ID\t��Ж�\t�d�b�ԍ�\t�{�ЏZ��");
			
			while(result.next()){
				String company=result.getString("��Ж�");
				String number=result.getString("�d�b�ԍ�");
				String address=result.getString("�{�ЏZ��");
				System.out.println(count + ":" + company + ":" + number + ":" + address );
				count++;
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}	
	}
	
	/**
	 * �X�V�̏����ɊY������f�[�^������������������쐬����
	 * @param where �d�b�ԍ����X�V�����������Ђ̉�Ж�������String
	 * @return �X�V�̏����ɊY������f�[�^���������������
	 */
	public String makeQuery(String where){
		String sql = "SELECT * FROM ������ WHERE ��Ж�='" + where + "'";
		return sql;
    }
	
	/**
	 * �X�V�̏����ɊY������f�[�^���P�̂Ƃ��X�V������������쐬����
	 * @param where �d�b�ԍ����X�V�����������Ђ̉�Ж�������String
	 * @return �X�V�̏����ɊY�����鐧���Ђ̓d�b�ԍ����X�V���������
	 */
	public String updateMakeQuery(String set,String where,ResultSet result){
		String sql = "UPDATE ������ SET �d�b�ԍ�='" + set + "' WHERE ��Ж�='" + where + "'";
		return sql;
    }

	/**
	 * (�X�V�Ώۂ���������ꍇ)���[�U�[���I�������f�[�^�̎�L�[(������ID)���X�V�̏����Ƃ���
	 * ���������쐬
	 * @param result �X�V�Ώۂ̌������ʂ�����ResultSet
	 * @return ���[�U�[���I�����������Ђ̎�L�[(������ID)���X�V�̏����Ƃ���������
	 */
	public String reupdateMakeQuery(String set,ResultSet result){
		String sql = null;
		int id;
		try {
			id = result.getInt("������ID");
			sql = "UPDATE ������ SET �d�b�ԍ�='" + set + "' WHERE ������ID='" + id + "'";
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return sql;
	}
}	