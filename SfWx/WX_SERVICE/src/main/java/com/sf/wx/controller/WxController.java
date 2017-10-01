package com.sf.wx.controller;

import java.util.HashMap;
import java.util.Map;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.cloud.client.discovery.DiscoveryClient;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import com.sf.sfcm.bean.UserInfo;
import com.sf.sfcm.logger.SFLogger;
import com.sf.sfcm.util.ResCode;
import com.sf.sfcm.util.ResponseUtil;
import com.sf.wx.service.WxService;


@RestController
@RequestMapping("/wx/")
public class WxController {

	@Autowired
	private DiscoveryClient client;
	
	@Autowired
	WxService		wxService;
	
	@RequestMapping(value = "/finduser", method = RequestMethod.GET)
    public UserInfo finduser(@RequestParam String username) {

		SFLogger.debug("finduser:"+username);
		return wxService.findByUsername(username);
    }
	
	@RequestMapping(value = "/test", method = RequestMethod.GET)
	public void test(){
		SFLogger.debug("test transaction");
		try {
			wxService.insertTest(0);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	/**
	 * 添加家电.
	 * @param reqMap
	 * 		  	map的key为数据库实际字段，全小写，key值如下：
	 * 		  	siteid 	服务商ID
	 * 		  	codeid	二维码ID
	 * 		  	其余key值为页面提交过来的对应家电表中的字段名称，全小写。
	 * @return
	 * 返回值map的key值说明如下：
	 * 			resCode 状态码 0 表示成功，其他失败。
	 * 			resMsg  返回值描述信息。如果失败，失败原因的描述信息。
	 */
	@RequestMapping(value = "addappliance",method = RequestMethod.POST)
	public Map<String,Object> addAppliance(Map<String,Object> reqMap){
		SFLogger.info("新增家电,参数为："+reqMap.toString());
		try{
			
			return wxService.addAppliance(reqMap);
		}catch(Exception e){
			SFLogger.error("新增家电失败:"+e.getMessage());
			e.printStackTrace();
			return null;
		}
		
	}
	
	/**
	 * 更新家电信息.
	 * @param reqMap 家电品类,家电品牌为必填参数.
	 * @return
	 */
	
	@RequestMapping(value = "updateappliance",method = RequestMethod.POST)
	public Map<String,Object> updateAppliance(Map<String,Object> reqMap){
		
		SFLogger.info("更新家电,参数为："+reqMap.toString());
		
		// 检查必填参数是否存在
		if((!reqMap.containsKey("category")) || (!reqMap.containsKey("brand"))){
			
			SFLogger.warn("更新家电失败:品牌和品类参数不可以为空。参数内容："+reqMap.toString());
			return ResponseUtil.FormatResMsg(ResCode.ERROR_PARAM, "", "品牌和品类参数不可以为空", null, false);  
		}
		
		try{
			
			return wxService.updateAppliance(reqMap);
			
		}catch(Exception e){
			SFLogger.error("更新家电失败:"+e.getMessage());
			e.printStackTrace();
			return null;
		}
	}
	
	/**
	 * 查询家电详情.
	 * @param reqMap
	 * 包含以下keys
	 * keys:
	 * code 	二维码code
	 * open_id  
	 *
	 * @return
	 * 
	 * 返回内容为家电表所有字段，key为表中的字段名，小写.
	 */
	
	@RequestMapping(value = "queryappliance",method = RequestMethod.GET)
	public Map<String,Object> queryAppliance(Map<String,Object> reqMap){
		SFLogger.info("查询家电详情,参数为："+reqMap.toString());
		
		// 判断参数是否有效.
		if(reqMap.isEmpty()){
			String msg = "查询家电详情失败。参数不可以为空";
			SFLogger.warn(msg);
			return ResponseUtil.FormatResMsg(ResCode.ERROR_PARAM, "", msg, null, false);  
		}
		
		try {
			
			return wxService.queryAppliance(reqMap);
			
		} catch (Exception e) {
			SFLogger.error("查询家电信息失败:"+e.getMessage());
			e.printStackTrace();
			return null;
		}
		
	}
	
	/**
	 * 
	 * @param reqMap
	 * keys:open_id,site_id
	 * @return
	 * 
	 */
	public Map<String,Object> updateCustomer(Map<String,Object> reqMap){
		SFLogger.info("更新用户信息,参数为："+reqMap.toString());
		
		// 判断参数有效性
		if(!reqMap.containsKey("open_id")){
			String msg = "更新用户信息失败。open_id不可以为空";
			SFLogger.warn(msg);
			return ResponseUtil.FormatResMsg(ResCode.ERROR_PARAM, "", msg, null, false);  
		}
		
		// 判断site_id
		if(!reqMap.containsKey("site_id")){
			String msg = "更新用户信息失败。site_id不可以为空";
			SFLogger.warn(msg);
			return ResponseUtil.FormatResMsg(ResCode.ERROR_PARAM, "", msg, null, false);  
		}
		
		try {
			return wxService.updateCustomer(reqMap);
		} catch (Exception e) {
			SFLogger.warn("更新用户信息失败:"+e.getMessage());
			e.printStackTrace();
			return null;
		}
		
	}
	
	/**
	 * 新增用户.
	 * @param reqMap
	 * keys:
	 * id,number,status,open_id
	 * @return
	 */
	public Map<String,Object> addCustomer(Map<String,Object> reqMap){
		SFLogger.info("新增用户,参数为："+reqMap.toString());
		
		// 判断参数有效性
		if(!reqMap.containsKey("open_id")){
			String msg = "新增用户失败。open_id不可以为空";
			SFLogger.warn(msg);
			return ResponseUtil.FormatResMsg(ResCode.ERROR_PARAM, "", msg, null, false);  
		}
		
		try {
			return wxService.insertCustomer(reqMap);
		} catch (Exception e) {
			SFLogger.warn("新增用户失败:"+e.getMessage());
			e.printStackTrace();
			return null;
		}
	}
	
	/**
	 * 查询用户.
	 * @param reqMap
	 * keys:
	 * open_id
	 * 
	 * @return
	 * keys:
	 * 用户表字段，小写
	 * 
	 */
	public Map<String,Object> queryCustomer(Map<String,Object> reqMap){
		SFLogger.info("查看用户,参数为："+reqMap.toString());
		
		if((!reqMap.containsKey("open_id"))|| reqMap.get("open_id").toString().isEmpty()){
			String msg = "查询用户失败。open_id不可以为空";
			SFLogger.warn(msg);
			return ResponseUtil.FormatResMsg(ResCode.ERROR_PARAM, "", msg, null, false);  
		}
		String open_id = reqMap.get("open_id").toString();
		
		try {
			return wxService.queryCustomer(open_id);
		} catch (Exception e) {
			SFLogger.warn("新增用户失败:"+e.getMessage());
			e.printStackTrace();
			return null;
		}
	}
	
	/**
	 * 查询我的家电列表.
	 * @param reqMap
	 * keys:
	 * open_id
	 * currentpage		当前页码
	 * showcount		每页显示条数
	 * @return
	 */
	public Map<String,Object> queryMyApplianceList(Map<String, Object> reqMap){
		SFLogger.info("查询我的家电列表,参数为："+reqMap);
		
		if(reqMap.isEmpty()){
			String msg = "查询用户家电列表失败。open_id不可以为空";
			SFLogger.warn(msg);
			return ResponseUtil.FormatResMsg(ResCode.ERROR_PARAM, "", msg, null, false); 
		}
		
		try {
			int curPage = 0;
			int showCount = 10;
			if(reqMap.containsKey("currentpage")){
				curPage = Integer.parseInt(reqMap.get("currentpage").toString());
			}
			
			if(reqMap.containsKey("showcount")){
				showCount = Integer.parseInt(reqMap.get("showcount").toString());
			}
			
			reqMap.put("SHOWCOUNT", showCount);
			reqMap.put("CURRENTPAGE", curPage);
			
			return wxService.queryMyApplianceList(reqMap);
		} catch (Exception e) {
			SFLogger.warn("查询用户家电列表失败:"+e.getMessage());
			e.printStackTrace();
			return null;
		}
	}
	
}
