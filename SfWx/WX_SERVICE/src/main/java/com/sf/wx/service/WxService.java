package com.sf.wx.service;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.sf.db.DataSourceSwitch;
import com.sf.db.MybatisDao;
import com.sf.page.PageUtil;
import com.sf.sfcm.bean.UserInfo;
import com.sf.sfcm.util.DataSourceSelect;
import com.sf.sfcm.util.ResCode;
import com.sf.sfcm.util.ResponseUtil;

/**
 * 
 * 微信服务相关接口的业务实现.
 * 
 * @author yls
 * 
 *
 */



@Service
public class WxService {

	@Autowired
	MybatisDao			baseDao;
	
	
	public void  insertTest(int i) throws Exception{
	
		DataSourceSwitch.setDataSourceType(DataSourceSelect.DS_DB1);
		baseDao.insert("WxServiceMapper.insertUser", "");
		
	}
	
	public UserInfo findByUsername(String username){
		
		DataSourceSwitch.setDataSourceType(DataSourceSelect.DS_DB1);
		return baseDao.get("WxServiceMapper.findByUsername", username);
	}
	
	/**
	 * 新增家电.
	 * @param reqMap
	 * @return
	 * @throws Exception
	 */
	public Map<String,Object> addAppliance(Map<String,Object> reqMap) throws Exception{
		
		// 判断参数
		if(reqMap.isEmpty() || reqMap == null){
			return ResponseUtil.FormatResMsg(ResCode.ERROR_PARAM, "", "参数不可以为空", null, false); 
		}
		
		// 切换数据库导微信数据库
		DataSourceSwitch.setDataSourceType(DataSourceSelect.DB_WX);
		
		// 执行SQL 
		int ret = baseDao.insert("WxServiceMapper.insertAppliance", reqMap);
		
		if(ret > 0){
			return ResponseUtil.FormatResMsg(ResCode.SUCCESS, "", "插入成功", null, false); 
		}else{
			return ResponseUtil.FormatResMsg(ResCode.SUCCESS, "", "插入失败", null, false);
		}
	}
	
	/**
	 * 更新家电.
	 * 
	 */
	public Map<String,Object> updateAppliance(Map<String,Object> reqMap) throws Exception{
		
		
		// 切换数据库导微信数据库
		DataSourceSwitch.setDataSourceType(DataSourceSelect.DB_WX);
		
		// 执行SQL 
		int ret = baseDao.update("WxServiceMapper.updateAppliance", reqMap);
				
		if(ret > 0){
			return ResponseUtil.FormatResMsg(ResCode.SUCCESS, "", "插入成功", null, false); 
		}else{
			return ResponseUtil.FormatResMsg(ResCode.SUCCESS, "", "插入失败", null, false);
		}
	}
	
	/**
	 * 查看家电详情.
	 * 
	 */
	public Map<String,Object> queryAppliance(Map<String,Object> reqMap) throws Exception{
		
		// 切换数据库导微信数据库
		DataSourceSwitch.setDataSourceType(DataSourceSelect.DB_WX);
		
		Map<String,Object> resMap =baseDao.get("WxServiceMapper.queryAppliance", reqMap);
		
		return ResponseUtil.FormatResMsg(ResCode.SUCCESS, "", "查询成功", resMap, false);  
	}
	
	/**
	 * 更新用户信息.
	 */
	
	public Map<String,Object> updateCustomer(Map<String,Object> reqMap) throws Exception{
		// 切换数据库导微信数据库
		DataSourceSwitch.setDataSourceType(DataSourceSelect.DB_WX);
		
		// 执行SQL 
		int ret = baseDao.update("WxServiceMapper.updateCustomer", reqMap);
						
		if(ret > 0){
			return ResponseUtil.FormatResMsg(ResCode.SUCCESS, "", "更新用户成功", null, false); 
		}else{
			return ResponseUtil.FormatResMsg(ResCode.SUCCESS, "", "更新用户失败", null, false);
		}
		
	}
	
	/**
	 * 新增用户.
	 * @param reqMap
	 * @return
	 * @throws Exception
	 */
	public Map<String,Object> insertCustomer(Map<String,Object> reqMap) throws Exception{
		// 切换数据库导微信数据库
		DataSourceSwitch.setDataSourceType(DataSourceSelect.DB_WX);
		
		// 执行SQL 
		int ret = baseDao.update("WxServiceMapper.insertCustomer", reqMap);
								
		if(ret > 0){
			return ResponseUtil.FormatResMsg(ResCode.SUCCESS, "", "新增用户成功", null, false); 
		}else{
			return ResponseUtil.FormatResMsg(ResCode.SUCCESS, "", "新增用户失败", null, false);
		}
	}
	
	public Map<String,Object> queryCustomer(String open_id) throws Exception{
		// 切换数据库导微信数据库
		DataSourceSwitch.setDataSourceType(DataSourceSelect.DB_WX);
		
		Map<String,Object> resMap = baseDao.get("WxServiceMapper.queryCustomer", open_id);
		
		return ResponseUtil.FormatResMsg(ResCode.SUCCESS, "", "查询用户成功", resMap, false); 
	}
	
	public Map<String,Object> queryMyApplianceList(Map<String,Object> reqMap) throws Exception{
		// 切换数据库导微信数据库
		DataSourceSwitch.setDataSourceType(DataSourceSelect.DB_WX);
		
		PageUtil<Object> page = new PageUtil<Object>(reqMap);
		reqMap.put("page", page);
    	List<Object>  reslist = baseDao.getList("WxServiceMapper.listPageQueryMyAppliance",reqMap);
    	page.setResult(reslist);
    	
    	return ResponseUtil.FormatResMsg(ResCode.SUCCESS, null, "查询执行成功", reqMap,
                false);
	}
	
	/**
	 * 
	 * @param reqMap
	 * 无
	 * @return
	 * 数据在data key中。
	 * @throws Exception
	 */
	public Map<String,Object> queryCategorys() throws Exception {
		// 切换数据库导微信数据库
		DataSourceSwitch.setDataSourceType(DataSourceSelect.DB_WX);
		
		List<Object>  reslist = baseDao.getList("WxServiceMapper.queryCategorys");
		Map<String,Object> resMap = new HashMap<String, Object>();
		resMap.put("data", reslist);
		
		return ResponseUtil.FormatResMsg(ResCode.SUCCESS, null, "查询执行成功", resMap,
                false);
	}
	
	/**
	 * 查询品牌.
	 * @param reqMap
	 * @return
	 * @throws Exception
	 */
	public Map<String,Object> queryBrands(Map<String,Object> reqMap) throws Exception {
		// 切换数据库导微信数据库
		DataSourceSwitch.setDataSourceType(DataSourceSelect.DB_WX);
		
		List<Object>  reslist = baseDao.getList("WxServiceMapper.queryBrands",reqMap);
		Map<String,Object> resMap = new HashMap<String, Object>();
		resMap.put("data", reslist);
		
		return ResponseUtil.FormatResMsg(ResCode.SUCCESS, null, "查询执行成功", resMap,
                false);
	}
	
	
}

