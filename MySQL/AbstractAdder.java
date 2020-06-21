/**
 * �f�[�^���f�[�^�x�[�X(animedb)�ɒǉ����钊�ۃN���X
 * @author Koichi.Yagihashi
 * @version 1.0
 */
import java.io.*;
import java.sql.*;

public abstract class AbstractAdder {
	
	/**
	 * �ǉ�����f�[�^�Ɠ����f�[�^������������������쐬����
	 * @param value1 �ǉ�����f�[�^���e������String
	 * @return �ǉ�����f�[�^�Ɠ����f�[�^���������������
	 */
	public abstract String makeQuery(String value1);
	
	/**
	 * �ǉ�����f�[�^�Ɠ����f�[�^������������������쐬����
	 * @param value1 �ǉ�����f�[�^���e������String
	 * @param value2 �ǉ�����f�[�^���e������String
	 * @return �ǉ�����f�[�^�Ɠ����f�[�^���������������
	 */
	public abstract String makeQuery(String value1,String value2);
	
	/**
	 * �ǉ�����f�[�^�Ɠ����f�[�^������������������쐬����
	 * @param value1 �ǉ�����f�[�^���e������String
	 * @param value2 �ǉ�����f�[�^���e������String
	 * @param value3 �ǉ�����f�[�^���e������String
	 * @return �ǉ�����f�[�^�Ɠ����f�[�^���������������
	 */
	public abstract String makeQuery(String value1,String value2,String value3);
	
	/**
	 * �ǉ�����e�[�u����̊����̎�L�[�iID�j�̍ő�l������������������쐬����
	 * @return �ǉ�����e�[�u����̊����̎�L�[�iID�j�̍ő�l���������������
	 */
	public abstract String makeKeyQuery();	//�Y������f�[�^�������Ă��邽�߂̏������̍쐬
	
	/**
	 * �f�[�^��ǉ����邽�߂̏��������쐬����
	 * @param result �����̎�L�[�iID�j�̍ő�l�̌������ʂ�����ResultSet 
	 * @param value1 �ǉ�����f�[�^���e������String
	 * @return �f�[�^��ǉ����������
	 */
	public abstract String addMakeQuery(ResultSet result,String value1);	//�A�b�v�f�[�g�̏������̍쐬
	
	/**
	 * �f�[�^��ǉ����邽�߂̏��������쐬����
	 * @param result �����̎�L�[�iID�j�̍ő�l�̌������ʂ�����ResultSet 
	 * @param value1 �ǉ�����f�[�^���e������String
	 * @param value2 �ǉ�����f�[�^���e������String
	 * @return �f�[�^��ǉ����������
	 */
	public abstract String addMakeQuery(ResultSet result,String value1,String value2);	//�A�b�v�f�[�g�̏������̍쐬
	
	/**
	 * �f�[�^��ǉ����邽�߂̏��������쐬����
	 * @param result �����̎�L�[�iID�j�̍ő�l�̌������ʂ�����ResultSet 
	 * @param value1 �ǉ�����f�[�^���e������String
	 * @param value2 �ǉ�����f�[�^���e������String
	 * @param value3 �ǉ�����f�[�^���e������String 
	 * @return �f�[�^��ǉ����������
	 */
	public abstract String addMakeQuery(ResultSet result,String value1,String value2,String value3);	//�A�b�v�f�[�g�̏������̍쐬
	
	/**
	 * �ǉ�����f�[�^�Əd������Ǝv������̂�\��
	 * @param result �ǉ�����f�[�^�Əd������Ǝv����f�[�^�̌������ʂ�����ResultSet 
	 */
	public abstract void showItem(ResultSet result);	//�d�������f�[�^�ꗗ��\��
	
	/**
	 * �d�����Ȃ��ꍇ�͂��̂܂܃f�[�^��ǉ����邪
	 * �d�������ꍇ�͒ǉ����邩�̓��[�U�[�̔��f�ɏ]��
	 * @param value1 �ǉ�����f�[�^���e������String
	 * @return �ǉ������������ꍇ��true,���s�����ꍇ��false
	 */
	public Boolean SetAndAdd(String value1) {
		Connection conn = null;
		try {
			
			BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
			
			conn = DriverManager.getConnection(
				"jdbc:mysql://localhost/animedb?useSSL=false", "root", "SITmeDB"
				);
			
			Statement stm1=conn.createStatement();
			Statement stm2=conn.createStatement();
			
			String sql1 = makeQuery(value1);	//�ǉ�����f�[�^�̏d�����i�������
			ResultSet exi_result=stm1.executeQuery(sql1);
		
			exi_result.last();
			int item_count=exi_result.getRow();
			exi_result.beforeFirst();
			
			String sql2 = makeKeyQuery();	//ID�̍ő�l���������������
			ResultSet key_result=stm2.executeQuery(sql2);
			
			String sql3=addMakeQuery(key_result,value1);	//�ǉ��̏��������쐬
			
			if(item_count==0)	//�d�����Ȃ�
				stm1.executeUpdate(sql3);
			else{				//�d������
				System.out.println("�ǉ����悤�Ƃ����f�[�^�Ɠ������̂����ɑ��݂��܂����B");
				showItem(exi_result);	//�d�������f�[�^�ꗗ��\��
				System.out.println("�f�[�^��ǉ����܂����H");
				System.out.println("1:YES / 0:NO");
				int judge = Integer.parseInt(reader.readLine());
				if(judge==1)
					stm1.executeUpdate(sql3);
				else{
					System.out.println("�ǉ��𒆎~���܂����B");
					return false;
				}
			}
			
			System.out.println("�ǉ��ɐ������܂����B");

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

	/**
	 * �d�����Ȃ��ꍇ�͂��̂܂܃f�[�^��ǉ����邪
	 * �d�������ꍇ�͒ǉ����邩�̓��[�U�[�̔��f�ɏ]��
	 * @param value1 �ǉ�����f�[�^���e������String
	 * @param value2 �ǉ�����f�[�^���e������String
	 * @return �ǉ������������ꍇ��true,���s�����ꍇ��false
	 */
	public Boolean SetAndAdd(String value1,String value2) {
		Connection conn = null;
		try {
			
			BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
			
			conn = DriverManager.getConnection(
				"jdbc:mysql://localhost/animedb?useSSL=false", "root", "SITmeDB"
				);
			
			Statement stm1=conn.createStatement();
			Statement stm2=conn.createStatement();
			
			String sql1 = makeQuery(value1,value2);	//�ǉ�����f�[�^�̏d�����i�������
			ResultSet exi_result=stm1.executeQuery(sql1);
		
			exi_result.last();
			int item_count=exi_result.getRow();
			exi_result.beforeFirst();
			
			String sql2 = makeKeyQuery();	//ID�̍ő�l���������������
			ResultSet key_result=stm2.executeQuery(sql2);
			
			String sql3=addMakeQuery(key_result,value1,value2);	//�ǉ��̏��������쐬
			
			if(item_count==0)	//�d�����Ȃ�
				stm1.executeUpdate(sql3);
			else{				//�d������
				System.out.println("�ǉ����悤�Ƃ����f�[�^�Ɠ������̂����ɑ��݂��܂����B");
				showItem(exi_result);	//�d�������f�[�^�ꗗ��\��
				System.out.println("�f�[�^��ǉ����܂����H");
				System.out.println("1:YES / 0:NO");
				int judge = Integer.parseInt(reader.readLine());
				if(judge==1)
					stm1.executeUpdate(sql3);
				else{
					System.out.println("�ǉ��𒆎~���܂����B");
					return false;
				}
			}
			
			System.out.println("�ǉ��ɐ������܂����B");

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

	/**
	 * �d�����Ȃ��ꍇ�͂��̂܂܃f�[�^��ǉ����邪
	 * �d�������ꍇ�͒ǉ����邩�̓��[�U�[�̔��f�ɏ]��
	 * @param value1 �ǉ�����f�[�^���e������String
	 * @param value2 �ǉ�����f�[�^���e������String
	 * @param value3 �ǉ�����f�[�^���e������String
	 * @return �ǉ������������ꍇ��true,���s�����ꍇ��false
	 */
	public Boolean SetAndAdd(String value1,String value2,String value3) {
		Connection conn = null;
		try {
		
			BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
			
			conn = DriverManager.getConnection(
				"jdbc:mysql://localhost/animedb?useSSL=false", "root", "SITmeDB"
				);
			
			Statement stm1=conn.createStatement();
			Statement stm2=conn.createStatement();
			
			String sql1 = makeQuery(value1,value2,value3);	//�ǉ�����f�[�^�̏d�����i�������
			ResultSet exi_result=stm1.executeQuery(sql1);
		
			exi_result.last();
			int item_count=exi_result.getRow();
			exi_result.beforeFirst();
			
			String sql2 = makeKeyQuery();	//ID�̍ő�l���������������
			ResultSet key_result=stm2.executeQuery(sql2);
			
			String sql3=addMakeQuery(key_result,value1,value2,value3);	//�ǉ��̏��������쐬
			
			if(item_count==0)	//�d�����Ȃ�
				stm1.executeUpdate(sql3);
			else{				//�d������
				System.out.println("�ǉ����悤�Ƃ����f�[�^�Ɠ������̂����ɑ��݂��܂����B");
				showItem(exi_result);	//�d�������f�[�^�ꗗ��\��
				System.out.println("�f�[�^��ǉ����܂����H");
				System.out.println("1:YES / 0:NO");
				int judge = Integer.parseInt(reader.readLine());
				if(judge==1)
					stm1.executeUpdate(sql3);
				else{
					System.out.println("�ǉ��𒆎~���܂����B");
					return false;
				}
			}
			
			System.out.println("�ǉ��ɐ������܂����B");
	
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
