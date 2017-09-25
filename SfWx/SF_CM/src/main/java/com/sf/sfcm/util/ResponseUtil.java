package com.sf.sfcm.util;

import java.util.HashMap;
import java.util.Map;

import org.springframework.transaction.interceptor.TransactionAspectSupport;

import com.sf.sfcm.bean.ResBean;



/**
 * 业务响应工具类，用于封装响应码及提供响应数据通用方法.
 */
public class ResponseUtil {
	
	/**
	 * 服务请求阶段组装响应码及描述.
	 *  @param res_code 一级响应码
	 *  @param sub_code 二级响应码
	 *  @param res_msg 响应描述
	 *  @param resMap 响应数据集合(无则传入null)
	 *  @param isRollBack 是否需要回滚事务
	 *  @return Map<String,Object>:业务数据和响应信息 {@link com.huipu.common.bean.ResBean}
	 */
	public static Map<String,Object> FormatResMsg(String res_code,String sub_code,String res_msg,Map<String,Object> resMap,boolean isRollBack) {
		ResBean rb = new ResBean();
		rb.setResCode(res_code);
		rb.setSubCode(sub_code);
		rb.setResMsg(res_msg);
		if(resMap==null){
			resMap = new HashMap<String, Object>();
		}
		resMap.put(ResCode.RESMSGKEY, rb);
		if(isRollBack){
			TransactionAspectSupport.currentTransactionStatus().setRollbackOnly();
		}
		return resMap;
	}
}
