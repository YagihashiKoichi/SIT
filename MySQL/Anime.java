/**���̃N���X�͎w�肳�ꂽ�����ɏ]���A�j���̏�����������N���X�ł���B
*�u�A�j���^�C�g���v�A�u�W�������v�A�u���D�v��3�v�f�ɂ��Č������\�ł���B
* �ǂ̗v�f�ɂ��Č������邩��I��������A���Ɍ������镶�������͂���Ƃ���Ɋւ����񂪏o�͂����B
* @author Masato Suemura
* modified by Koichi.Yagihashi
* ���g�p�̕ϐ����폜
* ���g�pimport�̍폜
* ���C�����\�b�h����N���X�ɕύX
* �e�X�g�p�̕W���o�͂��폜
* �I�����ȊO�̔ԍ������͂��ꂽ�ۂ̒��ӂ𑣂�����ǉ�
*/

import java.sql.*;
import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class Anime {
	void bigSearch(){
		Connection con = null;
		try {
		    // DB�ɐڑ�����
			con = DriverManager.getConnection(
				"jdbc:mysql://localhost/animedb?useSSL=false", "root", "SITmeDB"
				);

			// Statement�����
			Statement stm = con.createStatement();
			
			try{
				System.out.println("���ɂ��Č������܂����H");
				System.out.println("1�F�A�j���^�C�g��\n2�F�W������\n3�F���D");
				InputStreamReader isr = new InputStreamReader(System.in);
				BufferedReader br = new BufferedReader(isr);
				String buf3 = br.readLine();
				int buf1 = Integer.parseInt(buf3);
				String sqlA = "";
				String sqlB = "�A�j��.�^�C�g�� ";
				String sqlC = " ";
				if(buf1==2){
					System.out.println("\n�W���������猟�����܂�");
					sqlB = "�W������.�W�������� ";
					sqlA = " and �A�j��.��iID=������.��iID and ������.�W��������=�W������.�W��������";
					sqlC = ",������,�W������ ";
				}else if(buf1==3){
					System.out.println("\n���D���猟�����܂�");
					sqlB = "���D.���O ";
					sqlA = " and ���D.���DID=�o��.���DID and �A�j��.��iID=�o��.��iID";
					sqlC = ",�o��,���D ";
				}else if(buf1==1){
					sqlB = "�A�j��.�^�C�g�� ";
				}
				
				System.out.println("�������镶�������͂��Ă�������");
				InputStreamReader isr2 = new InputStreamReader(System.in);
				BufferedReader br2 = new BufferedReader(isr2);
				String buf2 = br2.readLine();
				
				// �^�C�g��
				String sql0 = "select �A�j��.�^�C�g�� from �A�j��"+ sqlC +" where "+ sqlB +"= '" + buf2 +"'"+ sqlA;
				List<String> titles = new ArrayList<String>();
				ResultSet rs0 = stm.executeQuery(sql0);
				while(rs0.next()){
					String title = rs0.getString("�^�C�g��");
					titles.add(title);
					//System.out.println("\t" + title);
				}
				
				if(buf1==1){
					for(String title : titles) {
					
						System.out.println("\n----------------------------------------\n");
						System.out.println("�^�C�g���F" + title);
						
						// �W������
						String sql5 = "";
						if(buf1 == 2){
							sql5 = "select �W������.�W�������� from �A�j��,������,�W������ where �A�j��.��iID=������.��iID and ������.�W��������=�W������.�W�������� and "+ sqlB +"= '"+ buf2 +"'"+ sqlA;
							
						}else{
							sql5 = "select �W������.�W�������� from �A�j��,������,�W������"+ sqlC +"where �A�j��.��iID=������.��iID and ������.�W��������=�W������.�W�������� and "+ sqlB +"= '"+ buf2 +"'"+ sqlA;
						}
						//System.out.println(sql5);
						ResultSet rs5 = stm.executeQuery(sql5);
						System.out.println("�W�������F");
						while(rs5.next()){
							String genre = rs5.getString("�W��������");
							System.out.println("\t" + genre);
						}
							
						// ����
						String sql6 = "select ����^�C�g�� from �A�j��,����"+ sqlC +" where �A�j��.����ID=����.����ID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA;
						//System.out.println(sql6);
						ResultSet rs6 = stm.executeQuery(sql6);
						System.out.println("����F");
						while(rs6.next()){
							String original = rs6.getString("����^�C�g��");
							System.out.println("\t" + original);
						}
						
						// �L�����N�^�[
						String sql1 = "select ���O,�L�����N�^�[�� from �A�j��,�o��,���D"+ sqlC +" where �A�j��.��iID=�o��.��iID and �o��.���DID=���D.���DID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA;
						ResultSet rs1 = stm.executeQuery(sql1);
						System.out.println("�L�����N�^�[�F");
						while(rs1.next()){
							String name = rs1.getString("���O");
							String caracter = rs1.getString("�L�����N�^�[��");
							System.out.println("\t" + caracter + " (CV:" + name + ")");
						}
						
						// ������
						String sql2 = "select ��Ж� from �A�j��,����,������"+ sqlC +" where �A�j��.��iID=����.��iID and ������.������ID=����.������ID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA;
						ResultSet rs2 = stm.executeQuery(sql2);
						System.out.println("����F");
						while(rs2.next()){
							String campany = rs2.getString("��Ж�");
							System.out.println("\t" + campany);
						}
						
						// ����X�^�b�t
						String sql3 = "select ����,��E from �A�j��,����,������,�X�^�b�t"+ sqlC +" where �A�j��.��iID=����.��iID and ����.������ID=������.������ID and �X�^�b�t.������ID=������.������ID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA;
						ResultSet rs3 = stm.executeQuery(sql3);
						System.out.println("����X�^�b�t�F");
						while(rs3.next()){
							String position = rs3.getString("��E");
							String staff = rs3.getString("����");
							System.out.println("\t" + position + " : " + staff);
						}
						
						// ������
						String sql4 = "select �ǖ� from �A�j��,����,������"+ sqlC +" where �A�j��.��iID=����.��iID and ����.������ID=������.������ID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA;
						ResultSet rs4 = stm.executeQuery(sql4);
						System.out.println("�����ǁF");
						while(rs4.next()){
							String broadcaster = rs4.getString("�ǖ�");
							System.out.println("\t" + broadcaster);
						}
					}
				}else if(buf1 == 2){
					
					for(String title : titles) {
						
						System.out.println("\n----------------------------------------\n");
						System.out.println("�^�C�g���F" + title);
						
						String current_title = title;
					
						// �W������
						String sql5 = "select �W������.�W�������� from �A�j��,������,�W������ where �A�j��.��iID=������.��iID and ������.�W��������=�W������.�W�������� and "+ sqlB +"= '"+ buf2 +"'"+ sqlA + " and �A�j��.�^�C�g�� ='" + current_title +"'";
						//System.out.println(sql5);
						ResultSet rs5 = stm.executeQuery(sql5);
						System.out.println("�W�������F");
						while(rs5.next()){
							String genre = rs5.getString("�W��������");
							System.out.println("\t" + genre);
						}
						
						// ����
						String sql6 = "select ����^�C�g�� from �A�j��,����,������,�W������ where �A�j��.����ID=����.����ID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA + " and �A�j��.�^�C�g�� ='" + current_title +"'";
						//System.out.println(sql6);
						ResultSet rs6 = stm.executeQuery(sql6);
						System.out.println("����F");
						while(rs6.next()){
							String original = rs6.getString("����^�C�g��");
							System.out.println("\t" + original);
						}
						
						// �L�����N�^�[
						String sql1 = "select ���O,�L�����N�^�[�� from �A�j��,�o��,���D,������,�W������ where �A�j��.��iID=�o��.��iID and �o��.���DID=���D.���DID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA + " and �A�j��.�^�C�g�� ='" + current_title +"'";
						ResultSet rs1 = stm.executeQuery(sql1);
						System.out.println("�L�����N�^�[�F");
						while(rs1.next()){
							String name = rs1.getString("���O");
							String caracter = rs1.getString("�L�����N�^�[��");
							System.out.println("\t" + caracter + " (CV:" + name + ")");
						}
						
						// ������
						String sql2 = "select ��Ж� from �A�j��,����,������,������,�W������ where �A�j��.��iID=����.��iID and ������.������ID=����.������ID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA + " and �A�j��.�^�C�g�� ='" + current_title +"'";
						ResultSet rs2 = stm.executeQuery(sql2);
						System.out.println("����F");
						while(rs2.next()){
							String campany = rs2.getString("��Ж�");
							System.out.println("\t" + campany);
						}
						
						// ����X�^�b�t
						String sql3 = "select ����,��E from �A�j��,����,������,�X�^�b�t,������,�W������ where �A�j��.��iID=����.��iID and ����.������ID=������.������ID and �X�^�b�t.������ID=������.������ID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA + " and �A�j��.�^�C�g�� ='" + current_title +"'";
						ResultSet rs3 = stm.executeQuery(sql3);
						System.out.println("����X�^�b�t�F");
						while(rs3.next()){
							String position = rs3.getString("��E");
							String staff = rs3.getString("����");
							System.out.println("\t" + position + " : " + staff);
						}
						
						// ������
						String sql4 = "select �ǖ� from �A�j��,����,������,������,�W������ where �A�j��.��iID=����.��iID and ����.������ID=������.������ID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA + " and �A�j��.�^�C�g�� ='" + current_title +"'";
						ResultSet rs4 = stm.executeQuery(sql4);
						System.out.println("�����ǁF");
						while(rs4.next()){
							String broadcaster = rs4.getString("�ǖ�");
							System.out.println("\t" + broadcaster);
						}
					}
				}else if(buf1 == 3){
					
					for(String title : titles) {
						
						System.out.println("\n----------------------------------------\n");
						System.out.println("�^�C�g���F" + title);
						
						String current_title = title;
					
						// �W������
						String sql5 = "select �W������.�W�������� from �A�j��,������,�W������,�o��,���D where �A�j��.��iID=������.��iID and ������.�W��������=�W������.�W�������� and "+ sqlB +"= '"+ buf2 +"'"+ sqlA + " and �A�j��.�^�C�g�� ='" + current_title +"'";
						//System.out.println(sql5);
						ResultSet rs5 = stm.executeQuery(sql5);
						System.out.println("�W�������F");
						while(rs5.next()){
							String genre = rs5.getString("�W��������");
							System.out.println("\t" + genre);
						}
						
						// ����
						String sql6 = "select ����^�C�g�� from �A�j��,����,�o��,���D where �A�j��.����ID=����.����ID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA + " and �A�j��.�^�C�g�� ='" + current_title +"'";
						//System.out.println(sql6);
						ResultSet rs6 = stm.executeQuery(sql6);
						System.out.println("����F");
						while(rs6.next()){
							String original = rs6.getString("����^�C�g��");
							System.out.println("\t" + original);
						}
						
						// �L�����N�^�[
						String sql1 = "select ���O,�L�����N�^�[�� from �A�j��,�o��,���D where �A�j��.��iID=�o��.��iID and �o��.���DID=���D.���DID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA + " and �A�j��.�^�C�g�� ='" + current_title +"'";
						System.out.println(sql5);
						ResultSet rs1 = stm.executeQuery(sql1);
						System.out.println("�L�����N�^�[�F");
						while(rs1.next()){
							String name = rs1.getString("���O");
							String caracter = rs1.getString("�L�����N�^�[��");
							System.out.println("\t" + caracter + " (CV:" + name + ")");
						}
						
						// ������
						String sql2 = "select ��Ж� from �A�j��,����,������,�o��,���D where �A�j��.��iID=����.��iID and ������.������ID=����.������ID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA + " and �A�j��.�^�C�g�� ='" + current_title +"'";
						ResultSet rs2 = stm.executeQuery(sql2);
						System.out.println("����F");
						while(rs2.next()){
							String campany = rs2.getString("��Ж�");
							System.out.println("\t" + campany);
						}
						
						// ����X�^�b�t
						String sql3 = "select ����,��E from �A�j��,����,������,�X�^�b�t,�o��,���D where �A�j��.��iID=����.��iID and ����.������ID=������.������ID and �X�^�b�t.������ID=������.������ID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA + " and �A�j��.�^�C�g�� ='" + current_title +"'";
						ResultSet rs3 = stm.executeQuery(sql3);
						System.out.println("����X�^�b�t�F");
						while(rs3.next()){
							String position = rs3.getString("��E");
							String staff = rs3.getString("����");
							System.out.println("\t" + position + " : " + staff);
						}
						
						// ������
						String sql4 = "select �ǖ� from �A�j��,����,������,�o��,���D where �A�j��.��iID=����.��iID and ����.������ID=������.������ID and "+ sqlB +"= '"+ buf2 +"'"+ sqlA + " and �A�j��.�^�C�g�� ='" + current_title +"'";
						ResultSet rs4 = stm.executeQuery(sql4);
						System.out.println("�����ǁF");
						while(rs4.next()){
							String broadcaster = rs4.getString("�ǖ�");
							System.out.println("\t" + broadcaster);
						}
					}
				}
				else
					System.out.println("�ԍ����s���ł�");
			} catch (IOException e) {
				System.out.println("IO Error: " + e.toString() + e.getMessage());
			} catch (Exception e) {
				System.out.println("Error: " + e.toString() + e.getMessage());
			}
		} catch (SQLException se) {
			System.out.println("SQL Error 1 : " + se.toString() + " "
				+ se.getErrorCode() + " " + se.getSQLState());
		} finally {
			if (con != null) {
				try {
					con.close();
				} catch (SQLException e) {
					System.out.println("MySQL�̃N���[�Y�Ɏ��s���܂����B");
				}
			}
		}
	}
}
