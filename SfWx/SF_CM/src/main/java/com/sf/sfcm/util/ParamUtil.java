package com.sf.sfcm.util;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Enumeration;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;

import org.springframework.web.context.request.RequestContextHolder;
import org.springframework.web.context.request.ServletRequestAttributes;

import com.sf.sfcm.bean.AjaxResponseBean;
import com.sf.sfcm.bean.MsgItem;
import com.sf.sfcm.bean.ResBean;

/**
 * 服务端参数处理.
 */
public class ParamUtil {

	public static final AjaxResponseBean SERVERERROR = getServerError();
	public static final String 	RESULT_KEY = "RESULT";
	
	public static final String 	PAGEINFO_KEY 	= "PAGEINFO";
	public static final String 	RESCODE_KEY 	= "resCode";
	public static final String 	RESMSG_KEY 		= "resMsg";
	public static final String 	RESRESULT_KEY 	= "result";
	public static final String 	RESPAGESTR_KEY 	= "pageStr";
	public static final	String 	RESCURRENTPAGE 	= "currentPage";
	public static final	String 	RESTOTALPAGE 	= "totalPage";
	

	

	/**
	 * 新框架在controller中返回内容转bean方法.
	 * @param resMap
	 * @return
	 */
	public static AjaxResponseBean getResultBean(Map<String,Object> resMap){
		
		AjaxResponseBean result = new AjaxResponseBean();
		
		Map<String,Object> rb = (Map<String, Object>) resMap.get(ResCode.RESMSGKEY);
		if (!rb.get(RESCODE_KEY).toString().equals(ResCode.SUCCESS)) {// 业务成功
			
			result.addErrorMessage(MsgItem.newMessageItem(rb.get(RESMSG_KEY).toString()));
			result.setSuccess(false);
			return result;
		}
		Map<String, Object> page = (Map<String, Object>) resMap.get(PAGEINFO_KEY);
		result.setData(page.get(RESRESULT_KEY));
		result.setPageStr(page.get(RESPAGESTR_KEY).toString());
		result.setCurrentPage(Integer.parseInt(page.get(RESCURRENTPAGE).toString()));
		result.setTotalPage(Integer.parseInt(page.get(RESTOTALPAGE).toString()));
		
		return result;
	}
	
	
	

	public static AjaxResponseBean getResponseBean(Map<String, Object> resMap) {
		return getResponseBean(resMap, RESULT_KEY);
	}

	public static AjaxResponseBean getResponseBean(Map<String, Object> resMap, String resultKey) {

		AjaxResponseBean result = new AjaxResponseBean();
		try {
			ResBean resBean = (ResBean) resMap.get(ResCode.RESMSGKEY);
			if (!ResCode.SUCCESS.equals(resBean.getResCode())) {
				result.setSuccess(false);
				result.addErrorMessage(MsgItem.newMessageItem(resBean.getResMsg()));
				return result;
			}
			result.setData(resMap.get(resultKey));
			return result;
		} catch (Exception e) {
			return SERVERERROR;
		}

	}

	public static AjaxResponseBean getPageBean(Map<String, Object> resMap) {
		return getPageBean(resMap, RESULT_KEY, 0);
	}

	public static AjaxResponseBean getPageBean(Map<String, Object> resMap, String reusltKey) {
		return getPageBean(resMap, reusltKey, 0);
	}

	public static AjaxResponseBean getPageBean(Map<String, Object> resMap, String reusltKey, int pageType) {
		try {
			AjaxResponseBean pageResult = getResponseBean(resMap, reusltKey);
			if (!pageResult.isSuccess()) {
				return pageResult;
			}
			PageUtil<?> page = (PageUtil<?>) pageResult.getData();
			pageResult.setData(page.getResult());
			int showPages = 6;// 默认显示10个分页标签按钮
			if (pageType == 0) {
				if (StringUtil.isNotEmpty(resMap.get("BUTTONCOUNT"))) {
					showPages = Integer.valueOf(String.valueOf(resMap.get("BUTTONCOUNT")));
				}
				pageResult.setPageStr(getPageDivStr(page.getCurrentPage(), page.getTotalPage(), showPages, page.getTotal(), "flip"));
			} else {
				pageResult.setPageStr(page.getPageStr());
			}
			pageResult.setCurrentPage(page.getCurrentPage());
			pageResult.setTotalPage(page.getTotalPage());
			pageResult.setTotalCount(page.getTotal());
			return pageResult;
		} catch (Exception e) {
			return SERVERERROR;
		}
	}

	public static AjaxResponseBean getPageBean(Map<String, Object> resMap, String reusltKey, int pageType, String strCSS) {
		try {
			AjaxResponseBean pageResult = getResponseBean(resMap, reusltKey);
			if (!pageResult.isSuccess()) {
				return pageResult;
			}
			PageUtil<?> page = (PageUtil<?>) pageResult.getData();
			pageResult.setData(page.getResult());
			if (pageType == 0) {
				pageResult.setPageStr(getPageDivStr(page.getCurrentPage(), page.getTotalPage(), 10, page.getTotal(), strCSS));
			} else {
				pageResult.setPageStr(page.getPageStr());
			}
			pageResult.setCurrentPage(page.getCurrentPage());
			pageResult.setTotalPage(page.getTotalPage());
			pageResult.setTotalCount(page.getTotal());
			return pageResult;
		} catch (Exception e) {
			return SERVERERROR;
		}
	}

	public static AjaxResponseBean getServerError() {
		AjaxResponseBean serverError = new AjaxResponseBean();
		serverError.setSuccess(false);
		serverError.addErrorMessage(MsgItem.newMessageItem("服务器错误"));
		return serverError;
	}

	/**
	 * 判断后台结果是否获取成功.
	 */
	public static AjaxResponseBean getResult(Map<String, Object> resMap) {
		AjaxResponseBean result = new AjaxResponseBean();
		try {
			ResBean resBean = (ResBean) resMap.get(ResCode.RESMSGKEY);
			if (!ResCode.SUCCESS.equals(resBean.getResCode())) {
				result.setSuccess(false);
				result.addErrorMessage(MsgItem.newMessageItem(resBean.getResMsg()));
				return result;
			}
			result.setSuccess(true);
			return result;
		} catch (Exception e) {
			return SERVERERROR;
		}

	}

	/**
	 * 查询结果mapkey值大小写.
	 * 
	 * @param map
	 *            查询返回值
	 * @param upper
	 *            ture大写，false小写
	 * @return
	 */
	@SuppressWarnings({ "unchecked", "rawtypes" })
	public static Map<String, Object> setResultMapKeyUpperOrLower(Map<String, Object> map, Boolean upper) {
		PageUtil<Object> page = (PageUtil<Object>) map.get("RESULT");
		List<Object> lb = page.getResult();
		List<Object> nlb = new ArrayList();
		for (Object object : lb) {
			if (upper) {
				object = BeanUtil.MapKeyToUpperCase((Map) object);
			} else {
				object = BeanUtil.MapKeyToLowerCase((Map) object);
			}
			nlb.add(object);
		}
		page.setResult(nlb);
		map.put("RESULT", page);
		return map;
	}
	
	/**
	 * 获取DIV翻页的模版代码.
	 * 
	 * @param nowpage
	 *            当前页
	 * @param totalPage
	 *            总页数
	 * @param buttonCount
	 *            翻页按钮个数
	 * @param sumCount
	 *            总记录数
	 * @param strCSS
	 *            CSS
	 * @return
	 */
	public static String getPageDivStr(int nowpage, int totalPage, int buttonCount, int sumCount, String strCSS) {
		// 索引的sum值 代表的是 google页面中最大显示页数
		int sumindex = buttonCount;
		// 开始的索引值
		int startindex;
		// 结束的索引值
		int endindex;
		final String firstPageLabel = "\u9996\u9875"; // 首页
		final String prePageLabel = "\u4e0a\u4e00\u9875"; // 上一页
		final String nextPageLabel = "\u4e0b\u4e00\u9875"; // 下一页
		final String lastPageLabel = "\u672B\u9875"; // 末页

		StringBuffer buffer = new StringBuffer();

		// 开始
		buffer.append("<div class='" + strCSS + "'>");

		// 计算索引位置
		if (nowpage <= sumindex / 2 + 1) {
			startindex = 1;
			endindex = nowpage + sumindex / 2 - 1;

			// 当结束的索引值>总页数
			if (endindex > totalPage) {
				endindex = totalPage;
			}
		} else {
			startindex = nowpage - sumindex / 2;
			endindex = nowpage + sumindex / 2 - 1;
			// 当结束的索引值>总页数
			// 当结束的索引值>索引的sum值 代表的是 google页面中最大显示页数
			if (endindex > totalPage && endindex > sumindex) {
				endindex = totalPage;
				// startindex = totalPage - sumindex - 1;
			}
			// 当结束的索引值<索引的sum值 代表的是 google页面中最大显示页数
			if (endindex < sumindex) {
				startindex = 1;
				endindex = totalPage;
			}
		}
		if (nowpage == 0 || nowpage == 1) {
			buffer.append("<span>&nbsp;" + firstPageLabel + "&nbsp;</span>");
		} else {
			buffer.append("<a href=\"javascript:void(0);\" onclick=\"nextPage(1)\">&nbsp;" + firstPageLabel + "&nbsp;</a>");
		}
		// 上一页
		if (nowpage != 0 && nowpage != 1) {
			buffer.append("<a href=\"javascript:void(0);\" onclick=\"nextPage(" + (nowpage - 1) + ")\">&nbsp;" + prePageLabel + "&nbsp;</a>");
		} else {
			buffer.append("<span>&nbsp;" + prePageLabel + "&nbsp;</span>");
		}
		for (int i = startindex; i <= endindex; i++) {
			if (i == nowpage) {
				buffer.append("<span class='on'>&nbsp;" + i + "&nbsp;</span>");
			} else {
				buffer.append("<a href=\"javascript:void(0);\"   class=\"flip_nosp\" onclick=\"nextPage(" + i + ")\">&nbsp;" + i + "&nbsp;</a> ");
			}
		}
		// 下一页
		if (nowpage + 1 <= totalPage) {
			buffer.append(" <a href=\"javascript:void(0);\" onclick=\"nextPage(" + (nowpage + 1) + ")\">&nbsp;" + nextPageLabel + "&nbsp;</a> ");
		} else {
			buffer.append("<span>&nbsp;" + nextPageLabel + "&nbsp;</span>");
		}
		// 末页
		if (nowpage == totalPage || totalPage <= 1) {
			buffer.append("<span >&nbsp;" + lastPageLabel + "&nbsp;</span>");
		} else {
			buffer.append(" <a href=\"javascript:void(0);\" onclick=\"nextPage(" + totalPage + ")\">&nbsp;" + lastPageLabel + "&nbsp;</a> ");
		}

		// 总条数
		buffer.append("<font class='f1'>总条数&nbsp;" + sumCount + "&nbsp;</font>");

		// 最后封闭
		buffer.append("</div>");

		return buffer.toString();
	}

}
