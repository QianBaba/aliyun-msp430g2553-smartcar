package smartcar;

import java.sql.Connection;
import java.sql.Statement;
import java.sql.ResultSet;
public class Login extends DBMessage {

	public Boolean user_validate (String... userInf)throws Exception
	{
		Connection conn=this.ConnectDB();
		Boolean val_result=false;
		ResultSet rs=null;
		String sql="SELECT phone,password FROM user";
		Statement st=conn.createStatement();
		rs=st.executeQuery(sql);
		while(rs.next()){
			String ph=rs.getString("phone");
			String pa=rs.getString("password");
			if(userInf[0].equals(ph)&&userInf[1].equals(pa)){
				val_result=true;
				break;
			}
		}
		rs.close();
		st.close();
		conn.close();
		return val_result;
	}

}