package com.sf.sfcm.bean;

import java.io.Serializable;

import com.sf.sfcm.util.StringUtil;

/**
 * 响应信息bean.
 */
public class ResBean implements Serializable{
	
	private static final long serialVersionUID = 1L;
	private String resCode;
	private String subCode;
	private String resMsg;
	/**一级响应码.*/
	public String getResCode() {
		return StringUtil.null2String(resCode);
	}
	public void setResCode(String resCode) {
		this.resCode = resCode;
	}
	/**二级响应码.*/
	public String getSubCode() {
		return StringUtil.null2String(subCode);
	}
	public void setSubCode(String subCode) {
		this.subCode = subCode;
	}
	/**响应描述.*/
	public String getResMsg() {
		return StringUtil.null2String(resMsg);
	}
	public void setResMsg(String resMsg) {
		this.resMsg = resMsg;
	}
	
}
