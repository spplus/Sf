package com.sf.sfcm.util;

import java.lang.reflect.Method;

@SuppressWarnings("rawtypes")
public class CachedMethod {
	private String className;
	private String fieldName;
	private Class[] pClass;
	private Method thisMethod;
	public CachedMethod(String className,String fieldName,Class[] pClass,Method thisMethod){
		this.className=className;
		this.fieldName=fieldName;
		this.pClass=pClass;
		this.thisMethod=thisMethod;
	}
	public Method getThisMethod() {
		return thisMethod;
	}
	public void setThisMethod(Method thisMethod) {
		this.thisMethod = thisMethod;
	}
	public String getClassName() {
		return className;
	}
	public void setClassName(String className) {
		this.className = className;
	}
	public String getFieldName() {
		return fieldName;
	}
	public void setFieldName(String fieldName) {
		this.fieldName = fieldName;
	}
	public Class[] getpClass() {
		return pClass;
	}
	public void setpClass(Class[] pClass) {
		this.pClass = pClass;
	}
}
