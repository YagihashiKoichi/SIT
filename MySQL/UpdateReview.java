/**
 * �f�[�^�x�[�X(animedb)�ɂ���w�肳�ꂽ�A�j���̕]���l�̕��ςƕ]�����̂��ꂼ��
 * �P���X�V����N���X
 * @author Koichi.Yagihashi
 * @version 1.0
 */

import java.sql.ResultSet;
import java.sql.SQLException;

public class UpdateReview extends AbstractUpdater {
	
	/**
	 * (�X�V�Ώۂ���������ꍇ)�X�V�ΏۂƂȂ肤��f�[�^�̈ꗗ��ԍ�������
	 * ��iID�A�^�C�g���A�X�V�O�̕��ϕ]���l�A�X�V�O�̕]�������܂߂ĕ\��
	 * @param result �X�V�ΏۂƂȂ肤��f�[�^�̌������ʂ�����ResultSet
	 */
	public void showItem(ResultSet result){
		try {
			int count=1;
			result.beforeFirst();
			System.out.println("0:�A�b�v�f�[�g�𒆎~���܂��B");
			System.out.println("�ԍ�\t��iID\t�^�C�g��\t�]���l\t�]����");
			while(result.next()){
				int id=result.getInt("�]��.��iID");
				String title=result.getString("�^�C�g��");
				double review=result.getDouble("�]���l");
				int viewer=result.getInt("�]����");
				System.out.println(count + ":\t" + id + ":\t" + title + ":\t" + review + ":\t" + viewer);
				count++;
			}
			
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}	
	}
	
	/**
	 * �X�V�̏����ɊY������f�[�^������������������쐬����
	 * @param where �]���l���X�V�������A�j���̃^�C�g��������String
	 * @return �X�V�̏����ɊY������f�[�^���������������
	 */
	public String makeQuery(String where){	//����������������Z�b�g
		String sql = "SELECT �]��.��iID,�^�C�g��,�]���l,�]���� FROM �]��,�A�j�� WHERE �A�j��.��iID=�]��.��iID AND �^�C�g��='" + where + "'";
		return sql;
    }
	
	/**
	 * �X�V�̏����ɊY������f�[�^���P�̂Ƃ��X�V������������쐬����
	 * @param where �]���l���X�V�������A�j���̃^�C�g��������String
	 * @return �X�V�̏����ɊY������A�j���̕]���l�ƕ]�������X�V���������
	 */
	public String updateMakeQuery(String set,String where,ResultSet result){	//�A�b�v�f�[�g�̏��������Z�b�g
		double review;
		int viewer,id;
		String sql = null;
		try{
			while(result.next()){	//�]���������^�C�g���i��i�j��ID����
				review = result.getDouble("�]���l");
				viewer=result.getInt("�]����");
				id=result.getInt("��iID");
				sql = "UPDATE �]�� SET �]���l=" + ((review*viewer+Double.parseDouble(set))/(viewer+1)) + ",�]����=" + (viewer+1) + " WHERE ��iID='" + id + "'";
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return sql;
    }
	
	/**
	 * (�X�V�Ώۂ���������ꍇ)���[�U�[���I�������f�[�^�̎�L�[(��iID)���X�V�̏����Ƃ���
	 * ���������쐬
	 * @param result �X�V�Ώۂ̌������ʂ�����ResultSet
	 * @return ���[�U�[���I�������]���̎�L�[(��iID)���X�V�̏����Ƃ���������
	 */
	public String reupdateMakeQuery(String set,ResultSet result){
		String sql = null;
		try {
			int id = result.getInt("�]��.��iID");
			double review = result.getDouble("�]���l");
			int viewer=result.getInt("�]����");
			sql = "UPDATE �]�� SET �]���l=" + ((review*viewer+Double.parseDouble(set))/(viewer+1)) + ",�]����=" + (viewer+1) + " WHERE �]��.��iID=" + id;

		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return sql;
	}
}	