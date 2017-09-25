package com.sf.sfcm.util;

import java.lang.reflect.Field;

@SuppressWarnings("rawtypes")
public class CachedField {
	private String className;
	private String fieldName;
	private Field thisField;
	public CachedField(String className,String fieldName,Field thisField){
		this.className=className;
		this.fieldName=fieldName;
		this.thisField=thisField;
	}
	public Field getThisField() {
		return thisField;
	}
	public void setThisField(Field thisField) {
		this.thisField = thisField;
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
}
