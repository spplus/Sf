package com.sf.page;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import org.codehaus.jackson.annotate.JsonIgnore;
/**
 * 分页信息。
 */
public class PageUtil<T> implements Serializable{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private int size = 10;/**每页显示几条*/
	private int total = 0; /**总条数*/
	private int currentPage = 0; /**当前页*/
	private int totalPage;	/**总页数*/	
	private int currentResult = 0; 	/**当前记录起始索引*/
	private List<T> result = new ArrayList<T>();	/**存放结果集*/
	@JsonIgnore
	private String pageStr;		/**最终页面显示的底部翻页导航，详细见：getPageStr();*/
	
	private static final String pageLable = "\u9875"; // 页 
	private static final String firstPageLabel = "\u9996\u9875"; // 首页
	private static final String endPageLabel = "\u672B\u9875";
	private static final String prePageLabel = "\u4e0a\u4e00\u9875"; // 上一页
	private static final String nextPageLabel = "\u4e0b\u4e00\u9875"; // 下一页
	private static final String errorPageInfo = "\u8bf7\u8f93\u5165\u6b63\u786e\u7684\u9875\u6570"; // 请输入正确的页数
	private static final String errorMaxPage = "\u8f93\u5165\u7684\u9875\u6570\u4e0d\u80fd\u5927\u4e8e\u603b\u9875\u6570\uff0c\u8bf7\u91cd\u65b0\u8f93\u5165"; // 输入的页数不能大于总页数，请重新输入
	private static final String goToPageLabel = "\u8df3\u8f6c\u5230"; // 跳转到
	private static final String countLabel = "\u6761"; // 条
	private static final String allLabel = "\u5171";//共
	
	@SuppressWarnings("unchecked")
	public PageUtil(Map<String,Object> map){
		if(map.get("SERVICE_HEADER")==null){
			int showCount = Integer.parseInt(map.get("SHOWCOUNT") != null ? map.get("SHOWCOUNT").toString() : "0");
			int currentPage = Integer.parseInt(map.get("CURRENTPAGE") != null ? map.get("CURRENTPAGE").toString() : "0");
			this.setSize(showCount);
			this.setCurrentPage(currentPage);
			this.getTotalPage();
		}else{
			Map<String,String> headerMap = (Map<String,String>)map.get("SERVICE_HEADER");
			int showCount = Integer.parseInt(headerMap.get("SHOWCOUNT") != null ? headerMap.get("SHOWCOUNT") : "0");
			int currentPage = Integer.parseInt(headerMap.get("CURRENTPAGE") != null ? headerMap.get("CURRENTPAGE") : "0");
			this.setSize(showCount);
			this.setCurrentPage(currentPage);
			this.getTotalPage();
		}
	}
	public PageUtil(){
		
	}
	public PageUtil(int TOTAL,int CURRENTPAGE,int showCount){
		setTotal(TOTAL);
		this.setSize(showCount);
		setCurrentPage(CURRENTPAGE);
		this.getTotalPage();
	}
	/**
	 * 获取结果集
	 */
	public List<T> getResult() {
		if (result == null) {
			return new ArrayList<T>();
		}
		return result;
	}

	public void setResult(List<T> result) {
		this.result = result;
	}
	/**
	 * 获取总页数
	 */
	public int getTotalPage() {
		if (total % size == 0) {
			totalPage =total / size;
		}else{
			totalPage = total / size + 1;	
		}		
		return totalPage;
	}

	/**
	 * 获取总条数
	 */
	public int getTotal() {
		return total;
	}
	public void setTotal(int total) {
		this.total = total;
	}

	public int getCurrentPage() {
		if (currentPage <= 0) {
			currentPage = 1;
		}
		if (currentPage > getTotalPage()) {
			currentPage = getTotalPage();
		}
		return currentPage;
	}

	public void setCurrentPage(int currentPage) {
		this.currentPage = currentPage;
	}

	public int getSize() {
		return size;
	}

	public void setSize(int size) {
		if (size == 0) {
			size = 10;
		}
		this.size = size;
	}

	public int getCurrentResult() {
		currentResult = (getCurrentPage() - 1) * getSize();
		if (currentResult < 0) {
			currentResult = 0;
		}
		return currentResult;
	}

	public void setCurrentResult(int currentResult) {
		this.currentResult = currentResult;
	}
	
	
	
	public void setTotalPage(int totalPage) {
		this.totalPage = totalPage;
	}

	/**
	* @MethodName: getPageStr 
	* @Description: 得到分页的字符串
	* @date 2012-7-17 下午5:45:46
	* @return String
	 */
	public String getPageStr() {
		this.getTotalPage();
		StringBuffer buffer = new StringBuffer();
		//buffer.append("<div class=\"flip_over float_r\">");
		//buffer.append("<span>"+allLabel+total+countLabel+"</span><span><em class=\"orange_b\">"+currentPage+"</em>/"+totalPage+pageLable + "</span>");
		buffer.append("<span>"+allLabel+total+countLabel+"</span><span>"+"&nbsp;"+currentPage+"/"+totalPage+pageLable + "&nbsp;"+"</span>");
		//首页
		if (currentPage == 0 || currentPage == 1) {
			buffer.append("&nbsp;"+firstPageLabel+"&nbsp;");
		} else {
			buffer.append("<b><a href=\"javascript:void(0);\" onclick=\"nextPage(1)\" style='color:#2369FF;'>"+firstPageLabel+"</a>&nbsp;</b>");
		}
		//上一页
		if (currentPage != 0 && currentPage != 1) {
			buffer.append("<b><a href=\"javascript:void(0);\" onclick=\"nextPage(" + (currentPage - 1) + ")\" style='color:#2369FF;'>" + prePageLabel + "</a>&nbsp;</b>");
		} else {
			buffer.append(prePageLabel+"&nbsp;");
		}
		//下一页
		if (currentPage + 1 <= totalPage) {
			buffer.append("<b><a href=\"javascript:void(0);\" onclick=\"nextPage(" + (currentPage + 1) + ")\" style='color:#2369FF;'>" + nextPageLabel + "</a>&nbsp;</b>");
		} else {
			buffer.append(nextPageLabel+"&nbsp;");
		}
		//尾页
		if(currentPage<totalPage){
			buffer.append("<b><a href=\"javascript:void(0);\" onclick=\"nextPage(" + (totalPage) + ")\" style='color:#2369FF;'>" + endPageLabel + "</a>&nbsp;</b>");
		}else{
			buffer.append(endPageLabel+"&nbsp;");
		}
		
		buffer.append("&nbsp;"+goToPageLabel+"<input value='"+currentPage+"' type=\"text\" class=\"page_text\" size=\"3\" maxlength=\"8\" type=\"text\" onkeydown=\"var e = event || window.event || arguments.callee.caller.arguments[0]; if(e && e.keyCode==13){var pageNoVal = $(this).val(); if(pageNoVal >" + totalPage + " ){alert('" + errorMaxPage + "');}else if(pageNoVal == 0){alert('"+errorPageInfo+"');} else {nextPage(pageNoVal);}}\" onkeyup=\"this.value=this.value.replace(/[^0-9]/g,'')\" onblur=\"this.value=this.value.replace(/[^0-9]/g,'')\" />"+pageLable+"<input type=\"button\" onclick=\"var pageNoVal = $(this).prev('input:eq(0)').val(); if(pageNoVal >" + totalPage + " ){alert('" + errorMaxPage + "');}else if(pageNoVal == 0){alert('"+errorPageInfo+"');} else {nextPage(pageNoVal);}\" class=\"page_btn\" value=\"GO\"/>");
		//buffer.append("</div>");
		pageStr = buffer.toString();
		return pageStr;
	}
}
