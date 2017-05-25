package com.sf.util;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

/**
 * @ProjectName:HUIPU_CM
 * @Package:com.huipu.common.util
 * @ClassName: PropertiesUtil
 * @Description:解析Properties文件
 * @Version:v1.0
 */
public class PropertiesUtil {
	/**
	 * @Title: getConfig
	 * @Description: 读取config.properties配置文件中的信息，根据key得到对应的value
	 * @param String
	 * @see
	 */
	public static String getConfigProp(String key) {
		return getProperty(key,"/config.properties");
	}
	/**
	 * @Description:根据key和properties获取值
	 * @param key
	 * @param propertiesName
	 */
	public static String getProperty(String key,String propertiesName){
		Properties p = new Properties();
		InputStream in = PropertiesUtil.class.getResourceAsStream(propertiesName);
		try {
			p.load(in);
			in.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		if (p.containsKey(key)) {
			return p.getProperty(key);
		}
		return "";
	}
	public static Properties getProperties(String filePath){
		Properties p = new Properties();
		InputStream in = PropertiesUtil.class.getResourceAsStream(filePath);
		try {
			p.load(in);
			in.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return p;
	}
}
