package com.sf.sfcm.util;

import java.beans.BeanInfo;
import java.beans.Introspector;
import java.beans.PropertyDescriptor;
import java.lang.reflect.Field;
import java.lang.reflect.ParameterizedType;
import java.lang.reflect.Type;
import java.math.BigDecimal;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

import org.dom4j.Element;
import org.dom4j.Node;


/**
 * BeanUtil.
 *
 */
public class BeanUtil {
	/**
	 * 将一个 Map 对象转化为一个 JavaBean.
	 * @param type 要转化的类型
	 * @param map 包含属性值的 map
	 * @return 转化出来的 JavaBean 对象
	 */
	@SuppressWarnings("rawtypes")
	public static <T> Object Map2Bean(Class<T> type, Map<String, Object> map) {
		if(null==map || map.size()<=0){
			return null;
		}
		BeanInfo bean = null;
		Object obj = null;
		try {
			bean = Introspector.getBeanInfo(type);
			obj = type.newInstance();
		} catch (Exception e) {
			e.printStackTrace();
		}
		/** 遍历bean中所有属性，并赋值 **/
		PropertyDescriptor[] propertyDescriptors = bean.getPropertyDescriptors();
		for (int i = 0; i < propertyDescriptors.length; i++) {
			PropertyDescriptor descriptor = propertyDescriptors[i];
			String propertyName = descriptor.getName();
			/** 设置bean属性和extends Bean属性值 **/
			Set<String> keys = map.keySet();
			Object beanFieldValue = null;
			for (Iterator<String> it = keys.iterator(); it.hasNext();) {
				String key = it.next();
				Object value = map.get(key);
				if (key.toLowerCase().equals(propertyName.toLowerCase())) {
					/** 判断是否引用其他Bean **/
					if(descriptor.getPropertyType().toString().indexOf("com.huipu.") != -1) {
						/** 为bean中引用的Bean赋值 **/
						/** 为bean中引用的Bean赋值 **/
						Object sonBean = null;
						if(value instanceof List){
							List<Map<String,Object>> list = (List<Map<String,Object>>)value;
							sonBean = Map2Bean(descriptor.getPropertyType(), list.get(0));
						}else if(value instanceof Map){
							Map<String,Object> MapObj = (Map<String,Object>)value;
							sonBean = Map2Bean(descriptor.getPropertyType(), MapObj);
						}
						beanFieldValue = sonBean;
					} else {
						if(value instanceof List){
							List<Map<String,Object>> list = (List<Map<String,Object>>)value;
							List<Object> listValue = new ArrayList<Object>();;
							Class genericClass = getSonClass(obj.getClass(),propertyName);
							for(Map<String,Object> s:list){
								listValue.add(Map2Bean(genericClass, s));
							}
							beanFieldValue = listValue;
						}else{
							if (!StringUtil.isEmpty(value)) {
								if (java.util.Date.class.getName().equals(descriptor.getPropertyType().getName())){
									beanFieldValue= DateUtil.formatStrToDateByLength(value.toString());
								}else if(java.math.BigDecimal.class.getName().equals(descriptor.getPropertyType().getName())){
									BigDecimal bigRate =new BigDecimal(value.toString()); 
									beanFieldValue= bigRate;
								}else if(Integer.class.getName().equals(descriptor.getPropertyType().getName()) || descriptor.getPropertyType().getName().equalsIgnoreCase("int")){
									int intVal = Integer.valueOf(value.toString()).intValue();
									beanFieldValue= intVal;
								}else if(Double.class.getName().equals(descriptor.getPropertyType().getName())){
									double doubleV = Double.parseDouble(value.toString());//Double.valueOf(value.toString()).intValue();
									beanFieldValue= doubleV;
								}else if(long.class.getName().equals(descriptor.getPropertyType().getName())||Long.class.getName().equals(descriptor.getPropertyType().getName())){
									long longV = Long.valueOf(value.toString()).longValue();
									beanFieldValue= longV;
								}else if("byte".equals(descriptor.getPropertyType().getName())){
									byte byteV =  Byte.valueOf(value.toString());
									beanFieldValue= byteV;
								}else if(String.class.getName().equals(descriptor.getPropertyType().getName())){
									beanFieldValue = String.valueOf(value);
								}else{
									beanFieldValue = value;
								}
							}else{
								beanFieldValue = value;
							}
						}
					}
					try {
						if (null!=beanFieldValue && !"".equals(beanFieldValue.toString())) {
							descriptor.getWriteMethod().invoke(obj, beanFieldValue);
						}
					} catch (Exception e) {
						System.out.println(obj.getClass()+"=============="+beanFieldValue.toString());
						e.printStackTrace();
					}
				}
			}
		}
		return obj;
	}
	@SuppressWarnings("rawtypes")
	public static Class getSonClass(Class clazz,String fieldName){
		Field[] fs = clazz.getDeclaredFields();
		for(Field f:fs){
			if(fieldName.equals(f.getName())){
				Class fieldClass = f.getType();
				if(fieldClass.isAssignableFrom(List.class)){
					Type fc = f.getGenericType();
					if(null!=fc && (fc instanceof ParameterizedType)){
						ParameterizedType pt = (ParameterizedType)fc;
						Class genericClass = (Class)pt.getActualTypeArguments()[0];
						return genericClass;
						}
					} else {
						return fieldClass;
					}
				}
			}
		return null;
	}
	
	/**
	 * @Title:listMap2listBean
	 * @Description:list<Map> 2 list<Bean>
	 * @param type
	 * @param listMap
	 */
	public static <T> List<Object> listMap2listBean(Class<T> type, List<Map<String, Object>> listMap) {
		List<Object> list = new ArrayList<Object>();
		for (Map<String, Object> map : listMap) {
			Object obj = Map2Bean(type, map);
			if(null!=obj){
				list.add(Map2Bean(type, map));
			}
		}
		return list;
	}

	/**
	 * 将一个 JavaBean 对象转化为一个 Map.
	 * @param bean 要转化的JavaBean 对象
	 * @return 转化出来的 Map 对象
	 */
	public static Map<String, Object> Bean2Map(Object bean) {
		return Bean2Map(bean, false);
	}

	/**
	 * 将一个 JavaBean 对象转化为一个 Map.
	 * 
	 * @param bean 要转化的JavaBean 对象
	 * @param page 是否有分页
	 * @return 转化出来的 Map 对象
	 */
	public static Map<String, Object> Bean2Map(Object bean, boolean page) {
		if (bean instanceof Map) {
			return (Map<String, Object>) bean;
		}
		if (null == bean) {
			return new HashMap<String, Object>();
		}
		Map<String, Object> map = new HashMap<String, Object>();

		map = (Map<String, Object>) ObjMapListUtil.toHashMap(bean);
		if (page) {
			Object page_control = null;
			Object showCount = null;
			Object currentPage = null;
			try {
				page_control = ReflectHelper.getValueByFieldName(bean, "page_control");
			} catch (Exception e) {
			}
			try {
				showCount = ReflectHelper.getValueByFieldName(bean, "showCount");
			} catch (Exception e) {
			}
			try {
				currentPage = ReflectHelper.getValueByFieldName(bean, "currentPage");
			} catch (Exception e) {
			}
			map.put("PAGE_CONTROL", page_control == null ? "1" : page_control);
			map.put("SHOWCOUNT", showCount == null ? "10" : showCount);
			map.put("CURRENTPAGE", currentPage == null ? "1" : currentPage);
		}
		return map;
	}
	public static Map<String ,Object> MapKeyToUpperCase(Map<String, Object> param) {
		Map<String, Object> paramUP = new HashMap<String, Object>();
		Set<?> set = param.entrySet();         
		Iterator<?> i = set.iterator();         
		while(i.hasNext()){
		     Map.Entry<String, Object> entry=(Map.Entry<String, Object>)i.next();
		     if(!paramUP.containsKey(entry.getKey().toUpperCase())){
			     paramUP.put(entry.getKey().toUpperCase(), entry.getValue());
		     }else{
		    	 if(StringUtil.isNotEmpty(entry.getValue())){
		    		paramUP.put(entry.getKey().toUpperCase(), entry.getValue());
		    	 }
		     }
		}   
		return paramUP;
	}
	public static Map<String ,Object> MapKeyToLowerCase(Map<String, Object> param) {
		Map<String, Object> paramLO = new HashMap<String, Object>();
		Set<?> set = param.entrySet();         
		Iterator<?> i = set.iterator();         
		while(i.hasNext()){
		     Map.Entry<String, String> entry=(Map.Entry<String, String>)i.next();
		     if(!paramLO.containsKey(entry.getKey().toLowerCase())){
		    	 paramLO.put(entry.getKey().toLowerCase(), entry.getValue());
		     }else{
		    	 if(StringUtil.isNotEmpty(entry.getValue())){
		    		 paramLO.put(entry.getKey().toLowerCase(), entry.getValue());
		    	 }
		     }
		}   
		return paramLO;
	}
	/**
	 * 将 List<Bean> 对象转化为 List< Map>.
	 * 
	 * @param obj 要转化的List<Bean> 对象
	 * @return 转化出来的 List< Map>对象
	 */
	public static List<Object> ListBean2Map(List<Object> obj) {
		List<Object> list = new ArrayList<Object>();
		for (Object o : obj) {
			try {
				list.add(Bean2Map(o));
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		return list;
	}

	/**
	 * 将一个 JavaBean 对象转化为一个 Map.
	 * 
	 * @param bean 要转化的JavaBean 对象
	 * @return 转化出来的 Map 对象
	 */
    @SuppressWarnings("rawtypes")
	public static <T> Object Xml2Bean(Class<T> type, Element element) {
		BeanInfo beanInfo = null;
		Object obj = null;
		try {
			beanInfo = Introspector.getBeanInfo(type);
			obj = type.newInstance();
		} catch (Exception e) {
			e.printStackTrace();
		}
		List<Element> elements = element.elements();
		PropertyDescriptor[] propertyDescriptors = beanInfo.getPropertyDescriptors();
		for (int i = 0; i < propertyDescriptors.length; i++) {
			PropertyDescriptor descriptor = propertyDescriptors[i];
			String propertyName = descriptor.getName();
			for (Element e : elements) {
				if (e.getName().toLowerCase().equals(propertyName.toLowerCase())) {
					Object[] args = new Object[1];
					Class t = descriptor.getPropertyType();
                    Object val = null;
                    if(t.isAssignableFrom(List.class)){
                        Class son = getSubType(type,propertyName);
                        if(!son.isAssignableFrom(String.class)){
	                    	List<Node> nodes = e.selectNodes("MAP");
	                    	val = setListObject(nodes,type,propertyName);
                        }else{
                        	val = StringUtil.setBeanValue(descriptor.getPropertyType(), e.getText());
                        }
                    } else {
                     	val = StringUtil.setBeanValue(descriptor.getPropertyType(), e.getText());
					}
					args[0] = val;
					try {
						descriptor.getWriteMethod().invoke(obj, args);
					} catch (Exception e1) {
						e1.printStackTrace();
					}
				}
			}
		}
		return obj;
	}

    /**
     * 获取List<Object>中Object的Class.
     */
    public static <T> Class<T> getSubType(Class<T> tClass,String fileName){
    	Class<T> tc = tClass;
    	Field[] fields = tc.getDeclaredFields();
    	Field field = null;
    	for (Field f : fields) {
    		if(f.getName().equals(fileName)){
    			field = f;
    			break;
    		}
    	}
    	if(null==field){
    		return null;
    	}
    	
    	Type gt = field.getGenericType();
    	if (gt.getClass().equals(String.class.getClass())) {
    		return (Class<T>)String.class;
    	}
    	ParameterizedType pt = (ParameterizedType)gt;
		Class<T> son = (Class<T>)pt.getActualTypeArguments()[0];
		return son;
    }
    
    @SuppressWarnings("rawtypes")
	public static <T> List<Object> setListObject(List<Node> nodes,Class<T> type,String fileName){
    	
		Class son = getSubType(type,fileName);
		if(null==son){
			return null;
		}
		if(son.isAssignableFrom(Map.class)){
			return Xml2ListMap(nodes);
		}else {
	    	return Xml2ListBean(nodes,son);
		}
	}
    
    public static <T> List<Object> Xml2ListMap(List<Node> nodes){
		List<Object> list = new ArrayList<Object>();
		 for (Node node : nodes) {
			if (node instanceof Element) {
				Element pEl = (Element) node;
				Map<String,String> map=new HashMap<String,String>();
				List<Element> elements = pEl.elements(); 
				for (Iterator<Element> it = elements.iterator(); it.hasNext();) { 
	                Element elem = it.next();
	                map.put(elem.getName(), elem.getText());
	            } 
				list.add(map);
			}
		 }
		return list;
	}
    
	public static <T> List<Object> Xml2ListBean(List<Node> nodes, Class<T> type) {
		List<Object> list = new ArrayList<Object>();
		for (Node node : nodes) {
			Element element = (Element) node;
			list.add(Xml2Bean(type, element));
		}
		return list;
	}
	public static byte[] ListInt2ByteArray(List<Integer> data){
		byte[] resultBytes=new byte[data.size()];
		for(int i=0;i<data.size();i++){
			int _temp=data.get(i);
			resultBytes[i]=(byte)_temp;
		}
		return resultBytes;
	}
	public static List<Integer> byteArray2ListInt(byte[] bytes){
		List<Integer> resultList=new ArrayList<Integer>();
		for(byte b:bytes){
			resultList.add((int)b);
		}
		return resultList;
	}
	public static Map<String,String> revertKeyToLowCase(Map<String,String> map){
		Map<String,String> newMap=new HashMap<String,String>();
		for(String key:map.keySet()){
			newMap.put(key.toLowerCase(), String.valueOf(map.get(key)));
		}
		return newMap;
	}
}
