package smartcar;

import sun.misc.BASE64Decoder;
import java.io.*;
public class ImgSave 
{
	public String  save(String url,String name)
			throws Exception
	{
		BASE64Decoder decoder = new BASE64Decoder();
		String data_url=url.replace(" ", "+");
		String path = "/usr/java/tomcat/apache-tomcat-9.0.8/webapps/SmartCar/camera/"+name; //获取绝对路径
		byte[] b = decoder.decodeBuffer(data_url);//转码得到图片数据
		OutputStream out = new FileOutputStream(path);
		out.write(b);
		out.flush();
		out.close();
		//System.out.println(1+":"+url+":"+name);
		String s = AliyunOSSClientUtil.init(path,name);
		//System.out.println(2+":"+s);
		return s;

	}
}

	