package com.sf.sfcm.util;

/**
 * 通用响应码定义.
 */
public class ResCode {
	
	// 成功响应码
	/**系统响应信息KEY值*/
	public final static String RESMSGKEY="RESPONSEMSG";
	
	/**执行成功*/
	public final static String SUCCESS="0";
	
	// 平台级错误码
	
	/**文件上传失败*/
	public final static String UPLOAD_FAIL="1";
	/** 权限不足*/
	public final static String INSUFFICIENT_PERMISSION="2";
	/** 远程服务出错*/
	public final static String REMOTE_SERVICE_ERROR="3";
	/** 不存在的方法名*/
	public final static String METHODS_NOT_FOUND="4";
	/** 缺少方法名参数*/
	public final static String MISS_METHODS_PARAM="5";
	/** 非法数据格式*/
	public final static String ILLEGAL_DATA_FORMAT="6";
	/** 缺少必选参数*/
	public final static String MISS_REQUIRED_PARAM="7";
	/** 非法的参数*/
	public final static String ILLEGAL_PARAM="8";
	/** 参数错误*/
	public final static String ERROR_PARAM="9";
	/** 缺少Session参数(超时)*/
	public final static String SESSION_TIMEOUT="10";
	

}
