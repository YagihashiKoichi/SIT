/**
 * �f�[�^�x�[�X(animedb)�ɂ���f�[�^�\�����邽�߂�
 * ���ۃN���X
 * @author Koichi.Yagihashi
 * @version 1.0
 */
import java.sql.*;
public abstract class AbstractExecuter {
	
	/**
	 * �f�[�^�����̏��������쐬����
	 * @return �f�[�^�����̏�����
	 */
	public abstract String makeQuery();		//���������Z�b�g
	
	/**
	 * ��������������ɊY�������f�[�^��\������
	 * @param result �������ʂ�����ResultSet
	 */
	public abstract void showResult(ResultSet result);	//�������ʈꗗ��\��
	
	/**
	 * �f�[�^�x�[�X(animedb)�ɂ���f�[�^����
	 * �������ɊY������f�[�^��\������
	 */
	public final void queryAndShow() {
		Connection conn = null;
		try {
			 
			conn = DriverManager.getConnection(
				"jdbc:mysql://localhost/animedb?useSSL=false", "root", "SITmeDB"
				);
			Statement stm=conn.createStatement();
			String sqlString = makeQuery();		//���������Z�b�g
			ResultSet result=stm.executeQuery(sqlString);
			showResult(result);			//�������ʈꗗ�\��
			conn.close();
		} catch (SQLException se) {
			System.out.println("SQL Error 1: " + se.toString() + " "
				+ se.getErrorCode() + " " + se.getSQLState());
		} catch (Exception e) {
			System.out.println("Error: " + e.toString() + e.getMessage());
		}finally {
			if (conn != null) {
				try {
					conn.close();
				} catch (SQLException e) {
					System.out.println("MySQL�̃N���[�Y�Ɏ��s���܂����B");
				}
			}
		}
	}
}
