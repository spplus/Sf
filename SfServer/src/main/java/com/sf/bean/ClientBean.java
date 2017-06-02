package com.sf.bean;

public class ClientBean {

	private String Id;
	private String regTime;

	public String getRegTime() {
		return regTime;
	}

	public void setRegTime(String regTime) {
		this.regTime = regTime;
	}

	public String getId() {
		return Id;
	}

	public void setId(String id) {
		Id = id;
	}
	
	public String toString() {
		return "[id]:"+Id+" [loginTime]:"+regTime;
	}
}
