/**
 * 
 */
package com.sf.util;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.util.Enumeration;
import java.util.Properties;

import org.apache.log4j.Logger;


/**
 * @author liuqing
 */
public abstract class PropertiesConfig implements Configurable {

	protected Properties prop=new Properties();
	
	private static Logger logger = Logger.getLogger(PropertiesConfig.class);
	public Boolean isLoaded=new Boolean(false);

	public void load(InputStream fis) {
		synchronized (isLoaded) {
			if(isLoaded){
				return;
			}
			try {
				if(fis!=null){
					Reader reader=new InputStreamReader(fis,"UTF-8");
					prop.load(reader);
				}
			} catch (IOException e) {
				logger.error("load properties config file error", e);
			}finally{
				try {
					if(fis!=null)
						fis.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			isLoaded=new Boolean(true);
		}
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see com.moloon.sonny.app.Configurable#getConfig(java.lang.String)
	 */
	public String getConfig(String key) {
		return prop.getProperty(key);

	}
	@SuppressWarnings("rawtypes")
	public String toString(){
		StringBuffer sb = new StringBuffer();
		Enumeration e = prop.keys();
		while(e.hasMoreElements())
		{
			String key = (String)e.nextElement();
			String value = (String)prop.get(key);
			sb.append("{"+key+"="+value+"}");
		}
		return sb.toString();
	}
}
