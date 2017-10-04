package com.sf.sfcm.bean;

import java.util.ArrayList;
import java.util.List;

/**
 * 服务器Ajax响应Bean
 * 
 * @ClassName: AjaxResponseBean
 * @Description: Ajax响应Bean
 */
public class AjaxResponseBean {

	/** 处理成功标志 */
	private boolean success = true;

	/** 响应数据 */
	private Object data;

	/** 额外数据 */
	private Object dataEx;

	/** 分页Html代码 */
	private String pageStr;

	/** 当前页码 */
	private int currentPage;
	/** 总页码 */
	private int totalPage;
	/** 总记录数 */
	private int totalCount;
	/** 返回页面名称 */
	private String pageName;
	/** functionId */
	private int functionId;
	/** 错误消息 */
	private List<MsgItem> errorMessages = new ArrayList<MsgItem>();
	/**
	 * 取得success
	 * 
	 * @return the success
	 */
	public boolean isSuccess() {
		return success;
	}

	/**
	 * 设定success
	 * 
	 * @param success the success to set
	 */
	public void setSuccess(boolean success) {
		this.success = success;
	}

	/**
	 * 取得data
	 * 
	 * @return the data
	 */
	public Object getData() {
		return data;
	}

	/**
	 * 设定data
	 * 
	 * @param data the data to set
	 */
	public void setData(Object data) {
		this.data = data;
	}

	/**
	 * 取得errorMessages
	 * 
	 * @return the errorMessages
	 */
	public List<MsgItem> getErrorMessages() {
		return errorMessages;
	}

	/**
	 * 追加错误消息
	 * 
	 * @param message 错误消息
	 */
	public void addErrorMessage(MsgItem message) {
		errorMessages.add(message);
	}

	/**
	 * @return the dataEx
	 */
	public Object getDataEx() {
		return dataEx;
	}

	/**
	 * @param dataEx the dataEx to set
	 */
	public void setDataEx(Object dataEx) {
		this.dataEx = dataEx;
	}

	/**
	 * @return the pageStr
	 */
	public String getPageStr() {
		return pageStr;
	}

	/**
	 * @param pageStr the pageStr to set
	 */
	public void setPageStr(String pageStr) {
		this.pageStr = pageStr;
	}

	/**
	 * @return the currentPage
	 */
	public int getCurrentPage() {
		return currentPage;
	}

	/**
	 * @param currentPage the currentPage to set
	 */
	public void setCurrentPage(int currentPage) {
		this.currentPage = currentPage;
	}

	/**
	 * @return the totalPage
	 */
	public int getTotalPage() {
		return totalPage;
	}

	/**
	 * @param totalPage the totalPage to set
	 */
	public void setTotalPage(int totalPage) {
		this.totalPage = totalPage;
	}

	/**
	 * @return the totalCount
	 */
	public int getTotalCount() {
		return totalCount;
	}

	/**
	 * @param totalCount the totalCount to set
	 */
	public void setTotalCount(int totalCount) {
		this.totalCount = totalCount;
	}

	public String getPageName() {
		return pageName;
	}

	public void setPageName(String pageName) {
		this.pageName = pageName;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see java.lang.Object#toString()
	 */
	@Override
	public String toString() {
		return "AjaxResponseBean [success=" + success + ", data=" + data + ", dataEx=" + dataEx + ", currentPage="
				+ currentPage + ", totalPage=" + totalPage + ", errorMessages=" + errorMessages + "]";
	}

	public int getFunctionId() {
		return functionId;
	}

	public void setFunctionId(int functionId) {
		this.functionId = functionId;
	}

}
