/**
 * �f�[�^�x�[�X(animedb)�ɂ���w�肳�ꂽ�����̃f�[�^��
 * �P�f�[�^�x�[�X�ォ��폜����N���X
 * @author Koichi.Yagihashi
 * @version 1.0
 */

import java.io.*;
import java.sql.*;

public abstract class AbstractDeleter {
	
	/**
	 * �폜�̏����ɊY������f�[�^������������������쐬����
	 * @param where �폜����Ώۂ̏���������String
	 * @return �폜�̏����ɊY������f�[�^���������������
	 */
	public abstract String makeQuery(String where);		//�Y������f�[�^�������Ă��邽�߂̏������̍쐬
	
	/**
	 * �폜�̏����ɊY������f�[�^���P�̂Ƃ��폜������������쐬����
	 * @param where �폜����Ώۂ̏���������String
	 * @return �폜�̏����ɊY������f�[�^���폜���������
	 */
	public abstract String deleteMakeQuery(String where);	//�폜�̏������̍쐬
	
	/**
	 * (�폜�Ώۂ���������ꍇ)���[�U�[���I�������f�[�^�̎�L�[���폜�̏����Ƃ���
	 * ���������쐬
	 * @param result �폜�Ώۂ̌������ʂ�����ResultSet
	 * @return ���[�U�[���I�������f�[�^�̎�L�[���폜�̏����Ƃ���������
	 */
	public abstract String redeleteMakeQuery(ResultSet result);	//�I�����ꂽ�f�[�^�̍폜������������쐬
	
	/**
	 * (�폜�Ώۂ���������ꍇ)�폜�ΏۂƂȂ肤��f�[�^�̈ꗗ��ԍ������ĕ\��
	 * @param result �폜�ΏۂƂȂ肤��f�[�^�̌������ʂ�����ResultSet
	 */
	public abstract void showItem(ResultSet result);
	
	/**
	 * �f�[�^�x�[�X(animedb)�ɂ���w�肳�ꂽ�����̃f�[�^��
	 * �f�[�^�x�[�X�ォ��P�폜����
	 * @param where �폜�ΏۂɂȂ肤��f�[�^�̏���
	 * @return �폜�����������ꍇ��true,���s�����ꍇ��false
	 */
	public final Boolean SetAndDelete(String where) {
		Connection conn = null;
		try {
			conn = DriverManager.getConnection(
			"jdbc:mysql://localhost/animedb?useSSL=false", "root", "SITmeDB"
			);
			
			BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
			
			Statement stm=conn.createStatement();
			String sql = makeQuery(where);		//���������Z�b�g
			ResultSet old_result=stm.executeQuery(sql);
			old_result.last();
			int item_count=old_result.getRow();
			old_result.beforeFirst();
			
			switch(item_count){
				case 0:
					System.out.println("�폜���邽�߂̏��������݂��܂���B");
					return false;
			
				case 1:
					String sql2=deleteMakeQuery(where);	//�폜�̏��������Z�b�g
					System.out.println(sql2);
					stm.executeUpdate(sql2);;		//�폜�����s
					System.out.println("�폜���������܂����B");
					return true;
				
				default:
					int item_number;
					System.out.println("�Y�����鍀�ڂ�����������܂����B");
					System.out.println("�폜�������ԍ���I�����Ă�������");
					System.out.println("�Y�����鍀�ڂȂ��ꍇ0����͂���ƍ폜�𒆎~�ł��܂��B");
					showItem(old_result);
					
					while(true){
						item_number = Integer.parseInt(reader.readLine());
						if(item_number==0){
							System.out.println("�폜�𒆎~���܂��B");
							return false;
						}else if((0<item_number)&&(item_number<=item_count)){
							old_result.absolute(item_number);	//���[�U�[���I�񂾍s�Ɉړ�
							String sql3=redeleteMakeQuery(old_result);
							stm.executeUpdate(sql3);
							break;
						}else{
							System.out.println("�I�����ڂ̔ԍ�����I��ł��������B");
						}
					}
					System.out.println("�폜���������܂����B");
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
