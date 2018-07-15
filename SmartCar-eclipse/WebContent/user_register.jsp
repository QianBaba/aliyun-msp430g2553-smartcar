<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
	
<%@ page import="smartcar.*" %>
<!DOCTYPE html>
<html>
	<head>
		
		<meta charset="utf-8" />
		
		<title>用户注册</title>
	</head>
	<body>
	
	<%
		request.setCharacterEncoding("utf-8"); //注释:设置编码方式为utf-8
		String name = request.getParameter("user_name");
		String phone = request.getParameter("user_phone");
		String password = request.getParameter("user_password");
		
		Register reg=new Register();
		Boolean val=reg.user_save(name,phone,password);
		String message = String.valueOf(val);
		response.setContentType("text/html;charset=utf-8");
		response.getWriter().write(message);
	%>
	</body>
</html>