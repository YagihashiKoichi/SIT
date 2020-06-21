import java.sql.*;
import java.io.*;

public class Sample {
	public static void main(String[] args) {
		Connection con = null;
		try {
		    // DB�ɐڑ�����
			con = DriverManager.getConnection(
				"jdbc:mysql://localhost/cy16137?useSSL=false", "root", "SITmeDB"
				);
			// System.out.println("MySQL�ɐڑ��ł��܂����B");

			// Statement�����
			Statement stm = con.createStatement();
			
			
			try{
				int x;
				System.out.println("�i������͂��Ă��������F");//�e�X�g�p�uGoodnote�v
				InputStreamReader isr = new InputStreamReader(System.in);
				BufferedReader br = new BufferedReader(isr);
				String buf = br.readLine();
				// ���s����SQL�𕶎���(String)�ɂ���
				String sql = "SELECT shop.ID, shop.name FROM product, shop, sales WHERE product.name='" + buf + "' AND product.ID=sales.productID AND sales.shopID=shop.ID";

				// SQL�����s���āA���s���ʂ�ResultSet�ɓ����
				ResultSet rs = stm.executeQuery(sql);

				// ���ʂ��P�s�����āA�K�v�ȏ���(�����ł͕\��)������
				while(rs.next()){
					int id = rs.getInt("shop.ID");
					String name = rs.getString("shop.name");
					System.out.println("�擾���� -> " + id + ":" + name);
				}
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
