package com.sf.db;

/**
 *数据源选择
 */
public class DataSourceSwitch{
	private static final ThreadLocal<String> contextHolder=new ThreadLocal<String>();
	
	public static void setDataSourceType(String dataSourceType){
		contextHolder.set(dataSourceType);
	}
	
	public static String getDataSourceType(){
		return (String) contextHolder.get();
	}
	
	public static void clearDataSourceType(){
		contextHolder.remove();
	}
}
