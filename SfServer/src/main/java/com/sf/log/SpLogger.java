package com.sf.log;

import java.io.PrintWriter;
import java.io.StringWriter;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.apache.log4j.Logger;

import com.sf.util.StringUtil;


public class SpLogger {
	static Logger logger = Logger.getLogger(SpLogger.class);

	public static void debug( Object message, Object param) {
		if (logger.isDebugEnabled()) {
			String paramStr=ingnoreSpaceKey(param);
			message = fillLoggerMsg( message, paramStr);
			logger.debug(message);
		}
	}
	public static void debug( Object message) {
		if (logger.isDebugEnabled()) {
			message = fillLoggerMsg( message, "");
			logger.debug(message);
		}
	}

	public static void info( Object message) {
		if (logger.isInfoEnabled()) {
			message = fillLoggerMsg( message, "");
			logger.info(message);
		}
	}

	public static void info( Object message,
			Throwable t) {
		if (logger.isInfoEnabled()) {
			message = fillLoggerMsg( message, "", t);
			logger.info(message);
		}

	}

	public static void warn( Object message) {
		message = fillLoggerMsg( message, "");
		logger.warn(message);
	}

	public static void warn( Object message, 
			Throwable t) {
		message = fillLoggerMsg( message, "", t);
		logger.warn(message);
	}

	public static void error( Object message,Throwable t, Object param) {
		String paramStr=ingnoreSpaceKey(param);
		message = fillLoggerMsg( message, paramStr,t);
		logger.error(message);
	}

	public static void error( Object message,
			Throwable t) {
		message = fillLoggerMsg( message, "", t);
		logger.error(message);
	}
	public static void error( Object message) {
		message = fillLoggerMsg( message, "");
		logger.error(message);
	}
	public static void fatal( Object message) {
		message = fillLoggerMsg( message, "");
		logger.fatal(message);
	}

	public static void fatal( Object message,
			Throwable t) {
		message = fillLoggerMsg( message, "", t);
		logger.fatal(message);
	}

	private static String fillLoggerMsg( Object msg,
			String param, Throwable t) {
		StringWriter sw = new StringWriter();
		PrintWriter pw = new PrintWriter(sw);
		t.printStackTrace(pw);
		String errorMsg = sw.toString();
		msg = msg + " "+errorMsg;
		String chat = "[%s:%s][%s][%s]";
		StackTraceElement author = new Throwable().getStackTrace()[2];
		String className = author.getClassName();// 文件名
		String[] fileNames=author.getFileName().split("\\.");
		className+="."+fileNames[fileNames.length-1];
		int lineNum = author.getLineNumber();
		return String.format(chat, className, lineNum , msg,
				param);
	}
	private static String ingnoreSpaceKey( Object param){
		String paramStr=StringUtil.toJsonString(param);
		String[] ingroneStr={"pwd","password"};
		if(ingroneStr!=null&&ingroneStr.length>0){
		    StringBuilder result=new StringBuilder();
	        boolean flag=false;
	        for (String string : ingroneStr) {
	            if (flag) {
	                result.append("|");
	            }else {
	                flag=true;
	            }
	            result.append(string);
	        }
		    String reg=String.format("[,]?['|\"][^,]*(%s)[^,]*['|\"]:['|\"].*?['|\"][,]?",result.toString());
			Pattern p=Pattern.compile(reg);  
			Matcher m=p.matcher(paramStr);   
			while(m.find()){   
				String _temp=m.group();
				paramStr=paramStr.replace(_temp, "");
			}
		}
		return (paramStr);
	}
	private static String fillLoggerMsg( Object msg, String param) {
		String chat = "[%s:%s][%s][%s]";
		StackTraceElement author = new Throwable().getStackTrace()[2];
		String className = author.getClassName();// 文件名
		String[] fileNames=author.getFileName().split("\\.");
		className+="."+fileNames[fileNames.length-1];
		int lineNum = author.getLineNumber();
		return String.format(chat, className, lineNum , msg,
				param);
	}

}
