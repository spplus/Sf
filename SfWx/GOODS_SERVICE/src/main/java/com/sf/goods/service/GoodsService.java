package com.sf.goods.service;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.sf.db.DataSourceSwitch;
import com.sf.db.MybatisDao;
import com.sf.page.PageUtil;
import com.sf.sfcm.util.DataSourceSelect;
import com.sf.sfcm.util.ResCode;
import com.sf.sfcm.util.ResponseUtil;



@Service
public class GoodsService {

	@Autowired
	MybatisDao			baseDao;
	
	
	
	
	/**
	 * 查询列表.
	 * @param reqMap
	 * @return
	 */
	public Map<String,Object> getGoodsList(Map<String,Object> reqMap){
		 // 分页参数
        PageUtil<Object> page = new PageUtil<Object>(reqMap);
        reqMap.put("page", page);

        DataSourceSwitch.setDataSourceType(DataSourceSelect.DS_DB1);
        List<Object> list = baseDao.getList(
                "GoodsServiceMapper.listPageGoods", reqMap);
        page.setResult(list);
        reqMap.put("goods", list);
        reqMap.put("PAGEINFO", page);
        return ResponseUtil.FormatResMsg(ResCode.SUCCESS, null, "查询执行成功", reqMap,
                false);
	}
	
	/**
	 * 查询单条记录.
	 */
	public Map<String,Object> getGoodsById(Map<String,Object> reqMap){
		 // 分页参数
  
       DataSourceSwitch.setDataSourceType(DataSourceSelect.DS_DB1);
       List<Object> list = baseDao.get(
               "GoodsServiceMapper.listPageFeeRate", reqMap);
     
       reqMap.put("goods", list);
      
       return ResponseUtil.FormatResMsg(ResCode.SUCCESS, null, "查询执行成功", reqMap,
               false);
	}
	
	
	
	/**
	 * 插入.
	 */
	public Map<String,Object>  insertTest(int i) throws Exception{
		
		DataSourceSwitch.setDataSourceType(DataSourceSelect.DS_DB1);
		baseDao.insert("WxServiceMapper.insertUser", "");
		return ResponseUtil.FormatResMsg(ResCode.SUCCESS, null, "查询执行成功", null,
	               false);
	}
	
	
	/**
	 * 更新.
	 */
	public Map<String,Object>  updateTest(int i) throws Exception{
		
		DataSourceSwitch.setDataSourceType(DataSourceSelect.DS_DB1);
		baseDao.insert("WxServiceMapper.insertUser", "");
		return ResponseUtil.FormatResMsg(ResCode.SUCCESS, null, "查询执行成功", null,
	               false);
	}
	
	
	/**
	 * 删除.
	 */
	public Map<String,Object>  deleteTest(int i) throws Exception{
		
		DataSourceSwitch.setDataSourceType(DataSourceSelect.DS_DB1);
		baseDao.insert("WxServiceMapper.insertUser", "");
		return ResponseUtil.FormatResMsg(ResCode.SUCCESS, null, "查询执行成功", null,
	               false);
	}
	
}
