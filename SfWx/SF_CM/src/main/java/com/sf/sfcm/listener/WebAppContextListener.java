package com.sf.sfcm.listener;

import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;
import javax.servlet.annotation.WebListener;

import org.springframework.web.context.support.WebApplicationContextUtils;

import com.sf.sfcm.logger.SFLogger;
import com.sf.sfcm.util.Const;


@WebListener
public class WebAppContextListener implements ServletContextListener {

	@Override
	public void contextDestroyed(ServletContextEvent event) {
		
	}
	@Override
	public void contextInitialized(ServletContextEvent event) {
		SFLogger.info("*********************WebAppContextListener contextInitialized.********************");
		Const.WEB_APP_CONTEXT = WebApplicationContextUtils.getWebApplicationContext(event.getServletContext());
	}

}
