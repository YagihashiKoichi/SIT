/**
 * �f�[�^�x�[�X(animedb)�ɂ���w�肳�ꂽ�������̓d�b�ԍ���
 * �P�X�V����N���X
 * @author Koichi.Yagihashi
 * @version 1.0
 */

import java.sql.ResultSet;
import java.sql.SQLException;

public class UpdateOfficeNumber extends AbstractUpdater{
	
	/**
	 * (�X�V�Ώۂ���������ꍇ)�X�V�ΏۂƂȂ肤��f�[�^�̈ꗗ��ԍ�������
	 * ���������A�X�V�O�̓d�b�ԍ��A�Z�����܂߂ĕ\��
	 * @param result �X�V�ΏۂƂȂ肤��f�[�^�̌������ʂ�����ResultSet
	 */
	public void showItem(ResultSet result){
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("0:�A�b�v�f�[�g�𒆎~���܂��B");
			System.out.println("�ԍ�\t��������\t�d�b�ԍ�\t�Z��");
			
			while(result.next()){
				String office=result.getString("��������");
				String number=result.getString("�d�b�ԍ�");
				String address=result.getString("�Z��");
				System.out.println(count + ":" + office + ":" + number + ":" + address );
				count++;
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}	
	}
	
	/**
	 * �X�V�̏����ɊY������f�[�^������������������쐬����
	 * @param where �d�b�ԍ����X�V�������������̎�������������String
	 * @return �X�V�̏����ɊY������f�[�^���������������
	 */
	public String makeQuery(String where){
		String sql = "SELECT * FROM ������ WHERE ��������='" + where + "'";
		return sql;
    }

	/**
	 * �X�V�̏����ɊY������f�[�^���P�̂Ƃ��X�V������������쐬����
	 * @param where �d�b�ԍ����X�V�������������̎�������������String
	 * @return �X�V�̏����ɊY�����鎖�����̓d�b�ԍ����X�V���������
	 */
	public String updateMakeQuery(String set,String where,ResultSet result){
		String sql = "UPDATE ������ SET �d�b�ԍ�='" + set + "' WHERE ��������='" + where + "'";
		return sql;
    }

	/**
	 * (�X�V�Ώۂ���������ꍇ)���[�U�[���I�������f�[�^�̎�L�[(������ID)���X�V�̏����Ƃ���
	 * ���������쐬
	 * @param result �X�V�Ώۂ̌������ʂ�����ResultSet
	 * @return ���[�U�[���I�������������̎�L�[(������ID)���X�V�̏����Ƃ���������
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