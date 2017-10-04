package com.sf.sfcm.util;
import java.lang.reflect.Array;
import java.lang.reflect.Method;
import java.math.BigDecimal;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;




/**
 * 转换工具类，支持反射的方式将对象转换为Map，将数组和Collection转换为List供XStrem使用
 */
@SuppressWarnings("rawtypes")
public class ObjMapListUtil {

    private static ObjMapListUtil instance = null;

    static public Object toHashMap(Object obj){
        return toHashMap(obj, false);
    }
    
    static public Object toHashMap(Object obj, boolean useClassConvert){
        if(instance == null){
            instance = new ObjMapListUtil();
        }
        return instance.getMapListObject(obj, useClassConvert);
    }

    /**
     * 代理类是否输出的检查，返回true则允许继续转换
     * @param bean
     * @return
     */
    protected boolean canProxyOutput(Object bean) {
        return true;
    }

    /**
     * 代理类时做的检查.返回应该检查的对象.
     * @param bean
     * @return
     */
    protected Object proxyConvert(Object bean){
        return bean;
    }

    public Object getMapListObject(Object bean, boolean useClassConvert){
        if(bean == null){
            return null;
        }
        bean = proxyConvert(bean);
		Class clazz = bean.getClass();
        if(bean instanceof Number || bean instanceof Boolean || bean instanceof String || bean instanceof BigDecimal){
            return bean;
        }
        if(bean instanceof Date){
        	DateFormat formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        	String val = formatter.format((Date)bean);
        	return val;
        }
        if(clazz.isArray()){
            ArrayList<Object> arrayList = new ArrayList<Object>();
            int arrayLength = Array.getLength(bean);
            for(int i = 0; i < arrayLength; i ++){
                Object rowObj = Array.get(bean, i);
                if(canProxyOutput(rowObj)){
                    arrayList.add(getMapListObject(rowObj, useClassConvert));
                }
            }
            return arrayList;
        }
        if(bean instanceof Collection){
            ArrayList<Object> arrayList = new ArrayList<Object>();
            Iterator iterator = ((Collection)bean).iterator();
            while(iterator.hasNext()){
                Object rowObj = iterator.next();
                if(canProxyOutput(rowObj)){
                    arrayList.add(getMapListObject(rowObj, useClassConvert));
                }
            }
            return arrayList;
        }
        if(bean instanceof Map){
            HashMap<String, Object> beanMap = new HashMap<String, Object>();
            Map map = (Map)bean;
            Iterator iterator = map.keySet().iterator();
            while(iterator.hasNext()){
                Object key = iterator.next();
                Object rowObj = map.get(key);
                if(canProxyOutput(rowObj)){
                    beanMap.put(key.toString(), getMapListObject(rowObj, useClassConvert));
                }
                beanMap.put(Const.PACKETS_DATATYPE, "MAP");
            }
            return beanMap;
        }

        HashMap<String, Object> beanMap = new HashMap<String, Object>();
        Class klass = bean.getClass();
        Method[] methods = klass.getMethods();
        for (int i = 0; i < methods.length; i ++) {
            try {
                Method method = methods[i];
                String name = method.getName();
                String key = "";
                if (name.startsWith("get")) {
                    key = name.substring(3);
                } else if (name.startsWith("is")) {
                    key = name.substring(2);
                }
                if (key.length() > 0 &&Character.isUpperCase(key.charAt(0)) && method.getParameterTypes().length == 0) {
                    if (key.length() == 1) {
                        key = key.toLowerCase();
                    } else if (!Character.isUpperCase(key.charAt(1))) {
                        key = key.substring(0, 1).toLowerCase() + key.substring(1);
                    }
                    Object elementObj = method.invoke(bean);
                    if(elementObj instanceof Class){
                        if(useClassConvert){
                            beanMap.put(key, elementObj.toString());
                        }
                    }else{
                        if(canProxyOutput(elementObj)){
                            beanMap.put(key, getMapListObject(elementObj, useClassConvert));
                        }
                    }
                }
            } catch (Exception e) {
            }
        }
        return beanMap;
    }
}