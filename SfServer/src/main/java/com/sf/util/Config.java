package com.sf.util;

import java.util.Properties;


/**
 * 读取项目conf文件属性.
 *
 */
public class Config extends PropertiesConfig{
	private static final String SYSTEMID="systemID";
	public static Config config	= null;
	private Properties properties = null;
	
	private Config() {
		init();
	}
	
	public void init(){
		try{
			properties = PropertiesUtil.getProperties("/config.properties");
			
		}catch (Exception e){
			throw new RuntimeException("Failed to get properties!");
		}
	}
	
	public static Config getInstance() {
		
		if (config == null) {
			config = new Config();
		}
		return config;
	}
	
	public String getSystemID(){
		String systemId = properties.getProperty(SYSTEMID);
		if(systemId==null){
			systemId="";
		}
		return systemId;
	}
	
	public String getValue(String key) {
		return properties.getProperty(key);
	}
	
	public Properties getProperties() {
		return properties;
	}
}
