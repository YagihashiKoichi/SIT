/**
 * �f�[�^�x�[�X(animedb)�ɂ���w�肳�ꂽ�����̃f�[�^��
 * �P�X�V����N���X
 * @author Koichi.Yagihashi
 * @version 1.0
 */

import java.io.*;
import java.sql.*;

public abstract class AbstractUpdater {
	
	/**
	 * �X�V�̏����ɊY������f�[�^������������������쐬����
	 * @param where �X�V����Ώۂ̏���������String
	 * @return �X�V�̏����ɊY������f�[�^���������������
	 */
	public abstract String makeQuery(String where);	//�Y������f�[�^�������Ă��邽�߂̏������̍쐬
	
	/**
	 * �X�V�̏����ɊY������f�[�^���P�̂Ƃ��X�V������������쐬����
	 * @param where �X�V����Ώۂ̏���������String
	 * @return �X�V�̏����ɊY������f�[�^���X�V���������
	 */
	public abstract String updateMakeQuery(String set,String where,ResultSet result);	//�A�b�v�f�[�g�̏������̍쐬
	
	/**
	 * (�X�V�Ώۂ���������ꍇ)���[�U�[���I�������f�[�^�̎�L�[���X�V�̏����Ƃ���
	 * ���������쐬
	 * @param result �X�V�Ώۂ̌������ʂ�����ResultSet
	 * @return ���[�U�[���I�������f�[�^�̎�L�[���X�V�̏����Ƃ���������
	 */
	public abstract String reupdateMakeQuery(String set,ResultSet result);	//��������ꍇ�I�����ꂽ���̂ɑ΂���������̍쐬
	
	/**
	 * (�X�V�Ώۂ���������ꍇ)�X�V�ΏۂƂȂ肤��f�[�^�̈ꗗ��ԍ������ĕ\��
	 * @param result �X�V�ΏۂƂȂ肤��f�[�^�̌������ʂ�����ResultSet
	 */
	public abstract void showItem(ResultSet result);	//�Y�������f�[�^�ꗗ��\��
	
	/**
	 * �f�[�^�x�[�X(animedb)�ɂ���w�肳�ꂽ�����̃f�[�^��
	 * �P�X�V����
	 * @param where �X�V�ΏۂɂȂ肤��f�[�^�̏���
	 * @return �X�V�����������ꍇ��true,���s�����ꍇ��false
	 */
	public final Boolean SetAndUpdate(String where,String set) {
		Connection conn = null;
		try {
			
			BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
			conn = DriverManager.getConnection(
				"jdbc:mysql://localhost/animedb?useSSL=false", "root", "SITmeDB"
				);

			Statement stm1=conn.createStatement();
			
			String sql1 = makeQuery(where);	//�Y������f�[�^���i�������
			ResultSet old_result=stm1.executeQuery(sql1);
		
			old_result.last();
			int item_count=old_result.getRow();
			old_result.beforeFirst();
			
			switch(item_count){
				case 0:
					System.out.println("�ύX���邽�߂̏��������݂��܂���B");
					return false;
			
				case 1:
					String sql2=updateMakeQuery(set,where,old_result);	//�A�b�v�f�[�g�̏��������Z�b�g
					stm1.executeUpdate(sql2);		//�A�b�v�f�[�g�����s
					System.out.println("�A�b�v�f�[�g���������܂����B");
					return true;
				
				default:
					int item_number;
					System.out.println("�Y�����鍀�ڂ�����������܂����B");
					System.out.println("�ύX�������ԍ���I�����Ă�������");
					System.out.println("�Y�����鍀�ڂȂ��ꍇ0����͂���ƃA�b�v�f�[�g�𒆎~�ł��܂��B");
					showItem(old_result);
					
					while(true){
						item_number = Integer.parseInt(reader.readLine());
						if(item_number==0){
							System.out.println("�A�b�v�f�[�g�𒆎~���܂��B");
							return false;
						}else if((0<item_number)&&(item_number<=item_count)){
							old_result.absolute(item_number);	//���[�U�[���I�񂾍s�Ɉړ�
							String sql3=reupdateMakeQuery(set,old_result);
							stm1.executeUpdate(sql3);
							break;
			
						}else{
							System.out.println("�I�����ڂ̔ԍ�����I��ł��������B");
						}
					}
					System.out.println("�A�b�v�f�[�g���������܂����B");
			}
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
		return true;
	}
	
}