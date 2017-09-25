package com.sf.sfcm.util;

import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.concurrent.ConcurrentHashMap;

public class ReflectCached {
	private static ConcurrentHashMap<String,CachedClass> classCachedMap=new ConcurrentHashMap<String, CachedClass>();
	public static Field  getDeclaredFieldFromClass(Class<?> t,String fieldName){
		String className=t.getName();
		return getDeclaredField(className, fieldName);
	}
	public static Class<?> getCachedClass(String className){
		if(classCachedMap.containsKey(className)){
			return classCachedMap.get(className).getThisClass();
		}else{
			synchronized (classCachedMap) {
				if(!classCachedMap.containsKey(className)){
					try{
						Class<?> runClass = Class.forName(className);
						classCachedMap.put(className, new CachedClass(className, runClass));
						return runClass;
					}catch (Exception e) {
						classCachedMap.put(className,new CachedClass(className, null));
					}
				}else{
					return classCachedMap.get(className).getThisClass();
				}
			}
			
		}
		return null;
		
	}
	public static Method  getMethodFromClass(Class t,String fieldName,Class[] pClass){
		String className=t.getName();
		return getMethod(className, fieldName, pClass);
	}
	public static Field getDeclaredField(String className,String fieldName){
		if(!classCachedMap.containsKey(className)){
			return initCachedDeclaredField(className, fieldName);
		}
		CachedClass classBean=classCachedMap.get(className);
		if(!classBean.isContainDeclaredField(fieldName)){
			return initCachedDeclaredField(className, fieldName);
		}
		return classBean.getDeclaredField(fieldName);
	}
	private   synchronized static Field initCachedDeclaredField(String className,String fieldName){
		Class<?> runClass=null;
		CachedClass classfy=null;
		Field ms =null;
		try {
			if(classCachedMap.containsKey(className)){
				classfy=classCachedMap.get(className);
				runClass=classfy.getThisClass();
				if(classfy.isContainDeclaredField(fieldName)){
					return classfy.getDeclaredField(fieldName);
				}
			}else{
				runClass = Class.forName(className);
				classfy=new CachedClass(className, runClass);
				classCachedMap.put(className, classfy);
			}
			try{
				if(ms==null){
					 ms = runClass.getDeclaredField(fieldName);
				}
			}catch (Exception e) {
				classfy.addDeclaredField(ms, fieldName);
			}
			classfy.addDeclaredField(ms, fieldName);
		} catch (Exception e) {
			e.printStackTrace();
		}
		return ms;
	}
	public static Method getMethod(String className,String fieldName,Class[] pClass){
		if(!classCachedMap.containsKey(className)){
			return initCachedMethod(className, fieldName, pClass);
		}
		CachedClass classBean=classCachedMap.get(className);
		if(!classBean.isContainMethod(fieldName, pClass)){
			return initCachedMethod(className, fieldName, pClass);
		}
		return classBean.getMethod(fieldName, pClass);
	}
	private  synchronized static    Method initCachedMethod(String className,String fieldName,Class[] pClass){
		Class<?> runClass=null;
		CachedClass classfy=null;
		Method ms =null;
		try {
			if(classCachedMap.containsKey(className)){
				classfy=classCachedMap.get(className);
				runClass=classfy.getThisClass();
				if(classfy.isContainMethod(fieldName, pClass)){
					return classfy.getMethod(fieldName, pClass);
				}
			}else{
				runClass = Class.forName(className);
				classfy=new CachedClass(className, runClass);
				classCachedMap.put(className, classfy);
			}
			try{
				if(ms==null){
					 ms = runClass.getMethod(fieldName, pClass);
				}
			}catch (Exception e) {
				classfy.addMethod(ms, fieldName, pClass);
			}
			classfy.addMethod(ms, fieldName, pClass);
		} catch (Exception e) {
			e.printStackTrace();
		}
		return ms;
	}
}
