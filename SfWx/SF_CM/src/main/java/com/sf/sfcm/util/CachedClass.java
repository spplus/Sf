package com.sf.sfcm.util;

import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentLinkedQueue;


/**
 * 缓存反射类
 * 
 * @author liuqing
 */
@SuppressWarnings("rawtypes")
public class CachedClass {
	private String className;
	public String getClassName() {
		return className;
	}
	public void setClassName(String className) {
		this.className = className;
	}
	public Class getThisClass() {
		return thisClass;
	}
	public void setThisClass(Class thisClass) {
		this.thisClass = thisClass;
	}
	private Class thisClass;
	public CachedClass(String className,Class thisClass){
		this.className=className;
		this.thisClass=thisClass;
	}
	public boolean isContainMethod(String fieldName,Class[] pClass){
		if(!methodList.containsKey(fieldName)){
			return false;
		}
		ConcurrentLinkedQueue<CachedMethod> list=methodList.get(fieldName);
		for(CachedMethod method:list){
			if(method.getFieldName().equals(fieldName)
					&&method.getpClass().length==pClass.length
					){
				return true;
			}
		}
		return false;
	}
	public Method getMethod(String fieldName,Class[] pClass){
		if(!methodList.containsKey(fieldName)){
			return null;
		}
		ConcurrentLinkedQueue<CachedMethod> list=methodList.get(fieldName);
		for(CachedMethod method:list){
			if(method.getFieldName().equals(fieldName)
					&&method.getpClass().length==pClass.length
					){
				return method.getThisMethod();
			}
		}
		return null;
	}
	public boolean isContainDeclaredField(String fieldName){
		if(!declaredFieldList.containsKey(fieldName)){
			return false;
		}
		ConcurrentLinkedQueue<CachedField> list=declaredFieldList.get(fieldName);
		for(CachedField method:list){
			if(method.getFieldName().equals(fieldName)
					){
				return true;
			}
		}
		return false;
	}
	public Field getDeclaredField(String fieldName){
		if(!declaredFieldList.containsKey(fieldName)){
			return null;
		}
		ConcurrentLinkedQueue<CachedField> list=declaredFieldList.get(fieldName);
		for(CachedField method:list){
			if(method.getFieldName().equals(fieldName)
					){
				return method.getThisField();
			}
		}
		return null;
	}
	public void addDeclaredField(Field thisMethod,String fieldName){
		if(!declaredFieldList.containsKey(fieldName)){
			ConcurrentLinkedQueue<CachedField> query=new ConcurrentLinkedQueue<CachedField>();
			query.add(new CachedField(className, fieldName, thisMethod));
			declaredFieldList.put(fieldName,query);
		}
		declaredFieldList.get(fieldName).add(new CachedField(className, fieldName, thisMethod));
	}
	public void addMethod(Method thisMethod,String fieldName,Class[] pClass){
		if(!methodList.containsKey(fieldName)){
			ConcurrentLinkedQueue<CachedMethod> query=new ConcurrentLinkedQueue<CachedMethod>();
			query.add(new CachedMethod(className, fieldName, pClass, thisMethod));
			methodList.put(fieldName,query);
		}
		methodList.get(fieldName).add(new CachedMethod(className, fieldName, pClass, thisMethod));
	}
	private ConcurrentHashMap<String, ConcurrentLinkedQueue<CachedMethod>> methodList=new ConcurrentHashMap<String, ConcurrentLinkedQueue<CachedMethod>>();
	private ConcurrentHashMap<String, ConcurrentLinkedQueue<CachedField>> declaredFieldList=new ConcurrentHashMap<String, ConcurrentLinkedQueue<CachedField>>();
}
