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
	request.setCharacterEncoding("utf-8");					//设置编码格式为utf-8	
	String url = request.getParameter("img_url");
	String name = request.getParameter("img_name");
	String message= new ImgSave().save(url, name);
	//System.out.println(5+":"+message);
	response.setContentType("text/html;charset=utf-8");	//设置响应头部内容
	response.getWriter().write(message);					//返回响应信息
%>
</body>
</html>