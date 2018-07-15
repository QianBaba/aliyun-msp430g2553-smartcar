package com.servlet;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import smartcar.ImgSave;

/**
 * Servlet implementation class ServletLogin
 */
//@WebServlet("/ServletLogin")
@SuppressWarnings("serial")
public class ImgProgram extends HttpServlet {

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		response.getWriter().append("Served at: ").append(request.getContextPath());
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		try {
			
			request.setCharacterEncoding("utf-8");					//���ñ����ʽΪutf-8	
			String url = request.getParameter("img_url");
			String name = request.getParameter("img_name");
			String message= new ImgSave().save(url, name);
			//System.out.println(5+":"+message);
			response.setContentType("text/html;charset=utf-8");	//������Ӧͷ������
			response.getWriter().write(message);					//������Ӧ��Ϣ
		} catch (Exception e) {
			e.printStackTrace();
		}
		
	}

}

