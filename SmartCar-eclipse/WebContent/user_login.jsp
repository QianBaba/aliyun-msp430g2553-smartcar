<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
	
<%@ page import="smartcar.*" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>用户登录</title>
</head>
<body>
<%
	String phone = request.getParameter("user_phone");
	String password = request.getParameter("user_password");
	
	Login login=new Login();
	Boolean validate= login.user_validate(phone,password);
	String message = String.valueOf(validate);
	response.setContentType("text/html;charset=utf-8");
	response.getWriter().write(message);
%>
</body>
</html>