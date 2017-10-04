package com.sf.sfcm.util;

import org.springframework.context.ApplicationContext;

public class Const {
	
	public static ApplicationContext WEB_APP_CONTEXT = null; // 该值会在web容器启动时由WebAppContextListener初始化

	public static Object getApplicationContextBean(String name){
		return WEB_APP_CONTEXT.getBean(name);
	}
	
	public static final String PACKETS_DATATYPE = "DATATYPE";

}
