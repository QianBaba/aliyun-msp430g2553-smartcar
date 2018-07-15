package smartcar;

import java.sql.Connection;
import java.sql.Statement;
public class Register extends DBMessage{
	
	public Boolean user_save (String... userInf)throws Exception
	{
		Connection conn=this.ConnectDB();
		String sql="INSERT INTO user(name,phone,password)"
				+" VALUES ('"+userInf[0]+"','"+userInf[1]+"','"+userInf[2]+"')";
		Statement st=conn.createStatement();
		Boolean b=false;
		st.executeUpdate(sql);
		st.close();
		conn.close();
		b=true;
		return b;
	}
}
