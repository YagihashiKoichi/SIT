/**
 * �f�[�^�x�[�X(animedb)�ɂ����iID�A�^�C�g���A�]���l�A�]������
 * �f�[�^�\�����邽�߂̃N���X
 * @author Koichi.Yagihashi
 * @version 1.0
 */
import java.sql.ResultSet;
import java.sql.SQLException;

public class ExecuteReview extends AbstractExecuter{

	/**
	 * �A�j���̕]���ꗗ��\�����邽�߂̏��������쐬����
	 * @return �f�[�^�����̏�����
	 */
	public String makeQuery() {
		String sql = "SELECT �A�j��.��iID,�^�C�g��,�]���l,�]����" +
					" FROM �A�j��,�]��" +
					" WHERE �A�j��.��iID=�]��.��iID";
		return sql;
	}

	/**
	 * ��������������ɊY�������f�[�^��\������
	 * @param result �]���̈ꗗ������ResultSet
	 */
	public void showResult(ResultSet result) {
		
		try {
			result.beforeFirst();
			System.out.println("��iID\t�^�C�g��\t�]���l\t�]����");
			
			while(result.next()){
				int id=result.getInt("��iID");
				String title=result.getString("�^�C�g��");
				double review=result.getDouble("�]���l");
				int viewer=result.getInt("�]����");
				System.out.println(id + ":" + title + ":" + review + ":" + viewer);
			}
			
		} catch (SQLException e) {
			System.out.println("AddAnime:showItem");
			e.printStackTrace();
		}
		return;
	}
	
}	