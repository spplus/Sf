package com.sf.sfcm.bean;

import java.util.ArrayList;

/**
 * 服务器消息Bean
 * 
 * @ClassName: MsgItem
 * @Description:MsgItem对象
 */
public class MsgItem {

	/** 消息 */
	private String msg;

	/** 替换参数 */
	private ArrayList<String> itemParam;

	/**
	 * CodeBook对象构造方法
	 * 
	 * @param type 对象类型
	 * @param code 对象Code
	 * @param value 对象值
	 */
	public MsgItem() {

	}

	/**
	 * CodeBook对象构造方法
	 * 
	 * @param type 对象类型
	 * @param code 对象Code
	 * @param value 对象值
	 */
	public MsgItem(String msg, ArrayList<String> itemParam) {
		this.msg = msg;
		this.itemParam = itemParam;
	}

	/**
	 * 取得msg
	 * 
	 * @return the msg
	 */
	public String getMsg() {
		return msg;
	}

	/**
	 * 设定msg
	 * 
	 * @param msg the msg to set
	 */
	public void setMsg(String msg) {
		this.msg = msg;
	}

	/**
	 * 取得itemParam
	 * 
	 * @return the itemParam
	 */
	public ArrayList<String> getItemParam() {
		return itemParam;
	}

	/**
	 * 设定itemParam
	 * 
	 * @param itemParam the itemParam to set
	 */
	public void setItemParam(ArrayList<String> itemParam) {
		this.itemParam = itemParam;
	}

	/**
	 * 添加单项目名
	 * 
	 * @param itemName 单项目名
	 */
	public void addItemParam(String itemName) {
		if (null != this.itemParam) {
			this.itemParam.add(itemName);
		} else {
			this.itemParam = new ArrayList<String>();
			this.itemParam.add(itemName);
		}
	}

	/**
	 * 由消息Key和参数构建一个MsgItem实例
	 * 
	 * @param msgKey 消息Key
	 * @param paramKeys 参数
	 * @return MsgItem
	 */
	public static MsgItem newMessageItem(String msgKey, String... paramKeys) {
		MsgItem item = new MsgItem();
		item.setMsg(msgKey);
		for (String paramKey : paramKeys) {
			item.addItemParam(paramKey);
		}
		return item;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return "MsgItem [msg=" + msg + ", itemParam=" + itemParam + "]";
	}
}
