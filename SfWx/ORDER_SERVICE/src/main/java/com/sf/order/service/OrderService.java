package com.sf.order.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.sf.db.DataSourceSwitch;
import com.sf.db.MybatisDao;
import com.sf.sfcm.bean.UserInfo;
import com.sf.sfcm.util.DataSourceSelect;




@Service
public class OrderService {

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
}
